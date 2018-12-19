/* Kyle Lotilla
This game seems to be a modified version of the board game 'Battleships'. The objective of the game is to destroy more ships than your opponent.
In the game, each player take turns shooting coordinates in the board. In order to destory a ship, the all the coordinates the ship is located.
However, the players do not know where the ships located and each player destinate the coordinates of the ships in the board of where their opponent will shoot. 
In this modified version, the players share the same board, instead of each player shoot in their own board. Also, the coordinates of the ships are preset, instead
of being decided by the players. */
#include <stdio.h>
#include <string.h>

/*This is used to represent the coodinates */
typedef struct coordinate {
   int cordX;
   int cordY;
} coordinate; 

/* This set is used to display the board and represent the elements of FREE */
typedef char space[5][6]; 
/* This Set is used to store the coordinate that the player shoot. 
Since the game is only up to 30 turns, the players can only shoot 15 coordinates each. */
typedef coordinate playerSet[15];
/* This Set is used to check if a player shoot down a ship. 
There are 3 ships a player must shoot down, and they must shoot 4 coordinates to shoot one ship */ 
typedef coordinate condSet[3][4]; 

void drawBoard (space board)
{
	/* Prints the Board */
	int i, j, k, l, boardIndex = 0;
	
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (j == 4)
			   printf("   \n");
			else
			   printf("   |");
		}
	
      boardIndex = 0;	
      for (k = 0; k < 5; k++)
      {
   	   if (k == 4)
   	      printf(" %c \n", board[boardIndex][i]);
   	   else
   	      printf(" %c |", board[boardIndex][i]);
   	      
   	  boardIndex++;
      }
      
      if (i < 5)
         printf("___|___|___|___|___\n");
      else
         printf("   |   |   |   |   \n");
	}
}

int match(playerSet player,  condSet winCond)
{
	/* Checks how many ships a player took down */
	int bFound = 1, i, j, k, score = 0;
	
	for (i = 0; i < 3; i++) // Goes through the ships
	{
		bFound = 1;
		for (j = 0; j < 4 && bFound ; j++) // Goes through the coordinates of a ship
		{
		   bFound = 0;
		   for (k = 0; k < 15 && !bFound; k++) // Goes through the cooridnates the player shoot
		      if (player[k].cordX == winCond[i][j].cordX && player[k].cordY == winCond[i][j].cordY) // Checks if the player did shoot a coordinate of a ship
		         bFound = !bFound; // If the player did shoot the coordinate, it stops going through the cooridnates of the player then proceeds to the next coordinate of the ship.
		}
        
        if (bFound) // The player shoot all 4 coordinates of a ship, 1 point is added
           score++;
	}
	
	return score;
}

void populateArr (space board, condSet setA, condSet setB)
{
   /* Initializes setA to {{(1, 2), (1,3), (1, 4), (1, 5)}, 
	                       {(3, 1),(3, 2),(3, 3),(3, 4)},
                           {(5, 3),(5, 4),(5, 5),(5, 6)}} */

   /* Initializes setB to {{(2, 1),(3, 1),(4, 1),(5, 1)},
                           {(1, 3),(2, 3),(3, 3),(4, 3)},
                           {(2, 5),(3, 5),(4, 5),(5, 5)}} */
                           
   /* Also Initilize the space array */	

	int i, j, firstCord = 1, secondCord = 2;
	for (i = 0; i < 5; i++)
	   for (j = 0; j < 6; j++)
	      board[i][j] = ' ';
	 
	for (i = 0; i < 3; i++)
	{
	   for (j = 0; j < 4; j++)
	   {
	   	setA[i][j].cordX = firstCord;
	   	setA[i][j].cordY = secondCord;
	   	setB[i][j].cordY = firstCord;
	   	
	   	if (i < 2)
	   		setB[i][j].cordX = secondCord;
	       else
	           setB[i][j].cordX = secondCord - 1;
	       
	       secondCord++;
	   }
	   
	   if (i == 0)
	      secondCord = 1;
	   else if (i == 1)
	      secondCord = 3;
	   
	   firstCord += 2;
	}		
}

int isValidMove (int moveX, int moveY, space board)
{
	/* Checks if the player made a valid move */
	if (moveX <= 0 || moveY <= 0 || moveX > 5 || moveY > 6)
	{
		printf("Coordinates are out of bound. Please enter other coordinates: ");
		return 0;
	}
	else if (board[moveX - 1][moveY - 1] != ' ') // In the program, the elements of FREE is represented by space characters
	{
		printf("Space already taken. Please enter other coordinates: ");
		return 0;
	}
	else
	   return 1;
}

int main()
{
	playerSet Alpha, Beta;
	condSet setA, setB; // SetA contains the coordinates the Alpha must shoot to destroy a ship.
	space board; // SetB contains the coordinates the Beta must shoot to destroy a ship.
	int moves = 0, bTurn = 1, over = 0, moveX, moveY, playerIndex = 0;
	
	
	populateArr(board, setA, setB);
	
	do
	{
		system("cls");
		drawBoard(board);
		
		if (bTurn) // When bTurn = 1, it's Alpha's turn.
			printf("Alpha's Turn. Enter X and Y Coordinates: ");
		else // Otherwise, it's Beta's Turn
		   printf("Beta's Turn. Enter X and Y Coordinates: ");
			do
			{
			scanf("%d %d", &moveX, &moveY); // The input should be "x y". For Example, the player inputs "1 4", so the player will shoot space (1,4)
			} while (!isValidMove(moveX, moveY, board));
			
			if (bTurn)
			{
			   /* Assign the corresponding character ('A' for Alpha, 'B' for Beta) to the 
			   coordinate the player inputted in the board array so it will show visually*/
			   board[moveX - 1][moveY - 1] = 'A'; 
			   Alpha[playerIndex].cordX = moveX;
			   Alpha[playerIndex].cordY = moveY;
			}
			else
			{
			   board[moveX - 1][moveY - 1] = 'B';
			   Beta[playerIndex].cordX = moveX;
			   Beta[playerIndex].cordY = moveY;
			   playerIndex++; // playerIndex increments, since both players have finished a turn
			}
			
			bTurn = !bTurn; //switches player
			moves++;
			if (moves == 30) // By 30 turns, the game is over and the result are showed
			   over = !over;
	} while (!over);
	
	system("cls");
	drawBoard(board);
	/* Whoever shoot down the most ships Wins */
	if (match(Alpha, setA) > match(Beta, setB))
	   printf("Alpha wins with %d points, defeating Beta who has %d points!", match(Alpha, setA), match(Beta, setB));
	else if (match(Alpha, setA) < match(Beta, setB))
	   printf("Beta wins with %d points, defeating Alpha who has %d points!", match(Beta, setB), match(Alpha, setA));
	else
	   printf("It's tie %d-to-%d!", match(Alpha, setA), match(Beta, setB));
   
   getchar();
   return 0;
}
