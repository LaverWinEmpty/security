# Crypter

MD file written in VS Code

## Features

    - AES-256
    - SHA-256
    - Base64

---

## How to use

    1. Include src/src/crypter.hpp and cpp
    2. Use Crypter class
       or
    2. Use Base64, SHA256, AES256 class

-   ### Guide

    > #### 1. crypter.cpp has base64.cpp, sha256.cpp, aes256.cpp
    >
    >     Implementation is inline (crypter.ipp)
    >     Instead of including crypter.cpp, it can include the 3 cpp files mentioned earlier

    > #### 2. Hash the key when calling Encrypt and Decrypt.
    >
    >     If do not want to hashing, call the SHA256 method.
    >     But if it key is not a 32-byte string, it throws an error.

    > #### 3. There is a helper class
    >
    >     Crypt::Helper
    >     It is static class with ToHex and ToString methods

---

-   ## Note
    -   Crypter is static class
    -   Use Base 64 when calling AES 256
        > **To use separately**
        >
        >     call Base64::Encoding and Base64::Decoding
        >     call AES256::Encrypt  and AES256::Decrypt
    -   struct Ptr behaves like a **char pointer**
    -   Blocks are not used, only used inside the module.
