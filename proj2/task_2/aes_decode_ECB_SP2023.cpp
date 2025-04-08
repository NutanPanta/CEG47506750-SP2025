// CEG 47506750 sample code - AES in CTR Mode

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"

using namespace CryptoPP;

string aes_decode(string &cipher, byte key[], byte iv[])
{
    string plain;
    try
    {
        CTR_Mode<AES>::Decryption dec;
        dec.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
        StringSource s(cipher, true, new StreamTransformationFilter(dec, new StringSink(plain)));
    }
    catch (const CryptoPP::Exception &e)
    {
        cerr << "Decryption error: " << e.what() << endl;
    }
    return plain;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "usage: aes_decode infile outfile key iv" << endl;
        return 0;
    }

    fstream file1(argv[1], ios::in);
    fstream file2(argv[2], ios::out);
    
    byte key[AES::DEFAULT_KEYLENGTH];
    byte iv[AES::BLOCKSIZE];

    // Read ciphertext
    stringstream buffer;
    buffer << file1.rdbuf();
    string cipher(buffer.str());

    // Get key
    memset(key, 0, AES::DEFAULT_KEYLENGTH);
    for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++)
    {
        if (argv[3][i] != '\0')
            key[i] = (byte)argv[3][i];
        else
            break;
    }

    // Get IV
    memset(iv, 0, AES::BLOCKSIZE);
    for (int i = 0; i < AES::BLOCKSIZE; i++)
    {
        if (argv[4][i] != '\0')
            iv[i] = (byte)argv[4][i];
        else
            break;
    }

    // Print key
    string encoded;
    encoded.clear();
    StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encoded)));
    cout << "key: " << encoded << endl;

    // Print IV
    encoded.clear();
    StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encoded)));
    cout << "IV: " << encoded << endl;

    // Decrypt
    string plain = aes_decode(cipher, key, iv);
    cout << "Recovered text: " << plain << endl;
    file2 << plain;
    cout << "Plain text stored in: " << argv[2] << endl;

    file1.close();
    file2.close();
}
