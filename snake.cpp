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
    CONRAN() {
        DoDai = 3;
        A[0].x = 12; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 10; A[2].y = 10;
    }
    void Ve() {
        ShowCur(false); // Ẩn con trỏ

        // Vẽ khung
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

        // Vẽ con rắn
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0)
                cout << "@";
            else
                cout << "o";
        }
    }
    int anmoi(POINT f)
    {
        if (A[0].x == f.x && A[0].y == f.y)
        {
            DoDai++;
            A[DoDai - 1] = A[DoDai - 2];
            return 1;
        }
        return 0;
    }
    int EndGame() {
        if ((A[0].x == 0) || (A[0].y == 0) || (A[0].x == FRAME_WIDTH - 1) || (A[0].y == FRAME_HEIGHT - 1)) {
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
                if (A[0].x == A[i].x && A[0].y == A[i].y) return 1;

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
	POINT FOOD;
	srand(time(NULL));
	FOOD.x = rand() % ((FRAME_WIDTH-1) - 1 + 1) + 1;
	FOOD.y = rand() % ((FRAME_HEIGHT-2) - 3 + 1) + 3;
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
		if (r.anmoi(FOOD) == 0)
		{
			gotoxy(FOOD.x, FOOD.y);
			cout << "x";
				
		}
		if (r.anmoi(FOOD) == 1)
		{
			srand(time(NULL));
			FOOD.x = rand() % ((FRAME_WIDTH-1) - 1 + 1) + 1;
			FOOD.y = rand() % ((FRAME_HEIGHT-2) - 3 + 1) + 3;
		}
		else
		{
			Sleep(50);
		}
		if (r.EndGame())
		{
			system("cls");
			cout << " You ARE SO STUPID . GAME OVER";
			Sleep(1000);
			break;
		}
		r.DiChuyen(Huong);
		//Sleep(200);
	}

	return 0;
}

// Đưa con trỏ đến vị trí column line
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

// whereX, whereY trả về vị trí hiện tại của con trỏ
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

// Đổi màu chữ trên màn hình console
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

// Ẩn con trỏ trên màn hình console
void ShowCur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}
