#!/bin/bash

PYTHON_VERSION=3
while getopts ":p:" options; do
    case "${options}" in
        p )
            PYTHON_VERSION=${OPTARG} ;;
    esac
done
PYTHON_VERSION=${PYTHON_VERSION%.*}

echo "sudo add-apt-repository universe"
echo "sudo apt update && sudo apt upgrade"
echo "sudo apt install g++ scons nodejs npm libboost-dev libboost-all-dev"

if [ $PYTHON_VERSION -eq 3 ]; then
    echo "sudo apt install python3-dev python3-pip"
    echo "sudo pip3 install -r pip_requirements.txt"
elif [ $PYTHON_VERSION -eq 2 ]; then
    echo "sudo apt install python-dev python-pip"
    echo "sudo pip install -r pip_requirements.txt"
else
    echo "Python version not supported."
fi

cd client
echo "npm install"

sed -i 's#/img/chesspieces/wikipedia/{piece}.png#/static/media/chesspieces/{piece}.png#g' node_modules/file.txt
