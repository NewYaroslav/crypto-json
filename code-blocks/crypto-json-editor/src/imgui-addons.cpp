#include "../include/imgui-addons.hpp"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"

namespace crypto_json_editor {

    void ErrorPopup::show_dialog() {

        if (is_open) {
            is_open = false;
            ImGui::OpenPopup(label.c_str());
        }

        ImGuiIO& io = ImGui::GetIO();
        max_size.x = io.DisplaySize.x;
        max_size.y = io.DisplaySize.y;

        ImGui::SetNextWindowSizeConstraints(min_size, max_size);
        ImGui::SetNextWindowPos(io.DisplaySize * 0.5f, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
        //ImGui::SetNextWindowSize(ImVec2(std::max(sz_xy.x, min_size.x), std::max(sz_xy.y, min_size.y)), ImGuiCond_Appearing);

        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, header_color);
        if (ImGui::BeginPopupModal(label.c_str(), nullptr,
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoScrollWithMouse)) {

            ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(55,16));

            ImGui::PushStyleColor(ImGuiCol_Text, header_color);
            ImGui::Text(title.c_str());
            ImGui::PopStyleColor();
            ImGui::Separator();
            ImGui::TextWrapped(text.c_str());
            if (ImGui::Button("ok")) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::PopStyleVar();

            ImGui::EndPopup();
        }
        ImGui::PopStyleColor();
    };
}; // crypto_json_editor
