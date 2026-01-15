//============================================================================
// Name        : i242544project.cpp
// Author      : Dr. Sibt Ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_

#include "util.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

//making this line gloal cuz i need the variables
int width = 1000, height = 840; // i have set my window size to be 800 x 600
// seed the random numbers generator by current time (see the documentation of srand for further help)...
const int cellSize = 40; // Each grid cell is 40x40 pixels
bool isMenuOpen;
bool isNameScreenOPen;
bool isGameScreenOpen;
bool hasGameStarted;
bool gameReload;
char playerChoice = '0';
bool isMouseHovering1, isMouseHovering2, isMouseHovering3, isMouseHovering4, isMouseHovering5, isMouseHovering6;
bool isMouseClicked;
bool NameEntered = false;
string PlayerName = "";
bool isLeaderBoardOpen;
int totalTime = 180; 
bool gameOver = false;



//Cell to Pixel logic
int getRowIndex(int yCord){
	int i = (yCord - 100) / cellSize;
	return i;
}
int getColIndex(int xCord){
	int j = (xCord - 200) / cellSize;
	return j;
}

int getXCoord(int j){
	int xCord = j * cellSize + 200;
	return xCord;
}
int getYCoord(int i){
	int YCord = i * cellSize + 100;
	return YCord;
}

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

class Menu{

public:

	void drawFirstMenuScreen(){

		isNameScreenOPen = true;

		DrawString( 200 , 600, "Welcome To The Rush Hour Game!", colors[MEDIUM_ORCHID]);
		DrawString( 200 , 400, "Enter Your Name here: ", colors[MEDIUM_ORCHID]);

		if(isMouseHovering4){
			DrawLine( 440 , 398 ,  560 , 398 , 2 , colors[BLACK] );	
			isMouseHovering4 = !isMouseHovering4;		
		}

		if(isMouseClicked){
			DrawLine( 440 , 398 ,  560 , 398 , 2 , colors[BLACK] );	
			DrawString(445, 402, PlayerName, colors[BLACK]);
		}
	}

	void drawSecondMenuScreen(){
		isMenuOpen = true;

		DrawRectangle(438, 580, 160, 65, colors[PALE_VIOLET_RED]);
		DrawString( 329 , 600, "=======   RUSH HOUR   =======", colors[BLACK]);

		DrawRectangle(465, 480, 100, 65, colors[PLUM]);
		DrawString( 465 , 500, "  MENU   ", colors[BLACK]);

		DrawString( 300 , 400, "Play as... ", colors[BLACK]);

		DrawString( 300 , 300, " Taxi Driver", colors[BLACK]);
		
		if(isMouseHovering1){
			DrawString( 300 , 300, " Taxi Driver", colors[WHITE]);
			
			isMouseHovering1 = !isMouseHovering1;
		}

		DrawString( 300 , 250, " Delivery Packages Rider", colors[BLACK]);
		
		if(isMouseHovering2){
			
			DrawString( 300 , 250, " Delivery Packages Rider", colors[WHITE]);
			isMouseHovering2 = !isMouseHovering2;
		}

		DrawRoundRect(295,180,150,40,colors[DEEP_PINK],20);
		DrawString( 300 , 190, " Randomize?", colors[BLACK]);
		
		if(isMouseHovering3){

			DrawRoundRect(295,180,150,40,colors[HOT_PINK],20);
			DrawString( 300 , 190, " Randomize?", colors[BLACK]);
			
			isMouseHovering3 = !isMouseHovering3;
		}

		DrawString( 60 , 750, " Go To Leader Board? ", colors[BLACK]);

		if(isMouseHovering5){

			DrawString( 60 , 750, " Go To Leader Board? ", colors[WHITE]);
			isMouseHovering5 = !isMouseHovering5;

		}
	}

	friend void MenuDisplay();
	friend void PrintableKeys(unsigned char key, int x, int y);
	friend void NonPrintableKeys(int key, int x, int y);

};
Menu menu;


void MenuDisplay(){
	glClearColor(0.847f /*Red*/, 0.749 /*Green*/, 0.847 /*Blue*/, 0.0 /*Alpha*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	
	if(!NameEntered){
		menu.drawFirstMenuScreen();
	}
	else if(NameEntered){
		menu.drawSecondMenuScreen();
	}

	glutSwapBuffers(); // do not modify this line..
}



class Vehicle{
public:
	int xI, yI;
	float fuel;
	string color;
public:
	Vehicle(){
		xI = 200, yI = 660; //hard coding initial value
		fuel = 40.0;
		color = "blue";
	}

	virtual void drawCar() = 0; //pure virtual function so vehicle is an abstract class now :)
};

class PlayerCar : public Vehicle{
public:
	int xI, yI;
	PlayerCar(){
		xI = 200, yI = 660; //hard coding initial value
		fuel = 40.0; //initially 40
		color = "blue";
	}

	void Refuel(float f){
		fuel += f;
	}

	void drawCar() override {
		
		if(color == "yellow"){
			DrawSquare(xI+5, yI+5, 30, colors[YELLOW]);
			DrawCircle(xI+12, yI+2, 4, colors[BLACK]);
			DrawCircle(xI+25, yI+2, 4, colors[BLACK]);
			glutPostRedisplay();
		}
		else if(color == "red"){
			DrawSquare(xI+5, yI+5, 30, colors[RED]);
			DrawCircle(xI+12, yI+2, 4, colors[BLACK]);
			DrawCircle(xI+25, yI+2, 4, colors[BLACK]);
			glutPostRedisplay();
		}
		
	}
};

// class NPCcar : public Vehicle{
// private: 
// 	int xPosition;
// 	int yPosition;
// public:
// 	NPCcar(){
// 		xPosition = 0;
// 		yPosition = 0;
// 	}
// 	void setPosition(int i, int j){
// 		xPosition = j * cellSize + 200; //100 is offset for both axes
// 		yPosition = i * cellSize + 100;
// 	}
//   //must make a drawCar function to override abstract class func
	
// };

class FuelStation{
	int xPosition;
	int yPosition;
public:
	FuelStation(){
		xPosition = rand() % 24;
		yPosition = rand() % 24;
	}
	void setPosition(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;
	}
	void drawFuelStation(){	
		
		DrawSquare(xPosition+10, yPosition, 25, colors[BLUE]);
		DrawLine( xPosition+25 , yPosition+20 ,  xPosition+25 , yPosition , 10 , colors[BLACK] );	
	}
};

class Garage{
	int xPosition;
	int yPosition;
public:
	Garage(){
		xPosition = rand() % 24;
		yPosition = rand() % 24;
	}
	void setPosition(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;
	}
	void drawGarage(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;
		DrawSquare(xPosition+10, yPosition, 20, colors[DEEP_PINK]);
		DrawTriangle(xPosition+10, yPosition+18, xPosition+29, yPosition+18, xPosition+20, yPosition+38 ,colors[DEEP_PINK]);
		
	}
};

class Obstacles{
protected:
	int xPosition;
	int yPosition;
	int color;
public:
	Obstacles(){
		color = rand() % 2;
	}
	void setPosition(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;
	}
	Obstacles(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;
	}
	virtual void draw(){
		if(color == 0){
			DrawSquare(xPosition+10, yPosition, 20, colors[BROWN]);
		}
		else{
			DrawSquare(xPosition+10, yPosition, 20, colors[SLATE_GRAY]);
		}
		
	}
};

class Trees : public Obstacles{
public:
	Trees(){
		xPosition = rand() % 24;
		yPosition = rand() % 24;
	}
	void draw() override {
		// DrawSquare(xPosition, yPosition, cellSize, colors[RED]);
		DrawCircle(xPosition+20 , yPosition+24 , 10, colors[GREEN]);
		DrawLine( xPosition+20 , yPosition+18 ,  xPosition+20 , yPosition , 3 , colors[BROWN] );	
	}
};

class Person{
protected:
	int xPosition;
	int yPosition;
public:
	Person(){
		xPosition = rand() % 24;
		yPosition = rand() % 24;
	}
	void setPosition(int i, int j) {
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;	
	}
	virtual void draw(){
		
		DrawCircle(xPosition+20 , yPosition+24 , 5, colors[BLUE]);
		DrawLine( xPosition+20 , yPosition+18 ,  xPosition+20 , yPosition+10 , 3 , colors[BLUE] );	
	}
};

class NPCperson : public Person{
public:
	NPCperson(){
		xPosition = rand() % 24;
		yPosition = rand() % 24;
	}

	void draw() override {
		
		DrawCircle(xPosition+20 , yPosition+27 , 7, colors[BLACK]);
		DrawLine( xPosition+20 , yPosition+20 ,  xPosition+20 , yPosition+7 , 3 , colors[BLACK] );	
		DrawLine( xPosition+20 , yPosition+7 ,  xPosition+12 , yPosition , 3 , colors[BLACK] );	
		DrawLine( xPosition+20 , yPosition+7 ,  xPosition+28 , yPosition , 3 , colors[BLACK] );	
		DrawLine( xPosition+20 , yPosition+20 ,  xPosition+12 , yPosition+15 , 3 , colors[BLACK] );	
		DrawLine( xPosition+20 , yPosition+20 ,  xPosition+28 , yPosition+15 , 3 , colors[BLACK] );	
	}
};


class Passenger : public Person{
public:
	bool isPicked;
	bool isDropped;
	int destI, destJ;
	Passenger(){
		isPicked = false;
		isDropped = false;
		destI = 0;
		destJ = 0;
	}
	void setPosition(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;	
	}
	int getXPos() const {
		return xPosition;
	}
	int getYPos() const {
		return yPosition;
	}

	float payTaxiDriver(){
		int startJ = getColIndex(xPosition);
		int startI = getRowIndex(yPosition);

		int distance = abs(startI - destI) + abs(startJ - destJ);

		if(distance > 20){
			return 75.0;
		}
			
		else if(distance > 15){
			return 65.0;
		}
			
		else if(distance > 10){
			return 55.0;
		}
			
		else if(distance > 5){
			return 40.0;
		}
			
		else if(distance > 2){
			return 35.0;
		}
			
		else{
			return 20.0;
		}
			

	}

	void drawPassenger(){
		
		DrawCircle(xPosition+20 , yPosition+27 , 7, colors[BLUE_VIOLET]);
		DrawLine( xPosition+20 , yPosition+20 ,  xPosition+20 , yPosition+7 , 3 , colors[BLUE_VIOLET] );	
		DrawLine( xPosition+20 , yPosition+7 ,  xPosition+12 , yPosition , 3 , colors[BLUE_VIOLET] );	
		DrawLine( xPosition+20 , yPosition+7 ,  xPosition+28 , yPosition , 3 , colors[BLUE_VIOLET] );	
		DrawLine( xPosition+20 , yPosition+20 ,  xPosition+12 , yPosition+15 , 3 , colors[BLUE_VIOLET] );	
		DrawLine( xPosition+20 , yPosition+20 ,  xPosition+28 , yPosition+15 , 3 , colors[BLUE_VIOLET] );	
		// cout << getRowIndex(yPosition) << " " << getColIndex(xPosition) << endl;
	}
};

class Packages{
	int xPosition;
	int yPosition;
public:
	int destI;
	int destJ;
	bool isPicked;
	bool isDropped;
	Packages(){
		isPicked = false;
		isDropped = false;
		destI = 0;
		destJ = 0;
	}
	void setPosition(int i, int j){
		xPosition = j * cellSize + 200; //100 is offset for both axes
		yPosition = i * cellSize + 100;	
	}
	int getXPos() const {
		return xPosition;
	}
	int getYPos() const {
		return yPosition;
	}
	float payDeliverRider(){
		int startJ = getColIndex(xPosition);
		int startI = getRowIndex(yPosition);

		int distance = abs(startI - destI) + abs(startJ - destJ);

		if(distance > 20){
			return 75.0;
		}
			
		else if(distance > 15){
			return 65.0;
		}
			
		else if(distance > 10){
			return 55.0;
		}
			
		else if(distance > 5){
			return 40.0;
		}
			
		else if(distance > 2){
			return 35.0;
		}
			
		else{
			return 20.0;
		}
	}

	void drawPackages(){		
		
		DrawRectangle(xPosition+7, yPosition, 25, 20, colors[KHAKI]);
		// cout << getRowIndex(yPosition) << " " << getColIndex(xPosition) << endl;
	}
};

class Player{
	string name;
	float wallet;
public:
	PlayerCar car;
	Passenger passengers[4];
	Packages packages[4];
	
	Player(){
		name = PlayerName;
		wallet = 3.0;
	}

	void PutInWallet(float num){
		wallet += num;
	}

	float getWalletAmount() const {
		return wallet;
	}

	void reduceMoneyInWallet(float num){
		wallet -= num;
	}

	void reset(){
		wallet = 3.0;
	}

	void setPlayerChoice(const char c){
		if(c == 't'){
			car.color = "yellow";
		}
		else if(c == 'd'){
			car.color = "red";
		}
	}
	
	string getPlayerName() const {
		return name;
	}

	void setPlayerName(string n){
		name = n;
	}
};


class BoardMap{
	static const int gridSize = 15;
	int grid[gridSize][gridSize]; //rows and cols start from bottom left (i = 0, j = 0)
	Garage G1;
	FuelStation F1, F2, F3;
	Obstacles O1;
	Trees T1, T2, T3;
	NPCperson P1, P2;
	// NPCcar cars[5];
	int npcCarnum;
	int random;
	bool visited[gridSize][gridSize];
	int passengerCount;
public:
	Player player;
	BoardMap(){
		playerChoice = '0';
		random = 0;
		passengerCount = 0;
	}
	
	void loadMap(const char c){
		player.setPlayerChoice(c);
		InitializeGrid(); 
	}

	void InitializeGrid(){

		srand(time(0)); // Seed RNG with current time
		for(int i=0; i<4; i++){
			player.passengers[i].isPicked = false;
			player.passengers[i].isDropped = false;
			player.packages[i].isPicked = false;
			player.packages[i].isDropped = false;
		}
		random = (rand() % 3) + 2;
		npcCarnum = rand() % 3;
		bool validGrid = false;

		while (!validGrid){

			for(int i=0; i<gridSize; i++){
				for(int j=0; j<gridSize; j++){
					grid[i][j] = rand() % 30;
				}
			}
	
			grid[0][0] = 11;
			grid[14][0] = 11;
			grid[14][14] = 11;
			grid[0][14] = 11;

			placingObjects();

			int rand_i[4], rand_j[4];
			for(int i=0; i<random; i++){
				getRandomRoadPosition(rand_i[i], rand_j[i]);
				player.passengers[i].destI = rand_i[i];
				player.passengers[i].destJ = rand_j[i];
				player.packages[i].destI = rand_i[i];
				player.packages[i].destJ = rand_j[i];
			}
	
			bool toCorner1 = checkPath(0, 0, 14, 0);
			bool toCorner2 = checkPath(0, 0, 14, 14);
			bool toCorner3 = checkPath(0, 0, 0, 14);
	
			validGrid = (toCorner1 && toCorner2 && toCorner3); 

		}
		
		
	}

	bool isRoad(int i, int j){
		return (grid[i][j] > 7);
	}

	bool isPassenger(int i, int j){
		if(grid[i][j] == 69){
			return true;
		}
		return false;
	}
	
	int getElement(int i, int j){
		return grid[i][j];
	}

	void setElement(int i, int j, int num){
		grid[i][j] = num;
	}

	void getRandomRoadPosition(int& i, int& j){
		do{
			i = rand() % gridSize;
			j = rand() % gridSize;
		} 
		while(!isRoad(i, j) || (i == 0 && j == 0) || (i == 14 && j == 0) || (i == 14 && j == 14) || (i == 0 && j == 14) || isObstacle(i,j) || isPassenger(i, j) || isPackage(i, j));
	}

	int getGridSize() const{
		return gridSize;
	}

	bool isObstacle(int i, int j){
		if(grid[i][j] == 52 || grid[i][j] == 32 || grid[i][j] == 42 || grid[i][j] == 62){
			return true;
		}
		return false;
	}

	bool isFuelStation(int i, int j){
		if(grid[i][j] == 52){
			return true;
		}
		return false;
	}

	void placingObjects(){
		int i1, j1, i2, j2, i3, j3;
		getRandomRoadPosition(i1, j1);
		F1.setPosition(i1, j1);
		grid[i1][j1] = 52;
		getRandomRoadPosition(i2, j2);
		F2.setPosition(i2, j2);
		grid[i2][j2] = 52;
		getRandomRoadPosition(i3, j3);
		F3.setPosition(i3, j3);
		grid[i3][j3] = 52;

		int oi, oj;
		getRandomRoadPosition(oi, oj);
		O1.setPosition(oi, oj);
		grid[oi][oj] = 32;

		int t1i, t1j, t2i, t2j, t3i, t3j;
		getRandomRoadPosition(t1i, t1j);
		T1.setPosition(t1i, t1j);
		grid[t1i][t1j] = 42;
		getRandomRoadPosition(t2i, t2j);
		T2.setPosition(t2i, t2j);
		grid[t2i][t2j] = 42;
		getRandomRoadPosition(t3i, t3j);
		T3.setPosition(t3i, t3j);
		grid[t3i][t3j] = 42;

		int p1i, p1j, p2i, p2j;
		getRandomRoadPosition(p1i, p1j);
		P1.setPosition(p1i, p1j);
		grid[p1i][p1j] = 62;
		getRandomRoadPosition(p2i, p2j);
		P2.setPosition(p2i, p2j);
		grid[p2i][p2j] = 62;

		for(int i=0; i<npcCarnum; i++){

		}

		int passI[4], passJ[4];
		for(int p=0; p<4; p++){
			getRandomRoadPosition(passI[p], passJ[p]);
			// if(hasAccessibleNeighbor(passI[p], passJ[p])){
				grid[passI[p]][passJ[p]] = 69;
				player.passengers[p].setPosition(passI[p], passJ[p]);
			// }
		}

		int packI[4], packJ[4];
		for(int p=0; p<4; p++){
			getRandomRoadPosition(packI[p], packJ[p]);
			// if(hasAccessibleNeighbor(packI[p], packJ[p])){
				grid[packI[p]][packJ[p]] = 79;
				player.packages[p].setPosition(packI[p], packJ[p]);
			// }
		}
	}

	int getRandom() const {
		return random;
	}

	bool checkPath(int startRow, int startCol, int targetRow, int targetCol){
		for(int i=0; i<gridSize; i++){
			for(int j=0; j<gridSize; j++){
				visited[i][j] = false;
			}
		}
		return isClear(startRow, startCol, targetRow, targetCol);
	}

	bool isClear(int i, int j, int targetI, int targetJ){
		if(i < 0 || j < 0 || i >= gridSize || j >= gridSize){
			return false;
		}
	
		if(i == targetI && j == targetJ){
			return true;//goal reached
		}
	
		if(grid[i][j] <= 7 || isObstacle(i, j) || grid[i][j] == 69 || grid[i][j] == 79){ 
			return false;
		}
	
		if(visited[i][j]){
			return false;
		}
	
		visited[i][j] = true;
	
		if(isClear(i, j+1, targetI, targetJ)){
			return true;
		} 
		if(isClear(i, j-1, targetI, targetJ)){
			return true;
		} 
		if(isClear(i+1, j, targetI, targetJ)){
			return true;
		} 
		if(isClear(i-1, j, targetI, targetJ)){
			return true;
		} 
	
		return false;
	}
	
	bool isPerson(int i, int j){
		if(grid[i][j] == 62){
			return true;
		}
		return false;
	}
	
	bool isPackage(int i, int j){
		if(grid[i][j] == 79){
			return true;
		}
		return false;
	}

	void DrawGrid(){
		int x = 0, y = 0;
		
		for(int i=0; i<gridSize; i++){
			for(int j=0; j<gridSize; j++){
				x = j * cellSize + 200; //100 is offset for both axes
				y = i * cellSize + 100;

				
				if(x >= width - 100){
					break;
				}
				if(y >= height - 100){
					break;
				}
				if((i == 0 && j == 14)){
					DrawSquare(x, y, cellSize, colors[WHITE]); // Road
				}
			
				else if(grid[i][j] <= 7 && (!(i == 14 && j == 0) || !(i == 14 && j == 14) || !(i == 0 && j == 14))){
					DrawSquare(x, y, cellSize, colors[BLACK]); // Building
				}
				else{
					DrawSquare(x, y, cellSize, colors[WHITE]);
				}
				if(i == 0 && j == 0){	
					G1.drawGarage(i,j);
				}
				if(i == 14 && j == 0){
					DrawSquare(x, y, cellSize, colors[BLUE]);
				}
				if(grid[i][j] == 89){
					for(int k=0; k<random; k++){
						if(!player.passengers[k].isDropped){
							DrawSquare(x, y, cellSize, colors[SEA_GREEN]);
							break;
						}
					}
				}
				if(grid[i][j] == 99){
					for(int k=0; k<random; k++){
						if(!player.packages[k].isDropped){
							DrawSquare(x, y, cellSize, colors[SALMON]);
							break;
						}
					}
				}
				
			}
			
		}
		
		F1.drawFuelStation();
		F2.drawFuelStation();
		F3.drawFuelStation();

		O1.draw();

		T1.draw();
		T2.draw();
		T3.draw();
		
		P1.draw();
		P2.draw();
		
		player.car.drawCar();

		if(playerChoice == 't'){
			for(int i=0; i<random; i++){
				if(!player.passengers[i].isPicked){
					player.passengers[i].drawPassenger();
					// cout << "passenger " << i << " position: " << player.passengers[i].getXPos() << " " << player.passengers[i].getYPos() << endl;
				}
			
			}
		}
		else if(playerChoice == 'd'){
			for(int i=0; i<random; i++){
				if(!player.packages[i].isPicked){
					player.packages[i].drawPackages();
				}
			}
		}
		

	
		// C1.drawCar();
	}

	friend void GameDisplay();
	friend void NonPrintableKeys(int key, int x, int y);
	friend void PrintableKeys(unsigned char key, int x, int y);
	friend void Timer(int m);
};

class Game{
private:
	BoardMap map;
	int score;
	bool hasPicked;
	int passengerCount;
	bool picked;
public:
	void gameStart(const char c){
		map.loadMap(c);
		hasPicked = false;
		passengerCount = 0;
		picked = false;
	}

	void ReloadGame(char c){
		map.loadMap(c);
		hasPicked = false;
		passengerCount = 0;
		map.player.reset();
		map.player.car.fuel = 40.0;
		score = 0;
	}

	void PickUpPassenger(){
		
		int carRow = getRowIndex(map.player.car.yI);
		int carCol = getColIndex(map.player.car.xI);
		

		int passnegersRows[4];
		int passengersCols[4];

		
		for(int i=0; i<map.getRandom(); i++){
			passnegersRows[i] = getRowIndex(map.player.passengers[i].getYPos());
			passengersCols[i] = getColIndex(map.player.passengers[i].getXPos());
		}


		for(int i=0; i<map.getRandom(); i++){
			
			if(((carRow + 1 == passnegersRows[i] && carCol == passengersCols[i]) || (carRow - 1 == passnegersRows[i] && carCol == passengersCols[i])) && !(picked)){
				map.setElement(passnegersRows[i], passengersCols[i], 11); //setting the block to white if it was a passenger before
				map.player.passengers[i].isPicked = true;
				picked = true;
				// cout << "hellow";
				map.setElement(map.player.passengers[i].destI, map.player.passengers[i].destJ, 89);
				glutPostRedisplay();
				
			}
			else if(((carCol + 1 == passengersCols[i] && carRow == passnegersRows[i]) || (carCol - 1 == passengersCols[i] && carRow == passnegersRows[i])) && !(picked) ){
				map.setElement(passnegersRows[i], passengersCols[i], 11);
				map.player.passengers[i].isPicked = true;
				picked = true;
				// cout << "hellow";
				map.setElement(map.player.passengers[i].destI, map.player.passengers[i].destJ, 89);
				glutPostRedisplay();
			}
				
		}
		
	}

	void DropPassenger(){

		int carRow = getRowIndex(map.player.car.yI);
		int carCol = getColIndex(map.player.car.xI);
		// cout << "car row: " << carRow << " " << "car col: " << carCol << endl;

		int destIndexI[4];
		int destIndexJ[4];

		for(int i=0; i<map.getRandom(); i++){
			destIndexI[i] = map.player.passengers[i].destI;
			destIndexJ[i] = map.player.passengers[i].destJ;
		}

		for(int i=0; i<map.getRandom(); i++){

			if(carRow == destIndexI[i] && carCol == destIndexJ[i] && !map.player.passengers[i].isDropped){
				map.setElement(destIndexI[i], destIndexJ[i], 11);
				map.player.passengers[i].isDropped = true;
				picked  = false;
				incrementScore(10);
				map.player.PutInWallet(map.player.passengers[i].payTaxiDriver());
				glutPostRedisplay(); 
			}

		}
	}

	void PickUpPackage(){
		
		
		int carRow = getRowIndex(map.player.car.yI);
		int carCol = getColIndex(map.player.car.xI);

		int packagesRows[4];
		int packagesCols[4];

		for(int i=0; i<map.getRandom(); i++){
			packagesRows[i] = getRowIndex(map.player.packages[i].getYPos());
			packagesCols[i] = getColIndex(map.player.packages[i].getXPos());
			
		}

		for(int i=0; i<map.getRandom(); i++){

			if(((carRow + 1 == packagesRows[i] && carCol == packagesCols[i]) || (carRow - 1 == packagesRows[i] && carCol == packagesCols[i]) && !(picked))){
				map.setElement(packagesRows[i], packagesCols[i], 11); //setting the block to white if it was a passenger before
				map.player.packages[i].isPicked = true;
				picked = true;
				map.setElement(map.player.packages[i].destI, map.player.packages[i].destJ, 99);
				glutPostRedisplay();
				
			}
			else if(((carCol + 1 == packagesCols[i] && carRow == packagesRows[i]) || (carCol - 1 == packagesCols[i] && carRow == packagesRows[i]) && !(picked))){
				map.setElement(packagesRows[i], packagesCols[i], 11);
				map.player.packages[i].isPicked = true;
				picked = true;
				map.setElement(map.player.packages[i].destI, map.player.packages[i].destJ, 99);
				glutPostRedisplay();
			}
		}
	}

	void DropPackage(){

		int carRow = getRowIndex(map.player.car.yI);
		int carCol = getColIndex(map.player.car.xI);
		// cout << "car row: " << carRow << " " << "car col: " << carCol << endl;

		int destIndexI[4];
		int destIndexJ[4];

		for(int i=0; i<map.getRandom(); i++){
			destIndexI[i] = map.player.packages[i].destI;
			destIndexJ[i] = map.player.packages[i].destJ;
		}

		for(int i=0; i<map.getRandom(); i++){

			if(carRow == destIndexI[i] && carCol == destIndexJ[i] && !map.player.packages[i].isDropped){
				map.setElement(destIndexI[i], destIndexJ[i], 11);
				map.player.packages[i].isDropped = true;
				picked = false;
				incrementScore(20);
				map.player.PutInWallet(map.player.packages->payDeliverRider());
				glutPostRedisplay(); 
			}

		}
	}

	void resetPicked(){
		picked = false;
	}

	void SwitchRole(){

		int carRow = getRowIndex(map.player.car.yI);
		int carCol = getColIndex(map.player.car.xI);

		if(carRow == 0 && carCol == 0){
			glutDisplayFunc(MenuDisplay);
		}

	}

	int getScore() const {
		return score;
	}

	void Refuel(){

		int carRow = getRowIndex(map.player.car.yI);
		int carCol = getColIndex(map.player.car.xI);

		if(map.getElement(carRow, carCol) == 52){

			int num = (rand() % 2) + 1;
			const float FuelPricePerUnit = 2.5;
			float affordableFuel = map.player.getWalletAmount() / (num * FuelPricePerUnit);

			float fuelNeededMin = 20.0;

			if(affordableFuel > fuelNeededMin){
				map.player.car.Refuel(affordableFuel);
				map.player.reduceMoneyInWallet(map.player.getWalletAmount()/num);
			}

		}

	}

	void ScoreManagement(const char c, int i, int j){

		if( i < 0 || j < 0 || i > map.getGridSize() || j > map.getGridSize()){
			return;
		}

		if(c == 't'){
			if(map.getElement(i, j) <= 7){
				decrementScore(1);
			}
			else if(map.isPerson(i, j)){
				decrementScore(5);
			}
			else if(map.isObstacle(i, j)){
				if(!map.isFuelStation(i, j)){
					decrementScore(2);
				}
			}
			else if(map.isPassenger(i, j)){
				decrementScore(5);
			}

		}
		else if(c == 'd'){
			if(map.getElement(i, j) <= 7){
				decrementScore(4);
			}
			else if(map.isPerson(i, j)){
				decrementScore(8);
			}
			else if(map.isObstacle(i, j)){
				if(!map.isFuelStation(i, j)){
					decrementScore(4);
				}
			}
			else if(map.isPackage(i, j)){
				decrementScore(4);
			}
		}
	}

	void incrementScore(int num){
		score += num;
	}

	void decrementScore(int num){
		score -= num;
	}

	bool isGameOver(){
		if(map.player.car.fuel <= 0){
			return true;
		}
		else if(score < 0){
			return true;
		}
		else if(score > 100){
			return true;
		}
		return false;
	}

	void drawGameOverScreen(){
		
		DrawString(400, 500, "GAME OVER" ,colors[BLACK]);


		stringstream fuelOutputStream;
		fuelOutputStream << fixed << setprecision(2) << "Fuel: " << map.player.car.fuel;

		stringstream WalletOutputStream;
		WalletOutputStream << fixed << setprecision(2) << "Money: " << map.player.getWalletAmount();

		DrawRectangle(380, 280, 180, 160, colors[PALE_VIOLET_RED]);

		DrawString(390, 400, ("Score: " + to_string(score)), colors[BLACK]);
		DrawString(390, 350, fuelOutputStream.str(), colors[BLACK]);
		DrawString(390, 300, WalletOutputStream.str(), colors[BLACK]);
		
		DrawString(400, 150, "See LeaderBoard?" ,colors[BLACK]);
		if(isMouseHovering6){
			DrawString(400, 150, "See LeaderBoard?" ,colors[BLUE_VIOLET]);
			isMouseHovering6 = !isMouseHovering6;
		}

		if(score >= 100){
			DrawString(390, 200, "You made it to TOP 10!" ,colors[BLACK]);
	
		}

	}

	friend void GameDisplay();
	friend void NonPrintableKeys(int key, int x, int y);
	friend void PrintableKeys(unsigned char key, int x, int y);
	friend void Timer(int m);
	friend void MouseClicked(int button, int state, int x, int y);
	friend void MenuDisplay();
	friend void LeaderBoardDisplay();
};
Game game;


class LeaderBoard{
	int scores[10];
	string names[10];
	int count;
	string nameStrings[10];
public:
	LeaderBoard(){
		for(int i=0; i<10; i++){
			scores[i] = 0;
		}
		for(int i=0; i<10; i++){
			names[i][0] = '\0';
		}
		count = 0;
	}

	void readFromFile(){
		
		ifstream file("scores.dat", ios::binary);
		if(file.is_open()){

			file.read(reinterpret_cast<char*>(scores), sizeof(scores));

			char names2[10][40] = {};

			file.read(reinterpret_cast<char*>(names2), sizeof(names2));
			for(int i=0; i< 10; i++){
					names[i] = names2[i];
			}

			file.close();
		}
		else{
			for(int i=0; i<10; i++){
				scores[i] = 0;
				names[i] = "";
			}
		}
	}

	void writeToFile(){
		ofstream file("scores.dat", ios::binary);
		if(file.is_open()){
			file.write(reinterpret_cast<char*>(scores), sizeof(scores));

			char names2[10][40] = {};
			for(int i=0; i<10; i++){
				for(int j=0; j<39; j++){
					if(j < names[i].length()){
						names2[i][j] = names[i][j];
					}
					else{
						names2[i][j] = '\0';
					}
				}
				names2[i][39] = '\0';
			}
			file.write(reinterpret_cast<char*>(names2), sizeof(names2));
			file.close();
		}	
	}

	void updateLeaderBoard(string playername, int newScore){

		bool updated = false;
		// cout << playername;
		
		for(int i=0; i<10; i++){
			if(names[i] == "" && scores[i] == 0){
				names[i] = playername;
				scores[i] = newScore;
				updated = true;
				break;
			}
			else{

			}
		}
		if(!updated){
			if(newScore > scores[9]){ 
				names[9] = playername;
				scores[9] = newScore;
			}
		}

		SortArray();
	}

	void SortArray(){
		for(int i=0; i<9; i++){
			for(int j = i+1; j<10; j++){
				if(scores[i] < scores[j]){
					int temp = scores[i];
					scores[i] = scores[j];
					scores[j] = temp;

					string temp2 = names[i];
					names[i] = names[j];
					names[j] = temp2;

				}
			}
		}
	}

	bool isHigherThanAny(int newScore){
		for(int i=0; i<10; i++){
			if(newScore > scores[i]){
				return true;
			}
		}
		return false;
	}

	void displayLeaderBoard(){	

		DrawRectangle(360, 690, 250, 65, colors[MEDIUM_ORCHID]);
		DrawString( 390 , 707, "LEADER BOARD", colors[WHITE]);

		DrawString(250, 600, "NAMES", colors[BLACK]);
		DrawString(600, 600, "SCORES", colors[BLACK]);

		for(int i=0; i<10; i++){

			DrawString(250, 550 - i*50, names[i], colors[BLACK]);
			DrawString(600, 550 - i*50, to_string(scores[i]), colors[BLACK]);
		}

	}
};

LeaderBoard Leaderboard;
bool update = true;
void LeaderBoardDisplay(){

	glClearColor(0.847f /*Red*/, 0.749 /*Green*/, 0.847 /*Blue*/, 0.0 /*Alpha*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	isLeaderBoardOpen = true;
	Leaderboard.readFromFile();


	
	if(Leaderboard.isHigherThanAny(game.getScore()) && gameOver && game.isGameOver() && update){
		// cout << game.map.player.getPlayerName();
		Leaderboard.updateLeaderBoard(game.map.player.getPlayerName(), game.getScore());
		Leaderboard.writeToFile();
		update = false;
	}


	Leaderboard.displayLeaderBoard();

	glutSwapBuffers(); // do not modify this line..
}


/*
* Main Canvas drawing function.
* */
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
	if(!gameOver && !game.isGameOver()){

		glClearColor(0.5/*Red Component*/, 0.5,	//148.0/255/*Green Component*/,
			0.5/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
			glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			//Red Square

		game.map.DrawGrid(); // Draw the randomized map
	
		if(playerChoice == 't'){
			DrawString(380, 750, "Play as a Taxi Driver! ", colors[BLUE_VIOLET]);
		}
		else if(playerChoice == 'd'){
			DrawString(380, 750, "Play as a Delivery Rider! ", colors[BLUE_VIOLET]);
		}
		
		stringstream fuelOutputStream;
		fuelOutputStream << fixed << setprecision(2) << "Fuel: " << game.map.player.car.fuel;

		stringstream WalletOutputStream;
		WalletOutputStream << fixed << setprecision(2) << "Money: " << game.map.player.getWalletAmount();

		DrawRoundRect(817,785,150,50,colors[PURPLE],20); //score block
		DrawRoundRect(815,730,160,50,colors[HOT_PINK],20);
		DrawRoundRect(815,675,160,50,colors[THISTLE],20);
		DrawRoundRect(819,620,150,50,colors[PAPAYA_WHIP],20);
		
		
		DrawString(827, 800, ("Score: " + to_string(game.score)), colors[BLACK]);
		DrawString(820, 748, fuelOutputStream.str(), colors[BLACK]);
		DrawString(820, 693, WalletOutputStream.str(), colors[BLACK]);
		DrawString(827, 638, to_string(totalTime) + " secs left" , colors[BLACK]);

		DrawSquare(20, 790, 40, colors[WHITE]); DrawString(64, 797, "Road", colors[BLACK]);
		DrawSquare(20, 730, 40, colors[BLACK]); DrawString(64, 743, "Building", colors[BLACK]);
		
	}
	else{
		gameOver = true;
		glClearColor(0.847f /*Red*/, 0.749 /*Green*/, 0.847 /*Blue*/, 0.0 /*Alpha*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		game.drawGameOverScreen();
	}
	
	glutSwapBuffers(); // do not modify this line..

}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

	//formulas calculated for index of grid
	int carCol = (game.map.player.car.xI - 200) / (cellSize); // fro j index of grid
	int carRow = 14 - (660 - game.map.player.car.yI) / (cellSize); //initially car col would be 0 when -14


	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		
		game.ScoreManagement(playerChoice, carRow, carCol - 1);
		
		if(game.map.getElement(carRow, carCol - 1) > 7 && !(game.map.player.car.xI - cellSize < 200)){
			game.map.player.car.xI -= cellSize;
			game.map.player.car.fuel -= 0.25;
		}

	} 
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

		game.ScoreManagement(playerChoice, carRow, carCol + 1);
		
		if(game.map.getElement(carRow, carCol + 1) > 7 && !(game.map.player.car.xI + cellSize > 780)){
			game.map.player.car.xI += cellSize;
			game.map.player.car.fuel -= 0.25;
		}
		
	} 
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

		game.ScoreManagement(playerChoice, carRow + 1, carCol);
		

		if(game.map.getElement(carRow + 1, carCol) > 7 && !(game.map.player.car.yI + cellSize > 660)){
			game.map.player.car.yI += cellSize;	
			game.map.player.car.fuel -= 0.25;
		}

	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

		game.ScoreManagement(playerChoice, carRow - 1, carCol);
		
		if(game.map.getElement(carRow - 1, carCol) > 7 && !(game.map.player.car.yI - cellSize < 100)){
			game.map.player.car.yI -= cellSize;
			game.map.player.car.fuel -= 0.25;
		}
		
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
	{
		//do something if b is pressed
		if(isGameScreenOpen && !gameOver && !game.isGameOver()){ //going back
			glutDisplayFunc(MenuDisplay);
			game.ReloadGame(playerChoice);
		}
		else if(isLeaderBoardOpen){
			glutDisplayFunc(MenuDisplay);
		}
		else if(isMenuOpen){
			NameEntered = false;
			glutDisplayFunc(MenuDisplay);
		}

	}

	bool dropFlag = true;
	if (key == 'd' || key == 'D'){
		
		if(isGameScreenOpen && playerChoice == 't' && dropFlag){
			game.DropPassenger();
			dropFlag = !dropFlag;
		}
		else if(isGameScreenOpen && playerChoice == 'd' && dropFlag){
			game.DropPackage();
			dropFlag = !dropFlag;
		}

	}

	if(key == 'r' || key == 'R'){
		game.map.InitializeGrid(); 
		// cout << "Grid reinitialized!" << endl;
		game.map.player.car.xI = 200; game.map.player.car.yI = 660;
		game.resetPicked();
		glutPostRedisplay(); 
	}

	if(key == 32){ //ascii for spacebar
		
		if(isGameScreenOpen && playerChoice == 't'){
			//cout << "space pressed\n";
			game.PickUpPassenger();
		}
		else if(isGameScreenOpen && playerChoice == 'd'){
			game.PickUpPackage();
		}
	}
	
	if(key == 'p' || key == 'P'){
		if(isGameScreenOpen){
			game.SwitchRole();
		}
	}

	if(key == 'f' || key == 'f'){
		if(isGameScreenOpen){
			game.Refuel();
		}
	}

	if(isMouseClicked){

		if(key == 13){
			isMouseClicked = !isMouseClicked;
			game.map.player.setPlayerName(PlayerName);
			NameEntered = true;
		}
		else if(key == 8){
			if(!PlayerName.empty()){
				// int len = PlayerName.length();
				// PlayerName[len-1] = '\0'; //last character removed
				PlayerName.pop_back();
			}
		}
		else{
			PlayerName += key;
		}

	}

	if(key == 'g' || key == 'G'){
		if(isGameScreenOpen){
			gameOver = true;
		}
	}
	glutPostRedisplay();
}




/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	if(!gameOver && hasGameStarted){
		totalTime = totalTime;
		totalTime--;
	}
	if(totalTime <= 0) {
		gameOver = true;
	}

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	// cout << x << " " << y << endl;
	
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	
	// cout << x << " " << y << endl;
	if(isMenuOpen){
		if( (x > 300 && x < 460) && (y > 425 && y < 454) ){
			isMouseHovering1 = true;
		}
		else if( (x > 300 && x < 562) && (y > 466 && y < 493)){
			isMouseHovering2 = true;
		}
		else if( (x > 300 && x < 451) && (y > 514 && y < 548)){
			isMouseHovering3 = true;
		}
		else if( (x > 74 && x < 290) && (y > 52 && y < 73) ){
			isMouseHovering5 = true;
		}
		
	}

	if(isNameScreenOPen){
		if( (x > 432 && x < 554) && (y > 338 && y < 365) ){
			isMouseHovering4 = true;
		}
	}


	if(gameOver){
		if( (x > 424 && x < 593) && (y > 550 && y < 578) ){
			isMouseHovering6 = true;
		}
	}
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
	
		if(isMenuOpen){
			if( (x > 300 && x < 460) && (y > 425 && y < 454) ){
				/*play as taxi driver
				player role = taxi driver
				grid change
				car yellow color

				make game class with parameterized constructor taht takes key and based on key it initializes player
				with the choice of player, the grid is inialized
				grids for both roles would be diff
				for grid obstacles and packages would be initialized (grid is composed of roads, buildings, obtacles)
				but grid also has packages, cars, people (not composition, weak relation)
				*/
				playerChoice = 't';
				game.gameStart('t');
				hasGameStarted = true;
				isMenuOpen = !isMenuOpen;
				isGameScreenOpen = true;
				game.map.InitializeGrid(); 
				game.map.player.car.xI = 200; game.map.player.car.yI = 660;
				glutDisplayFunc(GameDisplay);
			}
			else if( (x > 300 && x < 562) && (y > 466 && y < 493) ){
				/*play as package derivery rider
				player role = derilvery
				car = red
				grid change
				*/
				playerChoice = 'd';
				game.gameStart('d');
				hasGameStarted = true;
				isGameScreenOpen = true;
				isMenuOpen = !isMenuOpen;
				game.map.InitializeGrid(); 
				game.map.player.car.xI = 200; game.map.player.car.yI = 660;
				glutDisplayFunc(GameDisplay);
			}
			else if( (x > 300 && x < 451) && (y > 514 && y < 548) ){
				int num = rand() % 2;
				if(num == 0){
					playerChoice = 'd';
					game.gameStart('d');
					hasGameStarted = true;
					isMenuOpen = !isMenuOpen;
					isGameScreenOpen = true;
					game.map.InitializeGrid(); 
					game.map.player.car.xI = 200; game.map.player.car.yI = 660;
					glutDisplayFunc(GameDisplay);
				}
				else if(num == 1){
					playerChoice = 't';
					game.gameStart('t');
					hasGameStarted = true;
					isMenuOpen = !isMenuOpen;
					isGameScreenOpen = true;
					game.map.InitializeGrid(); 
					game.map.player.car.xI = 200; game.map.player.car.yI = 660;
					glutDisplayFunc(GameDisplay);
				}
			}
			else if( (x > 74 && x < 290) && (y > 52 && y < 73) ){
				cout << GLUT_DOWN << " " << GLUT_UP << endl;
				glutDisplayFunc(LeaderBoardDisplay);
			}
		}

		if(isNameScreenOPen){
			if( (x > 432 && x < 554) && (y > 338 && y < 365) ){
				isMouseClicked = true;
			}
		}

		if(gameOver){
			if (  (x > 424 && x < 593) && (y > 550 && y < 578) ){
				glutDisplayFunc(LeaderBoardDisplay);
			}
		}

	} 
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
			// cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */


 int main(int argc, char*argv[]) {

	
	// InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Laraib, 24I-2544, OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(MenuDisplay);

	// glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
