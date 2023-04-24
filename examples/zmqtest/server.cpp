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
    zmq::socket_t router(context, zmq::socket_type::router);
    router.bind("tcp://*:5555");

    int iteration = 0;

    std::unordered_map<int, int> client_on_connection_count;
    std::mutex connection_times_mutex;
    int next_client_id = 1;

    auto handle_client = [&]() {
        while (true)
        {
            zmq::multipart_t multipart;
            multipart.recv(router);
            int client_id = std::stoi(multipart[0].to_string());

            if(client_id == 0) 
            {
                zmq::multipart_t reply;
                reply.addstr(std::to_string(next_client_id));
                reply.send(router);
            }

            next_client_id++;
        }
    };

    std::thread t(handle_client);
    t.detach();

    while (true)
    {
        // sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
        iteration++;

        for (int i = 1; i <= next_client_id; ++i)
        {
            zmq::multipart_t reply;
            reply.addstr(std::to_string(i));

            std::stringstream message;
            message << "Client " << i << ": Iteration " << iteration;
            reply.addstr(message.str());

            reply.send(router);
        }
    }

    return 0;
}
