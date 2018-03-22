#include<iostream>
#include"DDS.h"
#include"keyboard.h"
#include"graphic.h"

class Player {
public:
	/////////플레이어 관련 변수/////////
	DDS_FILE * dds[8];	//DDS 부분이미지 들이 저장될 배열
	float px;
	float py;
	
	int imgldx;		//출력할 부분 이미지 배열 인덱스

	///////플레이어 관련 함수////////
	void init() {
		int subImgWidth = 184;	//부분 이미지의 가로 길이와 세로 길이
		int subImgHeight = 325;	

		//8개의 부분이미지를 읽어 온다..
		dds[0] = readDDSRect("sample.dds", 0 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[1] = readDDSRect("sample.dds", 1 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[2] = readDDSRect("sample.dds", 2 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[3] = readDDSRect("sample.dds", 3 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[4] = readDDSRect("sample.dds", 4 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[5] = readDDSRect("sample.dds", 5 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[6] = readDDSRect("sample.dds", 6 * subImgWidth, 0, subImgWidth, subImgHeight);
		dds[7] = readDDSRect("sample.dds", 7 * subImgWidth, 0, subImgWidth, subImgHeight);
		
		px = 0;
		py = 0;
		imgldx = 0;
	}

	void update() {
		imgldx++;

		if (imgldx > 7) {
			imgldx = 0;
		}
		Sleep(60);
	}
	
	void render() {
		//imgldx 번째 배열에 있는... DDS 이미지를 출력한다.
		BYTE* data = dds[imgldx]->data;

		for (int y = 0; y < dds[imgldx]->header.dwHeight; y++) {
			for (int x = 0; x < dds[imgldx]->header.dwWidth; x++) {
				BYTE a = data[3];
				BYTE r = data[2];
				BYTE g = data[1];
				BYTE b = data[0];

				setPixel(px + x, py + y, r, g, b);

				data += 4;
			}
		}
	}
};

int main() {
	Player player;

	///////초기화////////
	initGraphic();
	initTimer();
	initKey();
	
	player.init();

	while (true) {
		///////업데이트///////
		clear(0, 0, 0);
		updateKey();
		updateTimer();

		player.update();
		player.render();

		///////렌더링////////
		render();
	
	}
	fgetc(stdin);
	return 0;
}