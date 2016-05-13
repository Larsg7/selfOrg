1. Installation grundlegender Werkzeuge zum Kompilieren, apt-get:

sudo apt-get install build-essential

2. In das Downloadsverzeichnis wechseln, cd:

cd Downloads

3. Wenn ich Source lade, erstelle ich gerne ein Unterverzeichnis, da manche Archive sonst beim Entpacken das Verzeichnis Downloads zumüllen, mkdir:

mkdir LpzRobots

4. Wechsel in das gerade erstellte Verzeichnis:

cd LpzRobots

4. Sourcearchiv laden, wget:

wget https://github.com/georgmartius/lpzrobots/archive/master.zip

5. Archiv entpacken:

unzip master.zip

6. In das Unterverzeichnis wechseln:

cd lpzrobots-master

7. Die Abhängigkeiten installieren:

sudo apt-get install g++ make automake libtool xutils-dev m4 libreadline-dev libgsl0-dev libglu-dev libgl1-mesa-dev freeglut3-dev libopenscenegraph-dev libqt4-dev libqt4-opengl libqt4-opengl-dev qt4-qmake libqt4-qt3support gnuplot gnuplot-x11 libncurses5-dev

8. make ausführen:

make

Jetzt folgen einige Fragen, zuerst:

Where do you want to install the simulator?
Please use either /usr, /usr/local  or you home directory
unless you know what you are doing. (no tailing slash)
e.g. (/home/yourlogin) (don' use ~): [/usr/local]

Die nickt man per Enter ab (Die Vorgabe /usr/local steht in eckigen Klammern)

Installation type (user or development):
 Choose user  (u) if you are a user and only program your own simulations (default)
 Choose devel (d) if you develop the simulator
 
Kenne ich nicht, da wirst du schon wissen, was zu wählen ist, ich übernehme die Vorgabe d für develop...

Check your settings:
 Installation to /usr/local
 (d) development installation
All right? [y/N]

Hier ist die Vorgabe N für Nein, also gibt man y ein und drückt Enter. Anschließend hab ich das eingegeben:

sudo make all
