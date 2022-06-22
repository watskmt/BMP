#include "DxLib.h"

typedef struct _BITMAPFILEHEADER {
	unsigned short int bfType;
	unsigned int bfSize;
	unsigned short int bfReserved1;
	unsigned short int bfReserved2;
	unsigned int bfOffBits;
}_BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER {
	unsigned int bcSize;
	unsigned int bcWidth;
	int bcHeight;
	unsigned short int bcPlanes;
	unsigned short int bcBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPixPerMeter;
	unsigned int biYPixPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
}_BITMAPINFOHEADER;

typedef struct _BITMAP {
	_BITMAPFILEHEADER header;
	_BITMAPINFOHEADER info;
	char* pixData;
}_BITMAP;

int ReadBmpFile(char* filename, _BITMAP* bmp)
{
	int i;
	FILE* fp;
	unsigned char header[14];
	unsigned char info[40];

	fopen_s(&fp, filename, "rb");
	fread(header, 1, 14, fp);
	fread(info, 1, 40, fp);
	bmp->header.bfType = *header + *(header + 1) * 0x100;
	bmp->header.bfSize = *(header + 2)
		+ *(header + 3) * 0x100
		+ *(header + 4) * 0x10000
		+ *(header + 5) * 0x1000000;
	bmp->header.bfOffBits = *(header + 10)
		+ *(header + 11) * 0x100
		+ *(header + 12) * 0x10000
		+ *(header + 13) * 0x1000000;

	return 0;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int x;
	int color = 0;

	_BITMAP bmp1;

	ReadBmpFile((char*)"c:\\temp\\red.bmp", &bmp1);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);


	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}