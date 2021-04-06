#ifndef CRYPTO_JSON_UTILITIES_HPP_INCLUDED
#define CRYPTO_JSON_UTILITIES_HPP_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>
#include <dir.h>

#ifdef CRYPTO_JSON_USE_NLOHMANN_JSON
#include <nlohmann/json.hpp>
#endif

#if defined(_WIN32)
#ifndef __MINGW32__
#include <Windows.h>
#else
#include <windows.h>
#endif
#endif

namespace crypto_json {

    /** \brief Check for file existence
     * \param file_name File name
     * \return Returns true if the file exists
     */
    bool check_file(const std::string &file_name) {
        std::ifstream file;
        file.open(file_name);
        if(!file) return false;
        file.close();
        return true;
    }

    /** \brief Load whole file into std :: string
     * \param file_name File name
     * \param file_data File data
     * \return File size, will return -1 if the file could not be opened
     */
    int load_file(const std::string &file_name, std::string &file_data) {
        std::ifstream file(file_name, std::ios_base::binary);
        if(!file) return -1;
        file.seekg(0, std::ios_base::end);
        std::ifstream::pos_type file_size = file.tellg();
        file.seekg(0);
        file_data.reserve(file_size);
        char temp;
        while(file.read((char*)&temp, sizeof(char))) file_data.push_back(temp);
        file.close();
        return file_data.size();
    }

    /** \brief Write the entire file from the buffer
     * \param file_name File name
     * \param file_data File data
     * \return File size, will return -1 if the file could not be written
     */
    int write_file(const std::string &file_name, std::string &file_data) {
        std::ofstream file(file_name, std::ios_base::binary);
        if(!file) return -1;
        file.write((char*)file_data.c_str(), file_data.size());
        file.close();
        return file_data.size();
    }

    /** \brief Разобрать путь на составляющие
     * Данная функция парсит путь, например C:/Users\\user/Downloads разложит на
     * C:, Users, user и Downloads
     * \param path путь, который надо распарсить
     * \param output_list список полученных элементов
     */
    void parse_path(std::string path, std::vector<std::string> &output_list) {
        if(path.back() != '/' && path.back() != '\\') path += "/";
        std::size_t start_pos = 0;
        while(true) {
            std::size_t found_beg = path.find_first_of("/\\~", start_pos);
            if(found_beg != std::string::npos) {
                std::size_t len = found_beg - start_pos;
                if(len > 0) {
                    if(output_list.size() == 0 && path.size() > 3 && path.substr(0, 2) == "~/") {
                        output_list.push_back(path.substr(0, 2));
                    } else
                    if(output_list.size() == 0 && path.size() > 2 && path.substr(0, 1) == "/") {
                        output_list.push_back(path.substr(0, 1));
                    }
                    output_list.push_back(path.substr(start_pos, len));
                }
                start_pos = found_beg + 1;
            } else break;
        }
    }

    /** \brief Создать директорию
     * \param path директория, которую необходимо создать
     * \param is_file Флаг, по умолчанию false. Если указать true, последний раздел пути будет являться именем файла и не будет считаться "папкой".
     */
    void create_directory(std::string path, const bool is_file = false) {
        std::vector<std::string> dir_list;
        parse_path(path, dir_list);
        std::string name;
        size_t dir_list_size = is_file ? dir_list.size() - 1 : dir_list.size();
        for(size_t i = 0; i < dir_list_size; i++) {
            if(i > 0) name += dir_list[i] + "/";
            else if(i == 0 &&
                (dir_list[i] == "/" ||
                dir_list[i] == "~/")) {
                name += dir_list[i];
            } else name += dir_list[i] + "/";
            if (dir_list[i] == ".." ||
                dir_list[i] == "/" ||
                dir_list[i] == "~/") continue;
            mkdir(name.c_str());
        }
    }

    template <typename I>
    std::string n2hexstr(I w, size_t hex_len = sizeof(I)<<1) {
        static const char* digits = "0123456789ABCDEF";
        std::string rc(hex_len,'0');
        for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
            rc[i] = digits[(w>>j) & 0x0f];
        return rc;
    }

    template<class T>
    std::string to_hex_string(const T &source) {
        std::string temp;
        for(size_t i = 0; i < source.size(); ++i) {
#           if(0)
            std::stringstream stream;
            stream
                << std::uppercase
                << std::setfill ('0')
                << std::setw(2)
                << std::hex
                << (int)source[i];
            temp += std::string(stream.str());
#           endif
            temp += n2hexstr(source[i]);
        }
        return temp;
    }

    /** \brief Преобразовать строку hex в массив данных
     * \param source Строка Hex
     * \return Массив данных
     */
    template<class T>
    bool convert_hex_string_to_byte(const std::string &source, T &binary) {
        if (std::string::npos != source.find_first_not_of("0123456789ABCDEFabcdef")) {
            // you can throw exception here
            return false;
        }

        union {
            uint64_t binary;
            char byte[8];
        } value{};

        auto size = source.size(), offset = (size % 16);
        // T binary;
        // binary.reserve((size + 1) / 2);

        size_t k = 0;
        if (offset) {
            value.binary = std::stoull(source.substr(0, offset), nullptr, 16);
            for (auto index = (offset + 1) / 2; index--;){
                //binary.emplace_back(value.byte[index]);
                binary[k++] = value.byte[index];
            }
        }

        for (; offset < size; offset += 16) {
            value.binary = std::stoull(source.substr(offset, 16), nullptr, 16);
            for (auto index = 8; index--;){
                //binary.emplace_back(value.byte[index]);
                binary[k++] = value.byte[index];
            }
        }

        // return binary;
        return true;
    }

#   if defined(_WIN32)

    /** \brief Скопировать в буфер обмена
     * \param text  Строка, которая будет скопирована в буфер обмена
     */
    void to_clipboard(const std::string &text) {
        if (OpenClipboard(0)) {
            EmptyClipboard();
            char *hBuff = (char *) GlobalAlloc(GMEM_FIXED, text.size() + 1);
            strcpy(hBuff, (char *)text.c_str());
            SetClipboardData(CF_TEXT, hBuff);
            CloseClipboard();
        }
    }
#   endif


#ifdef CRYPTO_JSON_USE_NLOHMANN_JSON
    using json = nlohmann::json;

    class JsonSax : nlohmann::json_sax<json> {
    public:
        std::vector<std::pair<int, std::string>> errors;

        JsonSax() {};
        virtual ~JsonSax() {};


        // called when null is parsed
        bool null() {
            std::cout << "null" << std::endl;
            return true;
        };

        // called when a boolean is parsed; value is passed
        bool boolean(bool val) {return true;};

        // called when a signed or unsigned integer number is parsed; value is passed
        bool number_integer(number_integer_t val) {return true;};
        bool number_unsigned(number_unsigned_t val) {return true;};

        // called when a floating-point number is parsed; value and original string is passed
        bool number_float(number_float_t val, const string_t& s) {return true;};

        // called when a string is parsed; value is passed and can be safely moved away
        bool string(string_t& val) {return true;};
        // called when a binary value is parsed; value is passed and can be safely moved away
        bool binary(binary_t& val) {return true;};

        // called when an object or array begins or ends, resp. The number of elements is passed (or -1 if not known)
        bool start_object(std::size_t elements) {return true;};
        bool end_object(){return true;};
        bool start_array(std::size_t elements) {return true;};
        bool end_array(){return true;};
        // called when an object key is parsed; value is passed and can be safely moved away
        bool key(string_t& val) { return true; };

        // called when a parse error occurs; byte position, the last token, and an exception is passed
        bool parse_error(std::size_t position, const std::string& last_token, const nlohmann::detail::exception& ex) {
            errors.push_back(std::make_pair(position, ex.what()));
            return true;
        }
    };
#endif
}

#endif // CRYPTO_JSON_UTILITIES_HPP_INCLUDED
