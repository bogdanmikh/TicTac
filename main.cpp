// Программа Крестики-нолики
// Компьютер играет в "Крестики-нолики" против пользователя
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// глобальные константы
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
// прототипы функций
void instructions(){
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";
    cout << "Make your move known bу entering a number. 0 - 8. The number\n";
    cout << "corresponds to the desired board position. as illustrated:\n\n";
    cout << " 0 | 1 | 2\n";
    cout << " ---------\n";
    cout << " 3 | 4 | 5\n";
    cout <<" ---------\n";
    cout << " 6 | 7 | 8\n\n";
    cout << "Prepare yourself. human. The battle is about to begin.\n\n";
}

char askYesNo(string question) {
    char response;
    do {
        cout << question << " (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}

int askNumber(string question, int high, int low = 0){
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    } while (number > high || number < low);
    return number;
}

char humanPiece() {
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y') {
        cout << "\nThen take the first move. You will need it.\n";
        return X;
    } else {
        cout << "\nYour bravery will bе your undoing ... I will go first.\n";
        return O;
    }
}

char opponent(char piece) {
    return (piece == 'X') ? O : X;
}

void displayBoard(const vector<char>& board){
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
}

char winner (const vector<char>& board) {
    const int WINNING_ROWS[8][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8},
            {2, 4, 6}
    };
    const int TOTAL_ROWS = 8;
    // если в одном из выигрышных рядов уже присутствуют три одинаковых значения
    // (причем они не равны ЕМРТУ), то победитель определился
    for (int row = 0; row < TOTAL_ROWS; ++row) {
        if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
            (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
            return board[WINNING_ROWS[row][0]];
        }
    }
    // (остались ли на поле пустые клетки)
    if (count(board.begin(), board.end(), EMPTY) == 0) {
        return TIE;
    }
    // Поскольку победитель не определился. но и ничья еще не наступила.
    // игра продолжается
    return NO_ONE;
}

inline bool isLegal(const vector<char>& board, int move){
    return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human){
    int move = askNumber("\nWhere will you move?", (board.size() -1));
    while (!isLegal(board, move)){
        cout << "\nThat square is already occupied. foolish human.\n";
        move = askNumber("\nWhere will you move?", (board.size() -1));
    }
    cout << "Fine... \n";
    return move;
}

int computerMove (vector<char> board, char computer) {
    unsigned int move = 0;
    bool found = false;
    // если компьютер может выиграть следующим ходом. то он делает этот ход
    while (!found && move < board.size()) {
        if (isLegal(board, move)) {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }
        if (!found) {
            move++;
        }
    }
    if (!found) {
        move = 0;
        char human = opponent(computer);
        while (!found && move < board.size()) {
            if (isLegal(board, move)) {
                board[move] = human;
                found = winner(board) == human;
                board[move] = EMPTY;
            }
            if (!found) {
                move++;
            }
        }
    }
    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        while (!found && i < board.size()) {
            move = BEST_MOVES[i];
            if (isLegal(board, move)) {
                found = true;
            }
            i++;
        }

    }
    cout << "\nI shall take square number " << move << endl;
    return move;
}

void announceWinner(char winner, char computer, char human){
    if (winner == computer) {
        cout << endl << winner << "'s won!\n";
        cout << "As I predicted. human. I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    } else if(winner == human) {
        cout << endl << winner << "i    s won!\n";
        cout << "No. по! It cannot Ье! Somehow you tricked me. human. \n";
        cout << "But never again! I. the computer. so swear it!\n";
    } else{
        cout << "\nIt's a tie.\n";
        cout << "You were most lucky. human. and somehow managed to tie me.\n";
        cout << "Celebrate ... for this is the best you will ever achieve.\n";
    }
}

int main() {
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = 'X';
    displayBoard(board);
    while (winner(board) == NO_ONE) {
        if (turn == human) {
            move = humanMove(board, human);
            board[move] = human;
        } else {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }
    announceWinner(winner(board), computer, human);
    std::cout << "END" << std::endl;
    return 0;
}
