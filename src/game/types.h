#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <glm/glm.hpp>
#include <chrono>

namespace game {

using vec2 = glm::vec2;
using real = float;

using Time = std::chrono::steady_clock;
using TimePoint = std::chrono::steady_clock::time_point;
using TimeDelta = std::chrono::duration<float>;

}

#endif
