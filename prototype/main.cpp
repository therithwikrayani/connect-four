#include <iostream>
using namespace std;

// function prototypes
int displayBoard();
int resetBoard();
int insertToken(int column, int turn);
int removeToken(int column);
int changeTurn();
int checkWin();
int index(int row, int col);
int scoreBoard();
int insertTokenCPU();

// initializing global variables
int BOARD[42] = {0};
int TURN = 1;


int main() {
    int input = 0;
    int mode = 0;
    cout << "1 - Single Player" << endl;
    cout << "2 - Two Player" << endl;
    cout << "Select Mode: ";
    cin >> mode;

    if (mode == 1) {
        while (true)
        {
            displayBoard();
            checkWin();
            if (TURN == 1) {
                cout << "Player " << TURN << " choose a column ";
                cin >> input;
                insertToken(input, TURN);
            }
            else if (TURN == 2) {
                insertTokenCPU();
            }
            changeTurn();
        }
    }

    if (mode == 2) {
        while (true)
        {
            displayBoard();
            checkWin();
            cout << "Player " << TURN << " choose a column ";
            cin >> input;
            insertToken(input, TURN);
            changeTurn();
        }
    }

    return 0;
}

int index(int row, int col) {
    return row * 7 + col;
}

int displayBoard() {
    cout << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            cout << BOARD[index(i, j)] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < 7; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}

int resetBoard() {
    for (int i = 0; i < 42; i++) {
        BOARD[i] = 0;
    }
    TURN = 1;
    return 0;
}

int insertToken(int column, int turn = TURN) {
    if (column < 0 || column > 6) {
        cout << "Please insert a valid column." << endl;
        return 1;
    }
    
    for (int i = 5; i >= 0; i--) {
        if (BOARD[index(i, column)] == 0) {
            BOARD[index(i, column)] = turn;
            return 0;
        }
    }

    cout << "Cannot insert a token in this column." << endl;
    return 1;
}

int removeToken(int column) {
    if (column < 0 || column > 6) {
        cout << "Please insert a valid column." << endl;
        return 1;
    }

    for (int i = 0; i < 6; i++) {
        if (BOARD[index(i, column)] != 0) {
            BOARD[index(i, column)] = 0;
            return 0;
        }
    }
    
    cout << "Cannot remove a token in this column." << endl;
    return 1;
}

int changeTurn() {
    if (TURN == 1) {
        TURN = 2;
    }
    else if (TURN == 2) {
        TURN = 1;
    }
    return 0;
}

int checkWin() {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            int current = BOARD[index(row, col)];
            if (current == 0) {
                continue;
            }

            // Check horizontal
            if (col + 3 < 7 &&
                current == BOARD[index(row, col + 1)] &&
                current == BOARD[index(row, col + 2)] &&
                current == BOARD[index(row, col + 3)]) {
                cout << "Player " << current << " wins!" << endl;
                exit(0);
            }

            // Check vertical
            if (row + 3 < 6 &&
                current == BOARD[index(row + 1, col)] &&
                current == BOARD[index(row + 2, col)] &&
                current == BOARD[index(row + 3, col)]) {
                cout << "Player " << current << " wins!" << endl;
                exit(0);
            }

            // Check diagonal down-right
            if (row + 3 < 6 && col + 3 < 7 &&
                current == BOARD[index(row + 1, col + 1)] &&
                current == BOARD[index(row + 2, col + 2)] &&
                current == BOARD[index(row + 3, col + 3)]) {
                cout << "Player " << current << " wins!" << endl;
                exit(0);
            }

            // Check diagonal up-right
            if (row - 3 >= 0 && col + 3 < 7 &&
                current == BOARD[index(row - 1, col + 1)] &&
                current == BOARD[index(row - 2, col + 2)] &&
                current == BOARD[index(row - 3, col - 3)]) {
                cout << "Player " << current << " wins!" << endl;
                exit(0);
            }
        }
    }
    return 0;
}

int scoreBoard() {
    int totalScore = 0;
    int scores[] = {0, 1, 10, 1000, 100000};

    // Check rows
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            int count1 = 0, count2 = 0;
            for (int i = 0; i < 4; i++) {
                if (BOARD[index(row, col + i)] == 1) {
                    count1++;
                } else if (BOARD[index(row, col + i)] == 2) {
                    count2++;
                }
            }
            totalScore += scores[count1] - scores[count2];
        }
    }

    // Check columns
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 3; row++) {
            int count1 = 0, count2 = 0;
            for (int i = 0; i < 4; i++) {
                if (BOARD[index(row + i, col)] == 1) {
                    count1++;
                } else if (BOARD[index(row + i, col)] == 2) {
                    count2++;
                }
            }
            totalScore += scores[count1] - scores[count2];
        }
    }

    // Check diagonals down-right
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            int count1 = 0, count2 = 0;
            for (int i = 0; i < 4; i++) {
                if (BOARD[index(row + i, col + i)] == 1) {
                    count1++;
                } else if (BOARD[index(row + i, col + i)] == 2) {
                    count2++;
                }
            }
            totalScore += scores[count1] - scores[count2];
        }
    }

    // Check diagonals up-right
    for (int row = 3; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            int count1 = 0, count2 = 0;
            for (int i = 0; i < 4; i++) {
                if (BOARD[index(row - i, col + i)] == 1) {
                    count1++;
                } else if (BOARD[index(row - i, col + i)] == 2) {
                    count2++;
                }
            }
            totalScore += scores[count1] - scores[count2];
        }
    }

    return totalScore;
}

int insertTokenCPU() {
    insertToken(0, TURN);
    return 0;
}