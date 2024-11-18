#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Forward declaration of session to use in shared_ptr
class WebSocketSession;

// Define a type for managing symbol subscriptions
std::unordered_map<std::string, std::unordered_set<std::shared_ptr<WebSocketSession>>> subscriptions;

// Class to manage a single WebSocket connection
class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
    websocket::stream<tcp::socket> ws_;
    beast::flat_buffer buffer_;

public:
    explicit WebSocketSession(tcp::socket socket) : ws_(std::move(socket)) {}

    // Start the WebSocket handshake
    void run() {
        ws_.async_accept([self = shared_from_this()](beast::error_code ec) {
            if (!ec) self->read();
            });
    }

    // Read messages from client
    void read() {
        ws_.async_read(buffer_, [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
            if (!ec) {
                // Process the client's message
                self->processMessage(beast::buffers_to_string(self->buffer_.data()));
                self->buffer_.consume(bytes_transferred); // Clear buffer after processing
                self->read(); // Continue reading
            }
            });
    }

    // Process incoming message from client
    void processMessage(const std::string& message) {
        // Assuming message format is: "SUBSCRIBE <symbol>"
        if (message.rfind("SUBSCRIBE", 0) == 0) {
            std::string symbol = message.substr(10); // Get the symbol
            subscriptions[symbol].insert(shared_from_this()); // Add session to the symbol's subscription set
            std::cout << "Client subscribed to: " << symbol << std::endl;
            send("Subscribed to " + symbol);
        }
        // Further command handling can be added here
    }

    // Send a message to the client
    void send(const std::string& message) {
        ws_.async_write(net::buffer(message), [self = shared_from_this()](beast::error_code ec, std::size_t) {
            if (ec) {
                std::cerr << "Send error: " << ec.message() << std::endl;
            }
            });
    }
};

// Main listener class to accept incoming connections
class WebSocketServer {
    tcp::acceptor acceptor_;
    tcp::socket socket_;

public:
    WebSocketServer(net::io_context& ioc, tcp::endpoint endpoint)
        : acceptor_(ioc), socket_(ioc) {
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(net::socket_base::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        accept();
    }

private:
    void accept() {
        acceptor_.async_accept(socket_, [this](beast::error_code ec) {
            if (!ec) {
                std::make_shared<WebSocketSession>(std::move(socket_))->run();
            }
            accept(); // Accept next connection
            });
    }
};

// Main function to run the server
int main() {
    try {
        net::io_context ioc;
        tcp::endpoint endpoint{ tcp::v4(), 8080 };
        WebSocketServer server(ioc, endpoint);

        std::cout << "WebSocket server is running on ws://localhost:8080" << std::endl;
        ioc.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
