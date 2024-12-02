// Author: Nagham Wael Mohamed
// ID: 20231189
// Section: S19
// TA: Ahmed Ihab
// Version: 1.0
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
template<typename T>
class Ultimate_Tic_Tac_Toe_Board : public Board<T> {
private:
    bool over = false;
    Board<char>* smallBoards[3][3]; // 3x3 grid of smaller boards
    char bigBoard[3][3]; // To track who won each smaller board
public:
    Ultimate_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template<typename T>
class Ultimate_Tic_Tac_Toe_Player : public Player<T> {
    char bigBoard[3][3];
public:
    Ultimate_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};
template<typename T>
class Ultimate_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};
//--------------------------------------- IMPLEMENTATION
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;


#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
using namespace std;

class TicTacToeBoard : public Board<char> {
private:
    vector<vector<char>> board; // Define your own board

public:
    // Getter for board cell
    char get_cell(int x, int y) const {
        return board[x][y];
    }

    // Setter for board cell
    void set_cell(int x, int y, char value) {
        board[x][y] = value;
    }

    TicTacToeBoard() {
        // Initialize a 3x3 board
        board.resize(3, vector<char>(3, 0));
    }

    bool update_board(int x, int y, char symbol) override {
        if (board[x][y] == 0) {
            board[x][y] = symbol;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (auto &row : board) {
            for (auto &cell : row) {
                cout << (cell == 0 ? '.' : cell) << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        // Check rows, columns, and diagonals for a win
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
            if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
        }
        if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
        if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        for (auto &row : board) {
            for (auto &cell : row) {
                if (cell == 0) return false; // Empty cell found
            }
        }
        return !is_win(); // Draw if no win and board is full
    }

    bool game_is_over() override{
        return is_win() || is_draw();
    }
};



// Constructor for X_O_Board
template <typename T>
Ultimate_Tic_Tac_Toe_Board<T>::Ultimate_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            smallBoards[i][j] = new TicTacToeBoard();
            // Each small board is a 3x3 Tic-Tac-Toe
            bigBoard[i][j] = 0; // Initially, no winner in any small board
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    int smallX = x / 3, smallY = y / 3; // Determine which small board
    int cellX = x % 3, cellY = y % 3;   // Determine cell in the small board

    // Check if the small board is actually a TicTacToeBoard
    TicTacToeBoard* smallBoardPtr = dynamic_cast<TicTacToeBoard*>(smallBoards[smallX][smallY]);
    if (smallBoardPtr != nullptr) { // If it's a valid TicTacToeBoard
        // Ensure move is valid within the smaller board
        if (smallBoardPtr->get_cell(cellX, cellY) == 0) {
            smallBoardPtr->update_board(cellX, cellY, symbol);

            // Check if the small board is won or drawn
            if (smallBoardPtr->is_win()) {
                bigBoard[smallX][smallY] = symbol; // Mark winner in big board
            } else if (smallBoardPtr->is_draw()) {
                bigBoard[smallX][smallY] = '-'; // Mark as draw
            }
            this->n_moves++;
            return true;
        }
    }
    return false; // Return false if it's not a TicTacToeBoard or the move is invalid
}

template <typename T>
void Ultimate_Tic_Tac_Toe_Board<T>::display_board() {
    cout << "\nBig Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (bigBoard[i][j] == 0 ? '.' : bigBoard[i][j]) << " ";
        }
        cout << endl;
    }
    cout << "\nSmall Boards:\n";
    for (int i = 0; i < 3; i++) {
        for (int row = 0; row < 3; row++) {
            for (int j = 0; j < 3; j++) {
                for (int col = 0; col < 3; col++) {
                    // Check if the small board is actually a TicTacToeBoard
                    if (dynamic_cast<TicTacToeBoard*>(smallBoards[i][j]) != nullptr) {
                        char mark = dynamic_cast<TicTacToeBoard*>(smallBoards[i][j])->get_cell(row, col);
                        cout << (mark == 0 ? '.' : mark) << " ";
                    }
                }
                cout << " | "; // Separator between small boards
            }
            cout << endl;
        }
        cout << "-------------------------\n";
    }
}

// Returns true if there is any winner
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_win() {
    // Check rows, columns, and diagonals in the big board
    for (int i = 0; i < 3; i++) {
        if ((bigBoard[i][0] != 0 && bigBoard[i][0] == bigBoard[i][1] && bigBoard[i][1] == bigBoard[i][2]) || // Row
            (bigBoard[0][i] != 0 && bigBoard[0][i] == bigBoard[1][i] && bigBoard[1][i] == bigBoard[2][i])) { // Column
            return true;
        }
    }
    // Check diagonals
    if ((bigBoard[0][0] != 0 && bigBoard[0][0] == bigBoard[1][1] && bigBoard[1][1] == bigBoard[2][2]) ||
        (bigBoard[0][2] != 0 && bigBoard[0][2] == bigBoard[1][1] && bigBoard[1][1] == bigBoard[2][0])) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}
template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------
// Constructor for X_O_Player
template <typename T>
Ultimate_Tic_Tac_Toe_Player<T>::Ultimate_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void Ultimate_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "Enter your move (row space column, e.g., 1 3): ";
        cin >> x >> y;
        x--; y--; // Convert to 0-based indexing
        if (cin.fail() || x < 0 || x >= 9 || y < 0 || y >= 9) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        int smallX = x / 3, smallY = y / 3;
        if (this->bigBoard[smallX][smallY] != 0) {
            cout << "Small board already won or full. Choose a valid cell.\n";
            continue;
        }
        break;
    }
}

// Constructor for X_O_Random_Player
template <typename T>
Ultimate_Tic_Tac_Toe_Random_Player<T>::Ultimate_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void Ultimate_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
//--------------------------------------- MAIN FUNCTION
int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Ultimate_Tic_Tac_Toe_Board<char>();
    cout << "<--------- Welcome To Ultimate Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    cout << "Please enter Player 1 name:";
    getline(cin, player1Name);
    if (player1Type == "1") {
        players[0] = new Ultimate_Tic_Tac_Toe_Player<char>(player1Name, 'X');
    } else {
        players[0] = new Ultimate_Tic_Tac_Toe_Random_Player<char>('X');
    }
    checkPlayerType(player2Type, 2);                // Get info of player 2.
    cout << "Please enter Player 2 name:";
    getline(cin, player2Name);
    if (player2Type == "1") {
        players[1] = new Ultimate_Tic_Tac_Toe_Player<char>(player2Name,'O');
    }
    else {
        players[1] = new Ultimate_Tic_Tac_Toe_Random_Player<char>('O');
    }
    // Use the customized MisereGameManager
    GameManager<char> Ultimate_Tic_Tac_Toe_Game(gameBoard, players);
    Ultimate_Tic_Tac_Toe_Game.run();
    return 0;
}
