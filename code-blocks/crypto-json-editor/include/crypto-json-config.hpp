#ifndef CRYPTO_JSON_EDITOR_CRYPTO_JSON_CONFIG_HPP_INCLUDED
#define CRYPTO_JSON_EDITOR_CRYPTO_JSON_CONFIG_HPP_INCLUDED

#include <crypto-json/crypto-json.hpp>

class CryptoJsonConfig {
public:
    std::string path;
    std::vector<uint8_t> key;
    std::vector<uint8_t> iv;
    char key_buffer[65];
    char iv_buffer[65];
    bool use_brotly = true;
    bool use_encryption = true;
    bool is_init = false;

    crypto_json::EncryptionAlgorithmType type;

    void clear() {
        std::fill(key.begin(), key.end(), '\0');
        std::fill(iv.begin(), iv.end(), '\0');
        std::fill(key_buffer, key_buffer + sizeof(key_buffer), '\0');
        std::fill(iv_buffer, iv_buffer + sizeof(iv_buffer), '\0');
    }

    void clear_key() {
        std::fill(key.begin(), key.end(), '\0');
    }

    void clear_iv() {
        std::fill(iv.begin(), iv.end(), '\0');
    }

    void clear_key_buffer() {
        std::fill(key_buffer, key_buffer + sizeof(key_buffer), '\0');
    }

    void clear_iv_buffer() {
        std::fill(iv_buffer, iv_buffer + sizeof(iv_buffer), '\0');
    }

    CryptoJsonConfig() {
        clear();
    }
};

#endif // CRYPTO_JSON_EDITOR_CRYPTO_JSON_CONFIG_HPP_INCLUDED
