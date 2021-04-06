#ifndef CRYPTO_JSON_EDITOR_IMGUI_ADDONS_HPP_INCLUDED
#define CRYPTO_JSON_EDITOR_IMGUI_ADDONS_HPP_INCLUDED

#include <imgui.h>
#include <string>

namespace crypto_json_editor {

    class ErrorPopup {
    private:
        std::string label;
        std::string title;
        std::string text;
        bool is_open = false;
        ImVec2 min_size, max_size;
    public:
        ImVec4 header_color = ImVec4(192.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.00f);
        ImVec4 header_text_color = ImVec4(224.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.00f);

        ErrorPopup(const std::string &error_label) : label(error_label) {
            min_size = ImVec2(200,150);
        };

        /** \brief Открыть уведомление об ошибке
         * \param error_title   Заголовок
         * \param error_text    Текст ошибки
         */
        inline void open(const std::string &error_title, const std::string &error_text) {
            title = error_title;
            text = error_text;
            is_open = true;
        }

        /** \brief Показать окно ошибки
         *
         * Данный метод необходимо вызывать отдельно от всех окон, желательно в конце кода меню
         */
        void show_dialog();
    };
}; // crypto_json_editor

#endif // CRYPTO_JSON_EDITOR_IMGUI_ADDONS_HPP_INCLUDED
