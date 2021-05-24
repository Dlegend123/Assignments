using Microsoft.AspNetCore.Mvc;
using System;
using System.Threading.Tasks;

namespace GameWebAPI
{
    [Route("api/[controller]")]
    [ApiController]
    public class ItemsController : ControllerBase
    {
        private readonly MongoDbRepository repository = new();
        [HttpPost]
        [Route(".../players/{playerId}/items")]
        public Task<Item> CreateItem(Guid playerId, Item item)
        {
            return repository.CreateItem(playerId, item);
        }
        [HttpGet]
        [Route(".../players/{playerId}/items")]
        public Task<Item> GetItem(Guid playerId, Guid itemId)
        {
            return repository.GetItem(playerId, itemId);
        }
        [HttpGet]
        [Route(".../players/{playerId}/items")]
        public Task<Item[]> GetAllItems(Guid playerId)
        {
            return repository.GetAllItems(playerId);
        }
        [HttpPatch]
        [Route(".../players/{playerId}/items")]
        public Task<Item> UpdateItem(Guid playerId, Item item)
        {
            return repository.UpdateItem(playerId, item);
        }
        [HttpDelete]
        [Route(".../players/{playerId}/items")]
        public Task<Item> DeleteItem(Guid playerId, Item item)
        {
            return repository.DeleteItem(playerId, item);
        }
    }
}
