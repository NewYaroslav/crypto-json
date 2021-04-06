#include <iostream>
#include <array>
#include "../../include/crypto-json/crypto-json.hpp"

int main() {
    std::cout << "Hello world!" << std::endl;
    std::string src;
    crypto_json::load_file("test.json", src);
    std::string dst = crypto_json::strip_json_comments(src);
    std::cout << "dst:" << std::endl << dst << std::endl;
    std::string dst2 = crypto_json::strip_json_comments(src, true);
    std::cout << "dst2:" << std::endl << dst2 << std::endl;

    crypto_json::EncryptionAlgorithmType type = crypto_json::EncryptionAlgorithmType::USE_AES_CFB_256;

    std::array<uint8_t, 32> key;
    std::array<uint8_t, 32> iv;
    crypto_json::generate_key_or_iv(key);
    crypto_json::generate_key_or_iv(iv);

    std::cout << "key:" << std::endl << crypto_json::to_hex_string(key) << std::endl;
    std::cout << "iv:" << std::endl << crypto_json::to_hex_string(iv) << std::endl;

    std::array<uint8_t, 32> key2;
    std::array<uint8_t, 32> iv2;
    crypto_json::convert_hex_string_to_byte(crypto_json::to_hex_string(key), key2);
    crypto_json::convert_hex_string_to_byte(crypto_json::to_hex_string(iv), iv2);

    std::string encrypt_str = crypto_json::encrypt_data_with_size(type, src, key, iv);
    std::string decrypt_str = crypto_json::decrypt_data_with_size(type, encrypt_str, key2, iv2);
    std::cout << "decrypt:" << std::endl << decrypt_str << std::endl;

    if (decrypt_str != src) {
        std::cout << "decrypt error" << std::endl;
        return 0;
    }

    std::string crypto_json_str = crypto_json::to_crypto_json(src, key, iv, type, true);
    std::string crypto_json_str2 = crypto_json::to_crypto_json(src, key2, iv2, type, true);
    std::cout << "src size:" << src.size() << std::endl;
    std::cout << "crypto json size: " << crypto_json_str.size() << std::endl;

    if (crypto_json_str != crypto_json_str2) {
        std::cout << "error" << std::endl;
        return 0;
    }

    std::string str = crypto_json::to_string(crypto_json_str, key, iv, type, true);
    std::cout << "decrypt crypto json size: " << str.size() << std::endl;
    std::cout << "decrypt crypto json:" << std::endl << str << std::endl;

    /* дешифруем crypto json в класс json библиотеки nlohmann/json.hpp */
    nlohmann::json j = crypto_json::to_json(crypto_json_str, key, iv, type, true);
    std::cout << "to json:" << std::endl << j << std::endl;

    crypto_json_str = crypto_json::to_crypto_json(j, key, iv, type, true);
    std::cout << "crypto json size:" << crypto_json_str.size() << std::endl;

    nlohmann::json j2 = crypto_json::to_json(crypto_json_str, key, iv, type, true);
    std::cout << "to json:" << std::endl << j2 << std::endl;

    crypto_json::JsonSax my_sax;
    crypto_json::json::sax_parse(crypto_json_str, &my_sax);
    return 0;
}
