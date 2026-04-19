#pragma once

#include "Types.h"

#include <vector>

namespace seasonal_tree {

class Renderer {
 public:
  void DrawFrame(const TreeParameters& params,
                 const std::vector<BranchSegment>& branches,
                 const std::vector<LeafNode>& leaves) const;
};

}  // namespace seasonal_tree
