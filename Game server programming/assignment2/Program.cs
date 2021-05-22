using System;
using System.Collections.Generic;
using System.Linq;

namespace assignment2
{

    class Program
    {

        static void Main()
        {
            Player[] players = InstPlayers();
            players = SetPlayerData(players);

            TryGetItemHigh(players);
            TryFirstItem(players);
            TryFirstItemLinq(players);
            TryGetItems(players);
            TryGetItemsLinq(players);
            TryDelegates(players);

            InstGame(players);

            for (int i = 0; i < players.Length; i++)
            {
                Console.WriteLine("Player {0}", i);
                printItem(players[i]);
            }
        }
        public static void TryGetItemHigh(Player[] players)
        {
            Item[] temp = new Item[1000000];
            for (int i = 0; i < players.Length; i++)
            {
                temp[i] = MyExtensions.GetHighestLevelItem(players[i].Items);
                Console.WriteLine("Highest Level Item for Player {2}\n Guid: {0} \n Level: {1}", temp[i].Id, temp[i].Level, i);

            }
        }

        public static Action<Player> printItem = (Player player) =>
        {
            Action<Item> printActionDel = MyExtensions.PrintItem;
            MyExtensions.ProcessEachItem(player, printActionDel);
        };
        public static void TryDelegates(Player[] players)
        {
            Console.WriteLine("Using Delegates");
            Action<Item> printActionDel = MyExtensions.PrintItem;
            foreach (Player user in players)
            {
                MyExtensions.ProcessEachItem(user, printActionDel);
            }
        }
        public static void TryFirstItem(Player[] players)
        {
            Console.WriteLine("First Item");
            Item[] temp2 = new Item[players.Length];
            for (int i = 0; i < players.Length; i++)
            {
                temp2[i] = MyExtensions.FirstItem(players[i]);
                Console.WriteLine("Player {2}\n Guid: {0} \n Level: {1}", temp2[i].Id, temp2[i].Level, i);
            }
        }
        public static void TryFirstItemLinq(Player[] players)
        {
            Console.WriteLine("First Item Using Linq");
            Item[] temp2 = new Item[players.Length];
            for (int i = 0; i < players.Length; i++)
            {
                temp2[i] = MyExtensions.FirstItemWithLinq(players[i]);
                Console.WriteLine("Player {2}\n Guid: {0} \n Level: {1}", temp2[i].Id, temp2[i].Level, i);
            }
        }
        public static void TryGetItems(Player[] players)
        {
            Console.WriteLine("Get Items");
            Item[] tempItems;
            for (int i = 0; i < players.Length; i++)
            {
                tempItems = MyExtensions.GetItems(players[i]);
                foreach (Item invent in tempItems)
                {
                    Console.WriteLine("Guid: {0} \n Level: {1}", invent.Id, invent.Level);
                }
            }
        }
        public static void TryGetItemsLinq(Player[] players)
        {
            Console.WriteLine("Get Items Using Linq");
            Item[] tempItems;
            for (int i = 0; i < players.Length; i++)
            {
                tempItems = MyExtensions.GetItemsWithLinq(players[i]);
                foreach (Item invent in tempItems)
                {
                    Console.WriteLine("Guid: {0} \nLevel: {1}", invent.Id, invent.Level);
                }
            }
        }
        public static Player SetScores(int i,Player[] players)
        {
            int[] temp = new int[1000000];
            var rand = new Random();
            for (int x = 0; x < players.Length; x++)
            {
                while (!CheckUnique(players[i].Score, temp.Distinct()))
                {
                    for (int j = 0; j < players.Length; j++)
                    {
                        if (players[i].Score == players[j].Score)
                        {
                            players[i].Score = rand.Next();

                        }
                    }
                }
            }
            return players[i];
        }
        public static Player[] SetPlayerData(Player[] players)
        {
            var rand = new Random();
            foreach (Player user in players)
            {
                user.Items = MyExtensions.createPlayer();
                user.Score = rand.Next();
            }
            for (int i = 0; i < players.Length; i++)
                players[i] = SetScores(i, players);

            return players;
        }
        public static Player[] InstPlayers()
        {
            Player[] players = new Player[1000000];
            Guid[] temp = new Guid[1000000];
            for (int i = 0; i < 1000000; i++)
            {
                players[i] = new Player();
                temp[i] = new Guid();
                players[i].Id = temp[i] = Guid.NewGuid();
            }

            for (int i = 0; i < players.Length; i++)
            {

                while (!CheckUnique(players[i].Id, temp.Distinct()))
                {

                    for (int j = 0; j < players.Length; j++)
                    {
                        if (players[i].Id == players[j].Id)
                        {
                            players[i].Id = Guid.NewGuid();
                        }
                    }
                }
                // Console.WriteLine(players[i].Id);
            }
            return players;
        }
        public static bool CheckUnique(Guid id, IEnumerable<Guid> distinctGuid)
        {
            foreach (Guid age in distinctGuid)
            {
                if (age == id)
                    return false;
            }
            return true;
        }
        public static bool CheckUnique(int highScore, IEnumerable<int> distinctScore)
        {
            foreach (int age in distinctScore)
            {
                if (age == highScore)
                    return false;
            }
            return true;
        }
        public static void InstGame(Player[] players)
        {
            PlayerForAnotherGame playersForAnotherGame = new PlayerForAnotherGame();

            List<Player> players1 = new(players);
            Player temp = new Player();
            temp.Id = playersForAnotherGame.Id;
            temp.Items = playersForAnotherGame.Items;
            temp.Score = playersForAnotherGame.Score;
            players1.Add(temp);
            Game<Player> game = new(players1);

            Player[] players2 = game.GetTop10Players();
            Console.WriteLine("Top 10 players: ");
            for (int i = 0; i < players2.Length; i++)
            {
                Console.WriteLine("\nPlayer {0} \nHighscore: {1}", i, players2[i].Score);
            }
        }
    }
}
