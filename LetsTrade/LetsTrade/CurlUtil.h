#ifndef CURLUTIL_H
#define CURLUTIL_H
class CurlUtil
{
public:
	static std::string BuildURL(const std::string& api, const std::unordered_map<std::string, std::string>& params, bool isPrivateBaseURL = true);
	static std::string SendRequest(const std::string& url, const std::string& accessToken = "");
};
#endif //CURLUTIL_H

