
#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H
#include <string>

class OrderManager {
public:
    OrderManager()
        : client_id("Tt8yEvu7"), client_secret("xpKmTlEOa8h2LUnoR8oMBdtyQquqrJR-HFYIC6awbfw") {
        AuthenticateAndAssignAccessToken();
    }

    bool PlaceBuyOrder(const std::string& instrument, int amount, double price);   
    bool AuthenticateAndAssignAccessToken();    
    std::string get_access_token() const { return access_token; };
private:
    std::string client_id;
    std::string client_secret;
    std::string access_token;
    // Helper methods for making requests can go here   
    std::string send_request(const std::string& url);
    
};
#endif // ORDER_MANAGER_H