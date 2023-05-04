#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
    zmq::context_t context(1);
    zmq::socket_t rep(context, zmq::socket_type::rep);
    rep.bind("tcp://*:5555");

    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");

    int iteration = 0;

    std::vector<int> client_on_connection_count;
    std::mutex cmtx;

    auto handle_client = [&]() {
        while (true)
        {
            zmq::message_t msg;
            rep.recv(&msg);

            std::cout << "Client " << client_on_connection_count.size() + 1 << " Connected" << std::endl;

            std::unique_lock<std::mutex> lock(cmtx);
            client_on_connection_count.push_back(iteration);
            lock.unlock();

            rep.send(zmq::str_buffer("Hello, client!"), zmq::send_flags::none);
        }
    };

    std::thread t(handle_client);
    t.detach();

    while (true)
    {
        std::cout << "Iteration " << iteration << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        iteration++;

        std::stringstream ss;

        std::unique_lock<std::mutex> lock(cmtx);
        for (int i = 0; i < client_on_connection_count.size(); i++)
        {
            ss << "Client " << i + 1 << ": Iteration " << iteration - client_on_connection_count[i] << std::endl;
        }
        lock.unlock();
        zmq::message_t message(ss.str());

        publisher.send(message);
    }

    return 0;
}
