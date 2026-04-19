# Seasonal Tree Python to C++ (raylib)

This folder provides a full conversion structure for `Final_seasonal_tree.py` into modular C++ using raylib.

## Python -> C++ Mapping

- `draw_tree(...)` -> `TreeGenerator::GenerateRecursive(...)`
- `start_drawing()` -> `SeasonalTreeApp::Run()` + `SeasonalTreeApp::RegenerateTree()`
- Tkinter sliders -> keyboard controls in `Controls::HandleInput(...)`
- `season_var` -> `TreeParameters::season`
- turtle canvas drawing -> `Renderer::DrawFrame(...)`
- PNG export block -> `SeasonalTreeApp::SaveScreenshot()` with `TakeScreenshot`

## File Structure

- `include/Types.h`: shared enums and structs (`Season`, `TreeParameters`, `BranchSegment`, `LeafNode`)
- `include/TreeGenerator.h` + `src/TreeGenerator.cpp`: recursive tree geometry and seasonal leaf coloring
- `include/Controls.h` + `src/Controls.cpp`: user input and variable updates
- `include/Renderer.h` + `src/Renderer.cpp`: drawing tree + HUD/instructions
- `include/App.h` + `src/App.cpp`: app lifecycle and orchestration
- `src/main.cpp`: entry point
- `CMakeLists.txt`: standalone build config

## Variables You Will Tune

- `initialBranchLength`: equivalent to Python initial branch slider
- `branchAngleDegrees`: branch split angle
- `scaleFactor`: recursive shrink factor
- `minBranchLength`: leaf cutoff threshold
- `season`: spring/summer/autumn/winter leaf palette

## Controls

- `Q / A`: increase/decrease initial branch length
- `W / S`: increase/decrease branch angle
- `E / D`: increase/decrease scale factor
- `R / F`: increase/decrease minimum branch length
- `1 / 2 / 3 / 4`: spring / summer / autumn / winter
- `P`: save screenshot PNG

## Build

```bash
cmake -S . -B build
cmake --build build --config Release
```

Run executable from `build` folder.
