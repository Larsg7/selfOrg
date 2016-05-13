#!/bin/bash

echo "This script will download and install the lpzrobots-environment for you."
echo "It has been tested on Ubuntu 14.04."

echo "Making sure essentials are installed"

sudo apt-get update

sudo apt-get install build-essential

cd ~/Downloads

mkdir LpzRobots

cd LpzRobots

wget https://github.com/georgmartius/lpzrobots/archive/master.zip

unzip master.zip

cd lpzrobots-master

sudo apt-get install g++ make automake libtool xutils-dev m4 libreadline-dev libgsl0-dev \
	libglu-dev libgl1-mesa-dev freeglut3-dev libopenscenegraph-dev libqt4-dev libqt4-opengl \ 
	libqt4-opengl-dev qt4-qmake libqt4-qt3support gnuplot gnuplot-x11 libncurses5-dev
	
make

wait

sudo make all

exit 0
