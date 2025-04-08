# README - DES Encryption/Decryption Project

## Overview
This project involves working with DES encryption and decryption programs using the Crypto++ library. The goal is to compile, execute, and modify the provided source code to change the encryption mode and make the key user-input based.

---

## Task 1: Compile and Execute DES Encryption/Decryption

### Steps for Execution:

1. **Compile the DES encryption & decryption programs**
    ```sh
    cryptog++ des_encode_SP2025.cpp -o des_e_ecb_SP2025 -lcryptopp
    cryptog++ des_decode_SP2025.cpp -o des_d_ecb_SP2025 -lcryptopp
    ```

2. **Encrypt the test files**
    ```sh
    ./des_e_ecb_SP2025 MSG1 MSG1.e
    ./des_e_ecb_SP2025 MSG2 MSG2.e
    ./des_e_ecb_SP2025 MSG3 MSG3.e
    ./des_e_ecb_SP2025 text1 text1.e
    ./des_e_ecb_SP2025 hw2.pdf.gz hw2.pdf.gz.e
    ```

3. **Decrypt the encrypted files**
    ```sh
    ./des_d_ecb_SP2025 MSG1.e MSG1.d
    ./des_d_ecb_SP2025 MSG2.e MSG2.d
    ./des_d_ecb_SP2025 MSG3.e MSG3.d
    ./des_d_ecb_SP2025 text1.e text1.d
    ./des_d_ecb_SP2025 hw2.pdf.gz.e hw2.pdf.gz.d
    ```

4. **Verify decryption using `diff`**
    ```sh
    diff MSG1 MSG1.d
    diff MSG2 MSG2.d
    diff MSG3 MSG3.d
    diff text1 text1.d
    diff hw2.pdf.gz hw2.pdf.gz.d
    ```

5. **Check byte differences in encrypted files**
    ```sh
    od -b MSG1.e
    od -b MSG2.e
    od -b MSG3.e
    ```

6. **Compare byte differences**
    ```sh
    cmp -l MSG1.e MSG2.e | wc -l
    cmp -l MSG1.e MSG3.e | wc -l
    ```

---

## Task 2: Modify Encryption Mode to CBC

### Steps for Execution:

1. **Edit the encryption source file**
    ```sh
    vim des_encode_SP2025.cpp
    ```
    Replace:
    ```cpp
    string des_encode(string & plain,byte key[])
    {
    	string cipher;
    	try
    	{
    		//cout << "plain text: " << plain << endl;
    		ECB_Mode<DES>::Encryption enc;
    		enc.SetKey(key, DES::DEFAULT_KEYLENGTH);
    		StringSource(plain, true, new StreamTransformationFilter(enc, new StringSink(cipher)));//add padding by StreamTransformationFilter 
    	}
    	catch(const CryptoPP::Exception& e)
    	{
    		cerr << e.what() << endl;
    		exit(1);
    	}
    	return cipher;
    }
    ```
    With:
    ```cpp
    string des_encode(string & plain,byte key[], byte iv[])
    {
    	string cipher;
    	try
    	{
    		//cout << "plain text: " << plain << endl;
    		CBC_Mode<DES>::Encryption enc;
    		enc.SetKeyWithIV(key, DES::DEFAULT_KEYLENGTH, iv);
    		StringSource(plain, true, new StreamTransformationFilter(enc, new StringSink(cipher)));//add padding by StreamTransformationFilter 
    	}
    	catch(const CryptoPP::Exception& e)
    	{
    		cerr << e.what() << endl;
    		exit(1);
    	}
    	return cipher;
    }
    ```
    Add this in main function:
    ```cpp
    byte iv[DES::DEFAULT_KEYLENGTH]= {0};
    ```
    And Finally pass the key variable to decode function:
    ```cpp
    string cipher=des_decode(cipher,key,iv);
    ```
2. **Edit the decryption source file**
    ```sh
    vim des_decode_SP2025.cpp
    ```
    Replace:
    ```cpp
    string des_decode(string & cipher,byte key[])
    {
    	string plain;
    	//decryption
    	try
    	{
    		ECB_Mode< DES >::Decryption dec;
    		dec.SetKey(key, DES::DEFAULT_KEYLENGTH);
    		StringSource s(cipher, true, new StreamTransformationFilter(dec, new StringSink(plain)));  
    		cout << "recovered text: " << plain<< endl;
    	}
    	catch(const CryptoPP::Exception& e)
    	{
    		cerr << e.what() << endl;
    		exit(1);
    	}
    	return plain;	
    }
    ```
    With:
    ```cpp
    string des_decode(string & cipher,byte key[], byte iv[])
    {
    	string plain;
    	//decryption
    	try
    	{
    		CBC_Mode< DES >::Decryption dec;
    		dec.SetKeyWithIV(key, DES::DEFAULT_KEYLENGTH, iv);
    		StringSource s(cipher, true, new StreamTransformationFilter(dec, new StringSink(plain)));  
    		cout << "recovered text: " << plain<< endl;
    	}
    	catch(const CryptoPP::Exception& e)
    	{
    		cerr << e.what() << endl;
    		exit(1);
    	}
    	return plain;	
    }
    ```
    Add this in main function:
    ```cpp
    byte iv[DES::DEFAULT_KEYLENGTH]= {0};
    ```
    And Finally pass the key variable to decode function:
    ```cpp
    string cipher=des_decode(cipher,key,iv);
    ```

3. **Compile the modified programs**
    ```sh
    cryptog++ des_encode_SP2025.cpp -o des_e_cbc_SP2025 -lcryptopp
    cryptog++ des_decode_SP2025.cpp -o des_d_cbc_SP2025 -lcryptopp
    ```
4. **Encrypt the test files**
    ```sh
    ./des_e_cbc_SP2025 MSG1 MSG1.e
    ./des_e_cbc_SP2025 MSG2 MSG2.e
    ./des_e_cbc_SP2025 MSG3 MSG3.e
    ./des_e_cbc_SP2025 text1 text1.e
    ./des_e_cbc_SP2025 hw2.pdf.gz hw2.pdf.gz.e
    ```

5. **Decrypt the encrypted files**
    ```sh
    ./des_d_cbc_SP2025 MSG1.e MSG1.d
    ./des_d_cbc_SP2025 MSG2.e MSG2.d
    ./des_d_cbc_SP2025 MSG3.e MSG3.d
    ./des_d_cbc_SP2025 text1.e text1.d
    ./des_d_cbc_SP2025 hw2.pdf.gz.e hw2.pdf.gz.d
    ```

6. **Verify decryption using `diff`**
    ```sh
    diff MSG1 MSG1.d
    diff MSG2 MSG2.d
    diff MSG3 MSG3.d
    diff text1 text1.d
    diff hw2.pdf.gz hw2.pdf.gz.d
    ```

---

## Task 3: Modify Program to Accept Key from Command Line

### Steps for Execution:

1. **Modify encryption file to remove hardcoded key**
   
    Replace:
    ```cpp
    byte key[DES::DEFAULT_KEYLENGTH] = {'1','2','3','4','a','b','c','d'};
    ```
    With:
    ```cpp
    byte key[DES::DEFAULT_KEYLENGTH];
    strncpy((char*)key, argv[3], DES::DEFAULT_KEYLENGTH);
    ```
    Modify `main` function to accept key as the 4th argument:
    ```cpp
	if(argc!=3)
	{
		cout<<"usage:des_encode infile outfile" << endl;
	} else if(argc!=4) {	
		cout<<"Encode key not provided" << endl;
	}
    ```

2. **Modify decryption file**

    Replace:
    ```cpp
    byte key[DES::DEFAULT_KEYLENGTH] = {'1','2','3','4','a','b','c','d'};
    ```
    With:
    ```cpp
    byte key[DES::DEFAULT_KEYLENGTH];
    strncpy((char*)key, argv[3], DES::DEFAULT_KEYLENGTH);
    ```
    Modify `main` function:
    ```cpp
	if(argc!=3)
	{
		cout<<"usage:des_encode infile outfile" << endl;
	} else if(argc!=4) {	
		cout<<"Encode key not provided" << endl;
	}
    ```

3. **Compile the updated programs**
    ```sh
    cryptog++ des_encode_SP2025.cpp -o des_e_cbc_nh_SP2025 -lcryptopp
    cryptog++ des_decode_SP2025.cpp -o des_d_cbc_nh_SP2025 -lcryptopp
    ```

4. **Encrypt files with user-input key**
    ```sh
    ./des_e_cbc_nh_SP2025 MSG1 MSG1.e mysecretk
    ./des_e_cbc_nh_SP2025 MSG2 MSG2.e mysecretk
    ./des_e_cbc_nh_SP2025 MSG3 MSG3.e mysecretk
    ./des_e_cbc_nh_SP2025 text1 text1.e mysecretk
    ./des_e_cbc_nh_SP2025 hw2.pdf.gz hw2.pdf.gz.e mysecretk
    ```

5. **Decrypt files with user-input key**
    ```sh
    ./des_d_cbc_nh_SP2025 MSG1.e MSG1.d mysecretk
    ./des_d_cbc_nh_SP2025 MSG2.e MSG2.d mysecretk
    ./des_d_cbc_nh_SP2025 MSG3.e MSG3.d mysecretk
    ./des_d_cbc_nh_SP2025 text1.e text1.d mysecretk
    ./des_d_cbc_nh_SP2025 hw2.pdf.gz.e hw2.pdf.gz.d mysecretk
    ```

6. **Verify decryption using `diff`**
    ```sh
    diff MSG1 MSG1.d
    diff MSG2 MSG2.d
    diff MSG3 MSG3.d
    diff text1 text1.d
    diff hw2.pdf.gz hw2.pdf.gz.d
    ```
