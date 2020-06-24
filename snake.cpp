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