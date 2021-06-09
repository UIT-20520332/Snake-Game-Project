#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <fstream>
#define FRAME_WIDTH 60
#define FRAME_HEIGHT 28

using namespace std;

#pragma comment(lib, "winmm.lib")

void gotoxy(int column, int line);
void SetColor(WORD color);
void ShowCur(bool CursorVisibility);
void ChooseOptions();
void StartGame();
//void initHighScore();
int whereX();
int whereY();

int Diem = 0;

class HighScore {
public:
    int score;
    string name;
};

HighScore highscore[5];

struct Point {
    int x, y;
};

class CONRAN {
public:
    struct Point A[100];
    int DoDai;
    Point FOOD;
    CONRAN() {
        DoDai = 3;
        A[0].x = 12; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 10; A[2].y = 10;
        srand(time(NULL));
        FOOD.x = rand() % ((FRAME_WIDTH - 2) - 2 + 1) + 2;
        FOOD.y = rand() % ((FRAME_HEIGHT - 2) - 3 + 1) + 3;
    }
    void Ve() {
        ShowCur(false); // Ẩn con trỏ
        SetColor(12);

        // bảng hướng dẫn
        int Color;
        srand(time(NULL));
        Color = rand() % 15 + 1;
        SetColor(Color);
        for (int i = 70; i < 100; i++) {
            gotoxy(i, 0);
            cout << "#";
            gotoxy(i, 10 - 1);
            cout << "#";
        }
        for (int i = 1; i < 10; i++) {
            gotoxy(70, i);
            cout << "#";
            gotoxy(100 - 1, i);
            cout << "#";
        }
        gotoxy(72, 2);
        cout << " w = len ";
        gotoxy(72, 3);
        cout << " s = xuong ";
        gotoxy(72, 4);
        cout << " a = qua trai ";
        gotoxy(72, 5);
        cout << " s = qua phai ";
        gotoxy(72, 6);
        cout << " space = pause/continue ";
        gotoxy(72, 7);
        cout << " esc = quit ";
        gotoxy(70, 12);
        cout << "Score: " << Diem;

        // Vẽ con rắn
        SetColor(14);
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            if (i == 0)
                cout << "@";
            else
                cout << "o";
        }
    }
    int anmoi()
    {
        if (A[0].x == FOOD.x && A[0].y == FOOD.y)
        {
            DoDai++;
            A[DoDai - 1] = A[DoDai - 2];
            PlaySound(TEXT("SNAKE_eatFood.wav"), NULL, SND_ASYNC);
            srand(time(NULL));
            FOOD.x = rand() % ((FRAME_WIDTH - 2) - 2 + 1) + 2;
            FOOD.y = rand() % ((FRAME_HEIGHT - 2) - 3 + 1) + 3;
            Diem += 10;
            return 1;
        }
        else {
            gotoxy(FOOD.x, FOOD.y);
            SetColor(13);
            cout << "o";
            return 0;
        }
    }
    int EndGame() {
        if ((A[0].x == 0) || (A[0].y == 0) || (A[0].x == FRAME_WIDTH - 1) || (A[0].y == FRAME_HEIGHT - 1)) {
            PlaySound(TEXT("SNAKE_endGame.wav"), NULL, SND_ASYNC);
            Sleep(1000);
            return 1;
        }
        else
        {
            for (int i = 1; i < DoDai; i++)
            {
                if (A[0].x == A[i].x && A[0].y == A[i].y) {
                    PlaySound(TEXT("SNAKE_endGame.wav"), NULL, SND_ASYNC);
                    Sleep(1000);
                    return 1;
                }
            }
            return 0;
        }
    }
    void DiChuyen(int Huong) {
        gotoxy(A[DoDai - 1].x, A[DoDai - 1].y);
        cout << " ";
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
    //initHighScore();
    ChooseOptions();
    return 0;
}

/*void initHighScore() {
    fstream f;
    f.open("highscore.txt", ios::out);



    f.close();
}*/

void ChooseOptions() {
    ShowCur(false);
    gotoxy(47, 14);
    SetColor(4);
    cout << ">> Start <<";
    gotoxy(50, 15);
    SetColor(15);
    cout << "Quit";

    char pse;
    int Option = 1;
    pse = _getch();

    while (pse != 13) {
        if (pse == 'w' || pse == 's') {
            if (Option == 1) {
                Option++;
                gotoxy(47, 14);
                cout << "           ";
                gotoxy(50, 14);
                SetColor(15);
                cout << "Start";
                gotoxy(47, 15);
                SetColor(4);
                cout << ">> Quit <<";
            }
            else {
                if (Option == 2) {
                    Option--;
                    gotoxy(47, 15);
                    cout << "          ";
                    gotoxy(47, 14);
                    SetColor(4);
                    cout << ">> Start <<";
                    gotoxy(50, 15);
                    SetColor(15);
                    cout << "Quit";
                }
            }
        }
        pse = _getch();
    }
    if (Option == 1) {
        //PlaySound(TEXT("SNAKE_start.wav"), NULL, SND_ASYNC);
        StartGame();
    }
    else {
        system("cls");
        return;
    }
}

// Bắt đầu Game
void StartGame() {
    system("cls");
    PlaySound(TEXT("SNAKE_start.wav"), NULL, SND_ASYNC);
    Diem = 0;
    CONRAN r;
    int Huong = 0;
    char t;

    // Vẽ khung
    SetColor(13);
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

    char pse;
    int pc = 0;
    while (1) {
        if (_kbhit()) {
            t = _getch();
            //PlaySound(TEXT("SNAKE_beep.wav"), NULL, SND_ASYNC);
            if (t == 'a') Huong = 2;
            else if (t == 'w') Huong = 3;
            else if (t == 'd') Huong = 0;
            else if (t == 's') Huong = 1;
            else if (t == ' ')
            {
                gotoxy(FRAME_WIDTH / 2 - 10, FRAME_HEIGHT / 2);
                cout << "press SPACE to continue";
                pse = _getch();
                while (pse != ' ' && pse != 27)
                    pse = _getch();
                if (pse == ' ')
                {
                    gotoxy(FRAME_WIDTH / 2 - 10, FRAME_HEIGHT / 2);
                    cout << "                       ";
                }
                else {
                    if (pse == 27)
                    {
                        system("cls");
                        gotoxy(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
                        cout << "END GAME";
                        Sleep(1000);
                        system("cls");
                        break;
                    }
                }
            }
            else if (t == 27)
            {
                gotoxy(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
                cout << "END GAME";
                Sleep(1000);
                system("cls");
                break;
            }
        }
        r.Ve();
        r.anmoi();
        if (r.EndGame())
        {
            system("cls");
            //gotoxy(FRAME_WIDTH / 2, FRAME_HEIGHT / 2);
            cout << "Your score: " << Diem;
            Sleep(1000);
            system("cls");
            cout << "Ban co muon choi lai? [y/n]: ";
            char Ops;
            Ops = _getch();
            while (Ops != 'y' && Ops != 'n')
                Ops = _getch();
            if (Ops == 'y') {
                //PlaySound(TEXT("SNAKE_start.wav"), NULL, SND_ASYNC);
                StartGame();
            }
            else {
                system("cls");
                exit(0);
            }
            break;
        }
        r.DiChuyen(Huong);
        Sleep(100);
    }
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