#ifndef CRYPTO_JSON_EDITOR_UTILITY_HPP_INCLUDED
#define CRYPTO_JSON_EDITOR_UTILITY_HPP_INCLUDED

#include <iostream>
#include <crypto-json/crypto-json.hpp>

namespace crypto_json_editor {

    /** \brief Скопировать текст в буфер обмена
     * \param text      Текст для копирования в буфер обмена
     * \param formated  Флаг форматирования
     * \return Вернет true в случае успешного копирования
     */
    bool copy_json_to_clipboard(const std::string &text, const bool formated = false) {
        std::string strip_json = crypto_json::strip_json_comments(text);
        std::string dump_json;
        try {
            crypto_json::json j = crypto_json::json::parse(strip_json);
            if (formated) dump_json = j.dump(4);
            else dump_json = j.dump();
        } catch(...) {
            std::cerr << "crypto json editor: error copy json to clipboard" << std::endl;
            return false;
        };
        crypto_json::to_clipboard(dump_json);
        return true;
    }
}; // crypto_json_editor

#endif // CRYPTO_JSON_EDITOR_UTILITY_HPP_INCLUDED
