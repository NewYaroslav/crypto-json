#include <iostream>
#include "../../include/crypto-json/strip-json-comments.hpp"
#include "../../include/crypto-json/utilities.hpp"

int main() {
    std::cout << "Hello world!" << std::endl;
    std::string src;
    crypto_json::load_file("test.json", src);
    std::string dst = crypto_json::strip_json_comments(src);
    std::cout << "dst:" << std::endl << dst << std::endl;
    std::string dst2 = crypto_json::strip_json_comments(src, true);
    std::cout << "dst2:" << std::endl << dst2 << std::endl;
    return 0;
}
