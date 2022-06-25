#include <iostream>
using namespace std;

#define WHITE   "\033[37m"      /* White */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */

#define row 9
#define coloum 9

class Board {
  private:
    char board[row][coloum];
    char myBoard[row][coloum];
    char emptySpace = '?';
    char mine = '*';
    char flag = '$';
    int flagCount = 0;
    int maxFlag = 10;
    bool isGameOver = false;

  public:
    Board(int i, int j) {
      initBoard();
      placeBomb(i,j);
      countNoOfMines();
    }

    void initBoard() {
      for(int i = 0; i < row; i++) {
        for(int j = 0; j < coloum; j++) {
         board[i][j] = emptySpace;
         myBoard[i][j] = emptySpace;
        }
      }
    }

    void placeBomb(int m, int n) {
      srand(time(0));
      int noOfBomb = 10;
      for(int k = 0; k < noOfBomb; k++) {
        int i = rand() % 9;
        int j = rand() % 9;
        if(board[i][j] == emptySpace && i != m && j != n) {
          board[i][j] = mine;
        } else {
          k--;
        }
      }
    }

    bool insideBoard(int i, int j) {
      return i >= 0 && i < row && j >= 0 && j < coloum;
    }

    bool isMine(int i, int j) {
      if(!insideBoard(i,j)) {
        return false;
      }
      if(board[i][j] == mine) {
        return true;
      }
      return false;
    }

    int getMinesCount(int i, int j) {
      int minesCount = 0;
      if(isMine(i, j-1)) { minesCount++; }
      if(isMine(i, j+1)) { minesCount++; }
      if(isMine(i+1, j)) { minesCount++; }
      if(isMine(i-1, j)) { minesCount++; }
      if(isMine(i-1, j-1)) { minesCount++; }
      if(isMine(i-1, j+1)) { minesCount++; }
      if(isMine(i+1, j-1)) { minesCount++; }
      if(isMine(i+1, j+1)) { minesCount++; }
      return minesCount;
    }

    void countNoOfMines() {
      for(int i = 0; i < row; i++) {
        for(int j = 0; j < coloum; j++) {
          if(board[i][j] != mine) {
            int minesCount = getMinesCount(i, j);
            board[i][j] = '0' + minesCount;
          }
        }
      }
    }

    void reveledAdjecentCell(int i, int j) {
      if(!insideBoard(i,j) || board[i][j] == mine || myBoard[i][j] != emptySpace) {
        return;
      }
    
      myBoard[i][j] = board[i][j];
      if(insideBoard(i,j) && board[i][j] == '1' || board[i][j] == '2' || board[i][j] == '3') {
        myBoard[i][j] = board[i][j];
        return;
      }
    
      reveledAdjecentCell(i, j-1);
      reveledAdjecentCell(i, j+1);
      reveledAdjecentCell(i+1, j);
      reveledAdjecentCell(i-1, j);
      reveledAdjecentCell(i-1, j-1);
      reveledAdjecentCell(i-1, j+1);
      reveledAdjecentCell(i+1, j-1);
      reveledAdjecentCell(i+1, j+1);
    }

    void openSelectedCell(int i, int j) {
      if(myBoard[i][j] == emptySpace) {
        if(board[i][j] == mine) {
          myBoard[i][j] = board[i][j];
          isGameOver = true;
        } else if(board[i][j] == '0') {
          reveledAdjecentCell(i,j);
        } else {
          myBoard[i][j] = board[i][j];
        }
      } else {
        cout<< RED <<"\nCan't Open (Cell already Open) "<<endl;
      }
     
    }

    void insertFlag(int i, int j) {
      if(insideBoard(i,j) && myBoard[i][j] == emptySpace) {
        flagCount++;
        myBoard[i][j] = flag;
        if(board[i][j] == mine) {
          board[i][j] = flag;
        }
      } else {
        cout<< RED <<"\nCan't insert (Cell already Open) "<<endl;
      }
    }

    void removeFlag(int i, int j) {
      
    }

    bool checkIfWon() {
      if(flagCount >= maxFlag) {
        for(int i = 0; i < row; i++) {
          for(int j = 0; j < coloum; j++) {
            if(board[i][j] != myBoard[i][j]) {
              return false;
            }
          }
        }
        return true;
      }
      return false;
    }

    bool IsGameOver() {
      return isGameOver;
    }

    int getFlagCount() {
      return flagCount;
    }

    int getMaxFlag() {
      return maxFlag;
    }

    void print() {
       for(int j = 0; j <= coloum+1; j++) {
          if(j == 0 || j == 1) {
            cout<<" ";
          } else {
            cout<< WHITE <<" -";
          }
        }
        cout<<endl;
      
      for(int i = 0; i < row; i++) {
        cout<< WHITE << i+1 << " |";
    
        for(int j = 0; j < coloum; j++) {
          if(myBoard[i][j] == mine) {
            cout<< RED << myBoard[i][j];
          } else if(myBoard[i][j] == '0' || myBoard[i][j] == '1' ||
                    myBoard[i][j] == '2' || myBoard[i][j] == '3') {
            cout<< GREEN << myBoard[i][j];
          } else if(myBoard[i][j] == flag) {
            cout<< YELLOW << myBoard[i][j];
          } else {
            cout<< WHITE << myBoard[i][j];
          }
          cout<< WHITE << "|";
        }
        cout<<endl;
        
        for(int j = 0; j <= coloum+1; j++) {
          if(j == 0 || j == 1) {
            cout<<" ";
          } else {
            cout<< WHITE <<" -";
          }
        }
        cout<<endl;
      }
      
      int i = 1;
      for(int j = 0; j <= coloum+1; j++) {
         if(j == 0 || j == 1) {
            cout<<" ";
          } else {
           cout<< WHITE <<" "<< i;
           i++;
          }
      }
      cout<<endl;
        
    }

    void print1() {
      for(int i = 0; i < row; i++) {
          for(int j = 0; j < coloum; j++) {
            cout<< board[i][j] << " ";
          }
        cout<<endl;
        }
    }
};

class GameRule {
  public:
    GameRule() {
      printGameTitle();
      gameRule();
      howToPlay();
    }
    void printGameTitle() {
      for(int i = 0; i < 40; i++) {
        cout<<WHITE <<"*";
      }
      cout<<endl;
      cout<< WHITE <<"*                                      *"<<endl;
      cout<< WHITE <<"*        WELCOME TO MINESWEEPR         *"<<endl;
      cout<< WHITE <<"*                                      *"<<endl;
      for(int i = 0; i < 40; i++) {
        cout<<WHITE <<"*";
      }
      cout<<endl;
    }

    void gameRule() {
      cout<<endl<<endl<<endl<<endl;
      cout<< WHITE <<"Rules : "<<endl;
      cout<< WHITE <<"1. The board is devided into cell, With Mines (10) randomly distributed. "<<endl;
      cout<< WHITE <<"2. To Win, you need to open all the Cell. " <<endl;
      cout<< WHITE <<"3. You will loose, if you open Mines cell. " <<endl;
      cout<< WHITE <<"4. The number on Cell represent the number of Mines adjecent to it."<<endl;
      cout<< WHITE <<"   Using this information you can determine Cells are safe or contain Mines."<<endl;
      cout<<WHITE <<"5. You will get only 10 Flags.. "<<endl;
      
    }

    void howToPlay() {
      cout<<endl<<endl<<endl<<endl;
      cout<< WHITE <<"How to Play : "<<endl;
      cout<< WHITE <<"1. Select option ."<<endl;
      cout<< WHITE <<"     1) Open Cell - To open a new Cell. "<<endl;
      cout<< WHITE <<"     2) Set Flag - If cells not safe to open, you can mark it as flag. "<<endl;
      cout<<WHITE <<"2. Enter Row and Coloum number to open or set Flag."<<endl;
    }

    void gameStatusLogo(string status) {
      for(int i = 0; i < 30; i++) {
        cout<<WHITE <<"_";
      }
      cout<<endl;
      cout<<WHITE <<"|                            |"<<endl;
      cout<< WHITE <<"|        "<<status<<"          |"<<endl;
      cout<< WHITE <<"|                            |"<<endl;
      for(int i = 0; i < 30; i++) {
        cout<< WHITE <<"-";
      }
      cout<<endl;
    }
};

class GamePlay {
  private:
    int i, j, input;
    int maxInput = 9;
    int minInput = 1;
    int optionMaxInput = 2;
    int optionMinInput = 1;
    GameRule *rule;

  public:
    GamePlay() {
      rule = new GameRule();
      wantToPlay();
    }

    bool isInputInRange() {
      return i >= minInput && j >= minInput && i <= maxInput && j <= maxInput;
    }

    bool isOptionInRange() {
      return input >= optionMinInput && input <= optionMaxInput;
    }

    void getUserInput() {
      cout<< WHITE <<"\nEnter Row Number of Cell: ";
      cin>> i;
      cout<< WHITE <<"Enter Coloum Number of Cell : ";
      cin>> j;
    }

    void optionSelect() {
      cout<< WHITE <<"\nSelect Option : " <<endl;
      cout<< WHITE <<"  1. Open Cell " <<endl;
      cout<< WHITE <<"  2. Set Flag " <<endl;
      cin>> input;
    }

    void gameLoop() {
      getUserInput();
      if(isInputInRange() == false) {
        cout<< RED << "Input Not in Range "<<endl;
        gameLoop();
      }
      
      Board board(i-1,j-1);
      board.openSelectedCell(i-1,j-1);
      board.print();

      while(!board.IsGameOver() && !board.checkIfWon()){
        optionSelect();
        if(isOptionInRange() == false) {
          continue;
        }
        
        enterAgain:  // label
        getUserInput();
        if(isInputInRange() == false) {
          cout<< RED << "Input Not in Range "<<endl;
          goto enterAgain;
        }
        
        if(input == 2) {
          if(board.getFlagCount() < board.getMaxFlag()) {
             board.insertFlag(i-1 , j-1);
          } else {
            cout<< RED << "Flag Stock : NILL (Can't insert more flag) "<<endl;
          }
        } else {
          board.openSelectedCell(i-1,j-1);
        }
        board.print();
      }

      if(board.IsGameOver()) {
        //cout<< RED <<" You Lost "<<endl;
        cout<<endl<<endl;
        rule->gameStatusLogo(" YOU LOST ");
      } else {
        //cout<< GREEN <<" You Won" <<endl;
        cout<<endl<<endl;
        rule->gameStatusLogo("  YOU WON ");
      }
    }

    void wantToPlay() {
      char play;
      cout<<"\n\nEnter Y/y - To Play or N/n - To Quit :";
      cin>> play;

      if(play == 'Y' || play == 'y') {
        rule->gameStatusLogo("GAME START");
        cout<<endl<<endl;
        gameLoop();
      } else {
        rule->gameStatusLogo("   QUIT   ");
      }
    }
};


int main() {
  
  GamePlay play;

  return 0;
}
