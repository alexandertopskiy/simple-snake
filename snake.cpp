#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

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
			else if (i == thingY && j == thingX)
				cout << "F";
			else
				cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i <= wigth; i++) 
		cout << "#";
	cout << endl; 

	cout << "\nSCORE = " << score << endl;

	usleep(150000);
}

void Input(){
	char key = '\0'; //null
	if (kbhit()) key = mygetch();
    if (key == 'a' || key == 'A')
    	dir = LEFT;
    if (key == 'd' || key == 'D')
    	dir = RIGHT;
    if (key == 'w' || key == 'W')
    	dir = UP;
    if (key == 's' || key == 'S')
    	dir = DOWN;
    if (key == 'x' || key == 'X') {
    	cout << "\nGAME OVER\n";
		usleep(5000);
		gameover = true;
    }
}

void Logic(){
	if (dir == LEFT)
		x--;
	if (dir == RIGHT)
		x++;
	if (dir == UP)
		y--;
	if (dir == DOWN)
		y++;


	if (x > wigth || x < 0 || y > height || y < 0){
    	cout << "\nGAME OVER\n";
		usleep(5000);
		gameover = true;
    }
    if (x == thingX && y == thingY) {
    	score += 10;
    	thingX = rand() % wigth;
    	thingY = rand() % height;
    }
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