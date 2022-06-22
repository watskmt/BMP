#include "DxLib.h"

#define WINDOW_X 400
#define WINDOW_Y 400
#define COUNT_X 20
#define COUNT_Y 20
#define STATUS_WALL 1
#define STATUS_AVOID -1
#define STATUS_CLEAR 0
#define STATUS_DEADEND -2
#define INTERVAL 300

typedef struct Point {
    int x;
    int y;
}Point;

int status[COUNT_Y][COUNT_X];

int map[1][COUNT_Y][COUNT_X] =
{
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}

        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        ,{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }
};

Point pos;
Point enemy[5];
Point route[COUNT_X * COUNT_Y];

enum Direction {none, right, left, up, down};

int SetStatus();
int SetStatus(int mapNo);
int DrawSquares();
int ShowStatus(int);
int GoNext();
int GoNext(Point *me, Direction dir);
int GoNext(Point* me, Point* target);
Direction GetGoingDirection();
int IntervalExecute();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    enemy[0].x = COUNT_X / 2; enemy[0].y = COUNT_Y/2;

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }
    ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);
	int GHandle = LoadGraph(TEXT("me.bmp"));
    srand(GetNowCount());

        // キー入力待ち
    while (WaitKey() != KEY_INPUT_Q)
    {
        pos.x = 0;
        pos.y = 0;

        SetStatus(0);
        do {
            ClearDrawScreen();
            DrawSquares();
            ShowStatus(GHandle);
            if (pos.x == COUNT_X - 1 && pos.y == COUNT_Y - 1)
                break;
        	// 現在地更新ロジック
            Direction dir = GetGoingDirection();
            if (dir != none)
                GoNext(&pos, dir);
            if(IntervalExecute())
	            GoNext(&enemy[0], &pos);

        	if (ProcessMessage() == -1)
            {
                break;        // エラーが起きたらループを抜ける
            }
        } while (1);
    }

    // キー入力待ち
    WaitKey();

    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}

int IntervalExecute()
{
    static int previousExecuteTime = 0;

    if ((previousExecuteTime + INTERVAL) < GetNowCount())
    {
        previousExecuteTime = GetNowCount();
        return 1;
    }
    else
        return 0;
}


int GoNext(Point* me, Point* target)
{
    int i;
    Direction dir[5]={none, none, none, none, none};
    if(me->x > target->x)
    {
	    if(me->y > target->y)
	    {
            dir[0] = up; dir[1] = left; dir[2] = down; dir[3] = right;
	    }
        else
        {
            dir[0] = down; dir[1] = left; dir[2] = right; dir[3] = up;
        }
    }
    else
    {
        if (me->y > target->y)
        {
            dir[0] = up; dir[1] = right; dir[2] = down; dir[3] = left;
        }
        else
        {
            dir[0] = down; dir[1] = right; dir[2] = left; dir[3] = up;
        }
    }

    for (i = 0; i < 5; i++)
    {
        // 右方向
        if (dir[i] == right && me->x < COUNT_X - 1 && status[me->y][me->x + 1] == STATUS_CLEAR)
        {
            me->x++;
            break;
        }
        // 下方向
        else if (dir[i] == down && me->y < COUNT_Y - 1 && status[me->y + 1][me->x] == STATUS_CLEAR)
        {
            me->y++;
            break;
        }
        	// 左方向
        else if (dir[i] == left && me->x > 0 && status[me->y][me->x - 1] == STATUS_CLEAR)
        {
            me->x--;
            break;
        }// 上方向
        else if (dir[i] == up && me->y > 0 && status[me->y - 1][me->x] == STATUS_CLEAR)
        {
            me->y--;
            break;
        }
        else if (dir[i] == none)
            return -1;
    }
    return 0;

}

int GoNext(Point* me, Direction dir)
{
    // 右方向
    if (dir == right && me->x < COUNT_X - 1 && status[me->y][me->x + 1] == STATUS_CLEAR)
        me->x++;
    // 下方向
    else if (dir == down && me->y < COUNT_Y - 1 && status[me->y + 1][me->x] == STATUS_CLEAR)
        me->y++;
    // 左方向
    else if (dir == left && me->x > 0 && status[me->y][me->x - 1] == STATUS_CLEAR)
        me->x--;
    // 上方向
    else if (dir == up && me->y > 0 && status[me->y - 1][me->x] == STATUS_CLEAR)
        me->y--;

    return 0;
}

Direction GetGoingDirection()
{
    int keyCode = 0;
    static int previousKeyCode = 0;

	if (CheckHitKey(KEY_INPUT_RIGHT))
        keyCode = KEY_INPUT_RIGHT;
    else  if (CheckHitKey(KEY_INPUT_LEFT))
        keyCode = KEY_INPUT_LEFT;
    else if (CheckHitKey(KEY_INPUT_UP))
        keyCode = KEY_INPUT_UP;
    else if (CheckHitKey(KEY_INPUT_DOWN))
        keyCode = KEY_INPUT_DOWN;
    else
        keyCode = 0;

    if (keyCode != previousKeyCode)
    {
        previousKeyCode = keyCode;
        switch (keyCode)
        {
        case KEY_INPUT_RIGHT:
            return right;
        case KEY_INPUT_LEFT:
            return left;
        case KEY_INPUT_UP:
            return up;
        case KEY_INPUT_DOWN:
            return down;
        default:
            return none;
        }
    }
    else
	    return none;
}



int DrawSquares()
{
    int i, j;
    int x1, y1;
    int x2, y2;
    int sizeX = WINDOW_X / COUNT_X;
    int sizeY = WINDOW_Y / COUNT_Y;
    unsigned int color = GetColor(255, 255, 255);

    for (i = 0; i < COUNT_Y; i++)
    {
        y1 = i * sizeY;
        y2 = (i + 1) * sizeY;

        for (j = 0; j < COUNT_X; j++)
        {
            x1 = j * sizeX;
            x2 = (j + 1) * sizeX;
            DrawBox(x1, y1, x2, y2, color, 0);
        }
    }
    return 0;
}

int SetStatus()
{
	for(int i=0; i<COUNT_Y; i++)
        for(int j=0; j<COUNT_X; j++)
        {
            if ((rand() % 10) < 2)
                status[i][j] = STATUS_WALL;
            else
                status[i][j] = STATUS_CLEAR;
        }

    status[0][0] = STATUS_CLEAR;
    status[0][1] = STATUS_CLEAR;
    status[1][0] = STATUS_CLEAR;
    status[1][1] = STATUS_CLEAR;

    status[COUNT_Y - 1][COUNT_X - 1] = STATUS_CLEAR;
    status[COUNT_Y - 1][COUNT_X - 2] = STATUS_CLEAR;
    status[COUNT_Y - 2][COUNT_X - 1] = STATUS_CLEAR;
    status[COUNT_Y - 2][COUNT_X - 2] = STATUS_CLEAR;

    return 0;
}
int SetStatus(int mapNo)
{
    for (int i = 0; i < COUNT_Y; i++)
        for (int j = 0; j < COUNT_X; j++)
        {
            if (map[mapNo][i][j] == 1)
                status[i][j] = STATUS_WALL;
            else
                status[i][j] = STATUS_CLEAR;
        }

    return 0;
}

int ShowStatus(int gHandle)
{
    int i, j;
    int x1, y1;
    int x2, y2;
    const int sizeX = WINDOW_X / COUNT_X;
    const int sizeY = WINDOW_Y / COUNT_Y;
    unsigned int color;

    const unsigned int color_wall = GetColor(255, 255, 255);
    const unsigned int color_avoid = GetColor(200, 100, 100);
    const unsigned int color_clear = GetColor(0, 0, 0);
    const unsigned int color_me = GetColor(255, 0, 0);


    for (i = 0; i < COUNT_Y; i++)
    {
        y1 = i * sizeY+1;
        y2 = (i + 1) * sizeY-2;

        for (j = 0; j < COUNT_X; j++)
        {
            x1 = j * sizeX+1;
            x2 = (j + 1) * sizeX-2;
            switch(status[i][j])
            {
            case STATUS_WALL:
                color = color_wall;
                break;
            case STATUS_CLEAR:
                color = color_clear;
                break;
            case STATUS_AVOID:
                color = color_avoid;
                break;
            default:
                color = color_wall;
                break;
            }
            DrawBox(x1, y1, x2, y2, color, 1);

            if (j == pos.x && i == pos.y)
                DrawExtendGraph(x1,y1,x2,y2, gHandle, 1);
            if (j == enemy[0].x && i == enemy[0].y)
	            DrawCircle((x1 + x2) / 2, (y1 + y2) / 2, (sizeX > sizeY ? sizeY : sizeX) / 3, color_me, 1);
        }
    }

    return 0;
}

int GoNext()
{
    status[pos.y][pos.x] = STATUS_AVOID;
    // 右方向
    if (pos.x < COUNT_X - 1 && status[pos.y][pos.x + 1] == STATUS_CLEAR)
        pos.x++;
    // 下方向
	else if (pos.y < COUNT_Y - 1 && status[pos.y + 1][pos.x] == STATUS_CLEAR)
        pos.y++;
    // 左方向
    else if (pos.x > 0 && status[pos.y][pos.x - 1] == STATUS_CLEAR)
        pos.x--;
    // 上方向
    else if (pos.y > 0 && status[pos.y - 1][pos.x] == STATUS_CLEAR)
        pos.y--;
    else
        return -1;

	return 0;
}