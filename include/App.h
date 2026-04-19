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

  void AdjustBranchLength(float delta);
  void AdjustBranchAngle(float delta);
  void AdjustScaleFactor(float delta);
  void AdjustMinBranchLength(float delta);
  void SetSeason(int seasonIndex);
  void ResetTree();
  void CaptureScreenshot();

 private:
    void ProcessFrame();
  void RegenerateTree();
  void SaveScreenshot() const;

  TreeParameters params_;
  TreeGenerator generator_;
  Controls controls_;
  Renderer renderer_;

  std::vector<BranchSegment> branches_;
  std::vector<LeafNode> leaves_;

  int lastScreenWidth_ = -1;
  int lastScreenHeight_ = -1;
};

}  // namespace seasonal_tree
