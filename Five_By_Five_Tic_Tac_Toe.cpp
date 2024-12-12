// Author: Nagham Wael Mohamed
// ID: 20231189
// Section: S19
// TA: Ahmed Ihab
// Version: 4.0

/*
 * This is a simple implementation of the Five By Five Tic Tac Toe game.
 * The game is played on a 5x5 board where each cell is filled with either 'X' or 'O'.
 * The game is played between two players:
     ** The first player has the symbol 'X'.
     ** The second player has the symbol 'O'.
 * The players take turns to place their symbol in an empty cell.
 * The player who places more three's in a row, column, or diagonal wins the game.
 * The game ends in a draw if 24 cells are filled and their scores are equal.
*/

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

int n = 0;
string nameX;
bool winX = false;

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

class Five_By_Five_Tic_Tac_Toe_Board : public Board<char> {
private:
    bool draw = false;
    // Declare the helper function
    int count_three_in_a_row(
            char symbol); // private because it doesn't need to be extended to other classes or the game manager
public:
    Five_By_Five_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class Five_By_Five_Tic_Tac_Toe_Player : public Player<char> {
public:
    Five_By_Five_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class Five_By_Five_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    Five_By_Five_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION
// ---------------------------- BOARD CLASS

// Constructor for X_O_Board
Five_By_Five_Tic_Tac_Toe_Board::Five_By_Five_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    this->rows = this->columns = 5;    //5 rows and 5 columns to make the grid
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;   //initialized the board with zeros
        }
    }
    this->n_moves = 0;
}

bool Five_By_Five_Tic_Tac_Toe_Board::update_board(int x, int y, char mark) {
    if (winX) return true;
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            n++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

void Five_By_Five_Tic_Tac_Toe_Board::display_board() {
    cout << "\n     1   2   3   4   5\n";
    cout << "   ---------------------\n";

    for (int i = 0; i < this->rows; ++i) {
        cout << ' ' << i + 1 << " |";
        for (int j = 0; j < this->columns; ++j) {
            cout << " " << (this->board[i][j] ? this->board[i][j] : ' ') << " |";
        }
        cout << "\n   ---------------------\n";
    }
}

int Five_By_Five_Tic_Tac_Toe_Board::count_three_in_a_row(char symbol) {
    int count = 0;

    // Check horizontal
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[i][j] == symbol && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) {
                count++;
            }
        }
    }
    // Check vertical
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j] == symbol && this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol &&
                this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j - 1] == symbol &&
                this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

bool Five_By_Five_Tic_Tac_Toe_Board::is_win() {
    // Calculate scores for each player
    int scoreX = count_three_in_a_row('X');
    int scoreO = count_three_in_a_row('O');

    // Ensure the board is full except for one square
    if (this->n_moves < 24) {
        return false; // Not yet time to determine the winner
    }

    if (winX) {
        cout << nameX << " wins\n";
        return true;
    }
    // Announce the scores
    cout << "\nFinal Scores:\n";
    cout << "Player X: " << scoreX << " three-in-a-rows\n";
    cout << "Player O: " << scoreO << " three-in-a-rows\n";
    if (this->n_moves == 24 && scoreX > scoreO) {
        winX = true;
        return false;
    } else if (this->n_moves == 24 && scoreX == scoreO) {
        draw = true;
        return false;
    }
    return true; // Game over
}

// Return true if 9 moves are done and no winner
bool Five_By_Five_Tic_Tac_Toe_Board::is_draw() {
    return draw;
}

bool Five_By_Five_Tic_Tac_Toe_Board::game_is_over() {
    return is_win() || is_draw();
}

// ---------------------------- PLAYER CLASS

// Constructor for X_O_Player
Five_By_Five_Tic_Tac_Toe_Player::Five_By_Five_Tic_Tac_Toe_Player(string name, char symbol) : Player<char>(name, symbol) {}

void Five_By_Five_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
    if (winX) return;
    if (n == 0) nameX = this->name;
    while (true) {
        cout << "Enter your move in this form(row space column,e.g 1 3): ";
        cin >> x >> y;

        // Convert to 0-based indexing
        x--;
        y--;

        if (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
            cin.clear(); // Clear error flags
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
            cout << "Invalid input. Try again.\n";
        } else {
            break;
        }
    }
}

// ---------------------------- RANDOM PLAYER CLASS

// Constructor for X_O_Random_Player
Five_By_Five_Tic_Tac_Toe_Random_Player::Five_By_Five_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

void Five_By_Five_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    if (winX) return;
    if (n == 0) nameX = this->name;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

//--------------------------------------- MAIN FUNCTION

int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Five_By_Five_Tic_Tac_Toe_Board();
    cout << "<--------- Welcome To Five By Five Tic Tac Toe --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new Five_By_Five_Tic_Tac_Toe_Player(player1Name, 'X');
    } else {
        players[0] = new Five_By_Five_Tic_Tac_Toe_Random_Player('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new Five_By_Five_Tic_Tac_Toe_Player(player2Name, 'O');
    } else {
        players[1] = new Five_By_Five_Tic_Tac_Toe_Random_Player('O');
    }

    GameManager<char> FivebyFive_Tic_Tac_Toe_Game(gameBoard, players);
    FivebyFive_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}
