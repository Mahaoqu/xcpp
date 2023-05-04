#pragma once

namespace GameEngine
{

enum class PacketType
{
    PT_INVALID,
    PT_HELLO,
    PT_WELCOME,
    PT_WORLDSTATE,
    PT_INPUT,
    PT_DISCONNECT,
    PT_MAX
};

enum NetworkClientState
{
    NCS_Uninitialized,
    NCS_SayingHello,
    NCS_Welcomed
};

namespace Network
{

std::string setHelloPacket()
{
    std::string packet;
    packet.push_back(static_cast<char>(PacketType::PT_HELLO));
    return packet;
}

/**
 * Welcome packet
 */
std::string setWelcomePacket(json j)
{
    std::string packet;
    packet.push_back(static_cast<char>(PacketType::PT_WELCOME));
    packet += j.dump();
    return packet;
}

json parseFromWelcomePacket(char *packet, size_t size)
{
    json j;
    if (*packet == static_cast<char>(PacketType::PT_WELCOME))
    {
        std::stringstream json_str(packet + 1, size - 1);
        json j;
        json_str >> j;
        return j;
    }
    return j;
}

/**
 * World state packet
 */
std::string setWorldStatePacket(json j)
{
    std::string packet;
    packet.push_back(static_cast<char>(PacketType::PT_WORLDSTATE));
    packet += j.dump();
    return packet;
}

} // namespace Network

} // namespace GameEngine
