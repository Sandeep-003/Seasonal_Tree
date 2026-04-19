#pragma once

#include "raylib.h"

#include <string>

namespace seasonal_tree {

enum class Season {
  Spring = 0,
  Summer = 1,
  Autumn = 2,
  Winter = 3
};

inline std::string SeasonToString(Season season) {
  switch (season) {
    case Season::Spring:
      return "spring";
    case Season::Summer:
      return "summer";
    case Season::Autumn:
      return "autumn";
    case Season::Winter:
      return "winter";
    default:
      return "unknown";
  }
}

struct TreeParameters {
  float initialBranchLength = 100.0f;
  float branchAngleDegrees = 25.0f;
  float scaleFactor = 0.70f;
  float minBranchLength = 10.0f;
  Season season = Season::Summer;

  Vector2 root = {640.0f, 680.0f};
  float trunkAngleDegrees = 90.0f;
};

struct BranchSegment {
  Vector2 start{};
  Vector2 end{};
  float thickness = 2.0f;
};

struct LeafNode {
  Vector2 center{};
  float radius = 3.0f;
  Color color = GREEN;
};

}  // namespace seasonal_tree
