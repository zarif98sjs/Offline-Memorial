#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3


string to_string(int x) {
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position {

    int x, y;

public:

    Position (int x, int y) {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight() {
        x++;
    }

    void moveLeft() {
        x--;
    }

    void moveUp() {
        y++;
    }

    void moveDown() {
        y--;
    }

    bool isAdjacent(Position p) {
        //implement the function
    }

    bool isSamePoint(Position p) {
        //implement the function
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

};


class Wumpus {

    bool killed;
    Position p;

public:

    Wumpus(int x, int y) {
        p = Position(x, y);
        killed = false;
    }

    Wumpus() {
        //...
    }

    void kill() {
        killed = true;
    }

    Position getPosition() {
        return p;
    }

};


class Player {

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player() {
        //...
    }

    void turnLeft() {
        //...
    }

    void turnRight() {
        //...
    }

    void moveForward() {
        //...
    }

    bool isAdjacent(Position pos) {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos) {
        return p.isSamePoint(pos);
    }

    void kill() {
        killed = true;
    }

    string getPositionInfo() {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }

    string getDirectionInfo() {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }

};



class WumpusWorld {

private:

    Player player;
    Wumpus wumpus;
    Position gold_position;
    bool ended;

public:

    WumpusWorld() {
        //...
    }

    WumpusWorld(int wumpus_x, int wumpus_y) {
        //...
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y) {
        //...
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y) {
        //...
    }

    void moveForward() {
        player.moveForward();
        return showGameState();
    }

    void turnLeft() {
        player.turnLeft();
        return showGameState();
    }

    void turnRight() {
        player.turnRight();
        return showGameState();
    }

    void shoot() {
        //...
    }

    void showGameState() {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if (player.isAdjacent(wumpus.getPosition())) {
            cout << "stench!" << endl;
        }

        if (player.isSamePoint(wumpus.getPosition())) {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }

        if (player.isSamePoint(gold_position)) {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
    }

    bool isOver() {
        return ended;
    }

};


int main()
{
    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
    // take the six integers input from file
    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
    w.showGameState();
    while (!w.isOver()) {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1) {
            w.moveForward();
        } else if (c == 2) {
            w.turnLeft();
        } else if (c == 3) {
            w.turnRight();
        } else if (c == 4) {
            w.shoot();
        }
    }
    return 0;
}
