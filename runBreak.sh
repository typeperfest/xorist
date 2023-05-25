make

echo "some text\n123231\nlallalal" > build/plain.txt
echo "text\nword\njjiij" > build/dict.txt

pushd build

./xorist -k 100 -i plain.txt -o crackme.bin
./breaker -d dict.txt -c crackme.bin

popd
