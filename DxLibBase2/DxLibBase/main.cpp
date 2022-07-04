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
	unsigned char* pixData;
}_BITMAP;

int ReadBmpFile(char* filename, _BITMAP* bmp)
{
	int i;
	FILE* fp;
	unsigned char header[14];
	unsigned char info[40];
	int infotop = 0x0e;

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

	bmp->info.bcSize = *(info + 0x0e - infotop)
		+ *(info + 0x0f - infotop) * 0x100
		+ *(info + 0x10 - infotop) * 0x10000
		+ *(info + 0x11 - infotop) * 0x1000000;

	bmp->info.bcWidth = *(info + 0x12 - infotop)
		+ *(info + 0x13 - infotop) * 0x100
		+ *(info + 0x14 - infotop) * 0x10000
		+ *(info + 0x15 - infotop) * 0x1000000;

	bmp->info.bcHeight = *(info + 0x16 - infotop)
		+ *(info + 0x17 - infotop) * 0x100
		+ *(info + 0x18 - infotop) * 0x10000
		+ *(info + 0x19 - infotop) * 0x1000000;

	bmp->info.bcPlanes = *(info + 0x1a - infotop)
		+ *(info + 0x1b - infotop) * 0x100;

	bmp->info.bcBitCount = *(info + 0x1c - infotop)
		+ *(info + 0x1d - infotop) * 0x100;

	bmp->info.biCompression = *(info + 0x1e - infotop)
		+ *(info + 0x1f - infotop) * 0x100
		+ *(info + 0x20 - infotop) * 0x10000
		+ *(info + 0x21 - infotop) * 0x1000000;
	bmp->info.biSizeImage = *(info + 0x22 - infotop)
		+ *(info + 0x23 - infotop) * 0x100
		+ *(info + 0x24 - infotop) * 0x10000
		+ *(info + 0x25 - infotop) * 0x1000000;
	bmp->info.biXPixPerMeter = *(info + 0x26 - infotop)
		+ *(info + 0x27 - infotop) * 0x100
		+ *(info + 0x28 - infotop) * 0x10000
		+ *(info + 0x29 - infotop) * 0x1000000;
	bmp->info.biYPixPerMeter = *(info + 0x2a - infotop)
		+ *(info + 0x2b - infotop) * 0x100
		+ *(info + 0x2c - infotop) * 0x10000
		+ *(info + 0x2d - infotop) * 0x1000000;
	bmp->info.biClrUsed = *(info + 0x2e - infotop)
		+ *(info + 0x2f - infotop) * 0x100
		+ *(info + 0x30 - infotop) * 0x10000
		+ *(info + 0x31 - infotop) * 0x1000000;
	bmp->info.biClrImportant = *(info + 0x32 - infotop)
		+ *(info + 0x33 - infotop) * 0x100
		+ *(info + 0x34 - infotop) * 0x10000
		+ *(info + 0x35 - infotop) * 0x1000000;

	bmp->pixData = (unsigned char*)malloc(bmp->header.bfSize - sizeof(_BITMAPFILEHEADER) - sizeof(_BITMAPINFOHEADER));
	fread(bmp->pixData, 1, bmp->header.bfSize - sizeof(_BITMAPFILEHEADER) - sizeof(_BITMAPINFOHEADER), fp);

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int i;
	int x, y;
	int color = 0;

	_BITMAP bmp1;

	char filename[32] = "c:\\temp\\test1.bmp";

	ReadBmpFile(filename, &bmp1);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	ChangeWindowMode(TRUE);

	int width = bmp1.info.bcWidth;
	int height = bmp1.info.bcHeight;

	SetGraphMode(width, height, 32);
	SetMouseDispFlag(TRUE);

	int mouseX, mouseY;
	int count = 0;
	unsigned char** r = (unsigned char**)calloc(sizeof(unsigned char*), bmp1.info.bcHeight);
	unsigned char** g = (unsigned char**)calloc(sizeof(unsigned char*), bmp1.info.bcHeight);
	unsigned char** b = (unsigned char**)calloc(sizeof(unsigned char*), bmp1.info.bcHeight);
	for (i = 0; i < bmp1.info.bcHeight; i++)
	{
		r[i] = (unsigned char*)calloc(sizeof(unsigned char), bmp1.info.bcWidth);
		g[i] = (unsigned char*)calloc(sizeof(unsigned char), bmp1.info.bcWidth);
		b[i] = (unsigned char*)calloc(sizeof(unsigned char), bmp1.info.bcWidth);
	}


	for (int y = 0; y < bmp1.info.bcHeight; y++)
	{
		for (int x = 0; x < bmp1.info.bcWidth; x++)
		{
			//color = GetColor(*(bmp1.pixData + count++)
			//	, *(bmp1.pixData + count++)
			//	, *(bmp1.pixData + count++));

			//DrawPixel(x, height -1 - y, color);
			b[height - 1 - y][x] = *(bmp1.pixData + count++);
			g[height - 1 - y][x] = *(bmp1.pixData + count++);
			r[height - 1 - y][x] = *(bmp1.pixData + count++);

		}
		while (count % 4)
			count++;
	}
	for (int y = 0; y < bmp1.info.bcHeight; y++)
	{
		for (int x = 0; x < bmp1.info.bcWidth; x++)
		{
			DrawPixel(x, y, GetColor(r[y][x], g[y][x], b[y][x]));
		}
	}
		// キーが押されるまでループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// マウスの位置を取得
		GetMousePoint(&mouseX, &mouseY);
		if (GetMouseInput() == MOUSE_INPUT_LEFT)
		{
			DrawPixel(mouseX, mouseY, GetColor(0, 0, 0));
		}
	}
	WaitKey();				// 

	DxLib_End();				// 

	for (i = 0; i < bmp1.info.bcHeight; i++)
	{
		free(r[i]); free(g[i]); free(b[i]);
	}
	free(r); free(g); free(b);
	return 0;				//  
}