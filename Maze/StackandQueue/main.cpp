//Author: Zack Chambers
//Date: November 11th, 2018
//Description: A maze game using stack or queue


#include <iostream>
#include <stdlib.h>
#include "Maze.h"
#include <queue>
#include <stack>

using namespace std;


struct point{
	int r;
	int c;
};
/* Entry point of the program. Simply gets the filename from the user and then
    launches the one-player game. 
*/
int main()
{
	string fileName;
	cout << "Enter a maze file name: ";
	cin >> fileName;

	Maze maze(fileName);
	maze.display();
	
	cout << "Starting in " << maze.getStartRow() << ", " << maze.getStartCol() << endl;

	int selection;
	cout << "How would you like to explore the maze?" << endl;
	cout << "0: Exit" << endl;
	cout << "1: Stack" << endl;
	cout << "2: Queue" << endl;
	cout << "What would you like to do? ";
	cin >> selection;

	if (selection == 0)
	{
		exit(0);
	}
	else if (selection == 1)
	{
		cout << "Solving the maze using a stack..." << endl;
		stack<int> expStack; //explore Stack
		/*start from o
		* get north, east, south, west
		* if they have a valid pathway, add that to the stack
		* once done with that start exploring by using pop and setVisited
		* STACK will push in row first and column second
		* STACK will pop out column first and row second
		*/
		
		point startPoint; //beginning point: from where the program will explore north, east, south, west

		expStack.push(maze.getStartRow()); //push startr in
		expStack.push(maze.getStartCol()); //push startc in
		char expData = 'o';
		
		while (expData != 'X' && !expStack.empty())
		{
			maze.display(); //show the maze
			startPoint.c = expStack.top(); //get column
			expStack.pop(); //pop from stack
			startPoint.r = expStack.top(); //get row
			expStack.pop(); //pop from stack
			expData = maze.explore(startPoint.r, startPoint.c); //collect data about what is on the maze
			maze.setVisited(startPoint.r, startPoint.c); //setVisited to the place visited
			cout << "visiting (" << startPoint.r << ", " << startPoint.c << ")" << endl;
	
			//explore north (row-1, column)
			if (maze.explore(startPoint.r-1, startPoint.c) == '.' || maze.explore(startPoint.r-1, startPoint.c) == 'X')
			{
				expStack.push(startPoint.r-1);
				expStack.push(startPoint.c);
			}
	
			//explore east (row, column+1)
			if (maze.explore(startPoint.r, startPoint.c+1) == '.' || maze.explore(startPoint.r, startPoint.c+1) == 'X')
			{
				expStack.push(startPoint.r);
				expStack.push(startPoint.c+1);
			}
	
			//explore south (row+1, column)
			if (maze.explore(startPoint.r+1, startPoint.c) == '.' || maze.explore(startPoint.r+1, startPoint.c) == 'X')
			{
				expStack.push(startPoint.r+1);
				expStack.push(startPoint.c);
			}
		
			//explore west (row, column-1)
			if (maze.explore(startPoint.r, startPoint.c-1) == '.' || maze.explore(startPoint.r, startPoint.c-1) == 'X')
			{
				expStack.push(startPoint.r);
				expStack.push(startPoint.c-1);
			}

		}
		
		if (expData == 'X') //if program meets 'X' then print solution exists, otherwise solution does not exist
		{
			cout << "Solution exists" << endl;
		}
		else
		{
			cout << "Solution does not exist" << endl;
		}
		
	}
	else if (selection == 2)
	{
		cout << "Solving the maze using a queue" << endl;
		queue<int> expQueue; //stands for explore Queue
		/*start from o
		* get north, east, south, west
		* if they have a valid pathway, add that to the stack
		* once done with that start exploring by using pop and setVisited
		* QUEUE will push in row first and column second
		* QUEUE will pop out row first and column second
		*/
		
		point startPoint; //starting point
	
		expQueue.push(maze.getStartRow());
		expQueue.push(maze.getStartCol());
		char expData = 'o';
		
		while (expData != 'X' && !expQueue.empty())
		{
			maze.display(); //display the maze
			startPoint.r = expQueue.front(); //get row
			expQueue.pop(); //pop row
			startPoint.c = expQueue.front(); //get column
			expQueue.pop(); //pop column
			expData = maze.explore(startPoint.r, startPoint.c); //collect data about what is on the maze
			maze.setVisited(startPoint.r, startPoint.c); //setVisited to the place visited
			cout << "visiting (" << startPoint.r << ", " << startPoint.c << ")" << endl;

			

			//explore north (row-1, column)
			if (maze.explore(startPoint.r-1, startPoint.c) == '.' || maze.explore(startPoint.r-1, startPoint.c) == 'X')
			{
				expQueue.push(startPoint.r-1);
				expQueue.push(startPoint.c);
			}
	
			//explore east (row, column+1)
			if (maze.explore(startPoint.r, startPoint.c+1) == '.' || maze.explore(startPoint.r, startPoint.c+1) == 'X')
			{
				expQueue.push(startPoint.r);
				expQueue.push(startPoint.c+1);
			}
	
			//explore south (row+1, column)
			if (maze.explore(startPoint.r+1, startPoint.c) == '.' || maze.explore(startPoint.r+1, startPoint.c) == 'X')
			{
				expQueue.push(startPoint.r+1);
				expQueue.push(startPoint.c);
			}
		
			//explore west (row, column-1)
			if (maze.explore(startPoint.r, startPoint.c-1) == '.' || maze.explore(startPoint.r, startPoint.c-1) == 'X')
			{
				expQueue.push(startPoint.r);
				expQueue.push(startPoint.c-1);
			}

		}
		
		if (expData == 'X') //if program meets 'X' then print solution exists, otherwise solution does not exist
		{
			cout << "Solution exists" << endl;
		}
		else
		{
			cout << "Solution does not exist" << endl;
		}
	}

	return 0;
}
