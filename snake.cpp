#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

using namespace std;

bool gameover; 
const int wigth = 20, height = 20;
int x, y, thingX, thingY, score;
int tailX[100], tailY[100]; // координаты хвоста
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN, ENDGAME };
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
	for (int i = 0; i <= wigth + 1; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= wigth; j++) {
			if (j == 0 || j == wigth) 
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == thingY && j == thingX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i <= wigth + 1; i++) 
		cout << "#";
	cout << endl; 

	cout << "\nSCORE = " << score << endl;

	cout << "КООРДИНАТЫ ФРУКТА: x = " << thingX + 1 << ", y = " << thingY + 1 << endl;

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
    if (key == 'x' || key == 'X') 
    	dir = ENDGAME;
}

void Logic(){

	int prevX = tailX[0], prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x; tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i]; prev2Y = tailY[i];
		tailX[i] = prevX; tailY[i] = prevY;
		prevX = prev2X; prevY = prev2Y;
	}

	if (dir == LEFT) x--;
	if (dir == RIGHT) x++;
	if (dir == UP) y--;
	if (dir == DOWN) y++;
	if (dir == ENDGAME) {
		system("clear");
		Draw();
		cout << "\nGAME OVER\n";
		usleep(5000);
		gameover = true;
	}

	if (x >= wigth) 
		x = 0;
	else if (x < 0)
		x = wigth - 1;
	if (y >= height) 
		y = 0;
	else if (y < 0)
		y = height - 1;

    for (int i = 0; i < nTail; i++) {
    	if (tailX[i] == x && tailY[i] == y) {
    		system("clear");
    		// Draw();
    		cout << "\nGAME OVER\n";
			usleep(5000);
			gameover = true;
    	}
    }

    if (x == thingX && y == thingY) {
    	score += 10;
    	thingX = rand() % wigth;
    	thingY = rand() % height;
    	nTail++;
    }
}

int main () {
	Setup();

	cout << "1 - НАЧАТЬ ИГРУ" <<
	<< "2 - ПОСМОТРЕТЬ ТАБЛИЦУ РЕКОРДОВ" <<
	<< "3 - ВЫБРАТЬ УРОВЕНЬ СЛОЖНОСТИ" <<
	<< "0 - ВЫХОД" << endl;



	while (!gameover) {
		

		Draw();
		Input();
		Logic();
	}
	return 0;
}