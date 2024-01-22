#include "menu.hpp"

#include <string>
#include <vector>

namespace mandelbrot_visualizer::ui {

MenuValues Menu::ShowMenu(const MenuState& state) {
  ImGui::NewFrame();
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::Begin("Render Settings");
  const auto mode = ModeCombo(state.mode);
  WindowInfo(state);
  DurationInfo(state);
  auto color = state.base_color;
  SetColor(color);
  FpsInfo();
  ImGui::End();
  return {mode, color};
}

Mode Menu::ModeCombo(const Mode current) {
  static std::vector<std::string> items = {"Sequential", "OpenMP"};
  auto current_item = static_cast<int>(current);

  if (ImGui::BeginCombo("##combo", items[current_item].c_str())) {
    for (int i = 0; i < 2; i++) {
      const bool is_selected = (current_item == i);
      if (ImGui::Selectable(items[i].c_str(), is_selected)) current_item = i;
      if (is_selected) ImGui::SetItemDefaultFocus();
    }

    ImGui::EndCombo();
  }
  return static_cast<Mode>(current_item);
}

void Menu::FpsInfo() {
  ImGuiIO& io = ImGui::GetIO();

  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Application average %.3f ms/frame (%.1f FPS)",
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
      1000.0F / io.Framerate, io.Framerate);
}

void Menu::DurationInfo(const MenuState& state) {
  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Compute Time: %.1lims, Draw Time: %.1lims", state.compute_time.count(),
      state.draw_time.count());
  // TODO(ak): add progress bar + progress from mandel
  // ImGui::ProgressBar(0, ImVec2(-1, 0));
}

void Menu::WindowInfo(const MenuState& state) {
  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Window Size: %ix%i", state.display_width, state.display_height);
}

void Menu::SetColor(RGBColor& current) {
  ImGui::ColorEdit3("Base Color", current.data());
}

}  // namespace mandelbrot_visualizer::ui
