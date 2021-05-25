using Newtonsoft.Json;
using System;
using System.Collections.Generic;

namespace GameWebAPI
{
    [JsonObject(MemberSerialization = MemberSerialization.OptIn)]
    public class Player
    {
        
        [JsonProperty(PropertyName = "Id")]
        public Guid Id { get; set; }

        [JsonProperty(PropertyName = "Name")]
        public string Name { get; set; }

        [JsonProperty(PropertyName = "Score")]
        public int Score { get; set; }

        [JsonProperty(PropertyName = "Level")]
        public int Level { get; set; }

        [JsonProperty(PropertyName = "IsBanned")]
        public bool IsBanned { get; set; }

        [JsonProperty(PropertyName = "CreationTime")]
        public DateTime CreationTime { get; set; }

        [JsonProperty(PropertyName = "Items")]
        public List<Item> Items { get; set; }
        public Player()
        {
            Id =    Guid.NewGuid();
            Score = 0;
            Level = 0;
            IsBanned = false;
            CreationTime = DateTime.Now;
            Items = new List<Item>();
        }
    }
}
