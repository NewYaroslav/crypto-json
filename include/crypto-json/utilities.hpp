#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>
#include <dir.h>

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

}

#endif // UTILITIES_HPP_INCLUDED
