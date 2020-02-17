#!/bin/sh

#This script installs the game "Number Attack!" onto the system at /usr/games/numattack

echo Make sure this script is run as root!

mkdir /usr/games/numattack
cp ./numattack /usr/games/numattack
chmod 555 /usr/games/numattack/numattack
echo Done.
