#pragma once

#include <cstddef>
#include <string_view>

namespace constants {
inline constexpr int windowHeight{800};
inline constexpr int windowWidth{800};

inline constexpr float cameraSpeed{8.f};
inline constexpr float cameraSensivity{.04f};
inline constexpr float cameraAltitudeSpeed{6.f};

inline constexpr int blockVerticesCount{120};
inline constexpr int blockIndicesCount{36};

inline constexpr int chunckSize{1};

inline constexpr int elementOffset{5};
} // namespace constants
