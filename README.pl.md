# Warcaby - aplikacja webowa
Projekt realizowany na przedmiot Zaawansowane Programowanie w C++ [ZPR].<br>
Warcaby w [wariancie rosyjskim](https://pl.wikipedia.org/wiki/Warcaby) - aplikacja webowa w architekturze opartej na:
- C++, boost.python - logika aplikacji, mechanika gry,
- Django (Python) - obsługa strony serwera,
- AngularJS + HTML5 - obsługa strony klienta, GUI w przeglądarce.
<br>
Autorzy: Patrycja Cieplicka, Adam Napieralski.
Wyświetl w języku: [Angielskim](README.md)

## Instalacja

### Wymagania
Biblioteki i używane technologie:
- g++
- scons
- boost (Boost.Python, Boost.Test)
- python3 / python2
- nodejs >=v10.15
- django >=v1.11
- angularjs >=v1.7
- [chessboardjs](https://chessboardjs.com/) v1.0.0

### Na Linuxie (tworzone i testowane na Ubuntu 18.04)
Aby zainstalować wszystkie potrzebne pakiety i biblioteki, użyj skryptu:
```
./install.sh
```
Domyślna wersja Pythona przy takiej instalacji to 3.x, jednak możliwe jest wybór python2 przy pomocy argumentu: 
```
./install.sh python=2.6
```
### Na Windowsie
1. Zainstaluj Microsoft Visual Studio.
2. Zainstaluj preferowanego [Pythona](https://www.python.org/download/releases/) (np. Python3.6) w domyślnej ścieżce (C:\Python36\), następnie dodaj ją do zmiennej środowiskowej PATH.
3. Zainstaluj pip / pip3 - pobierz [get-pip.py](https://bootstrap.pypa.io/get-pip.py) i uruchom `python get-pip.py`.
4. `pip install --egg scons`
5. `pip install -r pip_requirements.txt`
6. Pobierz i zainstaluj [boost](http://www.boost.org) w C:\Boost\.
7. Zainstaluj [nodejs](http://nodejs.org/download/)
8. W folderze `client/` zainstaluj moduły JS: `npm install`.

## Budowanie
Aby skompilować i zbudować pełną aplikację użyj:
```
scons
```
Domyślna wersja Pythona w tym procesie to 3.6. By użyć innej wersji spośród wspieranych [2.6, 2.7, 3.6, 3.7], dodaj argument:
```
scons python=2.6
```
## Testy
Wykonaj testy jednostkowe po zbudowaniu aplikacji przy pomocy:
```
scons test=1
```
## Uruchom serwer
Aby uruchomić serwer django na domyślnym adresie (127.0.0.1:8000), użyj:
```
scons --run
```
lub manualnie: `python ./build_web/manage.py runserver [ip]:[port]` or `python3 ./build_web/manage.py runserver [ip]:[port]`
## Użytkowanie
Otwórz przeglądarkę i przejdź pod zdefiniowany wcześniej adres: http://127.0.0.1:8000/. Zostaniesz przekierowany na stronę początkową `/entry`, gdzie należy podać nick i wybrać kolor pionków. Po zaakceptowaniu danych przez kliknięcie przycisku nastąpi przejście na stronę samej gry `/play`.
