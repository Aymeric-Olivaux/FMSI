#!/bin/sh

cd ../

ourtest=1
for var in "$@"
do
    echo -e "\nTest message: '$var'"

    ./AliceEtBob "$var"

    ./rhoDePollard

    ourtest=0

done


if [ $ourtest == 1 ]
then
echo -e "Our tests :"

echo -e "\nTest message:  'Mougou'"
./AliceEtBob "Mougou"

./rhoDePollard

echo -e "\nTest message:  'Short message'"
./AliceEtBob "Short message"

./rhoDePollard

echo -e "\nTest message:  'Message a little bit longer but not extremly long.'"
./AliceEtBob "Message a little bit longer but not extremly long."

./rhoDePollard

echo -e "\nTest message:  'Pretty long message that talk about secret message that contains confidential data about governments that could cause a global conflict if revealed to the world!'"
./AliceEtBob "Pretty long message that talk about secret message that contains confidential data about governments that could cause a global conflict if revealed to the world!"

./rhoDePollard

fi
