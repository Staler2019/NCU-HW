using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Web;

namespace _21_12_13_iot
{
    class Program
    {
        static string azure_server_region = "westcentralus";
        static string ocp_apim_subscrip_key = "842a871c74c6408e8865441672d0e9bb";
        static string personGroupId = "jiajyun_g1";

        static HttpClient client;
        static System.Collections.Specialized.NameValueCollection queryString;

        static void Main(string[] args)
        {
            // RunJsonExample();
            // UseClassRunJsonExample();

            // practice 1
            // static string json_body = "{\"name\":\"++\",\"UserData\":\"123testing\",\"recongnitionModel\":\"recognition_03\"}";
            // PersonGroup p1 = new(azure_server_region, ocp_apim_subscrip_key, personGroupId, json_body);
            // p1.CreateAsync().Wait();

            // practice2
            useDetectApi();
            Console.ReadLine();

            // practice3
            // practice3_json();
        }

        // practice2
        static async void useDetectApi()
        {
            var client = new HttpClient();
            var queryString = HttpUtility.ParseQueryString(string.Empty);

            // Request headers
            client.DefaultRequestHeaders.Add("Ocp-Apim-Subscription-Key", ocp_apim_subscrip_key);

            // Request parameters
            queryString["returnFaceId"] = "true";
            queryString["returnFaceLandmarks"] = "false";
            queryString["returnFaceAttributes"] = "gender, age, emotion";
            queryString["recognitionModel"] = "recognition_03"; // 可不改
            queryString["returnRecognitionModel"] = "false";
            queryString["detectionModel"] = "detection_01";
            queryString["faceIdTimeToLive"] = "86400";
            var uri = "https://" + azure_server_region + ".api.cognitive.microsoft.com/face/v1.0/detect?" + queryString;

            HttpResponseMessage response;

            // Request body
            byte[] byteData = Encoding.UTF8.GetBytes("{\"url\":\"https://i0.wp.com/post.medicalnewstoday.com/wp-content/uploads/sites/3/2020/03/GettyImages-1092658864_hero-1024x575.jpg?w=1155&h=1528\"}");

            string result;
            using (var content = new ByteArrayContent(byteData))
            {
                content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                response = await client.PostAsync(uri, content);
                // print
                result = await response.Content.ReadAsStringAsync();
            }

            Console.WriteLine("DetectApi msg: " + result);
        }

        // practice3
        static void practice3_json()
        {
            // make json
            var jsonStr = new
            {
                fruit = new string[] { "apple", "banana", "grape" },
                color = new
                {
                    apple = "red",
                    banana = "yellow",
                    grape = "purple"
                },
                restaurant = new
                {
                    apple = new
                    {
                        left = "5",
                        price = "10"
                    },
                    banana = new
                    {
                        left = "10",
                        price = "15"
                    },
                    grape = new
                    {
                        left = "12",
                        price = "20"
                    }
                },
                info = new Dictionary<string, string>[] {
                    new Dictionary<string, string> {
                        {"food", "apple"},
                        {"left", "5"},
                        {"price", "10"}
                    },
                    new Dictionary<string, string> {
                        {"food", "banana"},
                        {"left", "10"},
                        {"price", "15"}
                    }
                }
            };

            string json_result = JsonConvert.SerializeObject(jsonStr);
            Console.WriteLine(json_result);

            JObject take = JObject.Parse(json_result);
            foreach (var item in take["restaurant"])
            {
                Console.WriteLine(item);
            }
        }

        // on class testing 
        static void RunJsonExample()
        {
            string[] fruits = new string[] { "apple", "banana", "grape" };
            var jstring = new
            {
                fruit = from f in fruits select f,
                color = new
                {
                    apple = "red",
                    banana = "yellow",
                    watermelon = "purple"
                }
            };

            Console.WriteLine(JsonConvert.SerializeObject(jstring));

            string result = JsonConvert.SerializeObject(jstring);
            JObject take = JObject.Parse(result);
            Console.WriteLine(take["fruit"][0].ToString());
            Console.WriteLine(take["color"]["apple"].ToString());
        }

        static void UseClassRunJsonExample()
        {
            MyClass myClass = new MyClass();
            myClass.fruit = new List<string> { "apple", "banana", "grape" };
            myClass.color = new Dictionary<string, string>
            {
                { "apple","red" },
                { "banana","yellow" },
                { "watermelon","purple" }
            };
            string json = JsonConvert.SerializeObject(myClass);
            Console.WriteLine(json);
            MyClass myNewClass = JsonConvert.DeserializeObject<MyClass>(json);
            foreach (var item in myNewClass.fruit)
            {
                Console.WriteLine(item);
            }
        }
    }
}

