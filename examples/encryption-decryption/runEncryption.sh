echo "Once upon a time besides
I saw a spartan on insights
Drow a weapon in a dark
Done a work with lots of spark" > plain.txt

./xorist -k 100 -i plain.txt -o encrypted.bin
./xorist -k 100 -i encrypted.bin -o decrypted.txt

diff plain.txt decrypted.txt

