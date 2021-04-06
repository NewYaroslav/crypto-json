#ifndef CRYPTO_JSON_EDITOR_FONTS_HPP_INCLUDED
#define CRYPTO_JSON_EDITOR_FONTS_HPP_INCLUDED

/** \brief Инициализировать шрифты
 */
static void init_fonts() {
    /* настраиваем язык */
    ImFontConfig font_config;
    font_config.OversampleH = 1; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 18.0f, NULL, ranges);
    //io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 24.0f, NULL, ranges);

    ImGui::SFML::UpdateFontTexture();
}

#endif // CRYPTO_JSON_EDITOR_FONTS_HPP_INCLUDED
