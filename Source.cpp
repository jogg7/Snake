#include <iostream>
#include <conio.h> //keyboard input
#include <time.h>  //random generator
#include<windows.h> //sleep function

//detrmines to end game true or false
bool gameover;

//board  dimensions
const int widith = 20;
const int length = 20;

//x and y for head position //fruit for fruit position on board //score to keep score
int x, y, fruit1, fruit2, score;

//tail length
int tailX[100], tailY[100];
int ntail; //specfies length of tail



//direction for snake
enum eDirecton { stop = 0, right, left, up, down };
eDirecton Dir;

//function sets up game
void setup()
{

	gameover = false;
	Dir = stop;                  //set snake head to 0
	x = widith / 2;              //set sanke in the middle of board
	y = length / 2;
	fruit1 = rand() % widith;    //place fruit randomly within board
	fruit2 = rand() % length;
	score = 0;                   //set score to 0 before game
}

//function makes map for game
void draw()
{
	system("cls"); //clears command window

	std::cout << "\n";
	std::cout << "\n";

	for (int i = 0; i < widith+2; i++) //creates top boarder of board
	{
		std::cout << "#";
	}

	std::cout << "\n";
	 
	//Print walls
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < widith; j++)
		{
			if (j == 0)                //prints first charcter for wall
			
				std::cout << "#";

			if (i == y && j == x)      //prints head for snake
				std::cout << "O";

			else if (i == fruit2 && j == fruit1) //prints fruit
				std::cout << "F";
				
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
					}
				} 
				if (!print)
					std::cout << " ";
			}

			if (j == widith - 1)      //print wall on other wall
			
				std::cout << "#";
			
		}
		std::cout << "\n";
	}

	for (int i = 0; i < widith+2; i++) //create lower boarder of board //add to to enclose rectangle grid
	{
		std::cout << "#";
	}
	std::cout << "\n";
	std::cout << "Score: " << score;


}


//function for controls for the snake
void input()
{

	if (_kbhit()) //checks if keyboard is hit 
	{
		switch (_getch())   // gets key pressed on keyboard
		{
		case 'w':
			Dir = up;                              //press w snake goes up
			break;
		case 'a':                                  //press a snake goes left
			Dir = left;
			break;
		case 's':                                  //press s snake goes down
			Dir = down;
			break;
		case 'd':                                 //press d snake goes right
			Dir = right;
			break;
		case 'x':                                  //press x game is over
			gameover = true;
			break;
		}

	}

}


//function that plays game
void logic()
{
	//tail length
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;     //tail follOWS
	tailY[0] = y;


	//loop to add tail after every fruit gets eaten
	for (int i = 0; i < ntail; i++)
	{
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2x;
		prevY = prev2y;
	}

	switch (Dir) //movement 
	{
	case right: //moves right
		x++;
		break;
	case left: //moves snake left
		x--;
		break;
	case up:  //moves snake up
		y--;
		break;
	case down: //moves snake down
		y++;
		break;
	}
	if (x > widith || x < 0 || y > length || y < 0) // ends program when walls are hit
	{
		gameover = true;
	}
	if (x == fruit1 && y == fruit2)       //adds 10 points when food is eaten by snake
	{
		ntail++; //add length to tail
		score += 10;
		fruit1 = rand() % widith;    //place fruit randomly within board
		fruit2 = rand() % length;
		
	}
}






int main()
{
	srand(time(NULL)); //reset time

	setup(); //sets up board
	while (gameover != true)
	{
		draw();

		//slows game speed down
		if (Dir == left || Dir == right)
		{
			Sleep(5);
		}

		Sleep(50);

		if (Dir == up || Dir == down)
		{
			Sleep(60);
		}

		input();
		logic();

	}



	return 0;
}