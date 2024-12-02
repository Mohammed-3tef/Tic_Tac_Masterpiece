// Author: Esraa Emary Abd El-Salam
// ID: 20230054
// Section: S19
// TA: Ahmed Ihab
// Version: 3.0

/*
 * This is a simple implementation of the Word Tic Tac Toe game.
 * The game is played on a 3x3 board where each cell is filled with a letter.
 * The game is played between two players.
 * The players take turns to place a letter in an empty cell.
 * The player who places a word from the dictionary wins the game.
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
    for (int i = 0; i < fileContent.size(); ++i) {
        if (fileContent[i] == '\n') {
            lines.push_back(s);
            s = "";
        } else {
            s += fileContent[i];
        }
    }
    lines.push_back(s);
    return lines;
}

//--------------------------------------- CLASSES

template<typename T>
class Word_Tic_Tac_Toe_Board : public Board<T> {
private:
    vector<string> dic;
    bool over = false;
public:
    Word_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void setDic(vector<string> lines);
};

template<typename T>
class Word_Tic_Tac_Toe_Player : public Player<T> {
public:
    Word_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y) override;
    char getChar();
};

template<typename T>
class Word_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Word_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- IMPLEMENTATION

template<typename T>
Word_Tic_Tac_Toe_Board<T>::Word_Tic_Tac_Toe_Board() {
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

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

template<typename T>
void Word_Tic_Tac_Toe_Board<T>::setDic(vector<std::string> lines) {
    dic = lines;
}

template<typename T>
void Word_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n   ___________________\n";
        cout << i + 1 << "  " << "|  ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(1) << this->board[i][j] << "  |  ";
        }
    }
    cout << "\n   ___________________\n      1     2     3\n\n";
}

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_win() {
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

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_draw() {
    if (this->n_moves == 9) return true;                                        // Check board is full.
    return false;
}

template<typename T>
bool Word_Tic_Tac_Toe_Board<T>::game_is_over() {
    return over;
}

template<typename T>
char Word_Tic_Tac_Toe_Player<T>::getChar() {
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
        if (character[0] < 65 || (character[0] > 90 && character[0] < 97) || character[0] > 122) { // Check input is a char.
            cout << "Please enter a valid char:";
            getline(cin, character);
            continue;
        }
        c = character[0];
        break;
    }
    return c;
}

template<typename T>
void Word_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {
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

template<typename T>
Word_Tic_Tac_Toe_Player<T>::Word_Tic_Tac_Toe_Player(std::string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void Word_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;                                       // Random number between 0 and 2
    y = rand() % this->dimension;
    int num = rand() % 26;                                              // Generate a random char.
    num += 97;
    this->symbol = static_cast<char>(num);
}

template<typename T>
Word_Tic_Tac_Toe_Random_Player<T>::Word_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
}

//--------------------------------------- MAIN FUNCTION

int main() {
    cout << "<--------- Welcome To Word Tic Tac Toe --------->\n";
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    Word_Tic_Tac_Toe_Board<char> *gameBoard = new Word_Tic_Tac_Toe_Board<char>();
    vector<string> lines = getFile();
    gameBoard->setDic(lines);

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new Word_Tic_Tac_Toe_Player<char>(player1Name, 'a');
    } else {
        players[0] = new Word_Tic_Tac_Toe_Random_Player<char>('a');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new Word_Tic_Tac_Toe_Player<char>(player2Name, 'a');
    } else {
        players[1] = new Word_Tic_Tac_Toe_Random_Player<char>('a');
    }

    GameManager<char> Pyramid_Tic_Tac_Toe_Game(gameBoard, players);
    Pyramid_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nThanks For Playing My Game :)";
}
