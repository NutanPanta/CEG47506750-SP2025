// CEG 47506750 sample code

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

#include"cryptopp/cryptlib.h"
#include"cryptopp/hex.h"
#include"cryptopp/filters.h"
#include"cryptopp/des.h"
#include"cryptopp/aes.h"
#include"cryptopp/modes.h"

using namespace CryptoPP;

string aes_decode(string & cipher, byte key[], byte iv[])
{
    string plain;
    try {
        CBC_Mode<AES>::Decryption dec;
        dec.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
        StringSource s(cipher, true, new StreamTransformationFilter(dec, new StringSink(plain)));
    }
    catch (const CryptoPP::Exception & e) {
        cerr << "Decryption Error: " << e.what() << endl;
    }
    return plain;	
}

int main(int argc, char *argv[])
{
    fstream file1;
    fstream file2;
    byte key[AES::DEFAULT_KEYLENGTH];
    byte iv[AES::BLOCKSIZE];

    if (argc != 5) {
        cout << "usage: aes_decode infile outfile key iv" << endl;
        return 0;
    }

    file1.open(argv[1], ios::in);
    file2.open(argv[2], ios::out);

    // Reading cipher text
    stringstream buffer;
    buffer << file1.rdbuf();
    string cipher(buffer.str());

    // Get key
    memset(key, 0, AES::DEFAULT_KEYLENGTH);
    for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++) {
        if (argv[3][i] != '\0') {
            key[i] = (byte)argv[3][i];
        } else {
            break;
        }
    }

    // Get IV
    memset(iv, 0, AES::BLOCKSIZE);
    for (int i = 0; i < AES::BLOCKSIZE; i++) {
        if (argv[4][i] != '\0') {
            iv[i] = (byte)argv[4][i];
        } else {
            break;
        }
    }

    // Print key
    string encoded;
    encoded.clear();
    StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encoded)));
    cout << "Key: " << encoded << endl;

    // Print IV
    encoded.clear();
    StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encoded)));
    cout << "IV: " << encoded << endl;

    // Decode
    string plain = aes_decode(cipher, key, iv);
    cout << "Recovered text: " << plain << endl;
    file2 << plain;
    cout << "Plain text stored in: " << argv[2] << endl;

    file1.close();
    file2.close();
}
