#include<iostream>
#include"DDS.h"
#include"keyboard.h"
#include"graphic.h"

class Player {
public:
	/////////�÷��̾� ���� ����/////////
	DDS_FILE* dds[8];	//DDS �κ��̹��� ���� ����� �迭
	float px;
	float py;
	float Speed;
	int imgldx;		//����� �κ� �̹��� �迭 �ε���

	///////�÷��̾� ���� �Լ�////////
	void init() {
		int subImgWidth = 184;	//�κ� �̹����� ���� ���̿� ���� ����
		int subImgHeight = 325;	

		//8���� �κ��̹����� �о� �´�..
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
		Speed = 100;
	}

	void update() {
		Sleep(80);
		float dt = getDeltaTime()*Speed;
		if (GetKey(VK_UP) == true) {
			py -= dt;					//ĳ���Ͱ� ���� �����϶�, py��ǥ�� �����ϰ�
			imgldx++;					//���� ������� �Ѿ�ϴ�.
		}
		if (GetKey(VK_DOWN) == true) {
			py += dt;					//ĳ���Ͱ� �Ʒ��� �����϶�, py��ǥ�� �����ϰ�
			imgldx--;					//����������� ���ư��ϴ�.

		}
		if (GetKey(VK_RIGHT) == true) {	
			px += dt;					//ĳ���Ͱ� ���������� �����϶�, px��ǥ�� �����ϰ�
			imgldx++;					//���� ������� �Ѿ�ϴ�.
		}
		if (GetKey(VK_LEFT) == true) {	
			px -= dt;					//ĳ���Ͱ� �������� �����϶�, px��ǥ�� �����ϰ�
			imgldx--;					//���� ������� ���ư��ϴ�.
		}
		
		if (imgldx > 7) {				//�ִ� �迭������ ��ȣ�ʰ��� imgldx�� �þ����,
			imgldx = 0;					//imgldx�� 0���� �ʱ�ȭ�Ǿ �ִϸ��̼��� ó�������� ���ư��ϴ�.
		}
		else if (imgldx < 0) {			//�ּ� �迭������ ��ȣ�̴޷� imgldx�� �پ�������,
			imgldx = 7;					//imgldx�� 7���� �ʱ�ȭ�Ǿ �ִϸ��̼��� ������������ ���ư��ϴ�.
		}
	}
	
	void render() {
		//imgldx ��° �迭�� �ִ�... DDS �̹����� ����Ѵ�.
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

	///////�ʱ�ȭ////////
	initGraphic();
	initTimer();
	initKey();
	
	player.init();

	while (true) {
		///////������Ʈ///////
		clear(0, 0, 0);
		updateKey();
		updateTimer();

		player.update();
		player.render();

		///////������////////
		render();
	}
	
	return 0;
}