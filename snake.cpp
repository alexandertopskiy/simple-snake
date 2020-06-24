#include <iostream>

using namespace std;

bool gameover; 
const int wigth = 20, height = 20;
int x, y, thingX, thingY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

//функции для проверки буфера. т.к. в unix нет <conio.h> и встроенных в нее kbhit и getch
int kbhit(void){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
int mygetch( ){
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void Setup(){
	gameover = false;
	dir = STOP;
	x = wigth / 2 - 1;
	y = height / 2 - 1;
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
			if (i == y && j == x)
				cout << "0";
			if (i == thingY && j == thingX)
				cout << "F";
			cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i <= wigth; i++) 
		cout << "#";
	cout << endl; 
}

void Input(){
	if (kbhit()) key = mygetch();
    if ((key == 'q') || (key == 'Q')) break;
    switch(key) {
    	case 'a':
    		dir = LEFT;
    		break;
    	case 'd':
    		dir = RIGHT;
    		break;
    	case 'w':
    		dir = UP;
    		break;
    	case 's':
    		dir = DOWN;
    		break;
    	case 'x':
    		gameover = true;
    		break;


    }
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