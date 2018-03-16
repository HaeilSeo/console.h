#include<stdio.h>
#include<windows.h>
#include"DDS.h"
#include"graphic.h"
#define EX01 0
#define EX02 0
#define EX03 1
#define EX04 0

#if	EX01
int main() {
	unsigned int col = 0x01020304;
	unsigned char A = (col >> 24) & 0xff;
	unsigned char R = (col >> 16) & 0xff;
	unsigned char G = (col >> 8) & 0xff;
	unsigned char B = col & 0xff;
	printf("A�� :0x%x\n", A);
	printf("R�� :0x%x\n", R);
	printf("G�� :0x%x\n", G);
	printf("B�� :0x%x\n", B);

	system("pause");
	return 0;
}
#endif

#if EX02
int main() {
	unsigned char A = 0x01;
	unsigned char R = 0x02;
	unsigned char G = 0x03; 
	unsigned char B = 0x04;
	unsigned int col = (A << 24) | (R << 16) | (G << 8) | B;
	printf("B���� 16������ ��� 0x%x\n");
	printf("32 ��Ʈ �ȼ�(col) 16������ ��� 0x%x \n");


}
#endif

#if EX03

void drawDDSAlphaBlending(int sx, int sy, DDS_FILE* DDS) {
	unsigned char* data = DDS->data;

	for (int y = 0; y < DDS->header.dwHeight; y++) {
		for (int x = 0; x < DDS->header.dwWidth; x++) {

			////////�̹��� RGBA - ����� �ȼ�/////////////
			unsigned char Cb = data[x + 4 + 0];
			unsigned char Cg = data[x + 4 + 1];
			unsigned char Cr = data[x + 4 + 2];
			unsigned char A = data[x + 4 + 3];

			////////����� RGB - ��� �ȼ�////////////////
			unsigned int BGcol = getPixel(sx + x, sy + y);

			unsigned char Br = (BGcol >> 16) & 0xff;
			unsigned char Bg = (BGcol >> 8) & 0xff;
			unsigned char Bb = (BGcol >> 0) & 0xff;

			/////////���ĺ��� ����ϱ�////////////////
			Cb = (unsigned char)((A*Cb + (255 - A)*Br) / 255.0f);
			Cg = (unsigned char)((A*Cg + (255 - A)*Bg) / 255.0f);
			Cr = (unsigned char)((A*Cr + (255 - A)*Br) / 255.0f);

			setPixel(sx + x, sy + y, Cr, Cg, Cb);
		}
		data += DDS->header.dwPitchOrLinearSize;
	}
}


int main() {
	DDS_FILE* DDS = readDDS("�����.dds");
	DDS_FILE* DDSBG = readDDS("bg.dds");


	float x = 100, y = 100;


	initGraphic();

	while (true) {
		clear(0, 0, 0);

		drawDDSAlphaBlending(0, 0, DDSBG);
		drawDDSAlphaBlending(x, y, DDS);


		render();
	}
	return 0;
}
#endif