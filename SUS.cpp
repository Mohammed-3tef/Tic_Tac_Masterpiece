// Author: Esraa Emary Abd El-Salam
// ID: 20230054
// Section: S19
// TA: Ahmed Ihab
// Version: 3.0

/*
 * This is a simple implementation of the SUS game.
 * The game is played on a 3x3 board where each cell is filled with either 'S' or 'U'.
 * The game is played between two players:
    ** The first player has the symbol 'S'.
    ** The second player has the symbol 'U'.
 * The players take turns to place their symbol in an empty cell.
 * The player who places "SUS" in a row, column, or diagonal wins the game.
 * The game ends in a draw if all cells are filled and no player wins.
*/

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

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
    bool over = false;
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

bool SUS_Board::is_win() {
    vector<string> patterns;
    for (int i = 0; i < 3; i++) {                                          // Check winning horizontally and vertically.
        string row, col;
        for (int j = 0; j < 3; j++) {
            row += this->board[i][j];
            col += this->board[j][i];
        }
        patterns.push_back(row);
        patterns.push_back(col);
    }
    string diag1 = "", diag2 = "";
    for (int i = 0; i < 3; i++) {                                           // Check winning diagonally.
        diag1 += this->board[i][i];
        diag2 += this->board[i][2 - i];
    }
    patterns.push_back(diag1);
    patterns.push_back(diag2);

    for (auto &pattern: patterns) {                                 // Compare between board and dictionary.
        if (pattern == "SUS") {
            over = true;
            return true;
        }
    }
    return false;
}

bool SUS_Board::is_draw() {
    if (this->n_moves == 9) return true;                                        // Check board is full.
    return false;
}

bool SUS_Board::game_is_over() {
    return over;
}

// ---------------------------- PLAYER CLASS

void SUS_Player::getmove(int &x, int &y) {
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
