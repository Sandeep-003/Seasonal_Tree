#include "Renderer.h"

#include "raylib.h"

#include <string>

namespace seasonal_tree {

void Renderer::DrawFrame(const TreeParameters& params,
                         const std::vector<BranchSegment>& branches,
                         const std::vector<LeafNode>& leaves) const {
  BeginDrawing();
  ClearBackground(SKYBLUE);

  for (const BranchSegment& branch : branches) {
    DrawLineEx(branch.start, branch.end, branch.thickness, Color{160, 82, 45, 255});
  }

  for (const LeafNode& leaf : leaves) {
    DrawCircleV(leaf.center, leaf.radius, leaf.color);
  }

  DrawRectangle(10, 10, 430, 190, Fade(RAYWHITE, 0.80f));
  DrawRectangleLines(10, 10, 430, 190, DARKBLUE);

  DrawText("Seasonal Tree - Python to C++ Structure", 20, 20, 20, DARKBLUE);
  DrawText("Q/A : Initial branch length", 20, 55, 18, BLACK);
  DrawText("W/S : Branch angle", 20, 77, 18, BLACK);
  DrawText("E/D : Scale factor", 20, 99, 18, BLACK);
  DrawText("R/F : Minimum branch length", 20, 121, 18, BLACK);
  DrawText("1-4 : Spring/Summer/Autumn/Winter", 20, 143, 18, BLACK);
  DrawText("P   : Save screenshot", 20, 165, 18, BLACK);

  const std::string info =
      "Len=" + std::to_string(static_cast<int>(params.initialBranchLength)) +
      "  Angle=" + std::to_string(static_cast<int>(params.branchAngleDegrees)) +
      "  Scale=" + std::to_string(params.scaleFactor).substr(0, 4) +
      "  Min=" + std::to_string(static_cast<int>(params.minBranchLength)) +
      "  Season=" + SeasonToString(params.season);

  DrawText(info.c_str(), 20, 210, 20, DARKGREEN);

  EndDrawing();
}

}  // namespace seasonal_tree
