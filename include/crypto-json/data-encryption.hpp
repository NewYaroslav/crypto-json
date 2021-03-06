#ifndef CRYPTO_JSON_DATA_ENCRYPTION_HPP_INCLUDED
#define CRYPTO_JSON_DATA_ENCRYPTION_HPP_INCLUDED

#include <ctime>
#include <random>
#include "AES.h"

namespace crypto_json {

    enum class EncryptionAlgorithmType {
        USE_AES_ECB_256,
        USE_AES_ECB_192,
        USE_AES_ECB_128,
        USE_AES_CBC_256,
        USE_AES_CBC_192,
        USE_AES_CBC_128,
        USE_AES_CFB_256,
        USE_AES_CFB_192,
        USE_AES_CFB_128,
    };

    size_t get_key_size(const EncryptionAlgorithmType type) noexcept {
        switch (type) {
		case EncryptionAlgorithmType::USE_AES_ECB_256:
		case EncryptionAlgorithmType::USE_AES_CBC_256:
		case EncryptionAlgorithmType::USE_AES_CFB_256:
            return 256;
            break;
        case EncryptionAlgorithmType::USE_AES_ECB_192:
        case EncryptionAlgorithmType::USE_AES_CBC_192:
        case EncryptionAlgorithmType::USE_AES_CFB_192:
            return 192;
            break;
        case EncryptionAlgorithmType::USE_AES_ECB_128:
        case EncryptionAlgorithmType::USE_AES_CBC_128:
        case EncryptionAlgorithmType::USE_AES_CFB_128:
            return 128;
            break;
        default:
            return 0;
		};
    }

    template<class T>
    inline bool check_key_length(const T& key, const EncryptionAlgorithmType type) {
        if ((get_key_size(type)/8) != key.size()) return false;
        return true;
    };

    inline bool check_ecb(const EncryptionAlgorithmType type) noexcept {
        switch (type) {
		case EncryptionAlgorithmType::USE_AES_ECB_256:
        case EncryptionAlgorithmType::USE_AES_ECB_192:
        case EncryptionAlgorithmType::USE_AES_ECB_128:
            return true;
        default:
            return false;
		};
    }

    inline void add_data_length(std::string &data, const uint32_t length) {
		const char *bytes = (const char *)&length;
		data.insert(data.end(), &bytes[0], &bytes[0] + sizeof(uint32_t));
    }

    inline uint32_t get_data_length(const std::string &data) noexcept {
        const char *bytes = data.substr(data.size() - sizeof(uint32_t), sizeof(uint32_t)).data();
        const uint32_t length = ((const uint32_t*)bytes)[0];
        return length;
    }

    /** \brief ?????????????????????? ???????????? ????????????
     * ?????? ???????????????????? ???????????????????????? ???????????????? AES ECB ?? ???????????? ???????????? 256 ??????.
     * \param data ???????????? ?????? ????????????????????
     * \param key ????????
     * \return ?????????????????????????? ????????????
     */
    template<class T>
	std::string encrypt_data_with_size(
            const EncryptionAlgorithmType type,
            const std::string &data,
            const T &key) noexcept {
		if(data.size() == 0) return std::string();
		uint32_t length = 0;
		const uint32_t key_size = get_key_size(type);
		if (!check_ecb(type) || key_size == 0) return std::string();
		AES aes(key_size);
        uint8_t *out = aes.EncryptECB((uint8_t*)data.c_str(), data.size(), (uint8_t*)key.data(), length);
        std::string temp((char*)out, (char*)out + length);
        delete[] out;

        add_data_length(temp, data.size());
        return temp;
	}

	/** \brief ?????????????????????? ???????????? ????????????
     * ?????? ???????????????????? ???????????????????????? ???????????????? AES ECB ?? ???????????? ???????????? 256 ??????.
     * \param data ???????????? ?????? ????????????????????
     * \param key ????????
     * \return ?????????????????????????? ????????????
     */
    template<class T>
	std::string encrypt_data_with_size(
            const EncryptionAlgorithmType type,
            const std::string &data,
            const T &key,
            const T &iv) noexcept {
		if(data.size() == 0) return std::string();
		uint32_t length = 0;
		const uint32_t key_size = get_key_size(type);
		if (check_ecb(type) || key_size == 0) return std::string();

		AES aes(key_size);
        uint8_t *out = nullptr;

		switch (type) {
		case EncryptionAlgorithmType::USE_AES_CBC_256:
		case EncryptionAlgorithmType::USE_AES_CBC_192:
		case EncryptionAlgorithmType::USE_AES_CBC_128:
            out = aes.EncryptCBC((uint8_t*)data.c_str(), data.size(), (uint8_t*)key.data(), (uint8_t*)iv.data(), length);
            break;
		case EncryptionAlgorithmType::USE_AES_CFB_256:
		case EncryptionAlgorithmType::USE_AES_CFB_192:
		case EncryptionAlgorithmType::USE_AES_CFB_128:
            out = aes.EncryptCFB((uint8_t*)data.c_str(), data.size(), (uint8_t*)key.data(), (uint8_t*)iv.data(), length);
            break;
        default:
            return std::string();
		};
		std::string temp((char*)out, (char*)out + length);
        delete[] out;

        add_data_length(temp, data.size());
        return temp;
	}

	/** \brief ?????????????????????? ???????????? ??????????????
     * ?????? ???????????????????? ???????????????????????? ???????????????? AES ECB ?? ???????????? ???????????? 256 ??????.
     * \param data ???????????? ???????????? ?????? ????????????????????
     * \param key ????????
     * \return ?????????????????????????? ???????????? ????????????
     */
    template<class T>
	std::string decrypt_data_with_size(
            const EncryptionAlgorithmType type,
            const std::string &data,
            const T &key) noexcept {
		if(data.size() < 4) return std::string();
		const uint32_t decrypted_data_length = get_data_length(data);
        if (decrypted_data_length > (data.size() - 4)) return std::string();

        const uint32_t key_size = get_key_size(type);
		if (!check_ecb(type) || key_size == 0) return std::string();

		try {
            AES aes(key_size);
            unsigned char *innew = aes.DecryptECB((uint8_t*)data.data(), data.size() - sizeof(uint32_t), (uint8_t*)key.data());
            std::string temp((const char*)innew, (const char*)innew + decrypted_data_length);
            delete[] innew;
            return temp;
		} catch(...) {};
		return std::string();
	}

	/** \brief ?????????????????????? ???????????? ??????????????
     * ?????? ???????????????????? ???????????????????????? ???????????????? AES ECB ?? ???????????? ???????????? 256 ??????.
     * \param data  ???????????? ???????????? ?????? ????????????????????
     * \param key   ????????
     * \param iv    ???????????????????????????????? ????????????
     * \return ?????????????????????????? ???????????? ????????????
     */
    template<class T>
	std::string decrypt_data_with_size(
            const EncryptionAlgorithmType type,
            const std::string &data,
            const T &key,
            const T &iv) noexcept {
		if(data.size() < 4) return std::string();
		const uint32_t decrypted_data_length = get_data_length(data);
        if (decrypted_data_length > (data.size() - 4)) return std::string();

        const uint32_t key_size = get_key_size(type);
		if (check_ecb(type) || key_size == 0) return std::string();

		AES aes(key_size);
		uint8_t *innew = nullptr;

		switch (type) {
		case EncryptionAlgorithmType::USE_AES_CBC_256:
		case EncryptionAlgorithmType::USE_AES_CBC_192:
		case EncryptionAlgorithmType::USE_AES_CBC_128:
            innew = aes.DecryptCBC((uint8_t*)data.data(), data.size() - sizeof(uint32_t), (uint8_t*)key.data(), (uint8_t*)iv.data());
            break;
		case EncryptionAlgorithmType::USE_AES_CFB_256:
		case EncryptionAlgorithmType::USE_AES_CFB_192:
		case EncryptionAlgorithmType::USE_AES_CFB_128:
            innew = aes.DecryptCFB((uint8_t*)data.data(), data.size() - sizeof(uint32_t), (uint8_t*)key.data(), (uint8_t*)iv.data());
            break;
        default:
            return std::string();
		};

		std::string temp((const char*)innew, (const char*)innew + decrypted_data_length);
		delete[] innew;
		return  temp;
	}


	/** \brief ?????????????????????????? ????????
     * \param src   ????????????, ?????????????? ???????? ?????????????????? ???????????????????? ??????????????
     * \param seed  ????????
     * \return ?????????????????????????????? ????????, ???????????? 32 ??????????
     */
    template<class T>
	void generate_key_or_iv(T &data, const uint32_t seed = time(0)) {
        std::mt19937 rand_engine(seed);
        /* ???????????????????? ?????????????? rand() ?? Visual Studio
         * ?????????? ???????? ???????????????????????? ???????????????????? ???
         * ???????????? ???????????????????????? ?????????????????? ?????????? ???? ???????????? ???????????????????? ???? ????????????????????.
         */
        std::uniform_int_distribution<> dist(0x00, 0xFF);
        for(size_t i = 0; i < data.size(); ++i) {
            data[i] = dist(rand_engine);
        }
	}

}; // crypto_json

#endif // CRYPTO_JSON_DATA_ENCRYPTION_HPP_INCLUDED
