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
#include "Pyramid_Tic_Tac_Toe.h"
#include "Four_In_A_Row.h"
#include "Five_By_Five_Tic_Tac_Toe.h"
#include "Word_Tic_Tac_Toe.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "Misere_Tic_Tac_Toe.h"
//#include "Ultimate_Tic_Tac_Toe.h"
#include "SUS.h"

using namespace std;

//--------------------------------------- HELPER FUNCTIONS

//--------------------------------------- ALL GAMES

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

//--------------------------------------- Word_Tic_Tac_Toe

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

//--------------------------------------- CALLING EACH FUNCTION

//--------------------------------------- Pyramid_Tic_Tac_Toe

void Pyramid_Tic_Tac_Toe() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    Pyramid_Tic_Tac_Toe_Board<char> *gameBoard = new Pyramid_Tic_Tac_Toe_Board<char>();

    cout << "<--------- Welcome To Pyramid Tic Tac Toe --------->\n";
    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new Pyramid_Tic_Tac_Toe_Player<char>(player1Name, 'X');
    } else {
        players[0] = new Pyramid_Tic_Tac_Toe_Random_Player<char>('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new Pyramid_Tic_Tac_Toe_Player<char>(player2Name, 'O');
    } else {
        players[1] = new Pyramid_Tic_Tac_Toe_Random_Player<char>('O');
    }

    GameManager<char> Pyramid_Tic_Tac_Toe_Game(gameBoard, players);
    Pyramid_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- Four_In_A_Row

void Four_In_A_Row() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Four_In_A_Row_Board<char>();
    cout << "<--------- Welcome To Four In A Row --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    // Create player 1
    if (player1Type == "1") {
        cout << "Please Enter Player 1 name :";
        getline(cin, player1Name);
        players[0] = new Four_In_A_Row_Player<char>(player1Name, 'X');
    } else {
        players[0] = new Four_In_A_Row_Random_Player<char>('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    // Create player 2
    if (player2Type == "1") {
        cout << "Please Enter Player 2 name :";
        getline(cin, player2Name);
        players[1] = new Four_In_A_Row_Player<char>(player2Name, 'O');
    } else {
        players[1] = new Four_In_A_Row_Random_Player<char>('O');
    }

    // Create the game manager
    GameManager<char> Four_In_A_Row_Game(gameBoard, players);
    Four_In_A_Row_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- Five_By_Five_Tic_Tac_Toe

void _5_X_5_Tic_Tac_Toe() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new FivebyFive_Tic_Tac_Toe_Board<char>();
    cout << "<--------- Welcome To 5x5 Tic Tac Toe --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new FivebyFive_Tic_Tac_Toe_Player<char>(player1Name, 'X');
    } else {
        players[0] = new FivebyFive_Tic_Tac_Toe_Random_Player<char>('X');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new FivebyFive_Tic_Tac_Toe_Player<char>(player2Name, 'O');
    } else {
        players[1] = new FivebyFive_Tic_Tac_Toe_Random_Player<char>('O');
    }

    GameManager<char> FivebyFive_Tic_Tac_Toe_Game(gameBoard, players);
    FivebyFive_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- Word_Tic_Tac_Toe

void Word_Tic_Tac_Toe() {
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
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- Numerical_Tic_Tac_Toe

void Numerical_Tic_Tac_Toe() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Numerical_Tic_Tac_Toe_Board<char>();
    cout << "<--------- Welcome To Numerical Tic Tac Toe --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new Numerical_Tic_Tac_Toe_Player<char>(player1Name, '1');
    } else {
        players[0] = new Numerical_Tic_Tac_Toe_Random_Player<char>('1');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new Numerical_Tic_Tac_Toe_Player<char>(player2Name, '2');
    } else {
        players[1] = new Numerical_Tic_Tac_Toe_Random_Player<char>('2');
    }

    // Create the game manager
    GameManager<char> Numerical_Tic_Tac_Toe_Game(gameBoard, players);
    Numerical_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- Misere_Tic_Tac_Toe

void Misere_Tic_Tac_Toe() {
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    auto *gameBoard = new Misere_Tic_Tac_Toe_Board<char>();
    cout << "<--------- Welcome To Misere Tic Tac Toe --------->\n";

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
    } else player1Name = "Random Computer Player";

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
    } else player2Name = "Random Computer Player";

    if (player1Type == "1") {
        players[0] = new Misere_Tic_Tac_Toe_Player<char>(player1Name, 'X');
    } else {
        players[0] = new Misere_Tic_Tac_Toe_Random_Player<char>('X');
    }

    if (player2Type == "1") {
        players[1] = new Misere_Tic_Tac_Toe_Player<char>(player2Name, 'O');
    } else {
        players[1] = new Misere_Tic_Tac_Toe_Random_Player<char>('O');
    }
    gameBoard->getNames(player1Name, player2Name);

    // Use the customized MisereGameManager
    GameManager<char> Misere_Tic_Tac_Toe_Game(gameBoard, players);
    Misere_Tic_Tac_Toe_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- Ultimate_Tic_Tac_Toe

void Ultimate_Tic_Tac_Toe() {

}

//--------------------------------------- SUS

void SUS() {
    cout << "<--------- Welcome To SUS --------->\n";
    string player1Type, player2Type, player1Name, player2Name;
    Player<char> *players[2];
    SUS_Board<char> *gameBoard = new SUS_Board<char>();

    checkPlayerType(player1Type, 1);                // Get info of player 1.
    if (player1Type == "1") {
        cout << "Please enter Player 1 name:";
        getline(cin, player1Name);
        players[0] = new SUS_Player<char>(player1Name, 'S');
    } else {
        players[0] = new SUS_Random_Player<char>('S');
    }

    checkPlayerType(player2Type, 2);                // Get info of player 2.
    if (player2Type == "1") {
        cout << "Please enter Player 2 name:";
        getline(cin, player2Name);
        players[1] = new SUS_Player<char>(player2Name, 'U');
    } else {
        players[1] = new SUS_Random_Player<char>('U');
    }

    GameManager<char> SUS_Game(gameBoard, players);
    SUS_Game.run();

    delete gameBoard;                                           // Delete board.
    delete players[0];                                          // Delete players.
    delete players[1];
    cout << "\nTHANKS FOR PLAYING THIS GAME :)\n\n";
}

//--------------------------------------- MAIN FUNCTION

int main() {
    cout << "<---------- WELCOME TO OUR APPLICATION ---------->\n"
         << "OUR APPLICATION HAS A NUMBER OF INTERESTING GAMES!\n\n";

    while (true) {
        string choice;
        cout << "Which game do you want?\n" << "[1] Pyramid_Tic_Tac_Toe.\n" << "[2] Four_In_A_Row.\n"
             << "[3] 5_X_5_Tic_Tac_Toe.\n" << "[4] Word_Tic_Tac_Toe.\n" << "[5] Numerical_Tic_Tac_Toe.\n"
             << "[6] Misere_Tic_Tac_Toe.\n" << "[7] Ultimate_Tic_Tac_Toe.\n" << "[8] SUS.\n" << "[9] Exit.\nChoice:";
        getline(cin, choice);
        while (true) {
            if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" &&
                choice != "7" && choice != "8" && choice != "9") {
                cout << "Please enter a valid choice!\n\n";
                cout << "Which game do you want?\n" << "[1] Pyramid_Tic_Tac_Toe.\n" << "[2] Four_In_A_Row.\n"
                     << "[3] 5_X_5_Tic_Tac_Toe.\n" << "[4] Word_Tic_Tac_Toe.\n" << "[5] Numerical_Tic_Tac_Toe.\n"
                     << "[6] Misere_Tic_Tac_Toe.\n" << "[7] Ultimate_Tic_Tac_Toe.\n" << "[8] SUS.\n"
                     << "[9] Exit.\nChoice:";
                getline(cin, choice);
                continue;
            }
            break;
        }
        cout << endl;
        if (choice == "1") Pyramid_Tic_Tac_Toe();
        else if (choice == "2") Four_In_A_Row();
        else if (choice == "3") _5_X_5_Tic_Tac_Toe();
        else if (choice == "4") Word_Tic_Tac_Toe();
        else if (choice == "5") Numerical_Tic_Tac_Toe();
        else if (choice == "6") Misere_Tic_Tac_Toe();
        else if (choice == "7") Ultimate_Tic_Tac_Toe();
        else if (choice == "8") SUS();
        else if (choice == "9") break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    cout << "THANKS FOR USING OUR APPLICATION :)";
    return 0;
}
