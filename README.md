# Seasonal Tree (C++ raylib + WebAssembly)

Interactive seasonal fractal tree built in C++ with raylib, with both desktop and browser (WASM) targets.

This project is a structured conversion of `Final_seasonal_tree.py` into modular C++ with improved rendering and web controls.

## Features

- Recursive branching tree generator
- Seasonal leaf palettes (`Spring`, `Summer`, `Autumn`, `Winter`)
- Realistic leaf shape rendering (veins + shading)
- Desktop keyboard controls
- Web UI controls wired directly into exported WASM functions
- Screenshot support

## Project Structure

- `include/Types.h`: enums + data models (`Season`, `TreeParameters`, `BranchSegment`, `LeafNode`)
- `include/TreeGenerator.h`, `src/TreeGenerator.cpp`: recursive geometry + leaf distribution + seasonal colors
- `include/Controls.h`, `src/Controls.cpp`: desktop keyboard input handling
- `include/Renderer.h`, `src/Renderer.cpp`: branch/leaf drawing and scene background
- `include/App.h`, `src/App.cpp`: app loop, parameter mutation API, web exports
- `src/main.cpp`: entry point
- `docs/index.html`: custom web UI (controls + runtime loader)
- `.github/workflows/deploy-pages.yml`: GitHub Pages build/deploy pipeline

## Python to C++ Mapping

- `draw_tree(...)` -> `TreeGenerator::GenerateRecursive(...)`
- `start_drawing()` -> app lifecycle in `SeasonalTreeApp::Run()`
- season selector -> `TreeParameters::season` + `SetSeason(...)`
- turtle canvas rendering -> `Renderer::DrawFrame(...)`
- save image -> `SaveScreenshot()` / `TakeScreenshot(...)`

## Desktop Run

### Build

```bash
cmake -S . -B build
cmake --build build --config Release
```

### Run

- Windows executable path:
	- `build/Release/seasonal_tree_raylib.exe`

## Desktop Controls (Keyboard)

- `Q / A`: increase/decrease initial branch length
- `W / S`: increase/decrease branch angle
- `E / D`: increase/decrease scale factor
- `R / F`: increase/decrease minimum branch length
- `1 / 2 / 3 / 4`: set season
- `P`: save screenshot

## WebAssembly Build (Local)

### 1. Activate Emscripten environment

```powershell
cd "d:\CREATION\SHE++\Computer Graphics\Algorithmic beauty of plants\CPP version\seasonal_tree_raylib"
& "d:\CREATION\SHE++\Computer Graphics\emsdk\emsdk_env.ps1"
```

### 2. Configure and build web target

```powershell
emcmake cmake -S . -B build-web -DCMAKE_BUILD_TYPE=Release
cmake --build build-web --config Release
```

### 3. Expected outputs

- `build-web/seasonal_tree_raylib.html`
- `build-web/seasonal_tree_raylib.js`
- `build-web/seasonal_tree_raylib.wasm`

## Run Web UI Locally

Recommended: serve the project root and open the custom UI page.

```powershell
python -m http.server 8080
```

Then open:

- `http://localhost:8080/docs/index.html`

The page auto-loads runtime files from either:

- `docs/seasonal_tree_raylib.js` (if copied there), or
- `../build-web/seasonal_tree_raylib.js` (default local fallback)

## Web Controls (Buttons)

All buttons call exported C++ functions via `Module.ccall(...)`.

- `Reset Tree` -> `st_resetTree`
- `Branch Length +/-` -> `st_adjustBranchLength`
- `Branch Angle +/-` -> `st_adjustBranchAngle`
- `Scale Factor +/-` -> `st_adjustScaleFactor`
- `Min Branch Len +/-` -> `st_adjustMinBranchLength`
- `Season buttons` -> `st_setSeason`
- `Save PNG` -> `st_saveScreenshot` + browser canvas download

## GitHub Pages Deployment

Workflow file:

- `.github/workflows/deploy-pages.yml`

Pipeline behavior:

1. Build WASM with Emscripten
2. Use `docs/index.html` as the page shell
3. Publish runtime files (`.js`, `.wasm`) with the page

### One-time setup

1. GitHub repository `Settings` -> `Pages`
2. Set source to `GitHub Actions`
3. Push to `master` or `main`

Site URL format:

- `https://<your-github-username>.github.io/<your-repo-name>/`

## Troubleshooting

### Buttons do nothing

- Rebuild web target:
	- `cmake --build build-web --config Release`
- Hard refresh browser:
	- `Ctrl + F5`
- Verify runtime loaded from Network tab:
	- `seasonal_tree_raylib.js` -> 200
	- `seasonal_tree_raylib.wasm` -> 200

### Stuck at "Compiling and loading..."

- Usually runtime path mismatch or stale cache.
- Open `docs/index.html` through an HTTP server (not raw file open).
- Confirm `.js` and `.wasm` are accessible from the served path.

### MIME type error for JS

- Means the JS URL returned HTML (typically 404 page).
- Check the exact JS path in DevTools Network and ensure it exists.

### Background or style changes not visible

- Browser cache is likely stale.
- Use hard refresh (`Ctrl + F5`) or clear site data.

## Notes

- Web and desktop share core logic, but desktop keyboard controls and web button controls are separate input paths.
- If you edit C++ rendering/input code, always rebuild `build-web` before testing in browser.
