#include "TreeGenerator.h"

#include <cmath>

namespace seasonal_tree
{

    namespace
    {
        constexpr float kLeafRadius = 3.5f;
        constexpr Color kBranchColor = Color{160, 82, 45, 255}; // sienna
    } // namespace

    TreeGenerator::TreeGenerator() : rng_(std::random_device{}()) {}

    void TreeGenerator::Generate(const TreeParameters &params,
                                 std::vector<BranchSegment> &outBranches,
                                 std::vector<LeafNode> &outLeaves)
    {
        outBranches.clear();
        outLeaves.clear();

        GenerateRecursive(params,
                          params.root,
                          params.trunkAngleDegrees,
                          params.initialBranchLength,
                          6.0f,
                          outBranches,
                          outLeaves);
    }

    void TreeGenerator::GenerateRecursive(const TreeParameters &params,
                                          Vector2 start,
                                          float headingDegrees,
                                          float branchLength,
                                          float thickness,
                                          std::vector<BranchSegment> &outBranches,
                                          std::vector<LeafNode> &outLeaves)
    {
        if (branchLength < params.minBranchLength)
        {
            outLeaves.push_back(LeafNode{start, kLeafRadius, GetLeafColor(params.season)});
            return;
        }

        const float radians = headingDegrees * DEG2RAD;
        const Vector2 end = {
            start.x + branchLength * std::cos(radians),
            start.y - branchLength * std::sin(radians),
        };

        outBranches.push_back(BranchSegment{start, end, thickness});

        const float nextLength = branchLength * params.scaleFactor;
        const float nextThickness = thickness * 0.75f;

        GenerateRecursive(params,
                          end,
                          headingDegrees - params.branchAngleDegrees,
                          nextLength,
                          nextThickness,
                          outBranches,
                          outLeaves);

        GenerateRecursive(params,
                          end,
                          headingDegrees + params.branchAngleDegrees,
                          nextLength,
                          nextThickness,
                          outBranches,
                          outLeaves);
    }

    Color TreeGenerator::GetLeafColor(Season season)
    {
        switch (season)
        {
        case Season::Spring:
            return Color{144, 238, 144, 255};
        case Season::Summer:
            return GREEN;
        case Season::Autumn:
        {
            const int pick = GetRandomValue(0, 2);
            if (pick == 0)
            {
                return ORANGE;
            }
            if (pick == 1)
            {
                return RED;
            }
            return YELLOW;
        }
        case Season::Winter:
        default:
            return RAYWHITE;
        }
    }

} // namespace seasonal_tree
