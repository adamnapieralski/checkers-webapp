# checkers-webapp
Project for university Advanced Programming course.<br>
Checkers (draughts) in [russian variant](https://en.wikipedia.org/wiki/Russian_draughts) - web application build on architecture containing:
- C++, boost.python - app's logic, game mechanics,
- Django (Python) - server controller,
- AngularJS + HTML5 - client controller and interface.
<br>
Authors: Adam Napieralski, Patrycja Cieplicka.<br>
View in: [Polish](README.pl.md)


## Installation

### Prerequisites
Packages and technologies used:
- g++
- scons
- boost (Boost.Python, Boost.Test)
- python3 / python2
- nodejs >=v10.15
- django >=v1.11
- angularjs >=v1.7
- [chessboardjs](https://chessboardjs.com/) v1.0.0

### On Linux (designed for and tested on Ubuntu 18.04)
To install all of needed packages, use bash script:
```
./install.sh
```
Default version of python for which some packages are installed is 3.x, however, you can change it to python2 with e.g.:
```
./install.sh python=2.6
```
### On Windows
1. Install Microsoft Visual Studio.
2. Install preferred [Python](https://www.python.org/download/releases/) (e.g. Python3.6) in the default path (C:\Python36\), add it to the PATH.
3. Install pip / pip3 - download [get-pip.py](https://bootstrap.pypa.io/get-pip.py) then run `python get-pip.py`.
4. `pip install --egg scons`
5. `pip install -r pip_requirements.txt`
6. Download and install [boost](http://www.boost.org) in C:\Boost\.
7. Install [nodejs](http://nodejs.org/download/).
8. In `client/` install js node modules with `npm install`.

## Build
To build and compile application, use:
```
scons
```
The default python version is 3.6. To build with one of other supported versions [2.6, 2.7, 3.6, 3.7, 3.8], set argument:
```
scons python=2.7
```
After once defined, it will be stored and used in further scons run, so there will be no need to define it again.
## Tests
To run unit tests (together with building), use:
```
scons --test
```
## Run server
To run django server on predefined address (127.0.0.1:8000), use:
```
scons --run
```
or manually run: `python ./build_web/manage.py runserver [ip]:[port]` or `python3 ./build_web/manage.py runserver [ip]:[port]`
## Usage
Open your browser and go to defined address, like: http://127.0.0.1:8000/. You will be redirected to `/entry` page of the game, where you can type your nickname and select your color of pieces. After submitting it with button click, you go to `/play` page with the game itself.
