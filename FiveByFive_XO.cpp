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
int player = 0;
template<typename T>
class FivebyFive_Tic_Tac_Toe_Board : public Board<T> {
private:
    bool over = false;
    // Declare the helper function
    int count_three_in_a_row(T symbol); //private because it doesn't need to be extended to other classes or the game manager
//    static int player;
public:
    FivebyFive_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
//    static int getPlayer(){return player;}
};

template<typename T>
class FivebyFive_Tic_Tac_Toe_Player : public Player<T> {
public:
    FivebyFive_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};

template<typename T>
class FivebyFive_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    FivebyFive_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};

template<typename T>
class FivebyFive_Tic_Tac_Toe_Game_Manager:public GameManager<T>{
public:
    FivebyFive_Tic_Tac_Toe_Game_Manager(Board<T>*, Player<T>* playerPtr[2]);
    void run();
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <cctype>
using namespace std;




template <typename T>
void FivebyFive_Tic_Tac_Toe_Game_Manager<T>::run() {
    int x, y;

    this->boardPtr->display_board();

    while (!this->boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            this->players[i]->getmove(x, y);
            while (!this->boardPtr->update_board(x, y, this->players[i]->getsymbol())) {
                this->players[i]->getmove(x, y);
            }
            this->boardPtr->display_board();
            if (this->boardPtr->is_win()) {
                if (player==1){
                    cout << this->players[1]->getname() << " wins\n";
                    return;
                }
                else if (player==2){
                    cout << this->players[2]->getname() << " wins\n";
                    return;
                }
                else{
                    cout << this->players[i]->getname() << " wins\n";
                    return;
                }
            }
            if (this->boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}

// Constructor for X_O_Board
template <typename T>
FivebyFive_Tic_Tac_Toe_Board<T>::FivebyFive_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    this->rows = this->columns = 5;    //5 rows and 5 columns to make the grid
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;   //initialized the board with zeros
        }
    }
    this->n_moves = 0;
}



template <typename T>
bool FivebyFive_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}



template<typename T>
void FivebyFive_Tic_Tac_Toe_Board<T>::display_board() {
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



template <typename T>
int FivebyFive_Tic_Tac_Toe_Board<T>::count_three_in_a_row(T symbol) {
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
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j - 1] == symbol && this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }

    return count;
}



// Returns true if there is any winner
template <typename T>
bool FivebyFive_Tic_Tac_Toe_Board<T>::is_win() {
    // Ensure the board is full except for one square
    if (this->n_moves < 24) {
        return false; // Not yet time to determine the winner
    }

    // Calculate scores for each player
    int scoreX = count_three_in_a_row('X');
    int scoreO = count_three_in_a_row('O');

    // Announce the winner
    std::cout << "\nFinal Scores:\n";
    std::cout << "Player X: " << scoreX << " three-in-a-rows\n";
    std::cout << "Player O: " << scoreO << " three-in-a-rows\n";

    if (scoreX > scoreO) {
//        std::cout << "Player X wins!\n";
        player = 1;
    } else if (scoreO > scoreX) {
//        std::cout << "Player O wins!\n";
        player = 2;
    } else {
//        std::cout << "It's a draw!\n";
    }

    // The game is over, return true to signal completion
    return true;

}



// Return true if 9 moves are done and no winner
template <typename T>
bool FivebyFive_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 24 && !is_win());
}



template <typename T>
bool FivebyFive_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}



//--------------------------------------

// Constructor for X_O_Player
template <typename T>
FivebyFive_Tic_Tac_Toe_Player<T>::FivebyFive_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}



template <typename T>
void FivebyFive_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "Enter your move in this form(row space column,e.g 1 3): ";
        cin >> x >> y;

        // Convert to 0-based indexing
        x--; y--;

        if (cin.fail() || x < 0 || x >= 5 || y < 0 || y >= 5) {
            cin.clear(); // Clear error flags
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
            cout << "Invalid input. Try again.\n";
        } else {
            break;
        }
    }
}



// Constructor for X_O_Random_Player
template <typename T>
FivebyFive_Tic_Tac_Toe_Random_Player<T>::FivebyFive_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}



template <typename T>
void FivebyFive_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}






//--------------------------------------- MAIN FUNCTION
int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new FivebyFive_Tic_Tac_Toe_Board<char>();

    cout << "<--------- Welcome To 5x5 Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    cout << "Please enter Player 1 name:";
    getline(cin, player1Name);

    if (player1Type == "1") {
        players[0] = new FivebyFive_Tic_Tac_Toe_Player<char>(player1Name, 'X');
    } else {
        players[0] = new FivebyFive_Tic_Tac_Toe_Random_Player<char>('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    cout << "Please enter Player 2 name:";
    getline(cin, player2Name);

    if (player2Type == "1") {
        players[1] = new FivebyFive_Tic_Tac_Toe_Player<char>(player2Name,'O');
    }
    else {
        players[1] = new FivebyFive_Tic_Tac_Toe_Random_Player<char>('O');
    }

    // Use the customized MisereGameManager
    FivebyFive_Tic_Tac_Toe_Game_Manager<char> FivebyFive_Tic_Tac_Toe_Game(gameBoard, players);
    FivebyFive_Tic_Tac_Toe_Game.run();

    return 0;
}
