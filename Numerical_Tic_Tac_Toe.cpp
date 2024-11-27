// Author: Mohammed Atef Abd El-Kader.
// ID: 20231143
// Section: S19
// TA: Ahmed Ihab
// Version: 3.0

/*
 * This is a simple implementation of the Numerical Tic Tac Toe game.
 * The game is played on a 3x3 board where each cell is filled with a number from 0 to 9.
 * The game is played between two players:
    ** The first player has the odd numbers {1, 3, 5, 7, 9}
    ** The second player has the even numbers {0, 2, 4, 6, 8}.
 * The players take turns to place a number in an empty cell.
 * The player who places three numbers that sum up to 15 in a row, column, or diagonal wins the game.
 * The game ends in a draw if all cells are filled and no player wins.
*/

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES

static set<int> firstPlayer = {1, 3, 5, 7, 9};
static set<int> secondPlayer = {0, 2, 4, 6, 8};
bool firstPlayerTurn = true;

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

void operator<<(ostream& out, set<int>& arr){
    for (auto number : arr) {
        if (number != *arr.rbegin()) cout << number << ", ";
        else cout << number;
    }
}

bool IsValidNumber(const string& str) {
    for (char character : str) {
        if (!isdigit(character)) return false;
    }
    return true;
}

//--------------------------------------- CLASSES

template<typename T>
class Numerical_Tic_Tac_Toe_Board : public Board<T> {
private:
    int row_sums[3] = {0};  // Sum of each row
    int col_sums[3] = {0};  // Sum of each column
    int diag_sum[2] = {0};  // Sum of diagonals
public:
    Numerical_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template<typename T>
class Numerical_Tic_Tac_Toe_Player : public Player<T> {
public:
    Numerical_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
};

template<typename T>
class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    explicit Numerical_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

template<typename T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 3;
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
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    // Validate move
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        cout << "Invalid move. Try again.\n";
        return false;
    }

    // Update board and related sums
    this->board[x][y] = symbol + '0';
    row_sums[x] += symbol;
    col_sums[y] += symbol;
    if (x == y) diag_sum[0] += symbol;      // Main diagonal
    if (x + y == 2) diag_sum[1] += symbol;  // Anti-diagonal

    this->n_moves++;
    if (firstPlayerTurn) {
        firstPlayer.erase(symbol);
    } else {
        secondPlayer.erase(symbol);
    }
    firstPlayerTurn = !firstPlayerTurn;
    return true;
}

template<typename T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board() {
    cout << "\n     1   2   3\n";
    cout << "   -------------\n";

    for (int i = 0; i < this->rows; i++) {
        cout << ' ' << i + 1 << " |";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << setw(1);

            if (this->board[i][j] == 0) cout << " ";
            else cout << this->board[i][j];

            cout << " |";
        }
        cout << "\n   -------------\n";
    }
    cout << endl;
}

template<typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_win() {
    // Check horizontal
    for (int i = 0; i < this->rows; i++) {
        int countRowCells = 0;          // Reset for each row

        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0) countRowCells++;
        }
        if (countRowCells == 3 && row_sums[i] == 15) return true;
    }

    // Check vertical
    for (int j = 0; j < this->columns; j++) {
        int countColCells = 0;          // Reset for each column

        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][j] != 0) countColCells++;
        }
        if (countColCells == 3 && col_sums[j] == 15) return true;
    }

    // Check diagonals
    int countDiagCells = 0, countAntiDiagCells = 0;
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][i] != 0) countDiagCells++;
        if (this->board[i][this->columns - 1 - i] != 0) countAntiDiagCells++;
    }
    if ((countDiagCells == 3 && diag_sum[0] == 15) || (countAntiDiagCells == 3 && diag_sum[1] == 15)) {
        return true;
    }

    // If no win condition is met
    return false;
}

template<typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over() {
    return (is_win() || is_draw());
}

template<typename T>
void Numerical_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {
    string numberAsString;
    cout << this->name << ", it's your turn.\n";

    // First player's turn.
    while (firstPlayerTurn) {
        cout << "Enter your available number [";
        cout << firstPlayer;
        cout << "] :";
        getline(cin, numberAsString);

        // Validate the input
        if (!IsValidNumber(numberAsString) || numberAsString.empty()) {
            cout << "Invalid number. Try again.\n";
            continue;
        }

        // Check if the number is available
        else if (firstPlayer.find(stoi(numberAsString)) == firstPlayer.end()) {
            cout << "Number already used. Try again.\n";
            continue;
        }
        else break;
    }

    // Second player's turn.
    while (!firstPlayerTurn) {
        cout << "Enter your available number [";
        cout << secondPlayer;
        cout << "] :";
        getline(cin, numberAsString);

        // Validate the input
        if (!IsValidNumber(numberAsString) || numberAsString.empty()) {
            cout << "Invalid number. Try again.\n";
            continue;
        }

        // Check if the number is available
        else if (secondPlayer.find(stoi(numberAsString)) == secondPlayer.end()) {
            cout << "Number already used. Try again.\n";
            continue;
        }
        else break;
    }

    this->symbol = numberAsString[0] - '0';     // Convert to integer

    // Get the row and column numbers
    while (true) {
        cout << "Enter the row number (1-3) :";
        string xAsString; getline(cin, xAsString);
        cout << "Enter the column number (1-3) :";
        string yAsString; getline(cin, yAsString);

        // Validate the input
        if (!IsValidNumber(xAsString) || !IsValidNumber(yAsString) || xAsString.empty() || yAsString.empty()) {
            cout << "Invalid number. Try again.\n";
            continue;
        }

        x = stoi(xAsString) -1;    // Convert to zero-based indexing
        y = stoi(yAsString) -1;    // Convert to zero-based indexing
        break;
    }
}

template<typename T>
Numerical_Tic_Tac_Toe_Player<T>::Numerical_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template<typename T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
}

//--------------------------------------- MAIN FUNCTION

int main() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Numerical_Tic_Tac_Toe_Board<char>();

    cout << "<--------- Welcome To Numerical Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    cout << "Please enter Player 1 name:";
    getline(cin, player1Name);

    if (player1Type == "1") {
        players[0] = new Numerical_Tic_Tac_Toe_Player<char>(player1Name, '1');
    } else {
        players[0] = new Numerical_Tic_Tac_Toe_Random_Player<char>('2');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    cout << "Please enter Player 2 name:";
    getline(cin, player2Name);

    if (player2Type == "1") {
        players[1] = new Numerical_Tic_Tac_Toe_Player<char>(player2Name,'1');
    }
    else {
        players[1] = new Numerical_Tic_Tac_Toe_Random_Player<char>('2');
    }

    GameManager<char> Numerical_Tic_Tac_Toe_Game(gameBoard, players);
    Numerical_Tic_Tac_Toe_Game.run();
    cout << "\n\tThanks For Playing My Game :)" << endl;

    return 0;
}