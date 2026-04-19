#pragma once

#include "Controls.h"
#include "Renderer.h"
#include "TreeGenerator.h"
#include "Types.h"

#include <vector>

namespace seasonal_tree {

class SeasonalTreeApp {
 public:
  SeasonalTreeApp();
  void Run();

 private:
  void RegenerateTree();
  void SaveScreenshot() const;

  TreeParameters params_;
  TreeGenerator generator_;
  Controls controls_;
  Renderer renderer_;

  std::vector<BranchSegment> branches_;
  std::vector<LeafNode> leaves_;
};

}  // namespace seasonal_tree
