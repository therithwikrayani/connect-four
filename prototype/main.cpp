#include <iostream>
using namespace std;

// function prototypes
int displayBoard();
int resetBoard();
int insertToken(int column);

// initializing global variables
int BOARD[6][7] = {0};
int TURN = 1;

int main() {
    insertToken(4);
    insertToken(3);
    insertToken(3);
    displayBoard();
    return 0;
}

int displayBoard() {
    cout << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << BOARD[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 1; i <= 7; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}

int resetBoard() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            BOARD[i][j] = 0;
        }
    }
    return 0;
}

int insertToken(int column) {
    for (int i = 5; i >= 0; i--) {
        if (BOARD[i][column] == 0) {
            BOARD[i][column] = TURN;
            if (TURN == 1) {TURN = 2;}
            else {TURN = 1;}
            return 0;
        }
    }
    return 1;
}

