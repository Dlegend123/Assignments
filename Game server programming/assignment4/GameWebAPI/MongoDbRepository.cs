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
    public class MongoDbRepository:IRepository
    {
        private IMongoDatabase database;
        private IMongoCollection<Player> players;
        private IMongoCollection<Item> items;
        public enum ItemType
        {
            EXCALIBUR, MEDIUM_POTION, AEGIS
        }
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

            players.DeleteOne(filter);
            return Task.FromResult(player);
        }

        public Task<Player[]> GetAllPlayers()
        {

            List<Player> list =  players.Find(new BsonDocument()).ToList();
            return Task.FromResult(list.ToArray());
        }

        public Task<Player> GetPlayer(Guid playerId)
        {
            Player player = new();
            FilterDefinition<Player> filter = Builders<Player>.Filter.Eq("Id", playerId);
            try
            {
                if (players == null)
                    throw new NotFoundException();
                if (!players.Find(filter).Any())
                    throw new NotFoundException();
                player = players.Find(filter).Single();
            }
            catch(NotFoundException e)
            {
                ErrorHandlingMiddleware.GetErrorCode(e);
            }
            return Task.FromResult(player) ;
        }
       
        public Task<Player> UpdatePlayer(Player player)
        {
            var filter = Builders<Player>.Filter.Eq("Id", player.Id);
            players.ReplaceOne(filter, player);
            return Task.FromResult(player);
        }

        public Task<Item> CreateItem(Guid playerId, Item item)
        {
            var filter = Builders<Player>.Filter.Eq("Id", playerId);
            try
            {
                if (!players.Find(filter).Any())
                  throw new NotFoundException();
                else
                {
                    try
                    {
                        if (players.Find(filter).Single().Level < 3 && item.Type.Equals(SWORD))
                            throw new TooLowLevelException();
                    }
                    catch (TooLowLevelException e)
                    {
                        ErrorHandlingMiddleware.GetErrorCode(e);
                    }
                }
            }
            catch (NotFoundException e)
            {
                ErrorHandlingMiddleware.GetErrorCode(e);
            }
            items.InsertOne(item);
            return Task.FromResult(item);
        }
        public Task<Item> UpdateItem(Guid playerId, Item item)
        {
            var filter = Builders<Player>.Filter.Eq("Id", playerId);
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
            items.ReplaceOne(filter2, item);
            return Task.FromResult(item);
        }

        public Task<Item> GetItem(Guid playerId, Guid itemId)
        {
            Item item = new();
            try
            {
                FilterDefinition<Item> filter = Builders<Item>.Filter.Eq("Id", itemId);
                if (!items.Find(filter).Any())
                    throw new NotFoundException();
                item = items.Find(filter).Single();
            }
            catch (NotFoundException e){
                ErrorHandlingMiddleware.GetErrorCode(e);
            }
            return Task.FromResult(item);
        }

        public Task<Item[]> GetAllItems(Guid playerId)
        {
            FilterDefinition<Item> filter = Builders<Item>.Filter.Eq("OwnerId", playerId);
            List<Item> list = items.Find(filter).ToList();
            return Task.FromResult(list.ToArray());
        }
        public Task<Item> DeleteItem(Guid playerId, Item item)
        {
            FilterDefinition<Item> filter = Builders<Item>.Filter.Eq("Id", item.Id);
            Item item1 = new();
            try
            {
                if(!items.Find(filter).Any())
                    throw new NotFoundException();
                item1 = items.Find(filter).Single();
                items.DeleteOne(filter);
            }
            catch(NotFoundException e)
            {
                ErrorHandlingMiddleware.GetErrorCode(e);
            }
            return Task.FromResult(item1);
        }
    }
}
