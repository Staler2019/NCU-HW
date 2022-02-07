using System.Net.Http.Headers;
using System.Text;
using System.Web;

namespace _21_12_13_iot
{
    internal class PersonGroup
    {
        // string azure_server_region;
        // string ocp_apim_subscrip_key;
        // string personGroupId;
        string json_body;

        string base_uri;

        HttpClient client;
        System.Collections.Specialized.NameValueCollection queryString;

        public PersonGroup(string azure_server_region, string ocp_apim_subscrip_key, string personGroupId, string json_body)
        {
            // azure_server_region = azure_server_region;
            // ocp_apim_subscrip_key = ocp_apim_subscrip_key;
            // personGroupId = personGroupId;
            if (String.IsNullOrEmpty(azure_server_region) || String.IsNullOrEmpty(ocp_apim_subscrip_key) || String.IsNullOrEmpty(personGroupId) || String.IsNullOrEmpty(json_body))
                throw new ArgumentNullException();

            this.json_body = json_body;

            base_uri = "https://" + azure_server_region + ".api.cognitive.microsoft.com/face/v1.0/persongroups/" + personGroupId;

            client = new HttpClient();
            queryString = HttpUtility.ParseQueryString(string.Empty);
            client.DefaultRequestHeaders.Add("Ocp-Apim-Subscription-Key", ocp_apim_subscrip_key);
        }

        public async Task CreateAsync()
        {
            var uri = base_uri + "?" + queryString;

            HttpResponseMessage response;

            byte[] byteData = Encoding.UTF8.GetBytes(json_body);

            string result;
            using (var content = new ByteArrayContent(byteData))
            {
                content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                response = await client.PutAsync(uri, content);
                // print
                result = await response.Content.ReadAsStringAsync();
            }

            Console.WriteLine("Create msg: " + result);
        }

        public async Task DeleteAsync()
        {
            var uri = base_uri + "?" + queryString;

            var response = await client.DeleteAsync(uri);
            // print
            string result = await response.Content.ReadAsStringAsync();
            Console.WriteLine("Delete msg: " + result);
        }

        public async Task GetAsync()
        {
            var tmp_queryString = queryString;

            tmp_queryString["returnRecognitionModel"] = "false";
            var uri = base_uri + "?" + tmp_queryString;

            var response = await client.GetAsync(uri);
            // print
            string result = await response.Content.ReadAsStringAsync();
            Console.WriteLine("Get msg: " + result);
        }

        public async Task GetTrainingStatusAsync()
        {
            var uri = base_uri + "/training?" + queryString;

            var response = await client.GetAsync(uri);
            // print
            string result = await response.Content.ReadAsStringAsync();
            Console.WriteLine("GetTrainingStatus msg: " + result);
        }

        public async Task ListAsync(string start_json)
        {
            if (String.IsNullOrEmpty(start_json))
                throw new ArgumentNullException();

            var tmp_queryString = queryString;

            tmp_queryString["start"] = start_json;
            tmp_queryString["top"] = "1000";
            tmp_queryString["returnRecognitionModel"] = "false";
            var uri = base_uri + "?" + tmp_queryString;

            var response = await client.GetAsync(uri);
            // print
            string result = await response.Content.ReadAsStringAsync();
            Console.WriteLine("List msg: " + result);
        }

        public async Task TrainAsync(string train_json)
        {
            if (String.IsNullOrEmpty(train_json))
                throw new ArgumentNullException();

            var uri = base_uri + "/train?" + queryString;

            HttpResponseMessage response;

            byte[] byteData = Encoding.UTF8.GetBytes(train_json);

            string result;
            using (var content = new ByteArrayContent(byteData))
            {
                content.Headers.ContentType = new MediaTypeHeaderValue("< your content type, i.e. application/json >");
                response = await client.PostAsync(uri, content);
                // print
                result = await response.Content.ReadAsStringAsync();
            }

            Console.WriteLine("Train msg: " + result);
        }

        public async Task UpdateAsync()
        {
            var uri = base_uri + "?" + queryString;
            //TODO. ???
        }
    }
}
