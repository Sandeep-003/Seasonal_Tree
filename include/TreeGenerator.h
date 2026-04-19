#pragma once

#include "Types.h"

#include <random>
#include <vector>

namespace seasonal_tree {

class TreeGenerator {
 public:
  TreeGenerator();

  void Generate(const TreeParameters& params,
                std::vector<BranchSegment>& outBranches,
                std::vector<LeafNode>& outLeaves);

 private:
  std::mt19937 rng_;

  void GenerateRecursive(const TreeParameters& params,
                         Vector2 start,
                         float headingDegrees,
                         float branchLength,
                         float thickness,
                         std::vector<BranchSegment>& outBranches,
                         std::vector<LeafNode>& outLeaves);

  Color GetLeafColor(Season season);
    Color GetLeafAccentColor(Season season);
    float RandomRange(float minValue, float maxValue);
};

}  // namespace seasonal_tree
