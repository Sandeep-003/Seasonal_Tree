#include "App.h"

#include "Config.h"

#include "raylib.h"

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

#include <chrono>
#include <iomanip>
#include <sstream>

namespace seasonal_tree {

namespace {
float ClampValue(float value, float low, float high) {
  if (value < low) {
    return low;
  }
  if (value > high) {
    return high;
  }
  return value;
}

#if defined(__EMSCRIPTEN__)
SeasonalTreeApp* gWebApp = nullptr;
#endif
}  // namespace

SeasonalTreeApp::SeasonalTreeApp() {
  params_.root = {static_cast<float>(config::kScreenWidth) / 2.0f,
                  static_cast<float>(config::kScreenHeight) - 40.0f};
}

void SeasonalTreeApp::Run() {
  InitWindow(config::kScreenWidth, config::kScreenHeight, config::kWindowTitle);
  SetTargetFPS(60);

  RegenerateTree();

#if defined(__EMSCRIPTEN__)
  gWebApp = this;
  emscripten_set_main_loop_arg(
      [](void* userData) {
        auto* app = static_cast<SeasonalTreeApp*>(userData);
        app->ProcessFrame();
      },
      this,
      0,
      1);
#else
  while (!WindowShouldClose()) {
    ProcessFrame();
  }

  CloseWindow();
#endif
}

void SeasonalTreeApp::ProcessFrame() {
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

void SeasonalTreeApp::RegenerateTree() {
  generator_.Generate(params_, branches_, leaves_);
}

void SeasonalTreeApp::AdjustBranchLength(float delta) {
  params_.initialBranchLength = ClampValue(
      params_.initialBranchLength + delta, config::kBranchLengthMin, config::kBranchLengthMax);
  RegenerateTree();
}

void SeasonalTreeApp::AdjustBranchAngle(float delta) {
  params_.branchAngleDegrees =
      ClampValue(params_.branchAngleDegrees + delta, config::kAngleMin, config::kAngleMax);
  RegenerateTree();
}

void SeasonalTreeApp::AdjustScaleFactor(float delta) {
  params_.scaleFactor = ClampValue(params_.scaleFactor + delta, config::kScaleMin, config::kScaleMax);
  RegenerateTree();
}

void SeasonalTreeApp::AdjustMinBranchLength(float delta) {
  params_.minBranchLength = ClampValue(
      params_.minBranchLength + delta, config::kMinBranchLenMin, config::kMinBranchLenMax);
  RegenerateTree();
}

void SeasonalTreeApp::SetSeason(int seasonIndex) {
  if (seasonIndex < 0) {
    seasonIndex = 0;
  }
  if (seasonIndex > 3) {
    seasonIndex = 3;
  }
  params_.season = static_cast<Season>(seasonIndex);
  RegenerateTree();
}

void SeasonalTreeApp::ResetTree() {
  params_.initialBranchLength = 100.0f;
  params_.branchAngleDegrees = 25.0f;
  params_.scaleFactor = 0.70f;
  params_.minBranchLength = 10.0f;
  params_.season = Season::Summer;
  RegenerateTree();
}

void SeasonalTreeApp::CaptureScreenshot() {
  SaveScreenshot();
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

#if defined(__EMSCRIPTEN__)
extern "C" {

EMSCRIPTEN_KEEPALIVE void st_adjustBranchLength(float delta) {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->AdjustBranchLength(delta);
  }
}

EMSCRIPTEN_KEEPALIVE void st_adjustBranchAngle(float delta) {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->AdjustBranchAngle(delta);
  }
}

EMSCRIPTEN_KEEPALIVE void st_adjustScaleFactor(float delta) {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->AdjustScaleFactor(delta);
  }
}

EMSCRIPTEN_KEEPALIVE void st_adjustMinBranchLength(float delta) {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->AdjustMinBranchLength(delta);
  }
}

EMSCRIPTEN_KEEPALIVE void st_setSeason(int seasonIndex) {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->SetSeason(seasonIndex);
  }
}

EMSCRIPTEN_KEEPALIVE void st_resetTree() {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->ResetTree();
  }
}

EMSCRIPTEN_KEEPALIVE void st_saveScreenshot() {
  if (seasonal_tree::gWebApp != nullptr) {
    seasonal_tree::gWebApp->CaptureScreenshot();
  }
}

}
#endif
