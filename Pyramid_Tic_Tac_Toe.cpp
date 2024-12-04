// Author: Esraa Emary Abd El-Salam
// ID: 20230054
// Section: S19
// TA: Ahmed Ihab
// Version: 3.0

/*
 * This is a simple implementation of the Pyramid Tic Tac Toe game.
 * The game is played on a 3x5 pyramid where each cell is filled with either 'X' or 'O'.
 * The game is played between two players:
    ** The first player has the symbol 'X'.
    ** The second player has the symbol 'O'.
 * The players take turns to place a number in an empty cell.
 * The player who places four symbols in a row, column, or diagonal loses the game.
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

vector<string> getFile() {
    string fileContent, s = "", fileName;
    stringstream content;
    vector<string> lines;
    cout << "\nPlease enter file name:";
    while (true) {
        getline(cin, fileName);                               // get file name and check the validity of format.
        if (fileName.size() < 5) {
            cout << "\nThe file name should be like this ----> (file name).txt\n";
            cout << "Please enter a valid file name :";
            continue;
        }
        if (fileName.substr(fileName.size() - 4, 4) != ".txt") {
            cout << "\nThe file name should be like this ----> (file name).txt\n";
            cout << "Please enter a valid file name :";
            continue;
        }
        ifstream file(fileName);
        if (!file.good()) {
            cout << "\nThe file name should be like this ----> (file name).txt\n";
            cout << "Please enter a valid file name :";
            continue;
        }
        content << file.rdbuf();
        break;
    }
    fileContent = content.str();
    for (char character: fileContent) {
        if (character == '\n') {
            lines.push_back(s);
            s = "";
        } else {
            s += character;
        }
    }
    lines.push_back(s);
    return lines;
}

//--------------------------------------- CLASSES

class Pyramid_Tic_Tac_Toe_Board : public Board<char> {
private:
    bool over = false;
public:
    Pyramid_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class Pyramid_Tic_Tac_Toe_Player : public Player<char> {
public:
    Pyramid_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class Pyramid_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    Pyramid_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

// ---------------------------- BOARD CLASS

Pyramid_Tic_Tac_Toe_Board::Pyramid_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 5;
    int num = 1;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[num];
        for (int j = 2 - i; j < num + 2 - i; j++) {
            this->board[i][j] = 0;
        }
        num += 2;
    }
    this->n_moves = 0;
}

bool Pyramid_Tic_Tac_Toe_Board::update_board(int x, int y, char symbol) {
    if (((x == 0 && y == 2) || (x == 1 && y == 1) || (x == 1 && y == 2) || (x == 1 && y == 3) || (x == 2 && y == 0) ||
         (x == 2 && y == 1) || (x == 2 && y == 2) || (x == 2 && y == 3) ||
         (x == 2 && y == 4)) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

void Pyramid_Tic_Tac_Toe_Board::display_board() {
    int num = 1;
    for (int i = 0; i < this->rows; i++) {
        if (i == 0) {
            cout << "\n            _____\n";
            cout << i + 1 << "           " << "| ";
            for (int j = 2 - i; j < num + 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " |";
            }
            cout << "\n        _____________\n";
        } else if (i == 1) {
            cout << i + 1 << "       " << "| ";
            for (int j = 2 - i; j < num + 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " | ";
            }
            cout << "\n    _____________________\n";
        } else {
            cout << i + 1 << "   " << "| ";
            for (int j = 2 - i; j < num + 2 - i; j++) {
                cout << setw(1) << this->board[i][j] << " | ";
            }
            cout << "\n    _____________________\n      1   2   3   4   5\n\n";
        }
        num += 2;
    }
}

bool Pyramid_Tic_Tac_Toe_Board::is_win() {                                   // Check winning.
    if ((this->board[0][2] != 0 && this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2][2]) ||
        (this->board[0][2] != 0 && this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) ||
        (this->board[0][2] != 0 && this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4]) ||
        (this->board[1][1] != 0 && this->board[1][1] == this->board[1][2] && this->board[1][1] == this->board[1][3]) ||
        (this->board[2][2] != 0 && this->board[2][2] == this->board[2][0] && this->board[2][2] == this->board[2][1]) ||
        (this->board[2][2] != 0 && this->board[2][2] == this->board[2][1] && this->board[2][2] == this->board[2][3]) ||
        (this->board[2][2] != 0 && this->board[2][2] == this->board[2][3] && this->board[2][2] == this->board[2][4])) {
        return true;
    }
    return false;
}

bool Pyramid_Tic_Tac_Toe_Board::is_draw() {
    if (this->n_moves == 9) return true;                                        // Check board is full.
    return false;
}

bool Pyramid_Tic_Tac_Toe_Board::game_is_over() {
    return over;
}

// ---------------------------- PLAYER CLASS

void Pyramid_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
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

Pyramid_Tic_Tac_Toe_Player::Pyramid_Tic_Tac_Toe_Player(std::string name, char symbol) : Player<char>(name, symbol) {}

// ---------------------------- RANDOM PLAYER CLASS

void Pyramid_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

Pyramid_Tic_Tac_Toe_Random_Player::Pyramid_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

//--------------------------------------- MAIN FUNCTION

int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    Pyramid_Tic_Tac_Toe_Board *gameBoard = new Pyramid_Tic_Tac_Toe_Board();

    cout << "<--------- Welcome To Pyramid Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new Pyramid_Tic_Tac_Toe_Player(player1Name, 'X');
    } else {
        players[0] = new Pyramid_Tic_Tac_Toe_Random_Player('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new Pyramid_Tic_Tac_Toe_Player(player2Name, 'O');
    } else {
        players[1] = new Pyramid_Tic_Tac_Toe_Random_Player('O');
    }

    GameManager<char> Pyramid_Tic_Tac_Toe_Game(gameBoard, players);
    Pyramid_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}
