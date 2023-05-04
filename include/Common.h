#pragma once

#ifndef _GAME_ENGINE_COMMON_H_
#define _GAME_ENGINE_COMMON_H_

#include <chrono>
#include <filesystem>
#include <iostream>
#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <zmq.hpp>
#include <zmq_addon.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GameEngine
{

template <typename T> inline void LOG(T msg)
{
    std::cerr << msg << std::endl;
}

template <typename T, typename... Args>
inline void LOG(T t, Args... args) {
    std::cerr << t << " ";
    LOG(args...);
}

} // namespace GameEngine

#endif // !_GAME_ENGINE_COMMON_H_
