#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int rollDice() {
    return (rand() % 6) + 1;
}
void diceGame() {
    char choice;
    cin.ignore();
    do {
        cout << "\n=== Dice Rolling Game ===\n";
        cout << "Press Enter...";
        cin.ignore();
        int user1 = rollDice();
        int user2 = rollDice();
        int userTotal = user1 + user2;
        int comp1 = rollDice();
        int comp2 = rollDice();
        int compTotal = comp1 + comp2;
        cout << "You rolled: " << user1 << " and " << user2 << " (Total: " << userTotal << ")\n";
        cout << "Computer rolled: " << comp1 << " and " << comp2 << " (Total: " << compTotal << ")\n";
        if(userTotal > compTotal) cout << "You win!\n";
        else if(userTotal < compTotal) cout << "Computer wins!\n";
        else cout << "It's a tie!\n";
        
        cout << "Play again? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while(choice == 'y' || choice == 'Y');
}
char board[3][3];
void initBoard() {
    char c = '1';
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j] = c++;
}
void printBoard() {
    cout << "\n";
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << " " << board[i][j] << " ";
            if(j<2) cout << "|";
        }
        cout << "\n";
        if(i<2) cout << "===|===|===\n";
    }
    cout << endl;
}
bool checkWin(char player) {
    for(int i=0;i<3;i++) {
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player) return true;
        if(board[0][i]==player && board[1][i]==player && board[2][i]==player) return true;
    }
    if(board[0][0]==player && board[1][1]==player && board[2][2]==player) return true;
    if(board[0][2]==player && board[1][1]==player && board[2][0]==player) return true;
    return false;
}
void aiEasy() {
    int emptyCells[9][2];
    int count = 0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]!='X' && board[i][j]!='O') {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
    if(count>0) {
        int r = rand() % count;
        board[emptyCells[r][0]][emptyCells[r][1]] = 'O';
    }
}
bool tryWinOrBlock(char mark) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j]!='X' && board[i][j]!='O') {
                char temp = board[i][j];
                board[i][j] = mark;
                if(checkWin(mark)) {
                    if(mark=='O') return true; 
                    board[i][j] = 'O'; 
                    return true;
                }
                board[i][j] = temp;
            }
        }
    }
    return false;
}
void aiMedium() {
    if(!tryWinOrBlock('O')) {  
        if(!tryWinOrBlock('X')) { 
            aiEasy(); 
        }
    }
}
int minimax(bool isAI) {
    if(checkWin('O')) return 1;
    if(checkWin('X')) return -1;
    int score = isAI ? -100 : 100;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!='X' && board[i][j]!='O') {
                char temp = board[i][j];
                board[i][j] = isAI ? 'O':'X';
                int moveScore = minimax(!isAI);
                board[i][j] = temp;
                if(isAI && moveScore>score) score = moveScore;
                if(!isAI && moveScore<score) score = moveScore;
            }
        }
    }
    if(score==-100 && !isAI) return 0;
    if(score==100 && isAI) return 0;
    return score;
}
void aiInsane() {
    int bestScore = -100;
    int moveRow = -1, moveCol = -1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!='X' && board[i][j]!='O') {
                char temp = board[i][j];
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = temp;
                if(score>bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }
    if(moveRow!=-1 && moveCol!=-1) board[moveRow][moveCol] = 'O';
}
    void resetBoard() {
    int num = 1;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = '0' + num;
            num++;
        }
    }
}
void ticTacToeAI() {
    initBoard();
    int move, turns = 0;
    char player = 'X';
    int difficulty;
    char choice;
    cin.ignore();
    cout << "\n=== Tic Tac Toe ===\n";
    cout << "\nSelect Difficulty:\n1. Easy\n2. Medium\n3. Insane\nChoose: ";
    cin >> difficulty;
do{
        resetBoard();
        turns =0;
        player ='X';
    while (true) {
        printBoard();
        if(player=='X') {
            cout << "Your turn (X). Enter move (1-9): ";
            cin >> move;
            int row = (move-1)/3;
            int col = (move-1)%3;
            if(board[row][col]!='X' && board[row][col]!='O') {
                board[row][col]='X';
                turns++;
                if(checkWin('X')) {
                    printBoard();
                    cout << "You win!\n";
                    break;
                }
                player='O';
            } else {
                cout << "Invalid move. Try again.\n";
                break;
            }
        } else { 
            if(difficulty==1) aiEasy();
            else if(difficulty==2) aiMedium();
            else aiInsane();
            turns++;
            if(checkWin('O')) {
                printBoard();
                cout << "Computer wins!\n";
                break;
            }
            player='X';
        }
        if(turns==9) {
            printBoard();
            cout << "It's a tie!\n";
            break;
        }
    }
        cout << "Play again? (y/n): ";
        cin >> choice;
        cin.ignore();
        
}while(choice == 'y' || choice == 'Y');
}     
int main() {
    srand(time(0));
    char option;
    do {
        cout << "\n=== Game Menu ===\n";
        cout << "1. Dice Rolling Game\n";
        cout << "2. Tic Tac Toe (vs Computer)\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> option;
        switch(option) {
            case '1':
                diceGame();
                break;
            case '2':
                ticTacToeAI();
                break;
            case '3':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while(option!='3');
}
