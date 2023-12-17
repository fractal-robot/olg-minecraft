#pragma once

#include <cstddef>
#include <string_view>

namespace constants {
inline constexpr int windowWidth{1920};
inline constexpr int windowHeight{1080};

inline constexpr float cameraSpeed{24.f};
inline constexpr float cameraSensivity{.04f};
inline constexpr float cameraAltitudeSpeed{22.f};
inline constexpr int viewDistance{400};

inline constexpr int blockVerticesCount{120};
inline constexpr int blockIndicesCount{36};

inline constexpr int chunkSize{60};

inline constexpr int elementOffset{5};
} // namespace constants
