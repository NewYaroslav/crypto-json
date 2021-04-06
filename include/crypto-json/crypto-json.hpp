#ifndef CRYPTO_JSON_HPP_INCLUDED
#define CRYPTO_JSON_HPP_INCLUDED

#include "strip-json-comments.hpp"
#include "data-encryption.hpp"
#include "utilities.hpp"

#ifdef CRYPTO_JSON_USE_BROTLI
#include <brotli/compress.hpp>
#include <brotli/decompress.hpp>
#endif

#ifdef CRYPTO_JSON_USE_NLOHMANN_JSON
#include <nlohmann/json.hpp>
#endif

namespace crypto_json {

    template<class T>
    std::string to_crypto_json(
            const std::string &src,
            const T &key,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
		if (!check_ecb(type) || !check_key_length(key, type)) return std::string();

        if (use_brotly) {
#ifdef      CRYPTO_JSON_USE_BROTLI
            return encrypt_data_with_size(type, brotli::compress(src), key);
#else
            return std::string();
#endif
        } else {
            return encrypt_data_with_size(type, src, key);
        }
    }

    template<class T>
    std::string to_crypto_json(
            const std::string &src,
            const T &key,
            const T &iv,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (key.size() != iv.size()) return std::string();
        if (check_ecb(type) || !check_key_length(key, type) || key.size() != iv.size()) return std::string();

        if (use_brotly) {
#ifdef      CRYPTO_JSON_USE_BROTLI
            return encrypt_data_with_size(type, brotli::compress(src), key, iv);
#else
            return std::string();
#endif
        } else {
            return encrypt_data_with_size(type, src, key, iv);
        }
    }


    std::string to_string(const std::string &src) {
#ifdef  CRYPTO_JSON_USE_BROTLI
        return brotli::decompress(src);
#else
        return std::string();
#endif
    }

    template<class T>
    std::string to_string(
            const std::string &src,
            const T &key,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (!check_ecb(type) || !check_key_length(key, type)) return std::string();

        if (use_brotly) {
#ifdef      CRYPTO_JSON_USE_BROTLI
            return brotli::decompress(decrypt_data_with_size(type, src, key));
#else
            return std::string();
#endif
        } else {
            return decrypt_data_with_size(type, src, key);
        }
    }

    template<class T>
    std::string to_string(
            const std::string &src,
            const T &key,
            const T &iv,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (key.size() != iv.size()) return std::string();

        if (check_ecb(type) || !check_key_length(key, type) || key.size() != iv.size()) return std::string();

        if (use_brotly) {
#ifdef      CRYPTO_JSON_USE_BROTLI
            return brotli::decompress(decrypt_data_with_size(type, src, key, iv));
#else
            return std::string();
#endif
        } else {
            return decrypt_data_with_size(type, src, key, iv);
        }
    }

    bool save_file(
            const std::string &file_name,
            const std::string &src,
            const bool use_brotly) {
        create_directory(file_name, true);
        std::ofstream file(file_name, std::ios_base::binary);
        if (!file) return false;
        if (use_brotly) {
#ifdef      CRYPTO_JSON_USE_BROTLI
            std::string temp = brotli::compress(src);
            file.write((char*)temp.data(), temp.size());
#else
            file.close();
            return false;
#endif
        } else {
            file.write((char*)src.data(), src.size());
        }
        file.close();
        return true;
    }

    template<class T>
    bool save_file(
            const std::string &file_name,
            const std::string &src,
            const T &key,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (check_ecb(type) || !check_key_length(key, type)) return false;
        create_directory(file_name, true);
        std::string temp = to_crypto_json(src, key, type, use_brotly);

        std::ofstream file(file_name, std::ios_base::binary);
        if (!file) return false;
        file.write((char*)temp.data(), temp.size());
        file.close();
        return true;
    }

    template<class T>
    bool save_file(
            const std::string &file_name,
            const std::string &src,
            const T &key,
            const T &iv,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (check_ecb(type) ||
            !check_key_length(key, type) ||
            key.size() != iv.size()) return false;
        create_directory(file_name, true);
        std::string temp = to_crypto_json(src, key, iv, type, use_brotly);

        std::ofstream file(file_name, std::ios_base::binary);
        if (!file) return false;
        file.write((char*)temp.data(), temp.size());
        file.close();
        return true;
    }

    /** \brief Загрузить файл
     *
     * Данная функция работает с режимами шифрования CBC и CFB
     * \param file_name     Имя файла
     * \param key           Ключ
     * \param iv            Инициализирующий вектор
     * \param type          Тип шифрования
     * \param use_brotly    Использовать алгоритм сжатия brotly
     * \return Вернет дешифрованную строку
     */
    template<class T>
    std::string load_file(
            const std::string &file_name,
            const T &key,
            const T &iv,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (check_ecb(type) ||
            !check_key_length(key, type) ||
            key.size() != iv.size()) return std::string();
        std::string file_data;
        std::ifstream file(file_name, std::ios_base::binary);
        if(!file) return std::string();
        file.seekg(0, std::ios_base::end);
        std::ifstream::pos_type file_size = file.tellg();
        file.seekg(0);
        file_data.reserve(file_size);
        char temp;
        while(file.read((char*)&temp, sizeof(char))) file_data.push_back(temp);
        file.close();
        return to_string(file_data, key, iv, type, use_brotly);
    }

    /** \brief Загрузить файл
     *
     * Данная функция работает с режимамом шифрования ECB
     * \param file_name     Имя файла
     * \param key           Ключ
     * \param type          Тип шифрования
     * \param use_brotly    Использовать алгоритм сжатия brotly
     * \return Вернет дешифрованную строку
     */
    template<class T>
    std::string load_file(
            const std::string &file_name,
            const T &key,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        if (check_ecb(type) ||
            !check_key_length(key, type)) return std::string();
        std::string file_data;
        std::ifstream file(file_name, std::ios_base::binary);
        if(!file) return std::string();
        file.seekg(0, std::ios_base::end);
        std::ifstream::pos_type file_size = file.tellg();
        file.seekg(0);
        file_data.reserve(file_size);
        char temp;
        while(file.read((char*)&temp, sizeof(char))) file_data.push_back(temp);
        file.close();
        return to_string(file_data, key, type, use_brotly);
    }

    /** \brief Загрузить файл
     *
     * Данная функция работает только с сжатием britli
     * \param file_name     Имя файла
     * \param use_brotly    Использовать алгоритм сжатия brotly
     * \return Вернет строку
     */
    std::string load_file(
            const std::string &file_name,
            const bool use_brotly) {
        std::string file_data;
        std::ifstream file(file_name, std::ios_base::binary);
        if(!file) return std::string();
        file.seekg(0, std::ios_base::end);
        std::ifstream::pos_type file_size = file.tellg();
        file.seekg(0);
        file_data.reserve(file_size);
        char temp;
        while(file.read((char*)&temp, sizeof(char))) file_data.push_back(temp);
        file.close();
        if (use_brotly) {
#ifdef      CRYPTO_JSON_USE_BROTLI
            return to_string(file_data);
#else
            return std::string();
#endif
        }
        return file_data;
    }

#ifdef CRYPTO_JSON_USE_NLOHMANN_JSON
    using json = nlohmann::json;

    template<class T>
    json to_json(
            const std::string &src,
            const T &key,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        try {
            return json::parse(strip_json_comments(to_string(src, key, type, use_brotly)));
        } catch(...) {}
        return nullptr;
    }

    template<class T>
    json to_json(
            const std::string &src,
            const T &key,
            const T &iv,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        try {
            return json::parse(strip_json_comments(to_string(src, key, iv, type, use_brotly)));
        } catch(...) {}
        return nullptr;
    }

    template<class T>
    std::string to_crypto_json(
            const json &src,
            const T &key,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        return to_crypto_json(src.dump(), key, type, use_brotly);
    }

    template<class T>
    std::string to_crypto_json(
            const json &src,
            const T &key,
            const T &iv,
            const EncryptionAlgorithmType type,
            const bool use_brotly) {
        return to_crypto_json(src.dump(), key, iv, type, use_brotly);
    }
#endif

}; // crypto_json

#endif // CRYPTO_JSON_HPP_INCLUDED
