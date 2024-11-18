#include <iostream>
#include <string>
#include <unordered_map>
#include <json/json.h>
#include <curl/curl.h>
#include "CurlUtil.h"


static const std::string CA_CERT = "D:\\Workspace\\GoQuant\\LetsTrade\\ThirdParty\\OpenSSL\\cacert.pem";
static const std::string PRIVATE_BASEURL = "https://test.deribit.com/api/v2/private/";
static const std::string PUBLIC_BASEURL = "https://test.deribit.com/api/v2/public/";

static size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* output)
{
	size_t total_size = size * nmemb;
	output->append((char*)contents, total_size);
	return total_size;
}

std::string CurlUtil::BuildURL(const std::string& api, const std::unordered_map<std::string, std::string>& params, bool isPrivateBaseURL)
{
	std::string url = (isPrivateBaseURL ? PRIVATE_BASEURL : PUBLIC_BASEURL) + api + '?';
	bool firstParam = true;

	for (const auto& [key, value] : params)
	{
		if (!firstParam)
		{
			url += '&';
		}
		url += key + '=' + value;
		if (firstParam)
			firstParam = false;
	}

	return url;
}

std::string CurlUtil::SendRequest(const std::string& url, const std::string& accessToken)
{
	std::string response;
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::cerr << "Failed to initialize CURL" << std::endl;
		return "";
	}

	struct curl_slist* headers = nullptr;
	headers = curl_slist_append(headers, "Content-Type: application/json");

	// **Add the Authorization header with Bearer token**
	if(!accessToken.empty())
	{
		std::string authHeader = "Authorization: Bearer " + accessToken;
		headers = curl_slist_append(headers, authHeader.c_str());
	}	

	// Set URL, headers, and POST data
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	 // Callback for capturing response
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	// Set SSL certificate path
	curl_easy_setopt(curl, CURLOPT_CAINFO, CA_CERT.c_str());  // Path to your CA certificate file

	// Execute request
	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);

	if (res != CURLE_OK) {
		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		return "";
	}
	return response;
}