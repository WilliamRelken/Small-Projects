/*
TIC-TAC-TOE PROGRAM
BY: William R.
*/

#include <stdio.h>
#include <string.h>

void PrintGameBoard(char gameBoard[3][3]);
void GetMove(int player, char gameBoard[3][3]);
int OverwriteCheck(int row, int column, char gameBoard[3][3]);

int RowCheck(char gridRow[5]);
int ColCheck(char gridColumn[5]);

int WinnerCheck(char gameBoard[3][3]);

int main(void) {
  char gameBoard[3][3];
  int winner = 0;

  //Pre-assigns gameboard
  for(int i = 0; i < 3; i++){
    gameBoard[i][0] = ' ';
    gameBoard[i][1] = ' ';
    gameBoard[i][2] = ' ';
  }
  //NOTE: While this could be done with 2 fors it will be the same line count.
  // I find multiple statement easier to read than multiple for()'s so I choose ^
  /* EXAMPLE:
  for(int i = 0; i < 3; i++){
    for(int j = 0; i < 3; j++){
      gameBoard[i][j] = ' ';
    }
  }*/
  
  //for loop goes on until winnerCheck finds a winner or the array fills with non-spaces
  for(int i = 0; winner == 0; i++){
    PrintGameBoard(gameBoard);

    //evens mean player 1's turn, odds are player 2  
    if(i % 2 == 0){  
    GetMove(1, gameBoard);
    }
    else{  
    GetMove(2, gameBoard);
    }

    //Doing this means I do not need to needlessly use WinnerCheck after the for()
    winner = WinnerCheck(gameBoard);
  }

  //winner is 1(player 1), 2(player 2) or 3(tied)
  if(winner < 3){ 
  printf("PLAYER %d IS THE WINNER!\n", winner);
  }
  else{
    printf("PLAYERS HAVE TIED.\n");
  }

  return 0;
}

//prints the gameBoard
void PrintGameBoard(char gameBoard[3][3]){
  //found this stange tidbit from //https://programmersheaven.com/discussion/212135/how-to-clear-screen-in-c
  //This statement clears the screen
  printf("\e[1;1H\e[2J");
  
  printf("        Left | Mid | Right\n");
  printf("\n");
  printf("Upper     %c  |  %c  |  %c   \n", gameBoard[0][0], gameBoard[0][1], gameBoard[0][2]);
  printf("-----   ------------------   \n");
  printf("  Mid     %c  |  %c  |  %c   \n", gameBoard[1][0], gameBoard[1][1], gameBoard[1][2]);
  printf("-----   ------------------   \n");
  printf("Lower     %c  |  %c  |  %c   \n", gameBoard[2][0], gameBoard[2][1], gameBoard[2][2]);
  printf(" ___________________________\n");
  printf("|  HOW TO PLAY              |\n");
  printf("|    INPUT FORM: Row Column |\n");
  printf("|       EXAMPLE: Upper Left |\n");
  printf("----------------------------- \n");

  return;
}

//Gets either players move in text-form and sends it to RowCheck and 
//ColCheck to be changed into a number location in the array.
void GetMove(int player, char gameBoard[3][3]){
  char gridRow[6];
  char gridColumn[6];
  int tempRow;
  int tempCol;

  do{  
    do{  
    printf("Player %d's Move: ", player);
    scanf("%s %s", gridRow, gridColumn);

    tempRow = RowCheck(gridRow);
    tempCol = ColCheck(gridColumn);
    }while(tempRow == -1 || tempCol == -1);
  }while(OverwriteCheck(tempRow, tempCol, gameBoard) == 1);

  printf("\n");

  if(player == 1){
    gameBoard[tempRow][tempCol] = 'X';
  }
  else{
    gameBoard[tempRow][tempCol] = 'O';
  }

  return;
}

//Converts users text input to an int for gameBoard row
int RowCheck(char gridRow[5]){
  int x;

  if(strcmp(gridRow, "Upper") == 0){
    x = 0;
  }
  else if(strcmp(gridRow, "Mid") == 0){
    x = 1;
  }
  else if(strcmp(gridRow, "Lower") == 0){
    x = 2;
  }
  else{
    printf("INVALID OPTION FOR ROW\n");
    x = -1;
  }
  return x;
}

//Converts users text input to an int for gameBoard column
int ColCheck(char gridColumn[5]){
  int x;

  if(strcmp(gridColumn, "Left") == 0){
    x = 0;
  }
  else if(strcmp(gridColumn, "Mid") == 0){
    x = 1;
  }
  else if(strcmp(gridColumn, "Right") == 0){
    x = 2;
  }
  else{
    printf("INVALID OPTION FOR COLUMN\n");
    x = -1;
  }

  return x;
}

//Checks if input has already been filled by GetMove
int OverwriteCheck(int row, int column, char gameBoard[3][3]){
  int overwrite;

  if(gameBoard[row][column] == ' '){
    overwrite = 0;
  }
  else{
    overwrite = 1;
    printf("That Position is already taken.\n");
  }

  return overwrite;
}

//Checks for win conditions and outputs the winner/tie
int WinnerCheck(char gameBoard[3][3]){
  int winLose = 0;
  
  //This for statement could be improved to break after winLose is found but is fine for now
  for(int i = 0; i < 3; i++){

    //Vertical tests
    if(gameBoard[0][i] == 'X' && gameBoard[1][i] == 'X' && gameBoard[2][i] == 'X'){
      winLose = 1;
    }
    else if(gameBoard[0][i] == 'O' && gameBoard[1][i] == 'O' && gameBoard[2][i] == 'O'){
      winLose = 2;
    }

    //Horizontal tests
    if(gameBoard[i][0] == 'X' && gameBoard[i][1] == 'X' && gameBoard[i][2] == 'X'){
      winLose = 1;
    }
    else if(gameBoard[i][0] == 'O' && gameBoard[i][1] == 'O' && gameBoard[i][2] == 'O'){
      winLose = 2;
    }
  }

  //A for loop wouldn't work for a diagonal check and if it did it would be extremely convoluted
  if(gameBoard[0][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][2] == 'X'){
    winLose = 1;
  }
  else if(gameBoard[0][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][2] == 'O'){
    winLose = 2;
  }
  else if(gameBoard[2][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[0][2] == 'X'){
    winLose = 1;
  }
  else if(gameBoard[2][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[0][2] == 'O'){
    winLose = 2;
  }

  //Checks for a tie by filling var full, if var is 9 by the end of the loop board is full.
  //winLose == 0 check is needed so a final winning move that fills board isn't mistaken as a tie.
  for(int i = 0, full = 0; i < 3 && winLose == 0; i++){
    for(int j = 0; j < 3; j++){
      if(gameBoard[i][j] != ' '){
        full++;
      }
    }
    if(full == 9){
      winLose = 3;
    }
  }

  //Prints the final gameBoard
  if(winLose != 0){
  printf("\e[1;1H\e[2J");
  
  printf("        Left | Mid | Right\n");
  printf("\n");
  printf("Upper     %c  |  %c  |  %c   \n", gameBoard[0][0], gameBoard[0][1], gameBoard[0][2]);
  printf("-----   ------------------   \n");
  printf("  Mid     %c  |  %c  |  %c   \n", gameBoard[1][0], gameBoard[1][1], gameBoard[1][2]);
  printf("-----   ------------------   \n");
  printf("Lower     %c  |  %c  |  %c   \n", gameBoard[2][0], gameBoard[2][1], gameBoard[2][2]);
  printf("\n");
  }

  return winLose;
}
