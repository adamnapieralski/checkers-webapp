struct Position {
    int x, y;
    Position() : x(0), y(0) {};
    Position(int setX, int setY) : x(setX), y(setY) {};

    bool isPositionValid() {
        if (x >= 0 && x <= 8 && y >=0 && y <=8) return true;
        else return false;
    }
};