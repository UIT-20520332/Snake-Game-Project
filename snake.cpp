#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <ctime>

#define FRAME_WIDTH 50
#define FRAME_HEIGHT 20

using namespace std;

void gotoxy(int column, int line);
void SetColor(WORD color);
void ShowCur(bool CursorVisibility);
int whereX();
int whereY();

struct Point {
    int x, y;
};
class CONRAN {
public:
    struct Point A[100];
    int DoDai;
    struct FOOD
	{
		POINT F;
		int kc;
	};
	FOOD FO[100];
	int slm;
    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
        slm = 50;
		FO[0].F.x = 5;
		FO[0].F.y = 5;
        for (int i = 1; i <= slm; i++)
		{
			if ((i-1) % 5 == 0 && (i-1) != 0) FO[i-1].kc=2;
			else FO[i-1].kc = 1;
			if ((i) % 2 == 0)
			{
				FO[i].F.x = FO[i-1].F.x + 7;
				FO[i].F.y = FO[i-1].F.y + 6;
			}
			else
			{
				FO[i].F.x = FO[i - 1].F.x - 3;
				FO[i].F.y = FO[i - 1].F.y - 2;
			}
		}
    }
    void Ve() {
        ShowCur(false);
        for (int i = 0; i < FRAME_WIDTH; i++) {
            gotoxy(i, 0);
            cout << "#";
            gotoxy(i, FRAME_HEIGHT - 1);
            cout << "#";
        }
        for (int i = 1; i < FRAME_HEIGHT; i++) {
            gotoxy(0, i);
            cout << "#";
            gotoxy(FRAME_WIDTH - 1, i);
            cout << "#";
        }
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0)
                cout << "@";
            else
                cout << "o";
        }
    }
    void vemoi(FOOD f)
	{
		if (f.kc == 1)
			{
				gotoxy(f.F.x, f.F.y);
				cout << "x";
			}
		else if (f.kc == 2)
			{
				gotoxy(f.F.x, f.F.y);
				cout << "X";
			}
	}
	int anmoi(FOOD f)
	{
		if (A[0].x == f.F.x&&A[0].y == f.F.y)
		{

			if (f.kc == 1)
			{
				DoDai++;
				A[DoDai - 1] = A[DoDai - 2];
				return 1;
			}
			else if (f.kc == 2)
			{
				DoDai += 3;
				A[DoDai - 1] = A[DoDai - 2];
				A[DoDai - 2] = A[DoDai - 3];
				A[DoDai - 3] = A[DoDai - 4];
				return 1;
			}	
		}
		return 0;
	}
    int EndGame() {
        if (A[0].x == 0 || A[0].y == 0 || A[DoDai - 1].x == FRAME_WIDTH || A[DoDai - 1].y == FRAME_HEIGHT) {
            system("cls");
            for (int i = 0; i < FRAME_WIDTH; i++) {
                gotoxy(i, 0);
                cout << "#";
                gotoxy(i, FRAME_HEIGHT - 1);
                cout << "#";
            }
            for (int i = 1; i < FRAME_HEIGHT; i++) {
                gotoxy(0, i);
                cout << "#";
                gotoxy(FRAME_WIDTH - 1, i);
                cout << "#";
            }
            gotoxy(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
            cout << "Game Over";
            return 1;
        }
        else
		{
			for (int i = 1; i < DoDai; i++)
				{
					if (A[0].x == A[i].x &&A[0].y == A[i].y) return 1;
				
				}
				return 0;
		}
    }
    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0;i--)
            A[i] = A[i - 1];
        if (Huong == 0) A[0].x = A[0].x + 1;
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1;
        if (Huong == 3) A[0].y = A[0].y - 1;
    }
};

int main()
{
    //initwindow(600,600);
    CONRAN r;
    int Huong = 0;
    char t;

    while (1) {
        if (_kbhit()) {
            t = _getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's') Huong = 1;
        }
        system("cls");
        r.Ve();
        if (s < r.slm)
		{
			if (r.anmoi(r.FO[s]) == 0)
			{
				r.vemoi(r.FO[s]);
			}
		}
		if (r.anmoi(r.FO[s]) == 1)
		{
			s++;

		}
		else
		{
			Sleep(200);
		}
        if (r.EndGame())
            break;
        r.DiChuyen(Huong);
    }

    return 0;
}


void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

int whereX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}

int whereY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}

void SetColor(WORD color) {
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void ShowCur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}
