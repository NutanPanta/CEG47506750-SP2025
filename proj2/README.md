# README - DES Encryption/Decryption Project

## Overview

This project involves working with DES encryption and decryption programs using the Crypto++ library. The goal is to compile, execute, and modify the provided source code to change the encryption mode and make the key user-input based.

---

## Task 1

### Steps for Execution:

1. **Compile the DES encryption & decryption programs**

   ```sh
   cryptog++ aes_encode_ECB_SP2023.cpp.cpp -o des_e_ecb_SP2023 -lcryptopp
   cryptog++ aes_decode_ECB_SP2023.cpp.cpp -o des_d_ecb_SP2023 -lcryptopp
   ```

2. **Encrypt the test files**

   ```sh
   ./des_e_ecb_SP2023 MSG1 MSG1.e w043nrp 1a2b3c4d5e6f7g
   ./des_e_ecb_SP2023 MSG2 MSG2.e w043nrp 1a2b3c4d5e6f7g
   ./des_e_ecb_SP2023 MSG3 MSG3.e w043nrp 1a2b3c4d5e6f7g
   ./des_e_ecb_SP2023 text1 text1.e w043nrp 1a2b3c4d5e6f7g
   ```

3. **Decrypt the encrypted files**

   ```sh
   ./des_d_ecb_SP2023 MSG1.e MSG1.d w043nrp 1a2b3c4d5e6f7g
   ./des_d_ecb_SP2023 MSG2.e MSG2.d w043nrp 1a2b3c4d5e6f7g
   ./des_d_ecb_SP2023 MSG3.e MSG3.d w043nrp 1a2b3c4d5e6f7g
   ./des_d_ecb_SP2023 text1.e text1. w043nrp 1a2b3c4d5e6f7g
   ```

4. **Verify decryption using `diff`**

   ```sh
   diff MSG1 MSG1.d
   diff MSG2 MSG2.d
   diff MSG3 MSG3.d
   diff text1 text1.d
   ```

5. **Check byte differences in encrypted files**

   ```sh
    od -b MSG1.e > MSG1_od.txt
    od -b MSG2.e > MSG2_od.txt
    od -b MSG3.e > MSG3_od.txt
    diff MSG1_od.txt MSG2_od.txt | wc -l
    diff MSG1_od.txt MSG3_od.txt | wc -l
   ```

---

## Task 2

### Steps for Execution:

1. **Compile the modified programs**
   ```sh
   cryptog++ aes_encode_ECB_SP2023.cpp.cpp -o des_e_ecb_SP2023 -lcryptopp
   cryptog++ aes_decode_ECB_SP2023.cpp.cpp -o des_d_ecb_SP2023 -lcryptopp
   ```
2. **Encrypt the test files**

   ```sh
   ./des_e_ecb_SP2023 MSG1 MSG1.e w043nrp 1a2b3c4d5e6f7g
   ./des_e_ecb_SP2023 MSG2 MSG2.e w043nrp 1a2b3c4d5e6f7g
   ./des_e_ecb_SP2023 MSG3 MSG3.e w043nrp 1a2b3c4d5e6f7g
   ./des_e_ecb_SP2023 text1 text1.e w043nrp 1a2b3c4d5e6f7g
   ```

3. **Decrypt the encrypted files**

   ```sh
   ./des_d_ecb_SP2023 MSG1.e MSG1.d w043nrp 1a2b3c4d5e6f7g
   ./des_d_ecb_SP2023 MSG2.e MSG2.d w043nrp 1a2b3c4d5e6f7g
   ./des_d_ecb_SP2023 MSG3.e MSG3.d w043nrp 1a2b3c4d5e6f7g
   ./des_d_ecb_SP2023 text1.e text1. w043nrp 1a2b3c4d5e6f7g
   ```

4. **Verify decryption using `diff`**

   ```sh
   diff MSG1 MSG1.d
   diff MSG2 MSG2.d
   diff MSG3 MSG3.d
   diff text1 text1.d
   ```

5. **Check byte differences in encrypted files**

   ```sh
    od -b MSG1.e > MSG1_od.txt
    od -b MSG2.e > MSG2_od.txt
    od -b MSG3.e > MSG3_od.txt
    diff MSG1_od.txt MSG2_od.txt | wc -l
    diff MSG1_od.txt MSG3_od.txt | wc -l
   ```

---
