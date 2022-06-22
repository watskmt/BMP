// dxlib1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
// #include "dxlib1.h"
#include "../../../../../../DxLib_VC/プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include "../dxlib1/resource.h"

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
	if (!InitInstance(hInstance, nCmdShow))
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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXLIB1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DXLIB1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	int Cr[BALL_COUNT] = { 0 };
	int i, j, k=0, count;
	float x[BALL_COUNT] = { 0 };
	float y[BALL_COUNT] = { 0 };
	int Cr1[BALL_COUNT] = { 0 };
	int Cr2[BALL_COUNT] = { 0 };
	int Cr3[BALL_COUNT] = { 0 };
	// 前回位置保存のため
	float xx[BALL_COUNT] = { 0 };
	float yy[BALL_COUNT] = { 0 };
	// 初期速度
	float vx[BALL_COUNT] = { 0 };
	float vy[BALL_COUNT] = { 0 };
	// 初期加速度
	float ax[BALL_COUNT] = { 0 };
	float ay[BALL_COUNT] = { 0 };
	// フラグ管理
	int flag = 0;
	count = 0;
	float g = 0.000003;
	float shot_degree = 30;
	float shot_v0 = 3;
	//色を決める
	Cr[0] = GetColor(0, 0, 255);
	Cr[1] = GetColor(0, 255, 0);
	Cr[2] = GetColor(255, 0, 0);
	Cr[3] = GetColor(0, 255, 255);
	Cr[4] = GetColor(255, 255, 0);
	Cr[5] = GetColor(255, 0, 255);
	Cr[6] = GetColor(255, 255, 255);
	Cr[7] = GetColor(128, 255, 0);
	Cr[8] = GetColor(255, 0, 128);
	Cr[9] = GetColor(255, 128, 255);
	for (i = 0; i < 100000; i++)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) && flag == 0)
		{
			vx[count] = 1.0 + count;
			vy[count] = 1.0 + count;
			count++;
			if (count >= BALL_COUNT)
				flag = 1;
		}
		// 前回の●を黒で上書き
		for (j = 0; j < BALL_COUNT; j++) {
			DrawCircle(xx[j], 600 - yy[j], 10, 0, TRUE);
			// 移動後の●を描画
			DrawCircle(x[j], 600 - y[j], 10, Cr[j], TRUE);
			// 位置を保存
			xx[j] = x[j];
			yy[j] = y[j];
			// 待つ
			Sleep(1);
			if (y[j] > 0)
				ay[j] -= g;			// 加速度を速度に加算
			vx[j] += ax[j];
			vy[j] += ay[j];
			// 速度を位置に加算（１回分の移動）
			x[j] += vx[j];
			y[j] += vy[j];
			// 下の跳ね返り（ｙが0より小さくなるとYの速度が反転するのと、反発係数で絶対値が小さくなる）
			if (y[j] < 0)
			{
				vy[j] = -vy[j] * 0.9;
				y[j] = 0;
			}
			// 上の跳ね返り
			if (y[j] > 600)
			{
				vy[j] = -vy[j] * 0.9;
				y[j] = 600 - 1;
			}
			// 左の跳ね返り
			if (x[j] < 0)
			{
				vx[j] = -vx[j] * 0.9;
				x[j] = 0;
			}
			// 右の跳ね返り
			if (x[j] > 800)
			{
				vx[j] = -vx[j] * 0.9;
				x[j] = 800 - 1;
			}
		}
		// 画面表示待ち（OSに処理を返す）
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}
		//ESCAPEを入力するとループを抜ける	
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;
	}
	// 読み込んだ画像のグラフィックハンドルを削除
	WaitKey();        // 結果を見るためにキー待ち(『WaitKey』を使用)
	DxLib_End();        // ＤＸライブラリ使用の終了処理
	return 0;        // ソフトの終了
}
