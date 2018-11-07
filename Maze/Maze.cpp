/* Zack Chambers
 * The following work is done by Zack Chambers and no one else can take credit for it.
 */

/* 
 * Created on October 28, 2018, 7:04 PM
 */

// Maze.cpp : Defines the entry point for the application.
//

#include "Maze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

char start[3][3] = { {'.','.','.'},{'.','S','.'},{'.','.','.'} };
char goal[3][3] = { {'.','.','.'},{'.','F','.'},{'.','.','.'} };
char open[3][3] = { {'.','.','.'},{'.','.','.'},{'.','.','.'} };
char wall[3][3] = { {'X','X','X'},{'X','X','X'},{'X','X','X'} };
char path[3][3] = { {',',',',','},{',',',',','},{',',',',','} };
int boxX = 3, boxY = 3;
int mazeX, mazeY;
string mazeboxes[20][20]; //Supports mazes up to 20 by 20 squares big.

//Opens or creates output file to write maze in.
ofstream outFile("outputfile.txt"); //Need to adjust file path.


void printMaze() {

	//Loops through coordinates, checking for the type of square and writing the correct characters to write the maze to the output file.
	int x = 0;
	for (int y = 0; y < mazeY; y++) {
		while (x < mazeX) {
			if (mazeboxes[x / 3][y / 3] == "Start") {
				for (int j = 0; j < boxX; j++) {
					outFile << start[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "End") {
				for (int j = 0; j < boxX; j++) {
					outFile << goal[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "Wall") {
				for (int j = 0; j < boxX; j++) {
					outFile << wall[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "Open") {
				for (int j = 0; j < boxX; j++) {
					outFile << open[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "Path") {
				for (int j = 0; j < boxX; j++) {
					outFile << path[y % 3][j];
					x++;
				}
			}

		}
		x = 0;
		outFile << endl;
	}
	for (int i = 0; i < mazeX; i++) {
		outFile << "-";
	}
	outFile << " " << endl;
}

class node {

public:
	int x;
	int y;
	node() {}
	node(int xx, int yy) {
		x = xx;
		y = yy;
	}
	node* north = NULL;
	node* east = NULL;
	node* south = NULL;
	node* west = NULL;
};

int main() {

	ifstream inFile("inputfile.txt"); //Need to adjust file path.

	if (inFile.fail()) {
		cerr << "Error opening file." << endl;
		system("Pause");
	}

	//Reads entire file into one string to ignore line breaks.
	string inputline;
	string wholeinput;
	while (getline(inFile, inputline)) {
		wholeinput = wholeinput + inputline;
	}

	//Removes "(" and ")" from string so it's easier to split by "." and ",".
	char chars[] = "()";
	for (unsigned int i = 0; i < strlen(chars); ++i) {
		wholeinput.erase(remove(wholeinput.begin(), wholeinput.end(), chars[i]), wholeinput.end());
	}

	//Splits string by "." to isolate important sections to use in different things.
	stringstream inputstream(wholeinput);
	string section;
	vector<string> splitinput;
	char delimeter = '.';
	while (getline(inputstream, section, delimeter)) {
		splitinput.push_back(section);
	}

	//Splits the size section and stores values as maze size (times 3 to compensate for 3x3 boxes for each space).
	stringstream sizestream(splitinput[0]);
	delimeter = ',';
	vector<int> mazesize;
	while (getline(sizestream, section, delimeter)) {
		mazesize.push_back(stoi(section));
	}
	mazeX = mazesize[0] * 3;
	mazeY = mazesize[1] * 3;

	for (int i = 0; i < mazesize[0]; i++) {
		for (int j = 0; j < mazesize[1]; j++) {
			mazeboxes[i][j] = "Open";
		}
	}

	//Splits the start position section and sets coordinates for start position.
	stringstream startstream(splitinput[1]);
	vector<int> startpos;
	while (getline(startstream, section, delimeter)) {
		startpos.push_back(stoi(section));
	}
	mazeboxes[startpos[0]][startpos[1]] = "Start";

	//Splits the finishing location position section and set coordinates for finishing location.
	stringstream finishstream(splitinput[2]);
	vector<int> finishpos;
	while (getline(finishstream, section, delimeter)) {
		finishpos.push_back(stoi(section));
	}
	mazeboxes[finishpos[0]][finishpos[1]] = "End";

	//Splits the wall coordinates and sets all positions of wall squares.
	stringstream wallstream(splitinput[3]);
	vector<int> wallpos;
	while (getline(wallstream, section, delimeter)) {
		wallpos.push_back(stoi(section));
	}
	int wallcount = 0;
	while (wallcount < wallpos.size()) {
		mazeboxes[wallpos[wallcount]][wallpos[wallcount + 1]] = "Wall";
		wallcount = wallcount + 2;
	}


	printMaze(); //Prints maze before solving it.
	
	//Runs through maze and makes nodes for all open spaces.
	vector<node> graph;
	for (int i = 0; i < mazeY; i++) {
		for (int j = 0; j < mazeX; j++) {
			if (mazeboxes[j][i] == "Start") {
				node start(j, i);
				graph.push_back(start);
			}
			if (mazeboxes[j][i] == "Open" | mazeboxes[j][i] == "End") {
				graph.emplace_back(node(j, i));
			}
		}
	}

	//Loops through graph and links any nodes that are next to each other.
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			if (graph[i].x - graph[j].x == -1 && graph[i].y == graph[j].y) {
				graph[i].west = &graph[j];
			}
			if (graph[i].x - graph[j].x == 1 && graph[i].y == graph[j].y) {
				graph[i].east = &graph[j];
			}
			if (graph[i].y - graph[j].y == -1 && graph[i].x == graph[j].x) {
				graph[i].south = &graph[j];
			}
			if (graph[i].y - graph[j].y == 1 && graph[i].x == graph[j].x) {
				graph[i].north = &graph[j];

			}
		}
	}

	//Breadth First Search.
	queue<node> route;
	route.push(graph.front());
	int ratX = route.front().x;
	int ratY = route.front().y;
	while (mazeboxes[ratX][ratY] != "End") {
		

		if (route.front().west != NULL && mazeboxes[(*route.front().west).x][(*route.front().west).y] != "Path") {
			route.push(*route.front().west);
		}
		if (route.front().south != NULL && mazeboxes[(*route.front().south).x][(*route.front().south).y] != "Path") {
			route.push(*route.front().south);
		}
		if (route.front().east != NULL && mazeboxes[(*route.front().east).x][(*route.front().east).y] != "Path") {
			route.push(*route.front().east);
		}
		if (route.front().north != NULL && mazeboxes[(*route.front().north).x][(*route.front().north).y] != "Path") {
			route.push(*route.front().north);
		}
		mazeboxes[ratX][ratY] = "Path";
		route.pop();
		ratX = route.front().x;
		ratY = route.front().y;
	}

	printMaze();
	
	//Displays message to console once finished and pauses.
	cout << "Check outputfile.txt to see the maze!" << endl;
	system("Pause");
	return 0;
}
