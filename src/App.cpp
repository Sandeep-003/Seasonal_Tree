#include "App.h"

#include "Config.h"

#include "raylib.h"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace seasonal_tree {

SeasonalTreeApp::SeasonalTreeApp() {
  params_.root = {static_cast<float>(config::kScreenWidth) / 2.0f,
                  static_cast<float>(config::kScreenHeight) - 40.0f};
}

void SeasonalTreeApp::Run() {
  InitWindow(config::kScreenWidth, config::kScreenHeight, config::kWindowTitle);
  SetTargetFPS(60);

  RegenerateTree();

  while (!WindowShouldClose()) {
    bool screenshotRequested = false;
    const bool changed = controls_.HandleInput(params_, screenshotRequested);

    if (changed) {
      RegenerateTree();
    }
    if (screenshotRequested) {
      SaveScreenshot();
    }

    renderer_.DrawFrame(params_, branches_, leaves_);
  }

  CloseWindow();
}

void SeasonalTreeApp::RegenerateTree() {
  generator_.Generate(params_, branches_, leaves_);
}

void SeasonalTreeApp::SaveScreenshot() const {
  const auto now = std::chrono::system_clock::now();
  const std::time_t t = std::chrono::system_clock::to_time_t(now);

  std::tm tm{};
#if defined(_WIN32)
  localtime_s(&tm, &t);
#else
  localtime_r(&t, &tm);
#endif

  std::ostringstream filename;
  filename << "tree_season_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".png";
  TakeScreenshot(filename.str().c_str());
}

}  // namespace seasonal_tree
