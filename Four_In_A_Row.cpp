// Author: Mohammed Atef Abd El-Kader.
// ID: 20231143
// Section: S19
// TA: Ahmed Ihab
// Version: 2.0

/*
 * This is a simple implementation of the Four In A Row game.
 * The game is played on a 6x7 board where each cell is filled with either 'X' or 'O'.
 * The game is played between two players:
     ** The first player has the symbol 'X'.
     ** The second player has the symbol 'O'.
 * The players take turns to place their symbol in an empty cell.
 * The player who places four symbols in a row, column, or diagonal wins the game.
 * The game ends in a draw if all cells are filled and no player wins.
*/

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

set<int> fullColumns;

//--------------------------------------- HELPER FUNCTIONS

void checkPlayerType(string &playerType, int num) {
    cout << "What is player " << num << " type ?\n [1] Human.\n [2] Computer.\nEnter Your Choice :";
    getline(cin, playerType);
    while (true) {
        if (playerType != "1" && playerType != "2") {
            cout << "Please enter a valid choice!!\n\n";
            cout << "What is player " << num << " type ?\n [1] Human.\n [2] Computer.\nEnter Your Choice :";
            getline(cin, playerType);
            continue;
        }
        return;
    }
}

//--------------------------------------- CLASSES

class Four_In_A_Row_Board : public Board<char> {
public:
    Four_In_A_Row_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class Four_In_A_Row_Player : public Player<char> {
public:
    Four_In_A_Row_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
    bool IsValidNumber(const string &str);
};

class Four_In_A_Row_Random_Player : public RandomPlayer<char> {
public:
    explicit Four_In_A_Row_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION
// ---------------------------- BOARD CLASS

// Constructor for the Four_In_A_Row_Board
Four_In_A_Row_Board::Four_In_A_Row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char *[this->rows];
    // Initialize the board with zeros
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize with zero
        }
    }
    this->n_moves = 0;
}

// Update the board with the new move
bool Four_In_A_Row_Board::update_board(int x, int y, char symbol) {
    // Validate move
    if (y < 0 || y >= this->columns) {
        cout << "Invalid column! Try again.\n";
        return false;
    }
    // Check if column is full
    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == 0) {
            this->board[i][y] = symbol;
            this->n_moves++;
            return true;
        }
    }
    cout << "Column is full! Try another column.\n\n";
    fullColumns.insert(y);
    return false;
}

void Four_In_A_Row_Board::display_board() {
    cout << "\n    1   2   3   4   5   6   7\n";
    cout << "  -----------------------------\n";

    for (int i = 0; i < this->rows; i++) {
        cout << "  |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << setw(1);
            if (this->board[i][j] == 0) {
                cout << " ";
            } else cout << this->board[i][j];
            cout << " |";
        }
        cout << "\n  -----------------------------\n";
    }
    cout << endl;
}

bool Four_In_A_Row_Board::is_win() {
    const int winCondition = 4;     // Number of consecutive symbols to win

    // i -> row, j -> column, k -> number of consecutive symbols;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            char symbol = this->board[i][j];
            if (symbol == 0) continue;      // Skip empty cells

            // Check horizontally
            if (j + winCondition - 1 < this->columns) {
                bool win = true;
                // Check if there are 4 consecutive symbols
                for (int k = 0; k < winCondition; k++) {
                    if (this->board[i][j + k] != symbol) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }

            // Check vertically
            if (i + winCondition - 1 < this->rows) {
                bool win = true;
                // Check if there are 4 consecutive symbols
                for (int k = 0; k < winCondition; k++) {
                    if (this->board[i + k][j] != symbol) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }

            // Check diagonal
            if (i + winCondition - 1 < this->rows && j + winCondition - 1 < this->columns) {
                bool win = true;
                // Check if there are 4 consecutive symbols
                for (int k = 0; k < winCondition; k++) {
                    if (this->board[i + k][j + k] != symbol) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }

            // Check Anti diagonal
            if (i + winCondition - 1 < this->rows && j - winCondition + 1 >= 0) {
                bool win = true;
                // Check if there are 4 consecutive symbols
                for (int k = 0; k < winCondition; k++) {
                    if (this->board[i + k][j - k] != symbol) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }
    }
    return false;
}

bool Four_In_A_Row_Board::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

bool Four_In_A_Row_Board::game_is_over() {
    return (is_win() || is_draw());
}

// ---------------------------- PLAYER CLASS

bool Four_In_A_Row_Player::IsValidNumber(const std::string &str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

void Four_In_A_Row_Player::getmove(int &x, int &y) {
    cout << this->name << ", it's your turn.\n";

    while (true) {
        cout << "Enter the column number (1-7) :";
        string yAsString;
        getline(cin, yAsString);

        // Validate the input
        if (!IsValidNumber(yAsString) || yAsString.empty() || yAsString.empty()) {
            cout << "Invalid number. Try again.\n";
            continue;
        }

        y = stoi(yAsString) - 1;    // Convert to zero-based indexing
        x = 5;
        break;
    }
}

// Constructor for the Four_In_A_Row_Player
Four_In_A_Row_Player::Four_In_A_Row_Player(string name, char symbol) : Player<char>(name, symbol) {}

// ---------------------------- RANDOM PLAYER CLASS

// Get a random move
void Four_In_A_Row_Random_Player::getmove(int &x, int &y) {
    y = rand() % this->dimension;  // Random number between 0 and 6
    // Check if column is full
    while (fullColumns.find(y) != fullColumns.end()) {
        y = rand() % this->dimension;
    }

    x = 5;
    cout << this->name << " chooses column: " << y + 1 << endl;
}

// Constructor for the Four_In_A_Row_Random_Player
Four_In_A_Row_Random_Player::Four_In_A_Row_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
}

//--------------------------------------- MAIN FUNCTION

int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Four_In_A_Row_Board();
    cout << "<--------- Welcome To Four In A Row --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    // Create player 1
    if (player1Type == "1") {
        cout << "Please Enter Player 1 name :";
        getline(cin, player1Name);
        players[0] = new Four_In_A_Row_Player(player1Name, 'X');
    } else {
        players[0] = new Four_In_A_Row_Random_Player('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    // Create player 2
    if (player2Type == "1") {
        cout << "Please Enter Player 2 name :";
        getline(cin, player2Name);
        players[1] = new Four_In_A_Row_Player(player2Name, 'O');
    } else {
        players[1] = new Four_In_A_Row_Random_Player('O');
    }

    // Create the game manager
    GameManager<char> Four_In_A_Row_Game(gameBoard, players);
    Four_In_A_Row_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}
