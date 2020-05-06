#include <stdio.h>

void AssignGameMap(char gameMap[30][50]);
void FindPlayer(int playerLoc[2], char gameMap[30][50]);
void MovePlayer(int playerLoc[2], char gameMap[30][50]);

int ExitReached(char gameMap[30][50]);

//NOTE: Cannot enter a variable array size for func input so 50col 30 row limit 

int main(void) {
  static char gameMap[30][50];
  int playerLoc[2];

  AssignGameMap(gameMap);

  /*
    this is here so movePlayer can be at the top of the for loop,
    this is important because the final screen needs to be printed 
    after the player moves else it wont look like the exit was reached.
  */
  printf("\e[1;1H\e[2J");
  for(int i = 0; i < 15; i++){
    printf("%s",gameMap[i]);
  }

  do{
    FindPlayer(playerLoc, gameMap);
    
    MovePlayer(playerLoc, gameMap);
    printf("\e[1;1H\e[2J");
    for(int i = 0; i < 15; i++){
      printf("%s",gameMap[i]);
    }
  }while(ExitReached(gameMap) == 0);

  printf("THANKS FOR PLAYING!\n");
  return 0;
}

void AssignGameMap(char gameMap[30][50]){

  for(int i = 0; i < 30; i++){
    for(int j = 0; j < 50; j++){
      gameMap[i][j] = ' ';
    }
  }

  FILE* map = fopen("GameMap.txt","r");
  for(int i = 0; i < 30; i++){ 
    fgets(gameMap[i], 50, map);
  }
  
  fclose(map);

  return;
}

void MovePlayer(int playerLoc[2], char gameMap[30][50]){
  char playerMove;
  int convertedPlayerMove[2];
  int killFunction = 0;
  char tempChar;

  printf("\nCONTROL WITH WASD: ");
  scanf("%c", &playerMove);

  if(playerMove == 'w'){
    convertedPlayerMove[0] = playerLoc[0] - 1;
    convertedPlayerMove[1] = playerLoc[1];
  }
  else if(playerMove == 'a'){
    convertedPlayerMove[1] = playerLoc[1] - 1;
    convertedPlayerMove[0] = playerLoc[0];
  }
  else if(playerMove == 's'){
    convertedPlayerMove[0] = playerLoc[0] + 1;
    convertedPlayerMove[1] = playerLoc[1];
  }
  else if(playerMove == 'd'){
    convertedPlayerMove[1] = playerLoc[1] + 1;
    convertedPlayerMove[0] = playerLoc[0];
  }
  else{
    //anything here is an invalid move
    killFunction = 1;
  }

  tempChar = gameMap[convertedPlayerMove[0]][convertedPlayerMove[1]];

  if(tempChar == '|' || tempChar == '-'){
    //anything here is out of the game bounds
    killFunction = 1;
  }

  if(killFunction == 0){ 
    gameMap[convertedPlayerMove[0]][convertedPlayerMove[1]] = 'O';
    gameMap[playerLoc[0]][playerLoc[1]] = tempChar;
  }

  return;
}

void FindPlayer(int playerLoc[2], char gameMap[30][50]){
  for(int i = 0; i < 30; i++){
    for(int j = 0; j < 50; j++){
      if(gameMap[i][j] == 'O'){
        playerLoc[0] = i;
        playerLoc[1] = j;
        i = 30;
      }
    }
  }
  return;
}

//reusing code from FindPlayer func to find exit and look for player
int ExitReached(char gameMap[30][50]){
  int exitCheck = 0;

  for(int i = 0; i < 30; i++){
    for(int j = 0; j < 50; j++){
      if(gameMap[i][j] == 'E'){
        //checking vertical area for player
        if(gameMap[i-1][j] == 'O' || gameMap[i+1][j] == 'O'){
          exitCheck = 1;
        }
        //checking horizontal area for player
        if(gameMap[i][j-1] == 'O' || gameMap[i][j+1] == 'O'){
          exitCheck = 1;
        }
        i = 30;
      }
    }
  }
  if(exitCheck == 1){ 
    printf("\nYOU HAVE ESCAPED.\n");
  }
  return exitCheck;
}
