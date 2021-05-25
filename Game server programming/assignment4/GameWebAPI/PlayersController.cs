using Microsoft.AspNetCore.Mvc;
using System;
using System.Threading.Tasks;

namespace GameWebAPI
{
    [Route("api/[controller]")]
    [ApiController]
    public class PlayersController: ControllerBase
    {
        private readonly MongoDbRepository repository= new();
        [HttpGet]
        [Route("{id}")]
        public Task<Player> Get(Guid id)
        {
            return repository.GetPlayer(id);
        }
        [HttpGet]
        [Route("")]
        public Task<Player[]> GetAll()
        {
            return repository.GetAllPlayers();
        }
        [HttpPost]
        [Route("")]
        public Task<Player> Create(Player player)
        {
            return repository.CreatePlayer(player);
        }
        [HttpPatch]
        [Route("")]
        public Task<Player> Update(Player player)
        {
            return repository.UpdatePlayer(player);
        }
        [HttpDelete]
        [Route("{id}")]
        public Task<Player> Delete(Guid id)
        {
            return repository.DeletePlayer(id);
        }
    }
}
