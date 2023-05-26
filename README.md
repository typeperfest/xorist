# Simple encoder and breaker

xorist is a project that consists of xorist executable, wich encodes a text by simple block cipher,
and breaker, which uses brute-force enumaration of all keys to crack a cipher. Project is made with educational purpose.

### xorist

- block cipher
- block size is 1 byte.
- operation is bitwise xor

### breaker

- brute-force
- accepts a dictionary txt file of words to detect in ciphertext
- implements disposable hash-table

### Building & Usage
1. to make xorist and breaker just run ```make```
2. to run examples run ```./runExamples```

xorist usage example:
```bash
./xorist -k 100 -i file.txt -o encrypted.bin
```

breaker usage example:
```bash
./breaker -d dictionary.txt -c crackme.bin
```