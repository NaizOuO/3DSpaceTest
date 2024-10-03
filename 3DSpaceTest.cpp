//******************************************
// fileName: 3DSpaceTest
// startDate: 2024/10/1
// Maker: Naiz (MartisHung assist in revising)
// screenSize: 64 * 64 (actually 128 * 64)
//******************************************

#include "Header.h"
#define NumberOfPosition 8

// Constants
const double d = 50 * 32 / 9 - 100;
const double rad = 3.1415926535 / 180;
const double cameraPosition[3] = {0, 50 + d, 0};
const int screenWidth = 128 * 2, screenHeight = 32 * 2;
// Positions of the points in 3D space
double anyPositions[NumberOfPosition][3] = {
    {20, 20, 20}, {-20, 20, 20}, {20, -20, 20}, {-20, -20, 20},
    {20, 20, -20}, {-20, 20, -20}, {20, -20, -20}, {-20, -20, -20}
};

double screenPositions[NumberOfPosition][2] = {};
double line[NumberOfPosition][3] = {}; 
double PerAngleX = 2 * rad, PerAngleY = 1 * rad, PerAngleZ = 1 * rad;
double bufNumber;

inline void showEveryLine(int c);

int main() {	 
    // Initialize const to avoid repetitive computation
    double cosX = cos(PerAngleX), sinX = sin(PerAngleX);
    double cosY = cos(PerAngleY), sinY = sin(PerAngleY);
    double cosZ = cos(PerAngleZ), sinZ = sin(PerAngleZ);
    
    // Initialize positions to avoid division by 0
    for (int i = 0; i < NumberOfPosition; i++) {
        for (int j = 0; j < 3; j++) {
            anyPositions[i][j] = (anyPositions[i][j]) ? anyPositions[i][j] : 0.001;
        }
    }
	
    while (!_kbhit() || _getch() != 'q') {		// Press 'q' to quit the loop
    
		// Clear last position of each particle
	    for (int i = 0; i < NumberOfPosition; i++) {
	        point(screenWidth, screenHeight, screenPositions[i][0], screenPositions[i][1], 32);
	    }
    
        // Rotate positions in 3D space around x, y, z axes
        for (int i = 0; i < NumberOfPosition; i++) {
            bufNumber = anyPositions[i][1] * cosX - anyPositions[i][2] * sinX;
            anyPositions[i][2] = anyPositions[i][1] * sinX + anyPositions[i][2] * cosX;
            anyPositions[i][1] = bufNumber;

            bufNumber = anyPositions[i][0] * cosY - anyPositions[i][2] * sinY;
            anyPositions[i][2] = anyPositions[i][0] * sinY + anyPositions[i][2] * cosY;
            anyPositions[i][0] = bufNumber;

            bufNumber = anyPositions[i][0] * cosZ - anyPositions[i][1] * sinZ;
            anyPositions[i][1] = anyPositions[i][0] * sinZ + anyPositions[i][1] * cosZ;
            anyPositions[i][0] = bufNumber;
        }

        // 3D to 2D transform
        for (int i = 0; i < NumberOfPosition; i++) {
            line[i][0] = sqrt(pow(anyPositions[i][0] - cameraPosition[0], 2) +
                              pow(anyPositions[i][1] - cameraPosition[1], 2) +
                              pow(anyPositions[i][2] - cameraPosition[2], 2));

            line[i][1] = sqrt(pow(anyPositions[i][0], 2) + pow(anyPositions[i][2], 2));
            line[i][2] = d * tan(asin(line[i][1] / line[i][0]));

            screenPositions[i][0] = -2 * line[i][2] * (anyPositions[i][0] / line[i][1]);
            screenPositions[i][1] = line[i][2] * (anyPositions[i][2] / line[i][1]);
        }
        
        // Initialize screen
        system("cls");
        
        // Draw every line between points
        showEveryLine(34);

        // Show positions of each particle
        for (int i = 0; i < NumberOfPosition; i++) {
            point(screenWidth, screenHeight, screenPositions[i][0], screenPositions[i][1], 65 + i);
        }
        
        // Show the outline of screen
        drawScreen(screenWidth, screenHeight, 77);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    system("pause");
    return 0;
}

inline void showEveryLine(int c) {
    showLine(screenWidth, screenHeight, screenPositions[0][0], screenPositions[0][1], screenPositions[1][0], screenPositions[1][1], c);
    showLine(screenWidth, screenHeight, screenPositions[0][0], screenPositions[0][1], screenPositions[2][0], screenPositions[2][1], c);
    showLine(screenWidth, screenHeight, screenPositions[0][0], screenPositions[0][1], screenPositions[4][0], screenPositions[4][1], c);
    showLine(screenWidth, screenHeight, screenPositions[7][0], screenPositions[7][1], screenPositions[3][0], screenPositions[3][1], c);
    showLine(screenWidth, screenHeight, screenPositions[7][0], screenPositions[7][1], screenPositions[5][0], screenPositions[5][1], c);
    showLine(screenWidth, screenHeight, screenPositions[7][0], screenPositions[7][1], screenPositions[6][0], screenPositions[6][1], c);
    showLine(screenWidth, screenHeight, screenPositions[4][0], screenPositions[4][1], screenPositions[5][0], screenPositions[5][1], c);
    showLine(screenWidth, screenHeight, screenPositions[4][0], screenPositions[4][1], screenPositions[6][0], screenPositions[6][1], c);
    showLine(screenWidth, screenHeight, screenPositions[1][0], screenPositions[1][1], screenPositions[3][0], screenPositions[3][1], c);
    showLine(screenWidth, screenHeight, screenPositions[1][0], screenPositions[1][1], screenPositions[5][0], screenPositions[5][1], c);
    showLine(screenWidth, screenHeight, screenPositions[2][0], screenPositions[2][1], screenPositions[3][0], screenPositions[3][1], c);
    showLine(screenWidth, screenHeight, screenPositions[2][0], screenPositions[2][1], screenPositions[6][0], screenPositions[6][1], c);
}
