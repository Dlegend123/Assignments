using System;
using System.Collections.Generic;
using System.Linq;
namespace assignment2
{
    public static class MyExtensions
    {
        public static Item GetHighestLevelItem(List<Item> Items)
        {
            int max = Items[0].Level;
            int index = 0;

            for (int i = 1; i < Items.Capacity; i++)
            {
                if (max < Items[i].Level)
                {
                    max = Items[i].Level;
                    index = i;
                }

            }
            return Items[index];
        }
        public static List<Item> createPlayer()
        {
            Player player = new Player();
            var rand = new Random();
            Item sword = new Item();
            Item gloves = new Item();
            Item helmet = new Item();
            Item shoes = new Item();
            sword.Id = Guid.NewGuid();
            sword.Level = rand.Next();
            gloves.Id = Guid.NewGuid();
            gloves.Level = rand.Next();
            helmet.Id = Guid.NewGuid();
            helmet.Level = rand.Next();
            shoes.Id = Guid.NewGuid();
            shoes.Level = rand.Next();
            List<Item> Items = new List<Item>();
            Items.Add(sword);
            Items.Add(gloves);
            Items.Add(helmet);
            Items.Add(shoes);
            return Items;
        }
        public static Item[] GetItems(Player player)
        {
            Item[] items = new Item[player.Items.Capacity];
            for (int i = 0; i < player.Items.Capacity; i++)
            {
                items[i] = player.Items[i];
            }

            return items;
        }
        public static Item[] GetItemsWithLinq(Player player)
        {
            return player.Items.ToArray<Item>();
        }
        public static Item FirstItem(Player player)
        {
            return (!(player.Items.Count == 0)) ? player.Items[0] : null;
        }
        public static Item FirstItemWithLinq(Player player)
        {
            return (!(player.Items.Count() == 0)) ? player.Items.First() : null;
        }
        public static void PrintItem(Item item)
        {
            Console.WriteLine("Guid: {0} \nLevel: {1}", item.Id, item.Level);
        }
        public static void ProcessEachItem(Player player, Action<Item> process)
        {
            foreach (Item item in player.Items)
            {
                process(item);
            }
        }
        
    }
}
    
