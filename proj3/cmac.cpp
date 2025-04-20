#include <cryptopp/cmac.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <fstream>
#include <iostream>

using namespace CryptoPP;

std::string computeCMAC(const std::string& message, const byte* key, size_t keySize) {
    CMAC<AES> cmac(key, keySize);
    byte digest[AES::BLOCKSIZE];
    cmac.CalculateDigest(digest, (const byte*)message.data(), message.size());

    std::string hexDigest;
    HexEncoder encoder(new StringSink(hexDigest));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return hexDigest;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <inputfile> <outputfile> <16-byte-hex-key>\n";
        return 1;
    }

    // Read input file
    std::ifstream file(argv[1], std::ios::binary);
    std::string message((std::istreambuf_iterator<char>(file)), {});
    file.close();

    // Decode hex key
    std::string keyHex = argv[3];
    if (keyHex.length() != 32) {
        std::cerr << "Error: Key must be 32 hex characters (16 bytes).\n";
        return 1;
    }
    SecByteBlock key(16);
    StringSource(keyHex, true, new HexDecoder(new ArraySink(key, key.size())));

    // Compute CMAC
    std::string cmac = computeCMAC(message, key, key.size());

    // Output
    std::cout << cmac << std::endl;
    std::ofstream out(argv[2]);
    out << cmac;
    out.close();

    return 0;
}

