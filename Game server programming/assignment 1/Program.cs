using System;
using System.IO;
using System.Net.Http;
using System.Runtime.Serialization;
using System.Threading.Tasks;
using static gCourse.Program;

namespace gCourse
{
    class Program
    {
        bool running = true;

        RealTimeCityBikeDataFetcher onlineFetcher = new RealTimeCityBikeDataFetcher();
        OfflineCityBikeDataFetcher offlineFetcher = new OfflineCityBikeDataFetcher();
        static async Task Main(string[] args)
        {
            Program p = new Program();
            string _bikeStationName;

            Console.WriteLine("Do you want to use the application (On)line or (Of)fline?");
            var answer = Console.ReadLine();
            if (answer.ToLower().Contains("on"))
            {
                Console.Write("Using online mode, fetcing data in real time..\n");
            }
            else if (answer.ToLower().Contains("of"))
            {
                Console.Write("Using offline mode, loading data from a pre-loaded file.\n");
            }
            else
            {
                Console.Write("Defaulting online mode, fetcing data in real time.. \n");
            }
            //Console.WriteLine(args[0]);
            while (p.running)
            {

                Console.WriteLine("Enter station's name or type 'exit' to exit: ");
                _bikeStationName = Console.ReadLine();

                if (_bikeStationName.ToLower().Contains("exit"))
                {
                    p.running = false;
                    break;
                }
                int x;
                x=(answer.ToLower().Contains("of"))? 
                    await p.offlineFetcher.GetBikeCountInStation(_bikeStationName) :
                    await p.onlineFetcher.GetBikeCountInStation(_bikeStationName);

                if (x != -1)
                    Console.WriteLine(_bikeStationName + " has " + x + " as the bike count.\n");
            }
            Console.WriteLine("Press any key to exit");
            Console.ReadKey();
        }


        public interface ICityBikeDataFetcher
        {
            Task<int> GetBikeCountInStation(string stationName);
        }

    }
    class RealTimeCityBikeDataFetcher : ICityBikeDataFetcher
    {
        static readonly HttpClient client = new HttpClient();
        public string[] invalidCharacters = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

        public async Task<int> GetBikeCountInStation(string stationName)
        {
            string responseBody = "\0";
            BikeRentalStationList stationInfo;
            int bikeCount = 0;
            try
            {
                for (int i = 0; i < invalidCharacters.Length; ++i)
                {
                    if (stationName.ToLower().Contains(invalidCharacters[i]))
                    {
                        throw new System.ArgumentException("Invalid character");
                    }
                }

                responseBody = await client.GetStringAsync("http://api.digitransit.fi/routing/v1/routers/hsl/bike_rental");
                stationInfo = Newtonsoft.Json.JsonConvert.DeserializeObject<BikeRentalStationList>(responseBody);
                int found = 1;
                for (int i = 0; i < stationInfo.stations.Length; i++)
                {
                    if (stationInfo.stations[i].name.ToLower() == stationName.ToLower())
                    {
                        found = 0;
                        return stationInfo.stations[i].bikesAvailable;
                    }
                }
                if (found == 1)
                    throw new NotFoundException("Station with that name was not found");
            }
            catch (Exception f)
            {
                if (f is HttpRequestException || f is ArgumentException)
                {
                    Console.WriteLine("\nException Caught!");
                    Console.WriteLine("Message :{0} ", f.Message);
                }
            }

            // await File.WriteAllTextAsync("WriteLines.txt", responseBody);
            bikeCount = -1;
            return bikeCount;
        }

    }

    [Serializable]
    internal class NotFoundException : Exception
    {
        public NotFoundException()
        {
        }

        public NotFoundException(string message) : base(message)
        {
            Console.WriteLine(message);
        }

        public NotFoundException(string message, Exception innerException) : base(message, innerException)
        {
        }

        protected NotFoundException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }

    public class BikeRentalStationList
    {
        public BikeRentalStation[] stations;
    }
    public class BikeRentalStation
    {
        public int id;
        public string name;
        public float x;
        public float y;
        public int bikesAvailable;
        public int spacesAvailable;
        public int capacity;
        public bool allowDropoff;
        public bool allowOverloading;
        public bool isFloatingBike;
        public bool isCarStation;
        public string state;
        public string[] networks;
        public bool realTimeData;
    }
    class OfflineCityBikeDataFetcher : ICityBikeDataFetcher
    {
        public async Task<int> GetBikeCountInStation(string stationName)
        {
            using (StreamReader streamReader = new StreamReader(@"bikedata.txt"))
            {
                int bikeCount = 0, found = 1;

                try
                {
                    while (!streamReader.EndOfStream)
                    {
                        var line = await streamReader.ReadLineAsync();
                        if (line.ToLower().Contains(stationName.ToLower()))
                        {
                            string[] words = line.Split(":");
                            found = 0;
                            bikeCount = Int32.Parse(words[1]);
                            return bikeCount;
                        }
                    }
                    if (found == 1)
                        throw new NotFoundException("Station with that name was not found");
                }
                catch (NotFoundException e)
                {
                    Console.WriteLine(e.Message);
                }
                return -1;
            }
        }
    }
}
