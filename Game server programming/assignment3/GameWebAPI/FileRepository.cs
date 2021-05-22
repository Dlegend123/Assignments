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

        public Task<Player> Get(Guid id)
        {
            string texts = File.ReadAllText(@"game-dev.txt");
            Player player1 = new Player();
            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(texts);
            try
            {
                foreach (Player player in players)
                {
                    if (player.Id == id)
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

        public Task<Player[]> GetAll()
        {

            var lineCount = 0;
            using (var reader = File.OpenText(@"game-dev.txt"))
            {
                while (reader.ReadLine() != null)
                {
                    lineCount++;
                }
            }
            Player[] players = new Player[lineCount];

            var lines = File.ReadAllText(@"game-dev.txt");

            players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(lines);
            return Task.FromResult(players);
        }

        public Task<Player> Create(Player player)
        {
            if(!File.Exists(@"game-dev.txt"))
                File.WriteAllText(@"game-dev.txt", Newtonsoft.Json.JsonConvert.SerializeObject(player));
            else
                File.AppendAllText(@"game-dev.txt", Newtonsoft.Json.JsonConvert.SerializeObject(player));
            return Task.FromResult(player);
        }

        public Task<Player> Modify(Guid id, ModifiedPlayer player)
        {
            string texts = File.ReadAllText(@"game-dev.txt");
            int found = 0;
            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(texts);
            for (int i = 0; i < players.Length; i++)
            {
                if (players[i].Id == id)
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

        public Task<Player> Delete(Guid id)
        {
            string texts = File.ReadAllText(@"game-dev.txt");
            int index = 0;
            Player temp = new Player();
            Player[] players = Newtonsoft.Json.JsonConvert.DeserializeObject<Player[]>(texts);
            var players1 = new List<Player>(players);
            for (int i = 0; i < players.Length; i++)
            {
                if (players[i].Id == id)
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
    }
}
