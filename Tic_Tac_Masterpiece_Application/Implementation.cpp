// Author 1: Esraa Emary Abd El-Salam
// Author 2: Mohammed Atef Abd El-Kader
// Author 3: Nagham Wael Mohamed El-Sayed

// ID 1: 20230054
// ID 2: 20231143
// ID 3: 20231189

// Section: S19
// TA: Ahmed Ihab
// Version: 3.0

//--------------------------------------- HEADERS

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Games.h"
using namespace std;

//--------------------------------------- GLOBAL VARIABLES
//---------------------------- Four_In_A_Row

set<int> fullColumns;

//---------------------------- Five_By_Five_Tic_Tac_Toe

int n = 0;
string nameX;

//---------------------------- Numerical_Tic_Tac_Toe

set<pair<int, int>> availablePositions;
static set<int> firstPlayer = {1, 3, 5, 7, 9};
static set<int> secondPlayer = {0, 2, 4, 6, 8};
bool firstPlayerTurn = true;

//---------------------------- Misere_Tic_Tac_Toe

string name1, name2;
int countNum = 0;

//--------------------------------------- HELPER FUNCTIONS
//---------------------------- Numerical_Tic_Tac_Toe

void operator<<(ostream &out, set<int> &arr) {
    for (auto number: arr) {
        if (number != *arr.rbegin()) cout << number << ", ";
        else cout << number;
    }
}

//--------------------------------------- Pyramid_Tic_Tac_Toe
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

//--------------------------------------- Four_In_A_Row
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

//--------------------------------------- Five_By_Five_Tic_Tac_Toe
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
    if (n == 0) nameX = this->name;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

//--------------------------------------- Word_Tic_Tac_Toe
// ---------------------------- BOARD CLASS

Word_Tic_Tac_Toe_Board::Word_Tic_Tac_Toe_Board() {
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

bool Word_Tic_Tac_Toe_Board::update_board(int x, int y, char symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

void Word_Tic_Tac_Toe_Board::setDic(vector<std::string> lines) {
    dic = lines;
}

void Word_Tic_Tac_Toe_Board::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n   ___________________\n";
        cout << i + 1 << "  " << "|  ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(1) << this->board[i][j] << "  |  ";
        }
    }
    cout << "\n   ___________________\n      1     2     3\n\n";
}

bool Word_Tic_Tac_Toe_Board::is_win() {
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
        if (find(dic.begin(), dic.end(), pattern) != dic.end()) {
            over = true;
            return true;
        }
    }
    return false;
}

bool Word_Tic_Tac_Toe_Board::is_draw() {
    if (this->n_moves == 9) return true;                                        // Check board is full.
    return false;
}

bool Word_Tic_Tac_Toe_Board::game_is_over() {
    return over;
}

// ---------------------------- PLAYER CLASS

char Word_Tic_Tac_Toe_Player::getChar() {
    string character;
    char c;
    cout << "Please enter a char:";
    getline(cin, character);
    while (true) {
        if (character.size() != 1) {
            cout << "Please enter a valid char:";
            getline(cin, character);
            continue;
        }
        if (character[0] < 65 || (character[0] > 90 && character[0] < 97) ||
            character[0] > 122) { // Check input is a char.
            cout << "Please enter a valid char:";
            getline(cin, character);
            continue;
        }
        c = character[0];
        break;
    }
    return c;
}

void Word_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
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
    char c = getChar();                                                     // Get char.
    this->symbol = c;
}

Word_Tic_Tac_Toe_Player::Word_Tic_Tac_Toe_Player(std::string name, char symbol) : Player<char>(name, symbol) {}

// ---------------------------- RANDOM PLAYER CLASS

void Word_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    x = rand() % this->dimension;                                       // Random number between 0 and 2
    y = rand() % this->dimension;
    int num = rand() % 26;                                              // Generate a random char.
    num += 97;
    this->symbol = static_cast<char>(num);
}

Word_Tic_Tac_Toe_Random_Player::Word_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
}

//--------------------------------------- Numerical_Tic_Tac_Toe
// ---------------------------- BOARD CLASS

Numerical_Tic_Tac_Toe_Board::Numerical_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new char *[this->rows];
    // Initialize the board with zeros
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize with zero
        }
    }
    this->n_moves = 0;
    // Initialize the global variables for each new game.
    firstPlayer = {1, 3, 5, 7, 9};
    secondPlayer = {0, 2, 4, 6, 8};
    firstPlayerTurn = true;
    availablePositions.clear();
}

// Update the board with the new move
bool Numerical_Tic_Tac_Toe_Board::update_board(int x, int y, char symbol) {
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

    // Random player
    availablePositions.insert({x, y});
    return true;
}

void Numerical_Tic_Tac_Toe_Board::display_board() {
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

bool Numerical_Tic_Tac_Toe_Board::is_win() {
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

bool Numerical_Tic_Tac_Toe_Board::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

bool Numerical_Tic_Tac_Toe_Board::game_is_over() {
    return (is_win() || is_draw());
}

// ---------------------------- PLAYER CLASS

bool Numerical_Tic_Tac_Toe_Player::IsValidNumber(const std::string &str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

void Numerical_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
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
        } else break;
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
        } else break;
    }

    this->symbol = numberAsString[0] - '0';     // Convert to integer

    // Get the row and column numbers
    while (true) {
        cout << "Enter the row number (1-3) :";
        string xAsString;
        getline(cin, xAsString);
        cout << "Enter the column number (1-3) :";
        string yAsString;
        getline(cin, yAsString);

        // Validate the input
        if (!IsValidNumber(xAsString) || !IsValidNumber(yAsString) || xAsString.empty() || yAsString.empty()) {
            cout << "Invalid number. Try again.\n";
            continue;
        }

        x = stoi(xAsString) - 1;    // Convert to zero-based indexing
        y = stoi(yAsString) - 1;    // Convert to zero-based indexing
        break;
    }
}

Numerical_Tic_Tac_Toe_Player::Numerical_Tic_Tac_Toe_Player(string name, char symbol) : Player<char>(name, symbol) {}

// ---------------------------- RANDOM PLAYER CLASS

void Numerical_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    int randomIndex = rand() % this->availableNumbers.size();
    this->symbol = this->availableNumbers[randomIndex];

    // Get the row and column numbers
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    // Check if the position is already taken
    while (availablePositions.find({x, y}) != availablePositions.end()) {
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % this->dimension;
    }

    cout << this->name << " chooses number: " << this->availableNumbers[randomIndex] << endl;
    cout << "and placed it in row: " << x + 1 << " and column: " << y + 1 << endl;

    this->availableNumbers.erase(this->availableNumbers.begin() + randomIndex);
}

Numerical_Tic_Tac_Toe_Random_Player::Numerical_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
    // Populate the set with either even or odd numbers
    if (symbol == '1') {
        this->availableNumbers = {1, 3, 5, 7, 9};
    } else {  // Odd numbers
        this->availableNumbers = {0, 2, 4, 6, 8};
    }
}

//--------------------------------------- Misere_Tic_Tac_Toe
// ---------------------------- BOARD CLASS

void Misere_Tic_Tac_Toe_Board::getNames(std::string namePlayer1, std::string namePlayer2) {
    name1 = namePlayer1;
    name2 = namePlayer2;
}

// Constructor for X_O_Board
Misere_Tic_Tac_Toe_Board::Misere_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    this->rows = this->columns = 3;    //3 rows and 3 columns to make the grid
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;   //initialized the board with zeros
        }
    }
    this->n_moves = 0;
}

bool Misere_Tic_Tac_Toe_Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            countNum++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

void Misere_Tic_Tac_Toe_Board::display_board() {
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

// Returns true if there is any winner
bool Misere_Tic_Tac_Toe_Board::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] &&
             this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] &&
             this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
bool Misere_Tic_Tac_Toe_Board::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

bool Misere_Tic_Tac_Toe_Board::game_is_over() {
    return is_win() || is_draw();
}

// ---------------------------- PLAYER CLASS

// Constructor for X_O_Player
Misere_Tic_Tac_Toe_Player::Misere_Tic_Tac_Toe_Player(string name, char symbol) : Player<char>(name, symbol) {}

void Misere_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
    if (countNum % 2 == 0) this->name = name2;
    else this->name = name1;

    while (true) {
        cout << "Enter your move in this form(row space column,e.g 1 3): ";
        cin >> x >> y;

        // Convert to 0-based indexing
        x--;
        y--;

        if (cin.fail() || x < 0 || x >= 3 || y < 0 || y >= 3) {
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
Misere_Tic_Tac_Toe_Random_Player::Misere_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

void Misere_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    if (countNum % 2 == 0) this->name = name2;
    else this->name = name1;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

//--------------------------------------- Ultimate_Tic_Tac_Toe
//---------------------------- BOARD CLASS
//---------------- SMALL BOARD

TicTacToeBoard::TicTacToeBoard() {
    // Initialize a 3x3 board
    board.resize(3, vector<char>(3, 0));
}

void TicTacToeBoard::display_board() {
    for (auto &row: board) {
        for (auto &cell: row) {
            cout << (cell == 0 ? '.' : cell) << " ";
        }
        cout << endl;
    }
}

bool TicTacToeBoard::update_board(int x, int y, char symbol) {
    if (board[x][y] == 0) {
        board[x][y] = symbol;
        return true;
    }
    return false;
}

bool TicTacToeBoard::is_win() {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

bool TicTacToeBoard::is_draw() {
    for (auto &row: board) {
        for (auto &cell: row) {
            if (cell == 0) return false; // Empty cell found
        }
    }
    return !is_win(); // Draw if no win and board is full
}

bool TicTacToeBoard::game_is_over() {
    return is_win() || is_draw();
}

void TicTacToeBoard::set_cell(int x, int y, char value) {
    board[x][y] = value;
}

char TicTacToeBoard::get_cell(int x, int y) const {
    return board[x][y];
}

//---------------- BIG BOARD

// Constructor for X_O_Board
Ultimate_Tic_Tac_Toe_Board::Ultimate_Tic_Tac_Toe_Board() { //the constructor here is where we initialize the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            smallBoards[i][j] = new TicTacToeBoard();
            // Each small board is a 3x3 Tic-Tac-Toe
            bigBoard[i][j] = 0; // Initially, no winner in any small board
        }
    }
    this->n_moves = 0;
}

bool Ultimate_Tic_Tac_Toe_Board::update_board(int x, int y, char symbol) {
    int smallX = x / 3, smallY = y / 3; // Determine which small board
    int cellX = x % 3, cellY = y % 3;   // Determine cell in the small board

    // Check if the small board is actually a TicTacToeBoard
    TicTacToeBoard *smallBoardPtr = dynamic_cast<TicTacToeBoard *>(smallBoards[smallX][smallY]);
    if (smallBoardPtr != nullptr) {
        // Ensure the small board is not already claimed
        if (bigBoard[smallX][smallY] != 0) {
            cout << "This board has already been claimed!" << endl;
            return false;
        }

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

void Ultimate_Tic_Tac_Toe_Board::display_board() {
    int count = 1;
    cout << "\nStatus:\n";
    cout << "      1  2  3     4  5  6     7  8  9\n";
    cout << "   -------------------------------------\n";
    for (int i = 0; i < 3; i++) {
        for (int row = 0; row < 3; row++) {
            cout << count++ << "  | ";
            for (int j = 0; j < 3; j++) {
                for (int col = 0; col < 3; col++) {
                    // Check if the small board is actually a TicTacToeBoard
                    if (dynamic_cast<TicTacToeBoard *>(smallBoards[i][j]) != nullptr) {
                        char mark = dynamic_cast<TicTacToeBoard *>(smallBoards[i][j])->get_cell(row, col);
                        cout << " " << (mark == 0 ? '.' : mark) << " ";
                    }
                }
                cout << " | "; // Separator between small boards
            }
            cout << endl;
        }
        cout << "   -------------------------------------\n";
    }
}

// Returns true if there is any winner
bool Ultimate_Tic_Tac_Toe_Board::is_win() {
    // Check rows, columns, and diagonals in the big board
    for (int i = 0; i < 3; i++) {
        if ((bigBoard[i][0] != 0 && bigBoard[i][0] == bigBoard[i][1] && bigBoard[i][1] == bigBoard[i][2]) || // Row
            (bigBoard[0][i] != 0 && bigBoard[0][i] == bigBoard[1][i] && bigBoard[1][i] == bigBoard[2][i])) { // Column
            cout << "Player " << bigBoard[i][0] << " wins the game!" << endl; // Declare winner
            over = true;
            return true;
        }
    }
    // Check diagonals
    if ((bigBoard[0][0] != 0 && bigBoard[0][0] == bigBoard[1][1] && bigBoard[1][1] == bigBoard[2][2]) ||
        (bigBoard[0][2] != 0 && bigBoard[0][2] == bigBoard[1][1] && bigBoard[1][1] == bigBoard[2][0])) {
        cout << "Player " << bigBoard[1][1] << " wins the game!" << endl; // Declare winner
        over = true;
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
bool Ultimate_Tic_Tac_Toe_Board::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

bool Ultimate_Tic_Tac_Toe_Board::game_is_over() {
    return over || is_draw();
}

// ---------------------------- PLAYER CLASS

// Constructor for X_O_Player
Ultimate_Tic_Tac_Toe_Player::Ultimate_Tic_Tac_Toe_Player(string name, char symbol) : Player<char>(name, symbol) {}

void Ultimate_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
    while (true) {
        cout << "Enter your move (row space column, e.g., 1 3): ";
        cin >> x >> y;
        x--;
        y--; // Convert to 0-based indexing
        if (cin.fail() || x < 0 || x >= 9 || y < 0 || y >= 9) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        break;
    }
}

// ---------------------------- RANDOM PLAYER CLASS

// Constructor for X_O_Random_Player
Ultimate_Tic_Tac_Toe_Random_Player::Ultimate_Tic_Tac_Toe_Random_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

void Ultimate_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

//--------------------------------------- SUS
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
