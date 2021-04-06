#ifndef CRYPTO_JSON_EDITOR_CONFIG_HPP_INCLUDED
#define CRYPTO_JSON_EDITOR_CONFIG_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <string>

namespace crypto_json_editor {

    /** \brief Параметры графического меню
     */
    class Config {
    public:
        const std::string window_name = "Crypto JSON Editor";
        const size_t start_window_width = 800;
        const size_t start_window_height = 500;
        const size_t framerate = 60;

        const size_t indent_basement = 58;

        const size_t decode_settings_width = 740;
        const size_t decode_settings_height = 280;

        const size_t error_width = 400;
        const size_t error_height = 250;

        sf::Color window_background = sf::Color(16,16,16);
    };
}; // crypto_json_editor

#endif // CRYPTO_JSON_EDITOR_CONFIG_HPP_INCLUDED
