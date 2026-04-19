#include "TreeGenerator.h"

#include <cmath>
#include <vector>

namespace seasonal_tree
{

    namespace
    {
        constexpr float kLeafWidthMin = 2.8f;
        constexpr float kLeafWidthMax = 4.8f;
        constexpr float kLeafHeightMin = 6.8f;
        constexpr float kLeafHeightMax = 11.0f;
        constexpr float kLeafJitter = 2.2f;
        constexpr int kLeafClusterMin = 2;
        constexpr int kLeafClusterMax = 4;
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
            const int leafCount = GetRandomValue(kLeafClusterMin, kLeafClusterMax);
            const float radians = headingDegrees * DEG2RAD;
            const Vector2 tangent = {std::cos(radians), -std::sin(radians)};
            const Vector2 normal = {-tangent.y, tangent.x};

            for (int i = 0; i < leafCount; ++i)
            {
                LeafNode leaf;
                const float along = RandomRange(-1.5f, 2.5f);
                const float side = RandomRange(-kLeafJitter, kLeafJitter);
                leaf.center = {
                    start.x + tangent.x * along + normal.x * side,
                    start.y + tangent.y * along + normal.y * side,
                };
                leaf.width = RandomRange(kLeafWidthMin, kLeafWidthMax);
                leaf.height = RandomRange(kLeafHeightMin, kLeafHeightMax);
                leaf.rotationDegrees = headingDegrees + RandomRange(-50.0f, 50.0f);
                leaf.color = GetLeafColor(params.season);
                leaf.accentColor = GetLeafAccentColor(params.season);
                outLeaves.push_back(leaf);
            }
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
        {
            const std::vector<Color> palette = {
                Color{152, 251, 152, 255}, // pale green
                Color{124, 252, 0, 255},   // lawn green
                Color{144, 238, 144, 255}, // light green
                Color{173, 255, 47, 255},  // green yellow
                Color{60, 179, 113, 255},  // medium sea green
            };
            return palette[static_cast<size_t>(GetRandomValue(0, static_cast<int>(palette.size()) - 1))];
        }
        case Season::Summer:
        {
            const std::vector<Color> palette = {
                Color{34, 139, 34, 255},   // forest green
                Color{46, 139, 87, 255},   // sea green
                Color{50, 205, 50, 255},   // lime green
                Color{0, 128, 0, 255},     // green
                Color{85, 107, 47, 255},   // dark olive green
            };
            return palette[static_cast<size_t>(GetRandomValue(0, static_cast<int>(palette.size()) - 1))];
        }
        case Season::Autumn:
        {
            const std::vector<Color> palette = {
                ORANGE,
                Color{255, 140, 0, 255},   // dark orange
                RED,
                Color{178, 34, 34, 255},   // firebrick
                YELLOW,
                Color{218, 165, 32, 255},  // goldenrod
                Color{205, 92, 92, 255},   // indian red
            };
            return palette[static_cast<size_t>(GetRandomValue(0, static_cast<int>(palette.size()) - 1))];
        }
        case Season::Winter:
        {
            const std::vector<Color> palette = {
                RAYWHITE,
                Color{245, 245, 245, 255},
                Color{224, 238, 255, 255},
                Color{220, 230, 240, 255},
            };
            return palette[static_cast<size_t>(GetRandomValue(0, static_cast<int>(palette.size()) - 1))];
        }
        default:
            return GREEN;
        }
    }

    Color TreeGenerator::GetLeafAccentColor(Season season)
    {
        Color base = GetLeafColor(season);
        // Slightly lighter accent used as vein/highlight on each leaf.
        return Color{
            static_cast<unsigned char>(base.r + (255 - base.r) * 0.35f),
            static_cast<unsigned char>(base.g + (255 - base.g) * 0.35f),
            static_cast<unsigned char>(base.b + (255 - base.b) * 0.35f),
            base.a};
    }

    float TreeGenerator::RandomRange(float minValue, float maxValue)
    {
        const float t = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;
        return minValue + (maxValue - minValue) * t;
    }

} // namespace seasonal_tree
