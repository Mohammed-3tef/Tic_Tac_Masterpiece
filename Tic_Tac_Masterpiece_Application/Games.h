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

#ifndef GAMES_H
#define GAMES_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

//--------------------------------------- Pyramid_Tic_Tac_Toe

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

//--------------------------------------- Four_In_A_Row

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

//--------------------------------------- Five_By_Five_Tic_Tac_Toe

class FivebyFive_Tic_Tac_Toe_Board : public Board<char> {
private:
    bool winX = false;
    bool draw = false;
    // Declare the helper function
    int count_three_in_a_row(
            char symbol); // private because it doesn't need to be extended to other classes or the game manager
public:
    FivebyFive_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class FivebyFive_Tic_Tac_Toe_Player : public Player<char> {
public:
    FivebyFive_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class FivebyFive_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    FivebyFive_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- Word_Tic_Tac_Toe

class Word_Tic_Tac_Toe_Board : public Board<char> {
private:
    vector<string> dic;
    bool over = false;
public:
    Word_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void setDic(vector<string> lines);
};

class Word_Tic_Tac_Toe_Player : public Player<char> {
public:
    Word_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
    char getChar();
};

class Word_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    Word_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- Numerical_Tic_Tac_Toe

class Numerical_Tic_Tac_Toe_Board : public Board<char> {
private:
    int row_sums[3] = {0};      // Sum of each row
    int col_sums[3] = {0};      // Sum of each column
    int diag_sum[2] = {0};      // Sum of diagonals
public:
    Numerical_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class Numerical_Tic_Tac_Toe_Player : public Player<char> {
public:
    Numerical_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
    bool IsValidNumber(const string &str);
};

class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
    vector<int> availableNumbers;
public:
    explicit Numerical_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- Misere_Tic_Tac_Toe

class Misere_Tic_Tac_Toe_Board : public Board<char> {
public:
    Misere_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void getNames(string namePlayer1, string namePlayer2);
};

class Misere_Tic_Tac_Toe_Player : public Player<char> {
public:
    Misere_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class Misere_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    Misere_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- Ultimate_Tic_Tac_Toe
//---------------- BIG BOARD

class Ultimate_Tic_Tac_Toe_Board : public Board<char> {
private:
    bool over = false;
    Board<char> *smallBoards[3][3]; // 3x3 grid of smaller boards
    char bigBoard[3][3]; // To track who won each smaller board
public:
    Ultimate_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

//---------------- SMALL BOARD

class TicTacToeBoard : public Board<char> {
private:
    vector<vector<char>> board; // Define your own board
public:
    TicTacToeBoard();
    void display_board() override;
    bool update_board(int x, int y, char symbol) override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    char get_cell(int x, int y) const ;     // Getter for board cell
    void set_cell(int x, int y, char value);        // Setter for board cell
};

class Ultimate_Tic_Tac_Toe_Player : public Player<char> {
    char bigBoard[3][3];
public:
    Ultimate_Tic_Tac_Toe_Player(string name, char symbol);
    void getmove(int &x, int &y) override;
};

class Ultimate_Tic_Tac_Toe_Random_Player : public RandomPlayer<char> {
public:
    Ultimate_Tic_Tac_Toe_Random_Player(char symbol);
    void getmove(int &x, int &y) override;
};

//--------------------------------------- SUS

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

#endif // GAMES_H