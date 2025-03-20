#include <iostream>
#include <string>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/des.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <vector>
#include <openssl/bio.h>
#include <openssl/evp.h>

class CryptoToolbox {
public:
    // AES Encryption
    static std::string AESEncrypt(const std::string &plainText, const std::string &key) {
        AES_KEY encryptKey;
        AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &encryptKey);

        std::string cipherText(plainText.size(), '\0');
        AES_encrypt(reinterpret_cast<const unsigned char*>(plainText.c_str()), 
                    reinterpret_cast<unsigned char*>(&cipherText[0]), 
                    &encryptKey);

        return cipherText;
    }

    // AES Decryption
    static std::string AESDecrypt(const std::string &cipherText, const std::string &key) {
        AES_KEY decryptKey;
        AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &decryptKey);

        std::string plainText(cipherText.size(), '\0');
        AES_decrypt(reinterpret_cast<const unsigned char*>(cipherText.c_str()), 
                    reinterpret_cast<unsigned char*>(&plainText[0]), 
                    &decryptKey);

        return plainText;
    }

    // DES Encryption
    static std::string DESEncrypt(const std::string &plainText, const std::string &key) {
        DES_cblock keyBlock;
        DES_key_schedule schedule;

        memcpy(keyBlock, key.c_str(), key.size() > 8 ? 8 : key.size());
        DES_set_key_unchecked(&keyBlock, &schedule);

        std::string cipherText(plainText.size(), '\0');
        DES_cblock inputText;
        DES_cblock outputText;

        for (size_t i = 0; i < plainText.size(); i += 8) {
            memcpy(inputText, plainText.c_str() + i, 8);
            DES_ecb_encrypt(&inputText, &outputText, &schedule, DES_ENCRYPT);
            memcpy(&cipherText[i], outputText, 8);
        }

        return cipherText;
    }

    // DES Decryption
    static std::string DESDecrypt(const std::string &cipherText, const std::string &key) {
        DES_cblock keyBlock;
        DES_key_schedule schedule;

        memcpy(keyBlock, key.c_str(), key.size() > 8 ? 8 : key.size());
        DES_set_key_unchecked(&keyBlock, &schedule);

        std::string plainText(cipherText.size(), '\0');
        DES_cblock inputText;
        DES_cblock outputText;

        for (size_t i = 0; i < cipherText.size(); i += 8) {
            memcpy(inputText, cipherText.c_str() + i, 8);
            DES_ecb_encrypt(&inputText, &outputText, &schedule, DES_DECRYPT);
            memcpy(&plainText[i], outputText, 8);
        }

        return plainText;
    }

    // RSA Key Pair Generation
    static void GenerateRSAKeyPair(std::string &publicKey, std::string &privateKey) {
        RSA *rsa = RSA_generate_key(2048, RSA_F4, nullptr, nullptr);
        BIO *pub = BIO_new(BIO_s_mem());
        BIO *pri = BIO_new(BIO_s_mem());

        PEM_write_bio_RSAPublicKey(pub, rsa);
        PEM_write_bio_RSAPrivateKey(pri, rsa, nullptr, nullptr, 0, nullptr, nullptr);

        size_t pubLen = BIO_pending(pub);
        size_t priLen = BIO_pending(pri);

        publicKey.resize(pubLen);
        privateKey.resize(priLen);

        BIO_read(pub, &publicKey[0], pubLen);
        BIO_read(pri, &privateKey[0], priLen);

        BIO_free_all(pub);
        BIO_free_all(pri);
        RSA_free(rsa);
    }

    // RSA Encryption
    static std::string RSAEncrypt(const std::string &plainText, const std::string &publicKey) {
        RSA *rsa = RSA_new();
        BIO *keybio = BIO_new_mem_buf((void*)publicKey.c_str(), -1);
        PEM_read_bio_RSAPublicKey(keybio, &rsa, nullptr, nullptr);

        std::string cipherText(RSA_size(rsa), '\0');
        RSA_public_encrypt(plainText.size(), 
                           reinterpret_cast<const unsigned char*>(plainText.c_str()), 
                           reinterpret_cast<unsigned char*>(&cipherText[0]), 
                           rsa, RSA_PKCS1_PADDING);

        BIO_free_all(keybio);
        RSA_free(rsa);

        return cipherText;
    }

    // RSA Decryption
    static std::string RSADecrypt(const std::string &cipherText, const std::string &privateKey) {
        RSA *rsa = RSA_new();
        BIO *keybio = BIO_new_mem_buf((void*)privateKey.c_str(), -1);
        PEM_read_bio_RSAPrivateKey(keybio, &rsa, nullptr, nullptr);

        std::string plainText(RSA_size(rsa), '\0');
        RSA_private_decrypt(cipherText.size(), 
                            reinterpret_cast<const unsigned char*>(cipherText.c_str()), 
                            reinterpret_cast<unsigned char*>(&plainText[0]), 
                            rsa, RSA_PKCS1_PADDING);

        BIO_free_all(keybio);
        RSA_free(rsa);

        return plainText;
    }

    // Simple Stream Cipher Encryption
    static std::string StreamEncrypt(const std::string &plainText, const std::string &key) {
        std::string cipherText(plainText.size(), '\0');
        for (size_t i = 0; i < plainText.size(); ++i) {
            cipherText[i] = plainText[i] ^ key[i % key.size()];
        }
        return cipherText;
    }

    // Simple Stream Cipher Decryption
    static std::string StreamDecrypt(const std::string &cipherText, const std::string &key) {
        std::string plainText(cipherText.size(), '\0');
        for (size_t i = 0; i < cipherText.size(); ++i) {
            plainText[i] = cipherText[i] ^ key[i % key.size()];
        }
        return plainText;
    }

    // Caesar Cipher Encryption
    static std::string CaesarEncrypt(const std::string &plainText, int shift) {
        std::string cipherText = plainText;
        for (char &c : cipherText) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
        }
        return cipherText;
    }

    // Caesar Cipher Decryption
    static std::string CaesarDecrypt(const std::string &cipherText, int shift) {
        return CaesarEncrypt(cipherText, 26 - shift);
    }

    // MD5 Hash
    static std::string MD5Hash(const std::string &input) {
        unsigned char hash[MD5_DIGEST_LENGTH];
        MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
        std::string output;
        for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            char buf[3];
            snprintf(buf, sizeof(buf), "%02x", hash[i]);
            output.append(buf);
        }
        return output;
    }

    // SHA1 Hash
    static std::string SHA1Hash(const std::string &input) {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
        std::string output;
        for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
            char buf[3];
            snprintf(buf, sizeof(buf), "%02x", hash[i]);
            output.append(buf);
        }
        return output;
    }

    // SHA256 Hash
    static std::string SHA256Hash(const std::string &input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);
        std::string output;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            char buf[3];
            snprintf(buf, sizeof(buf), "%02x", hash[i]);
            output.append(buf);
        }
        return output;
    }

    // Hill Cipher Encryption
    static std::string HillEncrypt(const std::string &plainText, const std::vector<std::vector<int>> &keyMatrix) {
        int n = keyMatrix.size();
        std::string cipherText;
        for (size_t i = 0; i < plainText.size(); i += n) {
            std::vector<int> block(n, 0);
            for (int j = 0; j < n; ++j) {
                if (i + j < plainText.size()) {
                    block[j] = plainText[i + j] - 'A';
                }
            }
            for (int j = 0; j < n; ++j) {
                int sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum += keyMatrix[j][k] * block[k];
                }
                cipherText += (sum % 26) + 'A';
            }
        }
        return cipherText;
    }

    // Hill Cipher Decryption
    static std::string HillDecrypt(const std::string &cipherText, const std::vector<std::vector<int>> &inverseKeyMatrix) {
        int n = inverseKeyMatrix.size();
        std::string plainText;
        for (size_t i = 0; i < cipherText.size(); i += n) {
            std::vector<int> block(n, 0);
            for (int j = 0; j < n; ++j) {
                if (i + j < cipherText.size()) {
                    block[j] = cipherText[i + j] - 'A';
                }
            }
            for (int j = 0; j < n; ++j) {
                int sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum += inverseKeyMatrix[j][k] * block[k];
                }
                plainText += (sum % 26) + 'A';
            }
        }
        return plainText;
    }

    // Base64 Encode
    static std::string Base64Encode(const std::string &input) {
        BIO *bio, *b64;
        BUF_MEM *bufferPtr;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        BIO_write(bio, input.c_str(), input.size());
        BIO_flush(bio);
        BIO_get_mem_ptr(bio, &bufferPtr);

        std::string encodedData(bufferPtr->data, bufferPtr->length);
        BIO_free_all(bio);

        return encodedData;
    }

    // Base64 Decode
    static std::string Base64Decode(const std::string &input) {
        BIO *bio, *b64;
        char *buffer = (char*)malloc(input.size());
        memset(buffer, 0, input.size());

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new_mem_buf(input.c_str(), input.size());
        bio = BIO_push(b64, bio);

        int decodedLength = BIO_read(bio, buffer, input.size());
        std::string decodedData(buffer, decodedLength);
        BIO_free_all(bio);
        free(buffer);

        return decodedData;
    }
};

int main() {
    // Example usage
    std::string aesKey = "thisisaverysecret";
    std::string plainText = "Hello, World!";
    std::string cipherText = CryptoToolbox::AESEncrypt(plainText, aesKey);
    std::string decryptedText = CryptoToolbox::AESDecrypt(cipherText, aesKey);

    std::cout << "AES Encrypted: " << cipherText << std::endl;
    std::cout << "AES Decrypted: " << decryptedText << std::endl;

    std::string publicKey, privateKey;
    CryptoToolbox::GenerateRSAKeyPair(publicKey, privateKey);

    cipherText = CryptoToolbox::RSAEncrypt(plainText, publicKey);
    decryptedText = CryptoToolbox::RSADecrypt(cipherText, privateKey);

    std::cout << "RSA Encrypted: " << cipherText << std::endl;
    std::cout << "RSA Decrypted: " << decryptedText << std::endl;

    // DES Example usage
    std::string desKey = "deskey12";
    std::string desPlainText = "Hello, DES!";
    std::string desCipherText = CryptoToolbox::DESEncrypt(desPlainText, desKey);
    std::string desDecryptedText = CryptoToolbox::DESDecrypt(desCipherText, desKey);

    std::cout << "DES Encrypted: " << desCipherText << std::endl;
    std::cout << "DES Decrypted: " << desDecryptedText << std::endl;

    // Stream Cipher Example usage
    std::string streamKey = "streamkey";
    std::string streamPlainText = "Hello, Stream!";
    std::string streamCipherText = CryptoToolbox::StreamEncrypt(streamPlainText, streamKey);
    std::string streamDecryptedText = CryptoToolbox::StreamDecrypt(streamCipherText, streamKey);

    std::cout << "Stream Encrypted: " << streamCipherText << std::endl;
    std::cout << "Stream Decrypted: " << streamDecryptedText << std::endl;

    // Caesar Cipher Example usage
    std::string caesarPlainText = "Hello, Caesar!";
    int shift = 3;
    std::string caesarCipherText = CryptoToolbox::CaesarEncrypt(caesarPlainText, shift);
    std::string caesarDecryptedText = CryptoToolbox::CaesarDecrypt(caesarCipherText, shift);

    std::cout << "Caesar Encrypted: " << caesarCipherText << std::endl;
    std::cout << "Caesar Decrypted: " << caesarDecryptedText << std::endl;

    // Hash Example usage
    std::string hashInput = "Hello, Hash!";
    std::string md5Hash = CryptoToolbox::MD5Hash(hashInput);
    std::string sha1Hash = CryptoToolbox::SHA1Hash(hashInput);
    std::string sha256Hash = CryptoToolbox::SHA256Hash(hashInput);

    std::cout << "MD5 Hash: " << md5Hash << std::endl;
    std::cout << "SHA1 Hash: " << sha1Hash << std::endl;
    std::cout << "SHA256 Hash: " << sha256Hash << std::endl;

    // Hill Cipher Example usage
    std::vector<std::vector<int>> keyMatrix = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    std::vector<std::vector<int>> inverseKeyMatrix = {{8, 5, 10}, {21, 8, 21}, {21, 12, 8}};
    std::string hillPlainText = "HELLOHILL";
    std::string hillCipherText = CryptoToolbox::HillEncrypt(hillPlainText, keyMatrix);
    std::string hillDecryptedText = CryptoToolbox::HillDecrypt(hillCipherText, inverseKeyMatrix);

    std::cout << "Hill Encrypted: " << hillCipherText << std::endl;
    std::cout << "Hill Decrypted: " << hillDecryptedText << std::endl;

    // Base64 Example usage
    std::string base64Input = "Hello, Base64!";
    std::string base64Encoded = CryptoToolbox::Base64Encode(base64Input);
    std::string base64Decoded = CryptoToolbox::Base64Decode(base64Encoded);

    std::cout << "Base64 Encoded: " << base64Encoded << std::endl;
    std::cout << "Base64 Decoded: " << base64Decoded << std::endl;

    return 0;
}
// g++ src/tools/CryptoToolbox.cpp -o bin/CryptoToolbox -I/home/chenliguo/.conan2/p/opens0aa3b75222f02/p/include -I/home/chenliguo/.conan2/p/zlib9780dc2008618/p/include -L/home/chenliguo/.conan2/p/opens0aa3b75222f02/p/lib -L/home/chenliguo/.conan2/p/zlib9780dc2008618/p/lib -lssl -ldl -lpthread -lcrypto -ldl -lrt -lpthread -lz
