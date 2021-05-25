using Microsoft.AspNetCore.Http;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;
using MongoDB.Driver;
using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using static GameWebAPI.ItemType;

namespace GameWebAPI
{
    [BsonIgnoreExtraElements]
    public class MongoDbRepository : IRepository
    {
        private IMongoDatabase database;
        private IMongoCollection<Player> players;
        private IMongoCollection<Item> items;

        public MongoDbRepository()
        {
            var _mongoClient = new MongoClient("mongodb+srv://mlegend123:Legacy123@cluster0.dd3zz.mongodb.net/game?retryWrites=true&w=majority");
            database = _mongoClient.GetDatabase("game");
            players = database.GetCollection<Player>("players");
            items = database.GetCollection<Item>("items");

        }

        public async Task<Player> CreatePlayer(Player player)
        {
            await players.InsertOneAsync(player);
            return player;
        }

        public Task<Player> DeletePlayer(Guid playerId)
        {
            Player player = new();
            FilterDefinition<Player> filter = Builders<Player>.Filter.Eq("Id", playerId);
            if (!players.Find(filter).Any())
                Task.FromException(new NotFoundException("Player not found"));
            players.DeleteOne(filter);
            return Task.FromResult(player);
        }

        public Task<Player[]> GetAllPlayers()
        {
            if (!players.Find(new BsonDocument()).Any())
                return Task.FromException<Player[]>(new NotFoundException("There are no players"));
            List<Player> list = players.Find(new BsonDocument()).ToList();
            return Task.FromResult(list.ToArray());
        }

        public Task<Player> GetPlayer(Guid playerId)
        {
            Player player = new();
            FilterDefinition<Player> filter = Builders<Player>.Filter.Eq("Id", playerId);

            if (players == null)
                return Task.FromException<Player>(new NotFoundException("There are no players"));
            if (!players.Find(filter).Any())
                return Task.FromException<Player>(new NotFoundException("Player was not found"));
            player = players.Find(filter).Single();
            return Task.FromResult(player);
        }

        public Task<Player> UpdatePlayer(Player player)
        {
            var filter = Builders<Player>.Filter.Eq("Id", player.Id);
            if (!players.Find(filter).Any())
                return Task.FromException<Player>(new NotFoundException("Player was not found"));
            players.ReplaceOne(filter, player);
            return Task.FromResult(player);
        }

        public Task<Item> CreateItem(Guid playerId, Item item)
        {
            var filter = Builders<Player>.Filter.Eq("Id", playerId);

            if (!players.Find(filter).Any())
                return Task.FromException<Item>(new NotFoundException("Player not found"));

            if (players.Find(filter).Single().Level < 3 && item.Type.Equals(SWORD))
                return Task.FromException<Item>(new TooLowLevelException("Player level is too low"));
            try
            {
                items.InsertOne(item);
            }
            catch (MongoWriteConcernException e)
            {
                if (e.Code == 11000)
                    return Task.FromException<Item>(new YourConflictException("Player already has that item"));
            }
            return Task.FromResult(item);
        }
        public Task<Item> UpdateItem(Guid playerId, Item item)
        {
            var filter = Builders<Player>.Filter.Eq("Id", playerId);
            
            
            if (!players.Find(filter).Any())
                return Task.FromException<Item>(new NotFoundException("Player not found"));
            var player = players.Find(filter).Single();
            List<Item> iList = player.Items;
            for (int i = 0; i < iList.Count; i++)
            {
                if (iList[i].Id == item.Id)
                {
                    iList[i] = item;
                    i = iList.Count - 1;
                }
            }
            player.Items = iList;
            players.ReplaceOne(filter, player);
            var filter2 = Builders<Item>.Filter.Eq("Id", item.Id);
            if(!items.Find(filter2).Any())
                return Task.FromException<Item>(new NotFoundException("Item not found"));
            items.ReplaceOne(filter2, item);
            return Task.FromResult(item);
        }

        public Task<Item> GetItem(Guid playerId, Guid itemId)
        {
            Item item = new();

            FilterDefinition<Item> filter = Builders<Item>.Filter.Eq("Id", itemId);
            if (!items.Find(filter).Any())
                return Task.FromException<Item>(new NotFoundException("Item not found"));
            item = items.Find(filter).Single();
            return Task.FromResult(item);
        }

        public Task<Item[]> GetAllItems(Guid playerId)
        {
            FilterDefinition<Item> filter = Builders<Item>.Filter.Eq("OwnerId", playerId);
            if (!items.Find(filter).Any())
                return Task.FromException<Item[]>(new NotFoundException("No items found"));
            List<Item> list = items.Find(filter).ToList();
            return Task.FromResult(list.ToArray());
        }
        public Task<Item> DeleteItem(Guid playerId, Item item)
        {
            FilterDefinition<Item> filter = Builders<Item>.Filter.Eq("Id", item.Id);
            if (!items.Find(filter).Any())
                return Task.FromException<Item>(new NotFoundException("Item not found"));
            items.DeleteOne(filter);
            return Task.FromResult<Item>(items.Find(filter).Single());
        }
    }
}
