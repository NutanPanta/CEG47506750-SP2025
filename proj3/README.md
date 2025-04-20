# README - HMAC-SHA512 and CMAC-AES128 Project

## Overview

This project demonstrates the computation and verification of HMAC-SHA512 and CMAC-AES128 message authentication codes using the Crypto++ library (C++) and OpenSSL command-line tools. Tasks include writing C++ programs for HMAC and CMAC, compiling and running them on `fry.cs.wright.edu`, and validating outputs against OpenSSL.

---

## Task 1: Compute HMAC-SHA512 Using Crypto++

### Steps for Execution:

1. **Compile the HMAC-SHA512 Program**

   ```sh
   cryptog++ hmac.cpp -lcryptopp -o hmacsha512
   ```

2. **Run HMAC-SHA512 on Test Files**

   ```sh
   ./hmacsha512 MSG2 MSG2.hmac w043nrp
   ./hmacsha512 MSG3 MSG3.hmac w043nrp
   ./hmacsha512 text1 text1.hmac w043nrp
   ./hmacsha512 hw2.pdf.gz hw2.pdf.gz.hmac w043nrp
   ```

---

## Task 2: Verify HMAC-SHA512 with OpenSSL

### Steps for Execution:

1. **Compute HMAC-SHA512 Using OpenSSL**

   ```sh
   openssl dgst -sha512 -hmac "w043nrp" MSG1
   openssl dgst -sha512 -hmac "w043nrp" MSG2
   openssl dgst -sha512 -hmac "w043nrp" MSG3
   openssl dgst -sha512 -hmac "w043nrp" text1
   openssl dgst -sha512 -hmac "w043nrp" hw2.pdf.gz
   ```

2. **Encrypt the test files**

   - Compared the hex output from your C++ program with the OpenSSL command output for each file. They all match.

## Task 3: Compute CMAC-AES128 Using Crypto++

### Steps for Execution:

1. **Compile the CMAC-AES128 Program**

   ```sh
   cryptog++ cmac.cpp -lcryptopp -o cmac_aes
   ```

2. **Run HMAC-SHA512 on Test Files**

   ```sh
   ./cmac_aes MSG1 MSG1.cmac 00112233445566778899aabbccddeeff
   ./cmac_aes MSG2 MSG2.cmac 00112233445566778899aabbccddeeff
   ./cmac_aes MSG3 MSG3.cmac 00112233445566778899aabbccddeeff
   ./cmac_aes text1 text1.cmac 00112233445566778899aabbccddeeff
   ./cmac_aes hw2.pdf.gz hw2.pdf.gz.cmac 00112233445566778899aabbccddeeff
   ```

## Task 4: Verify CMAC-AES128 with OpenSSL

### Steps for Execution:

1. **Compute CMAC-AES128 Using OpenSSL**

   ```sh
   openssl dgst -mac cmac -sha1 -macopt cipher:aes-128-cbc -macopt hexkey:00112233445566778899aabbccddeeff MSG1
   openssl dgst -mac cmac -sha1 -macopt cipher:aes-128-cbc -macopt hexkey:00112233445566778899aabbccddeeff MSG2
   openssl dgst -mac cmac -sha1 -macopt cipher:aes-128-cbc -macopt hexkey:00112233445566778899aabbccddeeff MSG3
   openssl dgst -mac cmac -sha1 -macopt cipher:aes-128-cbc -macopt hexkey:00112233445566778899aabbccddeeff text1
   openssl dgst -mac cmac -sha1 -macopt cipher:aes-128-cbc -macopt hexkey:00112233445566778899aabbccddeeff hw2.pdf.gz
   ```

2. **Encrypt the test files**

   - Compared the hex output from your C++ program with the OpenSSL command output for each file. They all match.

---
