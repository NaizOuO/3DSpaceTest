//******************************************
// fileName:3DSpaceTest
// startDate:2024/10/1
// Maker:Naiz
// screemSize:64 * 64 (actually 128 * 64)
//******************************************

#include"Header.h"
using namespace std;

const double d = 50*32/9-100;
const double rad = 3.1415926535/180;
const double cameraPosition[3] = {0,50+d,0};
const int numberOfPosition = 8;
//const int numberOfPosition = 25;
const int screenWidth = 64*2*2;
const int screenHeight = 64*2;
double anyPositions[numberOfPosition][3] = {{20,20,20},{-20,20,20},{20,-20,20},{-20,-20,20},{20,20,-20},{-20,20,-20},{20,-20,-20},{-20,-20,-20}};	//{A,B,C,D,E,F,G,H}
//double anyPositions[numberOfPosition][3] = {{20,60,20},{-20,60,20},{20,-60,20},{-20,-60,20},{20,60,-20},{-20,60,-20},{20,-60,-20},{-20,-60,-20},   {60,20,20},{-60,20,20},{60,-20,20},{-60,-20,20},{60,20,-20},{-60,20,-20},{60,-20,-20},{-60,-20,-20},   {20,20,60},{-20,20,60},{20,-20,60},{-20,-20,60},{20,20,-60},{-20,20,-60},{20,-20,-60},{-20,-20,-60},   {0,0,0}};
double bufPosition[numberOfPosition][3] = {};
double screenPositions[numberOfPosition][2] = {};
double line[numberOfPosition][3] = {};		//{TheDistanceOf aP to cP, TheDistanceOf aP to y-axis, TheDistanceOnScreen} or {rn,Rn,Kn}
double perAngleX = 1*rad;
double perAngleY = 0*rad;
double perAngleZ = 2*rad;
double bufNumber;
inline void showEveryLine(int c);

int main(){
	system("pause");
	for(int i = 0; i < numberOfPosition; i++){			//avoid dividing by 0
		for(int j = 0; j < 3; j++){
			if(anyPositions[i][j] == 0){
				bufPosition[i][j] = 0.001;
			}
			else
				bufPosition[i][j] = anyPositions[i][j];
		}
	}
	
	while(1){
		drawScreen(screenWidth, screenHeight, 65+12);
		
		showEveryLine(32);								//clear every line
		
		for(int i = 0; i < numberOfPosition; i++){		//clear last position of each particles
			point(screenWidth, screenHeight, screenPositions[i][0], screenPositions[i][1], 32);
		}
		
		for(int i = 0; i < numberOfPosition; i++){		//rotate the position of each particles in 3D  with x-axis
			bufNumber = bufPosition[i][1]*cos(perAngleX) - bufPosition[i][2]*sin(perAngleX);
			bufPosition[i][2] = bufPosition[i][1]*sin(perAngleX) + bufPosition[i][2]*cos(perAngleX);
			bufPosition[i][1] = bufNumber;
		}
		
		for(int i = 0; i < numberOfPosition; i++){		//rotate the position of each particles in 3D  with y-axis
			bufNumber = bufPosition[i][0]*cos(perAngleY) - bufPosition[i][2]*sin(perAngleY);
			bufPosition[i][2] = bufPosition[i][0]*sin(perAngleY) + bufPosition[i][2]*cos(perAngleY);
			bufPosition[i][0] = bufNumber;
		}
		
		for(int i = 0; i < numberOfPosition; i++){		//rotate the position of each particles in 3D with z-axis
			bufNumber = bufPosition[i][0]*cos(perAngleZ) - bufPosition[i][1]*sin(perAngleZ);
			bufPosition[i][1] = bufPosition[i][0]*sin(perAngleZ) + bufPosition[i][1]*cos(perAngleZ);
			bufPosition[i][0] = bufNumber;
		}
		
		for(int i = 0; i < numberOfPosition; i++){		//3D transform to 2D
			for(int j = 0; j < 3; j++){
				line[i][0] += pow( bufPosition[i][j] - cameraPosition[j], 2 );
			}
			line[i][0] = sqrt( line[i][0] );
			line[i][1] = sqrt( pow( bufPosition[i][0], 2 ) + pow( bufPosition[i][2], 2 ) );
			line[i][2] = d * tan( asin( line[i][1] / line[i][0] ) );
		}
		
		for(int i = 0; i < numberOfPosition; i++){		//write down the posotion in 2D
			screenPositions[i][0] = -2*line[i][2]*(bufPosition[i][0]/line[i][1]);
			screenPositions[i][1] = line[i][2]*(bufPosition[i][2]/line[i][1]);
		}
		
		showEveryLine(34);								//show every line
		
		for(int i = 0; i < numberOfPosition; i++){		//show the position of each particles in 2D
			point(screenWidth, screenHeight, screenPositions[i][0], screenPositions[i][1], 65+i);
		}
	}
	return 0;
}

inline void showEveryLine(int c){	//{A,B,C,D,E,F,G,H}
	showLine(screenWidth, screenHeight, screenPositions[0][0], screenPositions[0][1], screenPositions[1][0], screenPositions[1][1],c);
	showLine(screenWidth, screenHeight, screenPositions[0][0], screenPositions[0][1], screenPositions[2][0], screenPositions[2][1],c);
	showLine(screenWidth, screenHeight, screenPositions[0][0], screenPositions[0][1], screenPositions[4][0], screenPositions[4][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7][0], screenPositions[7][1], screenPositions[3][0], screenPositions[3][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7][0], screenPositions[7][1], screenPositions[5][0], screenPositions[5][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7][0], screenPositions[7][1], screenPositions[6][0], screenPositions[6][1],c);
	showLine(screenWidth, screenHeight, screenPositions[4][0], screenPositions[4][1], screenPositions[5][0], screenPositions[5][1],c);
	showLine(screenWidth, screenHeight, screenPositions[4][0], screenPositions[4][1], screenPositions[6][0], screenPositions[6][1],c);
	showLine(screenWidth, screenHeight, screenPositions[2][0], screenPositions[2][1], screenPositions[3][0], screenPositions[3][1],c);
	showLine(screenWidth, screenHeight, screenPositions[2][0], screenPositions[2][1], screenPositions[6][0], screenPositions[6][1],c);
	showLine(screenWidth, screenHeight, screenPositions[1][0], screenPositions[1][1], screenPositions[3][0], screenPositions[3][1],c);
	showLine(screenWidth, screenHeight, screenPositions[1][0], screenPositions[1][1], screenPositions[5][0], screenPositions[5][1],c);
	/*
	showLine(screenWidth, screenHeight, screenPositions[0+8][0], screenPositions[0+8][1], screenPositions[1+8][0], screenPositions[1+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[0+8][0], screenPositions[0+8][1], screenPositions[2+8][0], screenPositions[2+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[0+8][0], screenPositions[0+8][1], screenPositions[4+8][0], screenPositions[4+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7+8][0], screenPositions[7+8][1], screenPositions[3+8][0], screenPositions[3+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7+8][0], screenPositions[7+8][1], screenPositions[5+8][0], screenPositions[5+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7+8][0], screenPositions[7+8][1], screenPositions[6+8][0], screenPositions[6+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[4+8][0], screenPositions[4+8][1], screenPositions[5+8][0], screenPositions[5+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[4+8][0], screenPositions[4+8][1], screenPositions[6+8][0], screenPositions[6+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[2+8][0], screenPositions[2+8][1], screenPositions[3+8][0], screenPositions[3+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[2+8][0], screenPositions[2+8][1], screenPositions[6+8][0], screenPositions[6+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[1+8][0], screenPositions[1+8][1], screenPositions[3+8][0], screenPositions[3+8][1],c);
	showLine(screenWidth, screenHeight, screenPositions[1+8][0], screenPositions[1+8][1], screenPositions[5+8][0], screenPositions[5+8][1],c);
	
	showLine(screenWidth, screenHeight, screenPositions[0+16][0], screenPositions[0+16][1], screenPositions[1+16][0], screenPositions[1+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[0+16][0], screenPositions[0+16][1], screenPositions[2+16][0], screenPositions[2+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[0+16][0], screenPositions[0+16][1], screenPositions[4+16][0], screenPositions[4+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7+16][0], screenPositions[7+16][1], screenPositions[3+16][0], screenPositions[3+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7+16][0], screenPositions[7+16][1], screenPositions[5+16][0], screenPositions[5+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[7+16][0], screenPositions[7+16][1], screenPositions[6+16][0], screenPositions[6+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[4+16][0], screenPositions[4+16][1], screenPositions[5+16][0], screenPositions[5+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[4+16][0], screenPositions[4+16][1], screenPositions[6+16][0], screenPositions[6+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[2+16][0], screenPositions[2+16][1], screenPositions[3+16][0], screenPositions[3+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[2+16][0], screenPositions[2+16][1], screenPositions[6+16][0], screenPositions[6+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[1+16][0], screenPositions[1+16][1], screenPositions[3+16][0], screenPositions[3+16][1],c);
	showLine(screenWidth, screenHeight, screenPositions[1+16][0], screenPositions[1+16][1], screenPositions[5+16][0], screenPositions[5+16][1],c);
	*/
}
