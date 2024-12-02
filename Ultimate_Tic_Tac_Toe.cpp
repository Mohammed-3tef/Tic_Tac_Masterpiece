#include <iostream>
#include <vector>
using namespace std;

// Base Board class from BoardGame_Classes.h
template <typename T>
class Board {
public:
    virtual ~Board() {}
    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;
};

// Player class
template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* board;
public:
    Player(string n, T s) : name(n), symbol(s), board(nullptr) {}
    void setBoard(Board<T>* b) { board = b; }
    T getSymbol() { return symbol; }
    virtual bool makeMove() = 0;
};

// Human Player class
template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T s) : Player<T>(n, s) {}
    bool makeMove() override {
        int x, y;
        cout << this->name << " (" << this->symbol << "), enter your move (row and column): ";
        cin >> x >> y;
        return this->board->update_board(x, y, this->symbol);
    }
};

// Smaller Tic Tac Toe board
class SmallBoard : public Board<char> {
private:
    vector<vector<char>> grid;
    char winner;
    int moves;

public:
    SmallBoard() : grid(3, vector<char>(3, '-')), winner('-'), moves(0) {}

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || grid[x][y] != '-') {
            cout << "Invalid move. Try again.\n";
            return false;
        }
        grid[x][y] = symbol;
        moves++;
        return true;
    }

    void display_board() override {
        for (const auto& row : grid) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] != '-' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) return true;
            if (grid[0][i] != '-' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) return true;
        }
        if (grid[0][0] != '-' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return true;
        if (grid[0][2] != '-' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        return moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    char get_winner()  {
        return is_win() ? winner : '-';
    }

    char get_cell(int x, int y) const {
        return grid[x][y];
    }
};

// Ultimate Tic Tac Toe board
class UltimateBoard : public Board<char> {
private:
    vector<vector<SmallBoard>> boards;
    vector<vector<char>> metaBoard;
    int activeX, activeY;
    int moves;

public:
    UltimateBoard() : boards(3, vector<SmallBoard>(3)), metaBoard(3, vector<char>(3, '-')), activeX(-1), activeY(-1), moves(0) {}

    bool update_board(int x, int y, char symbol) override {
        int bigRow = x / 3, bigCol = y / 3;
        int smallRow = x % 3, smallCol = y % 3;

        if (activeX != -1 && activeY != -1 && (bigRow != activeX || bigCol != activeY)) {
            cout << "You must play in the active board (" << activeX << ", " << activeY << ").\n";
            return false;
        }

        if (!boards[bigRow][bigCol].update_board(smallRow, smallCol, symbol)) {
            return false;
        }

        moves++;

        // Update meta-board if small board is won or drawn
        if (boards[bigRow][bigCol].is_win()) {
            metaBoard[bigRow][bigCol] = symbol;
        } else if (boards[bigRow][bigCol].is_draw()) {
            metaBoard[bigRow][bigCol] = 'D';
        }

        activeX = smallRow;
        activeY = smallCol;

        if (metaBoard[activeX][activeY] != '-') {
            activeX = activeY = -1;
        }

        return true;
    }

    void display_board() override {
        for (int bigRow = 0; bigRow < 3; ++bigRow) {
            for (int smallRow = 0; smallRow < 3; ++smallRow) {
                for (int bigCol = 0; bigCol < 3; ++bigCol) {
                    for (int smallCol = 0; smallCol < 3; ++smallCol) {
                        cout << boards[bigRow][bigCol].get_cell(smallRow, smallCol) << " ";
                    }
                    cout << "| ";
                }
                cout << endl;
            }
            cout << "---------------------\n";
        }
    }

    bool is_win() override {
        // Check meta-board for wins
        for (int i = 0; i < 3; ++i) {
            if (metaBoard[i][0] != '-' && metaBoard[i][0] == metaBoard[i][1] && metaBoard[i][1] == metaBoard[i][2]) return true;
            if (metaBoard[0][i] != '-' && metaBoard[0][i] == metaBoard[1][i] && metaBoard[1][i] == metaBoard[2][i]) return true;
        }
        if (metaBoard[0][0] != '-' && metaBoard[0][0] == metaBoard[1][1] && metaBoard[1][1] == metaBoard[2][2]) return true;
        if (metaBoard[0][2] != '-' && metaBoard[0][2] == metaBoard[1][1] && metaBoard[1][1] == metaBoard[2][0]) return true;
        return false;
    }

    bool is_draw() override {
        return moves >= 81 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// Main function
int main() {
    Player<char>* players[2] = {
            new HumanPlayer<char>("Player 1", 'X'),
            new HumanPlayer<char>("Player 2", 'O')
    };

    UltimateBoard board;

    players[0]->setBoard(&board);
    players[1]->setBoard(&board);

    int currentPlayer = 0;
    while (!board.game_is_over()) {
        board.display_board();
        if (!players[currentPlayer]->makeMove()) continue;
        currentPlayer = 1 - currentPlayer;
    }

    board.display_board();
    if (board.is_win()) {
        cout << "Player " << (currentPlayer == 0 ? 2 : 1) << " wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    delete players[0];
    delete players[1];
    return 0;
}
