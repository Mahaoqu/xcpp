#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include <zmq.hpp>
#include <zmq_addon.hpp>

std::string generate_random_string(size_t length)
{
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::stringstream ss;
    for (size_t i = 0; i < length; ++i)
    {
        ss << characters[distribution(generator)];
    }

    return ss.str();
}

int main()
{
    zmq::context_t context(1);

    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    zmq::socket_t req(context, zmq::socket_type::req);
    req.connect("tcp://localhost:5555");

    req.send(zmq::str_buffer("Hello, server!"), zmq::send_flags::none);
    zmq::message_t reply;
    req.recv(&reply);

    while (true)
    {
        zmq::message_t msg;

        bool res = subscriber.recv(&msg);
        if (!res)
            break;

        std::string received_str(static_cast<char *>(msg.data()), msg.size());
        std::cout << received_str << std::endl;
    }

    // std::string id = generate_random_string(10);

    // zmq::socket_t dealer(context, zmq::socket_type::dealer);
    // dealer.setsockopt(ZMQ_IDENTITY, id.c_str(), 7);

    // dealer.connect("tcp://localhost:5555");
    // dealer.send(zmq::str_buffer("Hello, server!"), zmq::send_flags::none);

    // while (true)
    // {
    //     zmq::message_t msg;

    //     bool res = dealer.recv(&msg);
    //     if (!res)
    //         break;

    //     std::string received_str(static_cast<char *>(msg.data()), msg.size());
    //     std::cout << received_str << std::endl;
    // }

    return 0;
}