
echo "some text\n123231\nlallalal\n" > plain.txt
echo "text\nword\njjiij\n" > dict.txt

./xorist -k 100 -i plain.txt -o crackme.bin
./breaker -d dict.txt -c crackme.bin
