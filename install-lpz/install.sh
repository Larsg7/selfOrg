#!/bin/bash

echo
echo "This script will download and install the lpzrobots-environment for you."
echo "It has been tested on Ubuntu 14.04. Default values are in '[]'' and/or capitalized, \
just press ENTER to use them."
echo "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND."

# small function to check exit-status ToDo: show last command
function chExitStatus {
	if [[ ! $? -eq 0 ]]; then
	echo
	echo "Something went wrong while running the last command. - ABORT"
	exit 1
fi
}

# start with asking the user in which directory the files should go
while [[ true ]]; do
echo "In which directory should the program be downloaded and compiled ('/LpzRobots' \
	will be added to the end of the path)? [/home/${USER}/Downloads]"

read location

# if location is empty take default value
if [[ -z $location ]]; then
	location="/home/${USER}/Downloads"
fi

# check if location exists
if [[ ! -e $location || ! -w $location ]]; then
	echo "Directory does not exist or you do not have read/write-access! Choose another one."
	continue
fi

# ask user for confirmation
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
	echo "Sorry, did not catch that!"
	echo
	continue
fi

done

# move into the directory the user has specified
cd $location

# make directory LpzRobots (exits with error if directory already exists)
mkdir LpzRobots

# move into the newly created directory
cd LpzRobots

echo "Downloading files from github."
echo
wget https://github.com/georgmartius/lpzrobots/archive/master.zip

echo "Unzipping content."
echo
unzip master.zip

# check if directory existed
if [[ ! -e lpzrobots-master ]]; then
	echo
	echo "Sorry, something went wrong with the downloading or unzipping process ('lpzrobots-master'-directory does not exist). - ABORT"
	exit 1
fi

# move into the correct directory
cd lpzrobots-master

echo "Making sure essentials are installed."
echo
sudo apt-get update

sudo apt-get install build-essential

echo "Installing necessary packages for compiling."

sudo apt-get install g++ make automake libtool xutils-dev m4 libreadline-dev libgsl0-dev \
libglu-dev libgl1-mesa-dev freeglut3-dev libopenscenegraph-dev libqt4-dev libqt4-opengl \
libqt4-opengl-dev qt4-qmake libqt4-qt3support gnuplot gnuplot-x11 libncurses5-dev

# check if all packages were installed correctly
chExitStatus

echo "Starting the make-process."	
make

wait

# check if make process was successful
chExitStatus

# ask user if they want to continue with the build process
while true; do
echo
echo "The next command will compile the program, it will take a long time to finish. Do you want to continue? (write n/yes)"

read ans

if [[ $ans == "n" ]]; then
	echo "Exiting."
	exit 0
elif [[ $ans == "yes" ]]; then
	echo "OK, continuing."
	break
else
	echo "Sorry, did not catch that!"
	continue
fi
done

# start build-process
sudo make all

wait

# check if build process was successful
chExitStatus

# show user last message
echo
echo "That should be it, lpzrobots is now installed."
echo "Have a nice day!"
exit 0
