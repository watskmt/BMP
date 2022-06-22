// dxlib1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "dxlib1.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DXLIB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DXLIB1));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXLIB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DXLIB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


#include "DxLib.h"
#include <math.h>

#define PI    3.1415926535897932384626433832795f

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


#define BALL_COUNT 100
#define SHOT_MAX_ANGLE 90
#define SHOT_MIN_ANGLE 0
#define SHOT_CHANGE_ANGLE_DELTA 0.1
#define SHOT_MAX_SPEED 3
#define SHOT_MIN_SPEED 0.5
#define SHOT_CHANGE_SPEED_DELTA 0.005



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int GHandle;
	int GHandle1;

	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	GHandle = LoadGraph((TCHAR *)"d:\\download\\space.jpg");
	GHandle1 = LoadGraph((TCHAR *)"d:\\download\\apple.png");

	// SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	int C[7];
	int Cr[BALL_COUNT] = {0};
	int i;
	// 初期位置
	float x[BALL_COUNT] = {0};
	float y[BALL_COUNT] = {0};
	// 前回位置保存のため
	float xx[BALL_COUNT] = {0};
	float yy[BALL_COUNT] = {0};
	// 初期速度
	float vx[BALL_COUNT] = {0};
	float vy[BALL_COUNT] = {0};
	// 初期加速度
	float ax[BALL_COUNT] = {0};
	float ay[BALL_COUNT] = {0};
	// ボールが生きているかどうかのフラグ
	int isalive[BALL_COUNT] = {0};
	
	float g = 0.000003;
	float shot_degree = 45;
	float shot_v0 = 1;
	int shot_count = 0;
	int pressed_shot=0;

	C[0] = GetColor(0, 0, 255);
	C[1] = GetColor(0, 255, 0);
	C[2] = GetColor(255, 0, 0);
	C[3] = GetColor(0, 255, 255);
	C[4] = GetColor(255, 255, 0);
	C[5] = GetColor(255, 0, 255);
	C[6] = GetColor(255, 255, 255);

	int hole_pos_x = 300;
	int hole_pos_y = 150;
	int hole_radius = 20;
	
	Cr[0] = C[0];
	isalive[0] = 1;
	
	while(1)
	{
		if (CheckHitKey(KEY_INPUT_UP))
			shot_degree = (shot_degree + SHOT_CHANGE_ANGLE_DELTA) > SHOT_MAX_ANGLE ? SHOT_MAX_ANGLE : shot_degree + SHOT_CHANGE_ANGLE_DELTA;
		else if (CheckHitKey(KEY_INPUT_DOWN))
			shot_degree = (shot_degree - SHOT_CHANGE_ANGLE_DELTA) < SHOT_MIN_ANGLE ? SHOT_MIN_ANGLE : shot_degree - SHOT_CHANGE_ANGLE_DELTA;
		if (CheckHitKey(KEY_INPUT_RIGHT))
			shot_v0 = (shot_v0 + SHOT_CHANGE_SPEED_DELTA) > SHOT_MAX_SPEED ? SHOT_MAX_SPEED : shot_v0 + SHOT_CHANGE_SPEED_DELTA;
		if (CheckHitKey(KEY_INPUT_LEFT))
			shot_v0 = (shot_v0 - SHOT_CHANGE_SPEED_DELTA) < SHOT_MIN_SPEED ? SHOT_MIN_SPEED : shot_v0 - SHOT_CHANGE_SPEED_DELTA;

		clsDx();
		printfDx((TCHAR *)"shot_degree = %f", shot_degree);


		
		if (!pressed_shot)
		{
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				pressed_shot = 1;
				vx[shot_count] = shot_v0 * cos(shot_degree / 180.0 * PI);
				vy[shot_count] = shot_v0 * sin(shot_degree / 180.0 * PI);
				if (++shot_count >= BALL_COUNT)break;
				Cr[shot_count] = C[shot_count % 7];
				isalive[shot_count] = 1;
			}
		}
		else
		{
			if (!CheckHitKey(KEY_INPUT_SPACE))
				pressed_shot = 0;
		}


		
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;
		ClearDrawScreen();
		// LoadGraphScreen(0, 0, "space.jpg", TRUE);
		DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GHandle, FALSE);
		DrawLine(0, WINDOW_HEIGHT - 1, shot_v0 * cos(shot_degree / 180.0 * PI) * 100, WINDOW_HEIGHT - shot_v0 * sin(shot_degree / 180.0 * PI) * 100, GetColor(255,255,255));
		DrawCircle(hole_pos_x, hole_pos_y, hole_radius, GetColor(255, 255, 255), true);
		
		for (int i = BALL_COUNT-1; i >=0; i--)
		{
			// 移動後の●を描画
			if (isalive[i])
			{
				if (((x[i] - hole_pos_x)*(x[i] - hole_pos_x) + (y[i] - (WINDOW_HEIGHT - hole_pos_y))*(y[i] - (WINDOW_HEIGHT - hole_pos_y))) < hole_radius*hole_radius)
				{
					isalive[i] = 0;
					hole_pos_x = rand() % (WINDOW_WIDTH - hole_radius);
					hole_pos_y = rand() % (WINDOW_HEIGHT - hole_radius);
				}

 				// DrawCircle(x[i], WINDOW_HEIGHT - y[i], 10, Cr[i], TRUE);
				DrawExtendGraph(x[i] - 30, WINDOW_HEIGHT - y[i] - 30, x[i] + 30, WINDOW_HEIGHT - y[i] + 30, GHandle1, TRUE);
				// 位置を保存
				xx[i] = x[i];
				yy[i] = y[i];
				// 加速度を速度に加算
				vx[i] += ax[i];
				vy[i] += ay[i];
				// 速度を位置に加算（１回分の移動）
				x[i] += vx[i];
				y[i] += vy[i];

				if (y[i] > 0)
					ay[i] -= g;
				// 下の跳ね返り（ｙが0より小さくなるとYの速度が反転するのと、反発係数で絶対値が小さくなる）
				if (y[i] < 0)
				{
					vy[i] = -vy[i] * 0.9;
					y[i] = 0;
				}
				// 上の跳ね返り
				if (y[i] > WINDOW_HEIGHT)
				{
					vy[i] = -vy[i] * 0.9;
					y[i] = WINDOW_HEIGHT - 1;
				}
				// 左の跳ね返り
				if (x[i] < 0)
				{
					vx[i] = -vx[i] * 0.9;
					x[i] = 0;
				}
				// 右の跳ね返り
				if (x[i] > WINDOW_WIDTH)
				{
					vx[i] = -vx[i] * 0.9;
					x[i] = WINDOW_WIDTH - 1;
				}
			}
		}

		// 待つ
		Sleep(1);
		// 画面表示待ち（OSに処理を返す）
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}
	}

	// 読み込んだ画像のグラフィックハンドルを削除

	WaitKey();        // 結果を見るためにキー待ち(『WaitKey』を使用)
	DeleteGraph(GHandle);
	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}