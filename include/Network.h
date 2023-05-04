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

} // namespace GameEngine
