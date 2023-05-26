make

cp build/xorist examples/cracking
cp build/xorist examples/encryption-decryption

cp build/breaker examples/cracking
cp build/breaker examples/encryption-decryption

pushd examples/encryption-decryption
./runEncryption.sh
popd

pushd examples/cracking
./runCrack.sh
popd
