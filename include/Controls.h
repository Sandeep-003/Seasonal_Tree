#pragma once

#include "Types.h"

namespace seasonal_tree {

class Controls {
 public:
  bool HandleInput(TreeParameters& params, bool& screenshotRequested) const;

 private:
  static float Clamp(float value, float low, float high);
};

}  // namespace seasonal_tree
