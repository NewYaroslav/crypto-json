#ifndef CRYPTO_JSON_EDITOR_STYLE_HPP_INCLUDED
#define CRYPTO_JSON_EDITOR_STYLE_HPP_INCLUDED

/* Цвета меню брокера Олимп Трейд
 * 41 148 194 - RGB цвет фокуса
 * 35 51 66 - RGB цвет активного меню
 * 30 44 57 - RGB цвет неактивного меню
 * 24 38 49 - RGB цвет фона
 * 84 101 121 - RGB цвет неактивного текста
 */


const ImVec4 CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG = ImVec4(35.0f/255.0f, 35.0f/255.0f, 35.0f/255.0f, 1.00f);
const ImVec4 CRYPTO_JSON_EDITOR_INACTIVE_WINDOW_BG = ImVec4(30.0f/255.0f, 44.0f/255.0f, 57.0f/255.0f, 1.00f);

const ImVec4 CRYPTO_JSON_EDITOR_TEXT = ImVec4(250.0f/255.0f, 250.0f/255.0f, 250.0f/255.0f, 1.00f);
const ImVec4 CRYPTO_JSON_EDITOR_DISABLED_TEXT = ImVec4(84.0f/255.0f, 101.0f/255.0f, 121.0f/255.0f, 1.00f);

const ImVec4 CRYPTO_JSON_EDITOR_LIGHT = ImVec4(41.0f/255.0f, 148.0f/255.0f, 194.0f/255.0f, 1.00f);

const ImVec4 CRYPTO_JSON_EDITOR_BUTTON = ImVec4(32.0f/255.0f, 32.0f/255.0f, 32.0f/255.0f, 1.00f);
const ImVec4 CRYPTO_JSON_EDITOR_BUTTON_HOVERED = ImVec4(48.0f/255.0f, 48.0f/255.0f, 48.0f/255.0f, 1.00f);
const ImVec4 CRYPTO_JSON_EDITOR_BUTTON_ACTIVE = ImVec4(62.0f/255.0f, 62.0f/255.0f, 62.0f/255.0f, 1.00f);

const ImVec4 CRYPTO_JSON_EDITOR_WINDOW_BG = ImVec4(16.0f/255.0f, 16.0f/255.0f, 16.0f/255.0f, 1.00f);

const ImVec4 CRYPTO_JSON_EDITOR_RED_COLOR = ImVec4(255.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 1.00f);

static void init_style() {
    ImGuiStyle * style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->Colors[ImGuiCol_Button] = CRYPTO_JSON_EDITOR_BUTTON;
    style->Colors[ImGuiCol_ButtonHovered] = CRYPTO_JSON_EDITOR_BUTTON_HOVERED;
    style->Colors[ImGuiCol_ButtonActive] = CRYPTO_JSON_EDITOR_BUTTON_ACTIVE;

    style->Colors[ImGuiCol_Tab] = CRYPTO_JSON_EDITOR_INACTIVE_WINDOW_BG;
    style->Colors[ImGuiCol_TabActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;
    style->Colors[ImGuiCol_TabHovered] = CRYPTO_JSON_EDITOR_LIGHT;

    style->Colors[ImGuiCol_TitleBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_TitleBgCollapsed] = CRYPTO_JSON_EDITOR_LIGHT;
    style->Colors[ImGuiCol_TitleBgActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;

    style->Colors[ImGuiCol_Header] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_HeaderHovered] = CRYPTO_JSON_EDITOR_BUTTON_HOVERED;
    style->Colors[ImGuiCol_HeaderActive] = CRYPTO_JSON_EDITOR_BUTTON_ACTIVE;

    style->Colors[ImGuiCol_ScrollbarBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_ScrollbarGrabActive] = CRYPTO_JSON_EDITOR_BUTTON_ACTIVE;
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = CRYPTO_JSON_EDITOR_BUTTON_HOVERED;

    style->Colors[ImGuiCol_FrameBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_FrameBgHovered] = CRYPTO_JSON_EDITOR_BUTTON_HOVERED;
    style->Colors[ImGuiCol_FrameBgActive] = CRYPTO_JSON_EDITOR_BUTTON_ACTIVE;

    style->Colors[ImGuiCol_TextSelectedBg] = CRYPTO_JSON_EDITOR_LIGHT;

    // style->Colors[ImGuiCol_CheckMark] = CRYPTO_JSON_EDITOR_LIGHT;///
    // style->Colors[ImGuiCol_MenuBarBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    //style->Colors[ImGuiCol_ChildBg] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;
    //style->Colors[ImGuiCol_WindowBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
#   if(0)
    /* цвета текста */
    style->Colors[ImGuiCol_Text] = CRYPTO_JSON_EDITOR_TEXT;
    style->Colors[ImGuiCol_TextDisabled] = CRYPTO_JSON_EDITOR_DISABLED_TEXT;
    style->Colors[ImGuiCol_TextSelectedBg] = CRYPTO_JSON_EDITOR_LIGHT;

    /* цвет переднего фона меню */
    style->Colors[ImGuiCol_WindowBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;

    /* цвет чего пока не ясно, ставим КРАСНЫЙ */
    style->Colors[ImGuiCol_PopupBg] = CRYPTO_JSON_EDITOR_WINDOW2_BG;

    /* цвет фона дочернего меню */
    style->Colors[ImGuiCol_ChildBg] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;

    /* цвет бордюра */
    style->Colors[ImGuiCol_Border] = CRYPTO_JSON_EDITOR_DISABLED_TEXT;

    /* цвет тени бордюра, ставим КРАСНЫЙ */
    style->Colors[ImGuiCol_BorderShadow] = ERROR_COLOR;


    style->Colors[ImGuiCol_Tab] = CRYPTO_JSON_EDITOR_INACTIVE_WINDOW_BG;
    style->Colors[ImGuiCol_TabActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;
    style->Colors[ImGuiCol_TabHovered] = CRYPTO_JSON_EDITOR_LIGHT;

    /* цвет разделителя */
    style->Colors[ImGuiCol_Separator] = CRYPTO_JSON_EDITOR_DISABLED_TEXT;

    style->Colors[ImGuiCol_MenuBarBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;

    style->Colors[ImGuiCol_ScrollbarBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_ScrollbarGrabActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = CRYPTO_JSON_EDITOR_LIGHT;

    style->Colors[ImGuiCol_FrameBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_FrameBgHovered] = CRYPTO_JSON_EDITOR_LIGHT;
    style->Colors[ImGuiCol_FrameBgActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;

    style->Colors[ImGuiCol_TitleBg] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_TitleBgCollapsed] = CRYPTO_JSON_EDITOR_LIGHT;
    style->Colors[ImGuiCol_TitleBgActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;

    style->Colors[ImGuiCol_CheckMark] = CRYPTO_JSON_EDITOR_LIGHT;///

    style->Colors[ImGuiCol_Header] = CRYPTO_JSON_EDITOR_WINDOW_BG;
    style->Colors[ImGuiCol_HeaderHovered] = CRYPTO_JSON_EDITOR_LIGHT;
    style->Colors[ImGuiCol_HeaderActive] = CRYPTO_JSON_EDITOR_ACTIVE_WINDOW_BG;

    style->Colors[ImGuiCol_PlotLines] = ERROR_COLOR;
    style->Colors[ImGuiCol_PlotLinesHovered] = ERROR_COLOR;
    style->Colors[ImGuiCol_PlotHistogram] = ERROR_COLOR;
    style->Colors[ImGuiCol_PlotHistogramHovered] = ERROR_COLOR;
    style->Colors[ImGuiCol_TextSelectedBg] = CRYPTO_JSON_EDITOR_LIGHT;
    //style->Colors[ImGuiCol_ModalWindowDarkening] = ERROR_COLOR;

    style->Colors[ImGuiCol_ResizeGrip] = ERROR_COLOR;
    style->Colors[ImGuiCol_ResizeGripHovered] = ERROR_COLOR;
    style->Colors[ImGuiCol_ResizeGripActive] = ERROR_COLOR;

    style->Colors[ImGuiCol_SliderGrab] = ERROR_COLOR;
    style->Colors[ImGuiCol_SliderGrabActive] = ERROR_COLOR;
    style->Colors[ImGuiCol_Button] = CRYPTO_JSON_EDITOR_BUTTON2;
    style->Colors[ImGuiCol_ButtonHovered] = CRYPTO_JSON_EDITOR_LIGHT;
    style->Colors[ImGuiCol_ButtonActive] = CRYPTO_JSON_EDITOR_BUTTON2_HOVERED;
#   endif
#   if(0)
    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);

    /* не заметил влияния */
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.074f, 0.09f, 0.0133f, 1.00f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.074f, 0.09f, 0.0133f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.074f, 0.09f, 0.0133f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.368f, 0.372f, 0.384f, 1.00f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.27f, 0.278f, 0.301f, 1.00f);

    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);

    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.196f, 0.196f, 0.243f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.196f, 0.196f, 0.243f, 1.00f);

    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.18f, 1.0f, 0.34f, 1.0f);///!

    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
    //style->Colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);///!
    //style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    //style->Colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);///!
    //style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    //style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    //style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    //style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    //style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    //style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

    //style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);

    //style->Colors[ImGuiCol_] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.18f, 1.0f, 0.34f, 1.0f);///!
    //style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //style->Colors[ImGuiCol_] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    //style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    ///style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
    //style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    //style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
#   endif
}

#endif // CRYPTO_JSON_EDITOR_STYLE_HPP_INCLUDED
