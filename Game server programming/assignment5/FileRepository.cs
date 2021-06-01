using System;
using System.IO;
using System.Threading.Tasks;
using System.Net.Http;
using System.Linq;
using System.Collections.Generic;

namespace GameWebAPI
{
    public class FileRepository:IRepository
    {

        public Task<Player> GetPlayer(Guid playerId)
        {
            string texts = File.ReadAllText(@"game-dev.txt");
            Player player1 = new();
            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(texts);
            try
            {
                foreach (Player player in players)
                {
                    if (player.Id == playerId)
                        return Task.FromResult(player);
                }
                throw new NotFoundException("The player was not found");
            }
            catch (NotFoundException e)
            {
                Console.WriteLine("Message :{0} ", e.Message);
            }
            return Task.FromResult(player1);
        }

        public Task<Player[]> GetAllPlayers()
        {

            var lines = File.ReadAllText(@"game-dev.txt");

            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(lines);
            return Task.FromResult(players);
        }

        public Task<Player> CreatePlayer(Player player)
        {
            if(!File.Exists(@"game-dev.txt"))
                File.WriteAllText(@"game-dev.txt", Newtonsoft.Json.JsonConvert.SerializeObject(player));
            else
                File.AppendAllText(@"game-dev.txt", Newtonsoft.Json.JsonConvert.SerializeObject(player));
            return Task.FromResult(player);
        }

        public Task<Player> UpdatePlayer(Player player)
        {
            string texts = File.ReadAllText(@"game-dev.txt");
            int found = 0;
            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(texts);
            for (int i = 0; i < players.Length; i++)
            {
                if (players[i].Id == player.Id)
                {
                    found = i;
                    players[i].Score = player.Score;
                    File.WriteAllText(@"game-dev.txt", Newtonsoft.Json.JsonConvert.SerializeObject(players));
                    if (i != players.Length - 1)
                        i = players.Length - 1;
                }

            }
            return Task.FromResult(players[found]);
        }

        public Task<Player> DeletePlayer(Guid playerId)
        {
            string texts = File.ReadAllText(@"game-dev.txt");
            int index = 0;
            Player temp = new();
            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(texts);
            var players1 = new List<Player>(players);
            for (int i = 0; i < players.Length; i++)
            {
                if (players[i].Id == playerId)
                {
                    index = i;
                    temp = players[i];
                    i = players.Length - 1;
                }
            }
            players1.RemoveAt(index);
            players = players1.ToArray();
            File.WriteAllText(@"game-dev.txt", Newtonsoft.Json.JsonConvert.SerializeObject(players));
            return Task.FromResult(temp);
        }

        public Task<Item> CreateItem(Guid playerId, Item item)
        {
            throw new NotImplementedException();
        }

        public Task<Item> GetItem(Guid playerId, Guid itemId)
        {
            throw new NotImplementedException();
        }

        public Task<Item[]> GetAllItems(Guid playerId)
        {
            throw new NotImplementedException();
        }

        public Task<Item> UpdateItem(Guid playerId, Item item)
        {
            throw new NotImplementedException();
        }

        public Task<Item> DeleteItem(Guid playerId, Item item)
        {
            throw new NotImplementedException();
        }
    }
}
