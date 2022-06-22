// dxlib3.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "dxlib3.h"

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
    LoadStringW(hInstance, IDC_DXLIB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DXLIB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXLIB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DXLIB3);
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
#include "DxLib.h"
#define BALL_COUNT 10
#define PI    3.1415926535897932384626433832795f

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int GHandle;
	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	int Cr[BALL_COUNT];
	int i = 0;
	int j = 0;

	// 初期位置
	float x[BALL_COUNT];
	float y[BALL_COUNT];
	// 前回位置保存のため
	float xx[BALL_COUNT];
	float yy[BALL_COUNT];
	// 初期速度
	float vx[BALL_COUNT];
	float vy[BALL_COUNT];
	// 初期加速度
	float ax[BALL_COUNT];
	float ay[BALL_COUNT];

	for (i = 0; i < 10; i++) {
		Cr[i] = 0;
		x[i] = 0;
		y[i] = 0;
		xx[i] = 0;
		yy[i] = 0;
		vx[i] = 0;
		vy[i] = 0;
		ax[i] = 0;
		ay[i] = 0;
	}
	float shot_degree = 30;
	float shot_v0 = 3;
	Cr[0] = GetColor(255, 255, 255);
	// 前回の●を黒で上書き
	DrawCircle(xx[0], 600 - yy[0], 10, 0, TRUE);
	// 移動後の●を描画
	DrawCircle(x[0], 600 - y[0], 10, Cr[0], TRUE);

	for (i = 0; i < 3000; i++) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			vx[j] = 1.0;
			vy[j] = 1.0;
			Cr[j] = GetColor(255, 255, 255);
			if(++j>=10)break;

		}
		// 前回の●を黒で上書き
		DrawCircle(xx[j], 600 - yy[j], 10, 0, TRUE);
		// 移動後の●を描画
		DrawCircle(x[j], 600 - y[j], 10, Cr[j], TRUE);
		// 位置を保存
		xx[j] = x[j];
		yy[j] = y[j];
		// 待つ
		Sleep(1);
		// 加速度を速度に加算
		vx[j] += ax[j];
		vy[j] += ay[j];
		// 速度を位置に加算（１回分の移動）
		x[j] += vx[j];
		y[j] += vy[j];
		// 下の跳ね返り（ｙが0より小さくなるとYの速度が反転するのと、反発係数で絶対値が小さくなる）
		/*if (y < 0)
		{
			vy[0] = -vy[0] * 0.9;
			y[0] = 0;
		}*/
		// 上の跳ね返り
		if (y[j] > 600)
		{
			vy[j] = -vy[j] * 0.9;
			y[j] = 600 - 1;
		}
		// 左の跳ね返り
		/*if (x[0] < 0)
		{
			vx[0] = -vx[0] * 0.9;
			x[0] = 0;
		}*/
		// 右の跳ね返り
		if (x[j] > 800)
		{
			vx[j] = -vx[j] * 0.9;
			x[j] = 800 - 1;
			break;
		}
		// 画面表示待ち（OSに処理を返す）
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;
	}
	// 読み込んだ画像のグラフィックハンドルを削除
	WaitKey();        // 結果を見るためにキー待ち(『WaitKey』を使用)
	DxLib_End();        // ＤＸライブラリ使用の終了処理
	return 0;        // ソフトの終了
}