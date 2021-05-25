using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;

namespace GameWebAPI
{
    [Route("api/[controller]")]
    [ApiController]
    public class ValueController: ControllerBase
    {
        // GET api/values
        [HttpGet]
        [Route("")]
        public ActionResult<IEnumerable<string>> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET api/values/5
        [HttpGet]
        [Route("{id}")]
        public ActionResult<string> Get(int id)
        {
            return "value";
        }

        // POST api/values
        [HttpPost]
        [Route("")]
        public void Post([FromBody] string value)
        {

        }

        // PUT api/values/5
        [HttpPut]
        [Route("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete]
        [Route("{id}")]
        public void Delete(int id)
        {
        }
    }
}
