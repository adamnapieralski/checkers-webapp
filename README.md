# checkers-webapp
Project for university Advanced Programming course.<br>
Checkers (draughts) in russian variant - web application build on architecture using:
- C++ | boost.python - app's logic, game mechanics
- Django (Python) - server controller
- AngularJS + HTML5 - client controller and interface
<br>
Authors: Adam Napieralski, Patrycja Cieplicka

## Installation

### Prerequisites
Packages and technologies used:
- g++
- scons
- boost
- python2.6+ / python3.x
- nodejs
- django
- angularjs
- chessboardjs

### On Linux (designed for and tested on Ubuntu 18.04)
To install all of needed packages, use bash script:
```
./install.sh
```
Default version of python for which some packages are installed is 3.x, however, you can change it to python2, e.g.:
```
./install.sh python=2.6
```

## Build
To build and compile application, use:
```
scons
```
The default python version is 3.6. To build with one of other supported versions (2.6, 3.6, 3.7), set argument:
```
scons python=2.6
```
## Tests
To run unit tests (together with building), use:
```
scons test=1
```
## Run server
To run django server on predefined address (127.0.0.1:8000), use:
```
scons --run
```
or more manually use:
```
python ./build_web/manage.py runserver [ip]:[port]
```
or
```
python3 ./build_web/manage.py runserver [ip]:[port]
```
with matching python version used during build.
