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

#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

set<int> fullColumns;

//--------------------------------------- CLASSES

template<typename T>
class Four_In_A_Row_Board : public Board<T> {
public:
    Four_In_A_Row_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template<typename T>
class Four_In_A_Row_Player : public Player<T> {
public:
    Four_In_A_Row_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
    bool IsValidNumber(const string& str);
};

template<typename T>
class Four_In_A_Row_Random_Player : public RandomPlayer<T> {
public:
    explicit Four_In_A_Row_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

// Constructor for the Four_In_A_Row_Board
template<typename T>
Four_In_A_Row_Board<T>::Four_In_A_Row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    // Initialize the board with zeros
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize with zero
        }
    }
    this->n_moves = 0;
}

// Update the board with the new move
template<typename T>
bool Four_In_A_Row_Board<T>::update_board(int x, int y, T symbol) {
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

template<typename T>
void Four_In_A_Row_Board<T>::display_board() {
    cout << "\n    1   2   3   4   5   6   7\n";
    cout << "  -----------------------------\n";

    for (int i = 0; i < this->rows; i++) {
        cout << "  |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << setw(1);
            if (this->board[i][j] == 0) {
                cout << " ";
            }
            else cout << this->board[i][j] ;
            cout << " |";
        }
        cout << "\n  -----------------------------\n";
    }
    cout << endl;
}

template<typename T>
bool Four_In_A_Row_Board<T>::is_win() {
    const int winCondition = 4;     // Number of consecutive symbols to win

    // i -> row, j -> column, k -> number of consecutive symbols;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            T symbol = this->board[i][j];
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

template<typename T>
bool Four_In_A_Row_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template<typename T>
bool Four_In_A_Row_Board<T>::game_is_over() {
    return (is_win() || is_draw());
}

template<typename T>
bool Four_In_A_Row_Player<T>::IsValidNumber(const std::string &str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

template<typename T>
void Four_In_A_Row_Player<T>::getmove(int &x, int &y) {
    cout << this->name << ", it's your turn.\n";

    while (true) {
        cout << "Enter the column number (1-7) :";
        string yAsString; getline(cin, yAsString);

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
template<typename T>
Four_In_A_Row_Player<T>::Four_In_A_Row_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get a random move
template<typename T>
void Four_In_A_Row_Random_Player<T>::getmove(int &x, int &y) {
    y = rand() % this->dimension;  // Random number between 0 and 6
    // Check if column is full
    while (fullColumns.find(y) != fullColumns.end()) {
        y = rand() % this->dimension;
    }

    x = 5;
    cout << this->name << " chooses column: " << y + 1 << endl;
}

// Constructor for the Four_In_A_Row_Random_Player
template<typename T>
Four_In_A_Row_Random_Player<T>::Four_In_A_Row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
}

#endif // FOUR_IN_A_ROW_H