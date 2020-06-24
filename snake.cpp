#include <iostream>

using namespace std;

bool gameover; 
const int wigth = 20, height = 20;
int x, y, thingX, thingY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup(){
	gameover = false;
	dir = STOP;
	x = wigth / 2;
	y = height / 2;
	thingX = rand() % wigth;
	thingY = rand() % height;
	score = 0;
}

void Draw() {
	system("clear");
	for (int i = 0; i <= wigth; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < wigth; j++) {
			if (j==0 || j==wigth-1) 
				cout << "#";
			cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i <= wigth; i++) 
		cout << "#";
	cout << endl; 
}

void Input(){

}

void Logic(){

}

int main () {
	Setup();
	while (!gameover) {
		Draw();
		Input();
		Logic();

	}
	return 0;
}