#include <cryptopp/hmac.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <fstream>
#include <iostream>

using namespace CryptoPP;

std::string computeHMAC(const std::string& message, const byte* key, size_t keyLength) {
    std::string mac;
    HMAC<SHA512> hmac(key, keyLength);
    StringSource(message, true, new HashFilter(hmac, new StringSink(mac)));
    return mac;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <inputfile> <outputfile> <key>\n";
        return 1;
    }

    // Read input file
    std::ifstream file(argv[1], std::ios::binary);
    std::string message((std::istreambuf_iterator<char>(file)), {});
    file.close();

    // Compute HMAC
    std::string key = argv[3];
    std::string hmac = computeHMAC(message, (const byte*)key.data(), key.size());

    // Convert to hex
    std::string hexHMAC;
    StringSource(hmac, true, new HexEncoder(new StringSink(hexHMAC)));

    // Output
    std::cout << hexHMAC << std::endl;
    std::ofstream out(argv[2]);
    out << hexHMAC;
    out.close();

    return 0;
}

