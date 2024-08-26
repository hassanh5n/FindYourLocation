#include<iostream>
#include<string>
#include<cpprest/http_client.h>

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;


int main() {

	cout << "\t\tYour Location Finder" << endl;
	cout << "----------------------------------------------------------\n\n" << endl;
	string apiKey = "c28e127acfd5b07e18357b960ad0f66d";
	string IPAddress = "check";

	utility::string_t api_key_t = conversions::to_string_t(apiKey);
	utility::string_t ip_address_t = conversions::to_string_t(IPAddress);

	uri_builder builder(U("http://api.ipstack.com/"));
	builder.append_path(ip_address_t);
	builder.append_query(U("access_key"), api_key_t);

	http_client client(builder.to_uri());

	client.request(methods::GET)
		.then([](http_response response){
		if (response.status_code() == status_codes::OK) {
			return response.extract_json();
			}
		else {
			throw runtime_error("Failed to get a valid response from server");
		}
	})
		.then([](json::value body) {
		if (body.has_field(U("country_name"))) {
			utility::string_t country = body[U("country_name")].as_string();
#ifdef _WIN32
				wcout << L"\tYour Country: " << country << endl;
#else
				cout << "Country: " << conversions::to_utf8string(country) << endl;
#endif
		}
		if (body.has_field(U("city")))
		{
			utility::string_t city = body[U("city")].as_string();
#ifdef _WIN32
			wcout << L"\n\tYour City: " << city << endl;
			cout << "\n\n" << endl;
#else
			cout << "City: " << conversions::to_utf8string(city) << endl;
#endif
		}
			}).wait();

}
