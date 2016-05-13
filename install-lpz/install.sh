#!/bin/bash 

echo "This script will download and install the lpzrobots-environment for you."
echo "It has been tested on Ubuntu 14.04. Default values are in [] and capitalized."
echo

while [[ true ]]; do
echo "In which directory should the program be downloaded and compiled? [~/Downloads/]"

read location

# if location is empty take default value
if [[ -z $location ]]; then
	location="/home/${USER}/Downloads"
fi

# check if location exists
if [[ ! -e $location || ! -w $location ]]; then
	echo "Directory does not exist or you do not have read/write-access! - ABORT"
	exit 1
fi

echo "The lpzrobots-files will now be downloaded into the directory ${location}/LpzRobots. Is this OK? [n/Y]"

read ans

# check answer
if [[ $ans == "n" ]]; then
	echo
	continue
elif [[ $ans == "" || $ans == "Y" ]]; then
	echo "OK, continuing."
	break
else
	echo "Did not catch that!"
	echo
	continue
fi

done

cd $location

mkdir LpzRobots

cd LpzRobots

echo "Downloading files from github."
echo
wget https://github.com/georgmartius/lpzrobots/archive/master.zip

echo "Unzipping content."
echo
unzip master.zip

cd lpzrobots-master

echo "Making sure essentials are installed."
echo
sudo apt-get update

sudo apt-get install build-essential

echo "Installing necessary packages for compiling."

sudo apt-get install g++ make automake libtool xutils-dev m4 libreadline-dev libgsl0-dev \
libglu-dev libgl1-mesa-dev freeglut3-dev libopenscenegraph-dev libqt4-dev libqt4-opengl \
libqt4-opengl-dev qt4-qmake libqt4-qt3support gnuplot gnuplot-x11 libncurses5-dev

echo "Starting the make-process."	
make

wait

echo "This next command will compile the program, it will take a long time to finish. Do you want to continue? [n/Y]"

read ans

if [[ $ans == "n" ]]; then
	echo "Exiting."
	exit 0
elif [[ -d $ans || $ans == "Y" ]]; then
	echo "OK, continuing."
else
	echo "Did not catch that! - ABORT"
	exit 1
fi

sudo make all

wait

echo "That should be it, lpzrobots is now installed."
echo "Have a nice day!"
exit 0
