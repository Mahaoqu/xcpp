#pragma once
#include "Common.h"

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

std::string setHelloPacket();
std::string setWelcomePacket(json j);
json parseFromWelcomePacket(char *packet, size_t size);
std::string setWorldStatePacket(json j);
/**
 * Welcome packet
 */

} // namespace Network

} // namespace GameEngine
