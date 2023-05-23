
pushd ..

make

cp build/xorist example/. 

popd

./xorist -k 100 -i file.txt -o encrypted.bin
./xorist -k 100 -i encrypted.bin -o decrypted.txt

diff file.txt decrypted.txt

