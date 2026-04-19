#include "Renderer.h"

#include "raylib.h"

#include <cmath>
#include <string>

namespace seasonal_tree {

namespace {

Vector2 RotatePointAroundCenter(Vector2 point, Vector2 center, float angleDegrees) {
  const float angle = angleDegrees * DEG2RAD;
  const float s = std::sin(angle);
  const float c = std::cos(angle);

  const float px = point.x - center.x;
  const float py = point.y - center.y;

  return {
      center.x + px * c - py * s,
      center.y + px * s + py * c,
  };
}

void DrawLeaf(const LeafNode& leaf) {
  const Vector2 center = leaf.center;

  const Vector2 tip = {center.x, center.y - leaf.height};
  const Vector2 base = {center.x, center.y + leaf.height * 0.55f};
  const Vector2 left = {center.x - leaf.width, center.y};
  const Vector2 right = {center.x + leaf.width, center.y};

  const Vector2 tipR = RotatePointAroundCenter(tip, center, leaf.rotationDegrees);
  const Vector2 baseR = RotatePointAroundCenter(base, center, leaf.rotationDegrees);
  const Vector2 leftR = RotatePointAroundCenter(left, center, leaf.rotationDegrees);
  const Vector2 rightR = RotatePointAroundCenter(right, center, leaf.rotationDegrees);

  DrawTriangle(tipR, leftR, rightR, leaf.color);
  DrawTriangle(baseR, leftR, rightR, leaf.color);

  const float angleRad = leaf.rotationDegrees * DEG2RAD;
  const Vector2 midTop = {
      center.x + std::sin(angleRad) * leaf.height * 0.85f,
      center.y - std::cos(angleRad) * leaf.height * 0.85f,
  };
  const Vector2 midBottom = {
      center.x - std::sin(angleRad) * leaf.height * 0.40f,
      center.y + std::cos(angleRad) * leaf.height * 0.40f,
  };
  DrawLineEx(midBottom, midTop, 1.1f, leaf.accentColor);

  const Vector2 side1 = {
      center.x - std::cos(angleRad) * leaf.width * 0.6f,
      center.y - std::sin(angleRad) * leaf.width * 0.6f,
  };
  const Vector2 side2 = {
      center.x + std::cos(angleRad) * leaf.width * 0.6f,
      center.y + std::sin(angleRad) * leaf.width * 0.6f,
  };
  DrawLineEx(center, side1, 0.8f, Fade(leaf.accentColor, 0.65f));
  DrawLineEx(center, side2, 0.8f, Fade(leaf.accentColor, 0.65f));

  const Vector2 tipHighlight = {
      center.x + std::cos(angleRad) * leaf.height,
      center.y - std::sin(angleRad) * leaf.height,
  };
  DrawCircleV(tipHighlight, 1.2f, Fade(leaf.accentColor, 0.7f));
}

void DrawBranch(const BranchSegment& branch) {
  DrawLineEx(branch.start, branch.end, branch.thickness, Color{160, 82, 45, 255});
  // Thin bark highlight gives branches a less flat look.
  const Vector2 highlightStart = {
      branch.start.x + (branch.end.y - branch.start.y) * 0.02f,
      branch.start.y - (branch.end.x - branch.start.x) * 0.02f,
  };
  const Vector2 highlightEnd = {
      branch.end.x + (branch.end.y - branch.start.y) * 0.02f,
      branch.end.y - (branch.end.x - branch.start.x) * 0.02f,
  };
  DrawLineEx(highlightStart, highlightEnd, branch.thickness * 0.25f, Fade(BEIGE, 0.35f));
}

}  // namespace

void Renderer::DrawFrame(const TreeParameters& params,
                         const std::vector<BranchSegment>& branches,
                         const std::vector<LeafNode>& leaves) const {
  BeginDrawing();
  ClearBackground(SKYBLUE);

  for (const BranchSegment& branch : branches) {
    DrawBranch(branch);
  }

  for (const LeafNode& leaf : leaves) {
    DrawLeaf(leaf);
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
