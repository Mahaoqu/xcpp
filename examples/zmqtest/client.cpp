#include <iostream>
#include <chrono>
#include <thread>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main() {
    zmq::context_t context(1);
    zmq::socket_t dealer(context, zmq::socket_type::dealer);

    dealer.set(zmq::sockopt::routing_id, 0);
    dealer.connect("tcp://localhost:5555");

    while (true) {
        // 发送消息给服务器
        dealer.send(zmq::str_buffer("Hello, server!"), zmq::send_flags::none);

        zmq::multipart_t multipart;

        // 接收服务器消息
        multipart.recv(dealer);
        std::string server_message = multipart[0].to_string();

        std::cout << "Received: " << server_message << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}