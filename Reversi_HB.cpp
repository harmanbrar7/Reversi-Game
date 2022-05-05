//Assignment 2: FlipFlop
//CMPT 129 March 21/2021
//Harman Brar (301293707)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

#define MAX_ARRAY_SIZE 24
#define MIN_ARRAY_SIZE 8

const int NOPLAYER = 0;
const int WHITEPLAYER = 1;
const int BLACKPLAYER = 2;
const int FIRST_PIECE = 1;
const int SECOND_PIECE = 2;
const int MAXTRIES = 3;
const int TEXTWIDTH = 4;
const char WHITE = 'W';
const char BLACK = 'B';
//values for checkline 
const int NEGATIVEDIRECTION = -1;
const int POSITIVEDIRECTION = 1;
const int ZERODIRECTION = 0;


bool PlacePiece(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int whichPiece, int& numberCaptured);

bool DisplayBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

bool InitialiizeBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

bool CheckLine(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int xDirection, int yDirection, int& numCaptured);

bool IsAnyMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int whichPiece);

bool IsThisMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int whichPiece);


int main()
{
	int myFlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	int numRows = 0;
	int counter = 0;
	int player = 0; 
	int MAXTURNS = 0;
	int turns = 0;
	int squarePlayed = 0;
	int NumberCaptured = 0;
	int attempts = 0;
	int secondpieceattempts = 0;
	char secondpiece = '\0';
	bool BooleanAllocator;
	string PLAYER;
	char GameOverCharachter = '\0';

	do
	{
		cout << "Enter the number of squares along each edge of the board" << endl;

		if (!(cin >> numRows))
		{
			cerr << "ERROR: Board size is not an integer" << endl << "8 <= number of squares <= 24" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			counter++;
		}
		else if (numRows < MIN_ARRAY_SIZE)
		{
			cerr << "ERROR: Board size too small" << endl << "8 <= number of squares <= 24" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			counter++;
		}
		else if (numRows > MAX_ARRAY_SIZE && numRows % 2 == 0)
		{
			cerr << "ERROR: Board size too large" << endl << "8 <= number of squares <= 24" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			counter++;
		}
		else if (numRows % 2 != 0)
		{
			cerr << "ERROR: Board size odd" << endl << "8 <= number of squares <= 24" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			counter++;
		}
		else
		{
			break;
		}



	} while (counter < MAXTRIES);

	if (counter == MAXTRIES)
	{
		cerr << "ERROR: Too many errors entering the size of the board" << endl;
		exit(1);
	}

	MAXTURNS = numRows * numRows;
	InitialiizeBoard(myFlipFlopBoard, numRows);
	DisplayBoard(myFlipFlopBoard, numRows);
	cout << endl << endl << endl;
	player = WHITEPLAYER;
	PLAYER = "White";

	while (turns < MAXTURNS)
	{
		
		
		if (IsAnyMoveValid(myFlipFlopBoard, numRows, player, FIRST_PIECE) == true)
		{
			cout << PLAYER << " takes a turn" << endl;
			while (attempts < MAXTRIES)
			{
				cout << "Enter the square number of the square you want to put your first piece on" << endl;
				if (!(cin >> squarePlayed))
				{
					cerr << "Error: square chosen not an integer" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					attempts++;
					continue;
				}
				else if (squarePlayed < 0 || squarePlayed >(numRows*numRows-1))
				{
					cerr << "ERROR: that square is not on the board" << endl << "Try again" << endl;
					attempts++;
					continue;
					
				}
				else if (IsThisMoveValid(myFlipFlopBoard, numRows, player, squarePlayed, FIRST_PIECE) == false)
				{
					cerr << "ERROR: Illegal move" << endl << "Try again" << endl;
					attempts++;
					continue;
				}
				else if (IsThisMoveValid(myFlipFlopBoard, numRows, player, squarePlayed, FIRST_PIECE) == true)
				{
				    BooleanAllocator = PlacePiece(myFlipFlopBoard, numRows, player, squarePlayed, FIRST_PIECE, NumberCaptured);
					if (BooleanAllocator == false)
					{
						cerr << "ERROR: Illegal move" << endl << "Try again" << endl;
						attempts++;
						continue;
					}
					else if (BooleanAllocator == true)
					{
						DisplayBoard(myFlipFlopBoard, numRows);
						cout << endl << endl << endl;
						cout << "Your first piece captured " << NumberCaptured << " opponent's pieces" << endl;
						if (NumberCaptured > 1)
						{
							cout << "Do you wish to play a second piece?  Y/N ";
							cin >> secondpiece;
							if (secondpiece == 'N')
							{
								break;
							}
							if (secondpiece == 'Y')
							{
								if (IsAnyMoveValid(myFlipFlopBoard, numRows, player, SECOND_PIECE) == false)
								{
									cout << endl << PLAYER << " is unable to move" << endl;
									break;
								}
								else if (IsAnyMoveValid(myFlipFlopBoard, numRows, player, SECOND_PIECE) == true)
								{
									while (secondpieceattempts < MAXTRIES)
									{
										cout << "Enter the square number of the square you want to put your second piece on" << endl;
										if (!(cin >> squarePlayed))
										{
											cerr << "Error: square chosen not an integer" << endl;
											cin.clear();
											cin.ignore(256, '\n');
											secondpieceattempts++;
											continue;

										}
										else if (squarePlayed < 0 || squarePlayed >(numRows*numRows - 1))
										{
											cerr << "ERROR: that square is not on the board" << endl << "Try again" << endl;
											secondpieceattempts++;
											continue;

										}
										else if (IsThisMoveValid(myFlipFlopBoard, numRows, player, squarePlayed, SECOND_PIECE) == false)
										{
											cerr << "ERROR: Illegal move" << endl << "Try again" << endl;
											secondpieceattempts++;
											continue;
										}
										else if (IsThisMoveValid(myFlipFlopBoard, numRows, player, squarePlayed, SECOND_PIECE) == true)
										{
											NumberCaptured = 0;
											BooleanAllocator = PlacePiece(myFlipFlopBoard, numRows, player, squarePlayed, SECOND_PIECE, NumberCaptured);
											if (BooleanAllocator == false)
											{
												cerr << "ERROR: Illegal move" << endl << "Try again" << endl;
												secondpieceattempts++;
												continue;
											}
											else if (BooleanAllocator == true)
											{
												DisplayBoard(myFlipFlopBoard, numRows);
												cout << endl << endl << endl;
												cout << "Your second piece captured " << NumberCaptured << " opponent's pieces" << endl;
												break;

											}

										}

									}
									if (attempts == MAXTRIES)
									{
										cout << PLAYER << " has forfieted a turn" << endl;
										DisplayBoard(myFlipFlopBoard, numRows);
										cout << endl << endl << endl;
									}
									attempts = 0;
								}


							}


						}
						NumberCaptured = 0;//resetting numbercapture
						break;
					}

				}



			}
			if (attempts == MAXTRIES)
			{
				cout << PLAYER <<" has forfieted a turn" << endl;
				DisplayBoard(myFlipFlopBoard, numRows);
				cout << endl << endl << endl;
			}
			attempts = 0;

		}
		else
		{
			cout << PLAYER <<  " is unable to move" << endl;
			
		}
		
		if (player != BLACKPLAYER)
		{
			player = BLACKPLAYER;
			PLAYER = "Black";

		}
		else if(player != WHITEPLAYER)
		{
			player = WHITEPLAYER;
			PLAYER = "White";
		}


		

		if ((IsAnyMoveValid(myFlipFlopBoard, numRows, WHITEPLAYER, FIRST_PIECE) == false && IsAnyMoveValid(myFlipFlopBoard, numRows, BLACKPLAYER, FIRST_PIECE) == false))
		{
			cout << PLAYER << " is unable to move" << endl;
			if (player != BLACKPLAYER)
			{
				player = BLACKPLAYER;
				PLAYER = "Black";

			}
			else if (player != WHITEPLAYER)
			{
				player = WHITEPLAYER;
				PLAYER = "White";
			}
			cout << PLAYER << " is unable to move" << endl;

		
			break;
		}
		turns++;
		
	}

	


	





cout << "GAME OVER" << endl << "Please enter any character to close the game window" << endl;
cin >> GameOverCharachter;
exit(4);





}














bool PlacePiece(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int whichPiece, int& numberCaptured)
{
	bool BoolAllocator;
	int numcaptured = 0;
	int row = 0;
	int col = 0;
	col = squarePlayed % numRowsInBoard;
	row = squarePlayed / numRowsInBoard;
	int otherplayer = WHITEPLAYER;
	if (player == WHITEPLAYER)
	{
		otherplayer = BLACKPLAYER;
	}


	if (whichPiece == FIRST_PIECE)
	{


		if (IsThisMoveValid(FlipFlopBoard, numRowsInBoard, player, squarePlayed, whichPiece) == true)
		{
		

			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					if (x == 0 && y == 0)
					{
						continue;
					}
					BoolAllocator = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, x, y, numcaptured);
					if (BoolAllocator == true)
					{

						numberCaptured += numcaptured;
						row += y;
						col += x;

						while (FlipFlopBoard[row][col] == otherplayer)
						{
							FlipFlopBoard[row][col] = player;
							row += y;
							col += x;

						}
						col = squarePlayed % numRowsInBoard;
						row = squarePlayed / numRowsInBoard;


					}
				}
			}
			FlipFlopBoard[row][col] = player;

			if (player == WHITEPLAYER)
			{
				cout << "White has placed the first piece" << endl;
			}
			else
			{
				cout << "Black has placed the first piece" << endl;

			}
			return true;




		}
	}
	else if (whichPiece == SECOND_PIECE)
	{
		if (IsThisMoveValid(FlipFlopBoard, numRowsInBoard, player, squarePlayed, whichPiece) == true)
		{


			

			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					if (x == 0 && y == 0)
					{
						continue;
					}
					BoolAllocator = CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, x, y, numcaptured);
					if (BoolAllocator == true)
					{

						numberCaptured += numcaptured;
						row += y;
						col += x;

						while (FlipFlopBoard[row][col] == otherplayer)
						{
							FlipFlopBoard[row][col] = player;
							row += y;
							col += x;

						}
						col = squarePlayed % numRowsInBoard;
						row = squarePlayed / numRowsInBoard;


					}
				}
			}
			FlipFlopBoard[row][col] = player;

			if (player == WHITEPLAYER)
			{
				cout << "White has placed the second piece" << endl;
			}
			else
			{
				cout << "Black has placed the second piece" << endl;

			}
			return true;

		}
		numcaptured = 0;




		

		





	}
	
	
	return false;



}




bool DisplayBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{

	if (numRowsInBoard > MAX_ARRAY_SIZE || numRowsInBoard < MIN_ARRAY_SIZE)
	{
		return false;
	}


	int BoardNumber = 0;
	for (int x = 0; x < numRowsInBoard; x++)
	{
		for (int y = 0; y < numRowsInBoard; y++)
		{
			if (FlipFlopBoard[x][y] == WHITEPLAYER)
			{
				cout << setw(TEXTWIDTH) << WHITE;
			}
			else if (FlipFlopBoard[x][y] == BLACKPLAYER)
			{
				cout << setw(TEXTWIDTH) << BLACK;
			}
			else
			{
				cout << setw(TEXTWIDTH) << BoardNumber;
			}
			BoardNumber++;
		}
		cout << endl;
	}
	return true;



}





bool InitialiizeBoard(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	if (numRowsInBoard <= MAX_ARRAY_SIZE && numRowsInBoard >= MIN_ARRAY_SIZE)
	{
		for (int x = 0; x < numRowsInBoard; x++)
		{
			for (int y = 0; y < numRowsInBoard; y++)
			{
				FlipFlopBoard[x][y] = NOPLAYER;
			}
		}

		FlipFlopBoard[numRowsInBoard / 2 - 1][numRowsInBoard / 2 - 1] = WHITEPLAYER;
		FlipFlopBoard[numRowsInBoard / 2][numRowsInBoard / 2] = WHITEPLAYER;

		FlipFlopBoard[numRowsInBoard / 2 - 1][numRowsInBoard / 2] = BLACKPLAYER;
		FlipFlopBoard[numRowsInBoard / 2][numRowsInBoard / 2 - 1] = BLACKPLAYER;

		return true;
	}

	else
	{
		return false;
	}


}






bool IsAnyMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int whichPiece)
{
	int squarePlayed = 0;


	//DisplayBoard(FlipFlopBoard, numRowsInBoard);



	for (int x = 0; x < numRowsInBoard; x++)
	{
		for (int y = 0; y < numRowsInBoard; y++)
		{
			if (IsThisMoveValid(FlipFlopBoard, numRowsInBoard, player, squarePlayed, whichPiece))
			{

				return true;

			}
			else
			{
				squarePlayed++;
			}
		}
		
	}

	return false;



}





bool IsThisMoveValid(int FlipFlopBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int whichPiece)
{
	int numCaptured = 0;

	// if statement for which piece is 1 or 2(two if statements)
	//checkline 4 times if return true/false then this whole function is true/false
	if (whichPiece == FIRST_PIECE)
	{
		if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, POSITIVEDIRECTION, ZERODIRECTION, numCaptured) == true ||
			CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, NEGATIVEDIRECTION, ZERODIRECTION, numCaptured) == true ||
			CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, ZERODIRECTION, POSITIVEDIRECTION, numCaptured) == true ||
			CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, ZERODIRECTION, NEGATIVEDIRECTION, numCaptured) == true)
		{
			return true;
		}


	}
	else if (whichPiece == SECOND_PIECE)
	{
		if (CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, POSITIVEDIRECTION, POSITIVEDIRECTION, numCaptured) == true ||
			CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, POSITIVEDIRECTION, NEGATIVEDIRECTION, numCaptured) == true ||
			CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, NEGATIVEDIRECTION, POSITIVEDIRECTION, numCaptured) == true ||
			CheckLine(FlipFlopBoard, numRowsInBoard, player, squarePlayed, NEGATIVEDIRECTION, NEGATIVEDIRECTION, numCaptured) == true)
		{
			return true;
		}

	}
	return false;

}






bool CheckLine(int FlipFlopBoard[][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int squarePlayed, int xDirection, int yDirection, int& numCaptured)
{
	// This function takes the FlipFlopBoard and calculates
	// how the board changes when player player
	// (player=1 for white, player=2 for black)
	// This function checks along a row in one direction for
	// al legal move. If no legal move is found this function
	// returns false, if a legal move is found this function
	// returns true.
	// Author Janice Regan; 2021
	int otherPlayer;
	char piece = 2;           // to compare for otherPlayers
	int xIndex = 0;
	int yIndex = 0;
	int xCoordinate = 0;
	int yCoordinate = 0;
	bool edge = true;
	numCaptured = 0;

	otherPlayer = WHITEPLAYER;
	if (player == WHITEPLAYER)
	{
		otherPlayer = BLACKPLAYER;
	}

	// find row and column were new piece may be placed
	xCoordinate = squarePlayed % numRowsInBoard;
	yCoordinate = squarePlayed / numRowsInBoard;

	//if the square selected is occupied return false
	if (FlipFlopBoard[yCoordinate][xCoordinate] == player ||
		FlipFlopBoard[yCoordinate][xCoordinate] == otherPlayer)
	{
		return false;
	}


	// find the square next to the location the piece may
	// be played. Next in the direction (xDirection,yDirection)
	yIndex = yCoordinate + yDirection;
	xIndex = xCoordinate + xDirection;

	// while the square to be checked is on the board 
	// continue looking for a legal move
	// If the square is not on the board then return false
	// there is no legal move in the indicated direction
	while ((xIndex < numRowsInBoard &&
		yIndex < numRowsInBoard) &&
		(xIndex >= 0 && yIndex >= 0))
	{
		//if the location where the piece is to be placed
		//is next to an empty square or to another of the
		//player's pieces, then the there is no legal
		// move in the direction indicated 
		// return false
		if (FlipFlopBoard[yIndex][xIndex] == NOPLAYER ||
			FlipFlopBoard[yIndex][xIndex] == player)
		{
			return false;
		}
		else
		{
			// The next piece in the direction indicated is a
			// opponent's piece. The move may be legal, proceed
			// in the indicated direction and try to find a players
			// piece.  If one is found before the edge of the board
			// is reached the move is legal
			// If a legal move is found, count the number of pieces
			// captured,  then return true.
			edge = true;
			while (yIndex < numRowsInBoard &&
				xIndex < numRowsInBoard &&
				yIndex >= 0 && xIndex >= 0)
			{
				edge = false;
				if (FlipFlopBoard[yIndex][xIndex] == NOPLAYER)
				{
					//next square along the indicated direction is empty
					//move is illegal
					return false;
				}
				if (FlipFlopBoard[yIndex][xIndex] == player)
				{
					//next square along the direction indicated hold
					//one of the players pieces.  The move is legal
					break;
				}
				else
				{
					//next square along the direction indicated holds
					//an opponents piece, continue along the same 
					//direction and try the next square
					numCaptured++;
					xIndex += xDirection;
					yIndex += yDirection;
					edge = true;
				}
			}


			if (edge == true)
			{
				//The edge of the board has been reached without 
				//finding a players piece, move is not legal
				return false;
			}
			return true;
		}
	}
	//The edge of the board has been reached,
	//no legal move.  return false
	return false;
}