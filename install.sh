#!/bin/bash

PYTHON_VERSION=3
while getopts ":p:" options; do
    case "${options}" in
        p )
            PYTHON_VERSION=${OPTARG} ;;
    esac
done
PYTHON_VERSION=${PYTHON_VERSION%.*}

sudo add-apt-repository universe
sudo apt update && sudo apt upgrade
sudo apt install g++ scons nodejs npm libboost-dev libboost-all-dev

if [ $PYTHON_VERSION -eq 3 ]; then
    sudo apt install python3-dev python3-pip
    sudo pip3 install -r pip_requirements.txt
elif [ $PYTHON_VERSION -eq 2 ]; then
    sudo apt install python-dev python-pip
    sudo pip install -r pip_requirements.txt
else
    Python version not supported.
fi

cd client
npm install

sed -r -i 's/img\/chesspieces\/wikipedia/\/static\/media\/chesspieces/g' node_modules/@chrisoakman/chessboardjs/dist/chessboard-1.0.0.js



