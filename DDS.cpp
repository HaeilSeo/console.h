#include<stdio.h>
#include"graphic.h"
#include"DDS.h"

DDS_FILE* readDDS(const char* filename) {
	FILE* fp = NULL;
	DDS_FILE* DDS = NULL;

	errno_t errnno;
	int size;

	if ((errnno = fopen_s(&fp, filename, "rb")) != 0) {
		fprintf(stderr, "파일 열기 실패: file %s errno %d\n", filename, errnno);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);


	if ((DDS = (DDS_FILE*)new BYTE[size]) == NULL) {
		fprintf(stderr, "메모리를 할당 받지 못함\n");
		fclose(fp);			
		return NULL;
	}
	fread(DDS, size, 1, fp);

	fclose(fp);

	return DDS;
}

void drawDDSGray(int sx, int sy, DDS_FILE* DDS) {
	unsigned char* data = DDS->data;


	for (int y = 0; y < DDS->header.dwHeight; y++) {

		for (int x = 0; x < DDS->header.dwWidth; x++) {

			unsigned char b = data[x + 4 + 0];
			unsigned char g = data[x + 4 + 1];
			unsigned char r = data[x + 4 + 2];
			unsigned char a = data[x + 4 + 3];

			unsigned char gray = (unsigned char)((r + g + b) / 3); //rgb의 평균을 구한다. - 흑백 명도값


			setPixel(sx + x, sy + y, gray, gray, gray);

		}
		data += DDS->header.dwPitchOrLinearSize;

	}


}
