#include "Controls.h"

#include "Config.h"

#include "raylib.h"

namespace seasonal_tree {

bool Controls::HandleInput(TreeParameters& params, bool& screenshotRequested) const {
  bool changed = false;
  screenshotRequested = false;

  if (IsKeyDown(KEY_Q)) {
    params.initialBranchLength += 1.0f;
    changed = true;
  }
  if (IsKeyDown(KEY_A)) {
    params.initialBranchLength -= 1.0f;
    changed = true;
  }

  if (IsKeyDown(KEY_W)) {
    params.branchAngleDegrees += 0.5f;
    changed = true;
  }
  if (IsKeyDown(KEY_S)) {
    params.branchAngleDegrees -= 0.5f;
    changed = true;
  }

  if (IsKeyDown(KEY_E)) {
    params.scaleFactor += 0.005f;
    changed = true;
  }
  if (IsKeyDown(KEY_D)) {
    params.scaleFactor -= 0.005f;
    changed = true;
  }

  if (IsKeyDown(KEY_R)) {
    params.minBranchLength += 0.25f;
    changed = true;
  }
  if (IsKeyDown(KEY_F)) {
    params.minBranchLength -= 0.25f;
    changed = true;
  }

  if (IsKeyPressed(KEY_ONE)) {
    params.season = Season::Spring;
    changed = true;
  }
  if (IsKeyPressed(KEY_TWO)) {
    params.season = Season::Summer;
    changed = true;
  }
  if (IsKeyPressed(KEY_THREE)) {
    params.season = Season::Autumn;
    changed = true;
  }
  if (IsKeyPressed(KEY_FOUR)) {
    params.season = Season::Winter;
    changed = true;
  }

  if (IsKeyPressed(KEY_P)) {
    screenshotRequested = true;
  }

  params.initialBranchLength =
      Clamp(params.initialBranchLength, config::kBranchLengthMin, config::kBranchLengthMax);
  params.branchAngleDegrees = Clamp(params.branchAngleDegrees, config::kAngleMin, config::kAngleMax);
  params.scaleFactor = Clamp(params.scaleFactor, config::kScaleMin, config::kScaleMax);
  params.minBranchLength =
      Clamp(params.minBranchLength, config::kMinBranchLenMin, config::kMinBranchLenMax);

  return changed;
}

float Controls::Clamp(float value, float low, float high) {
  if (value < low) {
    return low;
  }
  if (value > high) {
    return high;
  }
  return value;
}

}  // namespace seasonal_tree
