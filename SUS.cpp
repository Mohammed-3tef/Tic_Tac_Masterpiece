// Author: Esraa Emary Abd El-Salam
// ID: 20230054
// Section: S19
// TA: Ahmed Ihab
// Version: 4.0

/*
 * This is a simple implementation of the SUS game.
 * The game is played on a 3x3 board where each cell is filled with either 'S' or 'U'.
 * The game is played between two players:
    ** The first player has the symbol 'S'.
    ** The second player has the symbol 'U'.
 * The players take turns to place their symbol in an empty cell.
 * The player who places more "SUS" in a row, column, or diagonal wins the game.
 * The game ends in a draw if number of points are equal.
*/

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

bool winU = false;

//--------------------------------------- HELPER FUNCTIONS

void checkPlayerType(string &playerType, int num) {
    cout << "\nWhat is player " << num << " type ?\n[1] Human.\n[2] Computer.\nChoice:";
    getline(cin, playerType);
    while (true) {
        if (playerType != "1" && playerType != "2") {
            cout << "Please enter a valid choice!\n\n";
            cout << "What is player " << num << " type ?\n[1] Human.\n[2] Computer.\nChoice:";
            getline(cin, playerType);
            continue;
        }
        return;
    }
}

//--------------------------------------- CLASSES

class SUS_Board : public Board<char> {
private:
    int countSus = 0;
    bool draw = false;
    int scoreS = 0;
    int scoreU = 0;
    int count_three();

public:
    SUS_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class SUS_Player : public Player<char> {
public:
    SUS_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class SUS_Random_Player : public RandomPlayer<char> {
public:
    SUS_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION
// ---------------------------- BOARD CLASS

SUS_Board::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

bool SUS_Board::update_board(int x, int y, char symbol) {
    if (winU) return true;
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

void SUS_Board::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n   ___________________\n";
        cout << i + 1 << "  " << "|  ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(1) << this->board[i][j] << "  |  ";
        }
    }
    cout << "\n   ___________________\n      1     2     3\n\n";
}

int SUS_Board::count_three() {
    int count = 0;
    // Check horizontal
    for (int i = 0; i < this->rows; ++i) {
        if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S') {
            count++;
        }
    }

    // Check vertical
    for (int j = 0; j < this->columns; ++j) {
        if (this->board[0][j] == 'S' && this->board[1][j] == 'U' && this->board[2][j] == 'S') {
            count++;
        }
    }

    // Check diagonal (top-left to bottom-right)
    if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
        count++;
    }

    // Check diagonal (top-right to bottom-left)
    if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
        count++;
    }
    return count;
}

bool SUS_Board::is_win() {
    // Calculate scores for each player
    countSus = count_three();
    if (this->n_moves % 2 == 0) scoreU = countSus - scoreS;
    else scoreS = countSus - scoreU;

    // Ensure the board is full except for one square
    if (this->n_moves < 9) {
        return false; // Not yet time to determine the winner
    }

    if (winU) {
        cout << "\nFinal Scores:\n";
        cout << "Player S: " << scoreS << " of SUS\n";
        cout << "Player U: " << scoreU << " of SUS\n";
        return true;
    }

    // Announce the scores
    if (this->n_moves == 9 && scoreS < scoreU) {
        winU = true;
        return false;
    }
    cout << "\nFinal Scores:\n";
    cout << "Player S: " << scoreS << " of SUS\n";
    cout << "Player U: " << scoreU << " of SUS\n";
    if (this->n_moves == 9 && scoreS == scoreU) {
        draw = true;
        return false;
    }
    return true; // Game over
}

bool SUS_Board::is_draw() {
    return draw;
}

bool SUS_Board::game_is_over() {
    return is_win() || is_draw();
}

// ---------------------------- PLAYER CLASS

void SUS_Player::getmove(int &x, int &y) {
    if (winU) return;
    cout << "It's " << this->name << " turn\n";
    string dim1, dim2;
    cout << "\nPlease enter the row:";                                          // Get move.
    getline(cin, dim1);
    cout << "Please enter the column:";
    getline(cin, dim2);
    while (true) {                                                              // Check validity of move.
        if (dim1.size() != 1 || dim2.size() != 1) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "Please enter the column:";
            getline(cin, dim2);
            continue;
        }
        if (dim1[0] < 49 || dim1[0] > 57) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "Please enter the column:";
            getline(cin, dim2);
            continue;
        }
        if (dim2[0] < 49 || dim2[0] > 57) {
            cout << "Please enter a valid position!\n\n";
            cout << "\nPlease enter the row:";
            getline(cin, dim1);
            cout << "Please enter the column:";
            getline(cin, dim2);
            continue;
        }
        break;
    }
    x = stoi(dim1) - 1;                                                 // Set move.
    y = stoi(dim2) - 1;
}

SUS_Player::SUS_Player(std::string name, char symbol) : Player<char>(name, symbol) {}

// ---------------------------- RANDOM PLAYER CLASS

void SUS_Random_Player::getmove(int &x, int &y) {
    if (winU) return;
    x = rand() % this->dimension;                                       // Random number between 0 and 2
    y = rand() % this->dimension;
}

SUS_Random_Player::SUS_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
}

//--------------------------------------- MAIN FUNCTION

int main() {
    cout << "<--------- Welcome To SUS --------->\n";
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    SUS_Board *gameBoard = new SUS_Board();

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new SUS_Player(player1Name, 'S');
    } else {
        players[0] = new SUS_Random_Player('S');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new SUS_Player(player2Name, 'U');
    } else {
        players[1] = new SUS_Random_Player('U');
    }

    GameManager<char> SUS_Game(gameBoard, players);
    SUS_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}
