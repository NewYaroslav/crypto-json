#ifndef CRYPTO_JSON_STRIP_JSON_COMMENTS_HPP_INCLUDED
#define CRYPTO_JSON_STRIP_JSON_COMMENTS_HPP_INCLUDED

#include <string>
#include <algorithm>

namespace crypto_json {

    inline bool check_escaped(const std::string &json_string, const int quote_position) noexcept {
        int index = quote_position - 1;
        int backslash_count = 0;
        while (index >= 0 && json_string[index] == '\\') {
            index -= 1;
            backslash_count += 1;
        }
        return (backslash_count % 2);
    };

    /** \brief Strip comments from JSON
     *
     * Source JS code: https://github.com/sindresorhus/strip-json-comments
     * \param json_string JSON string with comments
     * \return JSON string without comments
     */
    std::string strip_json_comments(const std::string &json_string) noexcept {
        enum CommentType {
            NO_COMMENT = 0,
            SINGLE_COMMENT = 1,
            MULTI_COMMENT = 2,
        };
        CommentType inside_comment = CommentType::NO_COMMENT;
        bool inside_string = false;
        size_t offset = 0;
        const size_t json_string_size = json_string.size();
        const size_t json_max_index = json_string_size - 1;
        std::string result;
        for (size_t i = 0; i < json_string_size; ++i) {
            const char current_character = json_string[i];
            const char next_character = i < json_max_index ? json_string[i + 1] : 0;

            if (inside_comment == CommentType::NO_COMMENT && current_character == '"') {
                const bool escaped = check_escaped(json_string, i);
                if (!escaped) inside_string = !inside_string;
            }

            if (inside_string) continue;

            if (inside_comment == CommentType::NO_COMMENT &&
                    ((current_character == '#' &&
                    next_character == ' ') ||
                    (current_character == '/' &&
                    next_character == '/'))) {

                result += json_string.substr(offset, i - offset);
                offset = i;
                inside_comment = CommentType::SINGLE_COMMENT;
                i++;
            } else if (inside_comment == CommentType::SINGLE_COMMENT &&
                    current_character == '\r' &&
                    next_character == '\n') {
                i++;
                inside_comment = CommentType::NO_COMMENT;
                offset = i;
                continue;
            } else if (inside_comment == CommentType::SINGLE_COMMENT &&
                    current_character == '\n') {
                inside_comment = CommentType::NO_COMMENT;
                offset = i;
            } else if (inside_comment == CommentType::NO_COMMENT &&
                    current_character == '/' &&
                    next_character == '*') {
                result += json_string.substr(offset, i - offset);
                offset = i;
                inside_comment = CommentType::MULTI_COMMENT;
                i++;
                continue;
            } else if (inside_comment == CommentType::MULTI_COMMENT &&
                    current_character == '*' &&
                    next_character == '/') {
                i++;
                inside_comment = CommentType::NO_COMMENT;
                offset = i + 1;
                continue;
            }
        }

        if (inside_comment == CommentType::NO_COMMENT) {
            result += json_string.substr(offset);
        }
        return result;
    };
};

#endif // CRYPTO_JSON_STRIP_JSON_COMMENTS_HPP_INCLUDED
