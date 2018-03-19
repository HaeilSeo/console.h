#include<stdio.h>
#include<windows.h>
#include"DDS.h"
#include"graphic.h"


void drawDDSAlphaBlending(int sx, int sy, DDS_FILE* DDS);
int main() {
	DDS_FILE* DDS = readDDS("��.dds");
	DDS_FILE* DDS_enemy1 = readDDS("�Ǵ�1.dds");
	DDS_FILE* DDS_enemy2 = readDDS("�Ǵ�2.dds");
	DDS_FILE* DDS_enemy3 = readDDS("�Ǵ�3.dds");
	DDS_FILE* DDSBG = readDDS("���.dds");
	float x = 300, y = 250;
	initGraphic();

	while (true) {
		clear(0, 0, 0);
		drawDDSAlphaBlending(0, 0, DDSBG);
		drawDDSAlphaBlending(x, y, DDS);
		drawDDSAlphaBlending(x-300, -50, DDS_enemy1);
		drawDDSAlphaBlending(x+50, 50, DDS_enemy2);
		drawDDSAlphaBlending(x + 100, 50, DDS_enemy3);

		render();
	}
	return 0;
}
void drawDDSAlphaBlending(int sx, int sy, DDS_FILE* DDS) {
	unsigned char* data = DDS->data;

	for (int y = 0; y < DDS->header.dwHeight; y++) {
		for (int x = 0; x < DDS->header.dwWidth; x++) {

			////////�̹��� RGBA - ����� �ȼ�/////////////
			unsigned char Cb = data[x * 4 + 0];
			unsigned char Cg = data[x * 4 + 1];
			unsigned char Cr = data[x * 4 + 2];
			unsigned char A = data[x * 4 + 3];

			////////����� RGB - ��� �ȼ�////////////////
			unsigned int BGCol = getPixel(sx + x, sy + y);

			unsigned char Br = (BGCol >> 16) & 0xff;
			unsigned char Bg = (BGCol >> 8) & 0xff;
			unsigned char Bb = (BGCol >> 0) & 0xff;

			/////////���ĺ��� ����ϱ�////////////////
			Cb = (unsigned char)((A*Cb + (255 - A)*Bb) / 255.0f);
			Cg = (unsigned char)((A*Cg + (255 - A)*Bg) / 255.0f);
			Cr = (unsigned char)((A*Cr + (255 - A)*Br) / 255.0f);

			setPixel(sx + x, sy + y, Cr, Cg, Cb);
		}
		data += DDS->header.dwPitchOrLinearSize;
	}
}
