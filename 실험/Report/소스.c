#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4) 
// ��Ʈ�� ���� �԰ݿ���, ���ι��� ������ ũ��� 4�� ���(����Ʈ����)�� �Ѵ�.
// ��?? -> ������ ã�Ƽ� ����Ʈ�� ÷��
#define BYTE unsigned char
#define WEIGHT_SIZE 3

FILE *file;// ���� ������ ����
int rwsize, rwsize2;// ���� ���� �� ����Ʈ ��
BYTE *lpImg;// �Է� �����Ͱ� ����Ǵ� �޸� �ּҸ� �����ϴ� ������
BYTE *lpOutImg;// ��� �����Ͱ� ����Ǵ� �޸� �ּҸ� �����ϴ� ������
RGBQUAD *pRGB;// Lookup Table
RGBQUAD qRGB;
BITMAPFILEHEADER hf;// ��Ʈ�� ���� �ش�
BITMAPINFOHEADER hinfo;// ��Ʈ�� ���� ���
int weight_x[9] = { 1,0,-1,2,0,-2,1,0,-1 };
int weight_y[9] = { 1,2,1,0,0,0,-1,-2,-1 };

int cal_place(int i, int j, int weight) {
	int x = weight % WEIGHT_SIZE - 1;
	int y = weight / WEIGHT_SIZE - 1;
	return (i + y) * hinfo.biWidth + j + x;
}


int box_mul_x(int i, int j);
int box_mul_y(int i, int j);
void bitof24_to_8bit_gray(void);
void egdt(void); // ����!!
// ���α׷� ���� �Լ��� ���� ����

int main()
{
	bitof24_to_8bit_gray();
	// ������ ������� �ٲ��ִ� �Լ�
	egdt();
	// ���� bitof24_to_8bit_grapy���� ������� �ٲ� ������ �޾ƿ� edge detecting �ϴ� �Լ�.

	return 0;
}


int box_mul_x(int i, int j) {
	int result;
	if (i == 0) {
		if (j == 0)
			result = weight_x[5] * lpImg[cal_place(i, j, 5)] + weight_x[8] * lpImg[cal_place(i, j, 8)];
		else if (j == hinfo.biWidth - 1)
			result = weight_x[3] * lpImg[cal_place(i, j, 3)] + weight_x[6] * lpImg[cal_place(i, j, 6)];
		else
			result = weight_x[3] * lpImg[cal_place(i, j, 3)] + weight_x[6] * lpImg[cal_place(i, j, 6)] + weight_x[5] * lpImg[cal_place(i, j, 5)] + weight_x[8] * lpImg[cal_place(i, j, 8)];
	}

	else if (i == hinfo.biHeight - 1) {
		if (j == 0)
			result = weight_x[2] * lpImg[cal_place(i, j, 2)] + weight_x[5] * lpImg[cal_place(i, j, 5)];
		else if (j == hinfo.biWidth - 1)
			result = weight_x[0] * lpImg[cal_place(i, j, 0)] + weight_x[3] * lpImg[cal_place(i, j, 3)];
		else
			result = weight_x[0] * lpImg[cal_place(i, j, 0)] + weight_x[3] * lpImg[cal_place(i, j, 3)] + weight_x[2] * lpImg[cal_place(i, j, 2)] + weight_x[5] * lpImg[cal_place(i, j, 5)];
	}
	else {
		if (j == 0)
			result = weight_x[2] * lpImg[cal_place(i, j, 2)] + weight_x[5] * lpImg[cal_place(i, j, 5)] + weight_x[8] * lpImg[cal_place(i, j, 8)];
		// ������� �ۼ�
		else if (j == hinfo.biWidth - 1)
			result = weight_x[0] * lpImg[cal_place(i, j, 0)] + weight_x[3] * lpImg[(cal_place(i, j, 3))] + weight_x[6] * lpImg[(cal_place(i, j, 6))];
		else
			result = weight_x[0] * lpImg[cal_place(i, j, 0)] + weight_x[3] * lpImg[cal_place(i, j, 3)] + weight_x[6] * lpImg[cal_place(i, j, 6)] + weight_x[2] * lpImg[cal_place(i, j, 2)] + weight_x[5] * lpImg[cal_place(i, j, 5)] + weight_x[8] * lpImg[cal_place(i, j, 8)];
	}
	return result;
}

int box_mul_y(int i, int j) {
	int result;
	if (i == 0) {
		if (j == 0)
			result = weight_y[7] * lpImg[cal_place(i, j, 7)] + weight_y[8] * lpImg[cal_place(i, j, 8)];
		else if (j == hinfo.biWidth - 1)
			result = weight_y[7] * lpImg[cal_place(i, j, 7)] + weight_y[6] * lpImg[cal_place(i, j, 6)];
		else
			result = weight_y[6] * lpImg[cal_place(i, j, 6)] + weight_y[7] * lpImg[cal_place(i, j, 7)] + weight_y[8] * lpImg[cal_place(i, j, 8)];
	}

	else if (i == hinfo.biHeight - 1) {
		if (j == 0)
			result = weight_y[2] * lpImg[cal_place(i, j, 2)] + weight_y[1] * lpImg[cal_place(i, j, 1)];
		else if (j == hinfo.biWidth - 1)
			result = weight_y[0] * lpImg[cal_place(i, j, 0)] + weight_y[1] * lpImg[cal_place(i, j, 1)];
		else
			result = weight_y[0] * lpImg[cal_place(i, j, 0)] + weight_y[1] * lpImg[cal_place(i, j, 1)] + weight_y[2] * lpImg[cal_place(i, j, 2)];
	}
	else {
		if (j == 0)
			result = weight_y[2] * lpImg[cal_place(i, j, 2)] + weight_y[1] * lpImg[cal_place(i, j, 1)] + weight_y[8] * lpImg[cal_place(i, j, 8)] + weight_y[7] * lpImg[cal_place(i, j, 7)];
		else if (j == hinfo.biWidth - 1)
			result = weight_y[0] * lpImg[cal_place(i, j, 0)] + weight_y[1] * lpImg[cal_place(i, j, 1)] + weight_y[6] * lpImg[cal_place(i, j, 6)] + weight_y[7] * lpImg[cal_place(i, j, 7)];
		else
			result = weight_y[0] * lpImg[cal_place(i, j, 0)] + weight_y[1] * lpImg[cal_place(i, j, 1)] + weight_y[2] * lpImg[cal_place(i, j, 2)] + weight_y[6] * lpImg[cal_place(i, j, 6)] + weight_y[7] * lpImg[cal_place(i, j, 7)] + weight_y[8] * lpImg[cal_place(i, j, 8)];
	}
	return result;
}
void egdt(void)
{
	int x_kernel, y_kernel, i, j, t;
	double *edge, edge_MAX = 0, edge_MIN = 9999;

	BITMAPFILEHEADER ohf; // ��� ������ ���� ��Ʈ�� ���� ���
	BITMAPINFOHEADER ohinfo; // ��� ������ ���� ��Ʈ�� ���� ���� ���

	printf("RUN egdt()\n\n");
	file = fopen("BW.bmp", "rb");
	if (file == NULL) {
		printf("Error At File open!!!\n");
		exit(1);
	}

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); // ������ ���� ������ BITMAPFILEHEADER��ŭ�� hf�� ����

	if (hf.bfType != 0x4D42) // 0X4D42 == BM(�ƽ�Ű �ڵ�), ��Ʈ�������� �� ó�� ������ BM�̴�. ���� ù �κ��� �а�, �� �κ��� �м��ؼ� ��Ʈ���� �ƴϸ�...
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); // ������ ���� ������ BITMAPINFOHEADER��ŭ�� hinfo�� ����

	ohf = hf;
	// ���� ����� ���� ��� ����� ����
	ohinfo = hinfo;
	// ���� ���� ����� ���� ��� ���� ����� ����

	t = (int)pow(2, hinfo.biBitCount);
	// bitcount�� ���� �ȷ�Ʈ�� ������ �˾Ƴ���.
	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * t);
	//pRGB�� �ȷ�Ʈ�� ũ�⸸ŭ �迭�� ����
	fread(pRGB, sizeof(RGBQUAD), t, file);
	// �ȷ�Ʈ�� �о�´�.

	ohf.bfOffBits = sizeof(ohf) + sizeof(ohinfo) + sizeof(pRGB)*t;
	// ������ offset�� �״�� �ᵵ ����.

	fseek(file, hf.bfOffBits, SEEK_SET);
	// Ŀ���� ������ ��Ұ� �ִ� �κб��� �̵��Ѵ�.
	lpImg = (BYTE*)malloc(hinfo.biWidth*hinfo.biHeight);
	// �����͸� �о�� �ڷ����� ������ ũ�⸸ŭ �����Ҵ�.
	// 8bit palette�� ���� ���, �� �ȼ��� 1byte�� �����Ͱ� �Ҵ�Ǹ� pixel�� ������ �� byte ���� ������ ũ���̴�.
	fread(lpImg, sizeof(char), hinfo.biWidth*hinfo.biHeight, file);
	// �����͸� �о�´�.
	fclose(file);


	lpOutImg = (BYTE*)malloc(ohinfo.biWidth*ohinfo.biHeight);
	// ����� �����͸� ���� �Ҵ�
	edge = (float*)malloc(8 * ohinfo.biWidth*ohinfo.biHeight);
	// sqrt�� �������� double�̴�. ���� ĳ���� �ʿ�

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{

			x_kernel = box_mul_x(i, j);
			// x��ǥ ����ġ�� ���. �� �����ڸ��� ���� ��� Ư�� �κ��� ��꿡�� ������ ��
			y_kernel = box_mul_y(i, j);
			// y��ǥ ����ġ�� ���. ���������� �����ڸ��� ���� ��� Ư�� �κ��� ��꿡�� ����.
			if (edge_MAX < (edge[i*hinfo.biWidth + j] = (float)sqrt(pow(x_kernel, 2) + pow(y_kernel, 2))))
				// ���� ����� ���� ���� �ִ밪���� ������
				edge_MAX = edge[i*hinfo.biWidth + j];
				// �ٲ��ش�
			if (edge_MIN > (edge[i*hinfo.biWidth + j] = (float)sqrt(pow(x_kernel, 2) + pow(y_kernel, 2))))
				// ���� ����� ���� ���� �ּҰ����� ������
				edge_MIN = edge[i*hinfo.biWidth + j];
				// �ٲ��ش�.
		}
	}
	for (i = 0; i < hinfo.biHeight; i++)
		for (j = 0; j < hinfo.biWidth; j++)
			lpOutImg[i*hinfo.biWidth + j] = (BYTE)(255 / (edge_MAX - edge_MIN) * (edge[i*hinfo.biWidth + j] - edge_MIN));
			// ������ ����ص״� �ִ밪�� �ּҰ� �� BYTE_MAX�� ���� ���͸��� �� ��ȭ���� 0���� 255������ �缳���Ѵ�.

	file = fopen("edge_detect.bmp", "wb");
	// ��� ������ ����
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	// ���� ��� ��Ҹ� �Է�
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	// ���� ��� ��Ҹ� �Է�
	fwrite(pRGB, sizeof(RGBQUAD), t, file);
	// �ȷ�Ʈ ��Ҹ� �ȷ�Ʈ�� ����(t)��ŭ �Է�
	fwrite(lpOutImg, sizeof(BYTE), rwsize2*hinfo.biHeight, file);
	// ������ ��Ҹ� �Է�
	fclose(file);

	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	// �� �� ���� �Ҵ� �����͵��� �Ҵ� �������ش�.
}

void bitof24_to_8bit_gray(void)
// ������ �޾� ��� �������� ��ȯ���ش�.
{
	int i, j;
	BYTE R, G, B, GRAY;

	BITMAPFILEHEADER ohf; // ��� ������ ���� ��Ʈ�� ���� ���
	BITMAPINFOHEADER ohinfo; // ��� ������ ���� ��Ʈ�� ���� ���� ���

	printf("RUN bitof24_to_8bit_gray()\n\n");

	file = fopen("ori.bmp", "rb");// ������ �б� ���� ��

	if (file == NULL)// ���� ���⿡ �����ϸ�
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); // ������ ���� ������ BITMAPFILEHEADER��ŭ�� hf�� ����

	if (hf.bfType != 0x4D42) // 0X4D42 == BM(�ƽ�Ű �ڵ�), ��Ʈ�������� �� ó�� ������ BM�̴�. ���� ù �κ��� �а�, �� �κ��� �м��ؼ� ��Ʈ���� �ƴϸ�...
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); // ������ ���� ������ BITMAPINFOHEADER��ŭ�� hinfo�� ����

	printf("File size : %d\n", hf.bfSize); // �Է¹��� ��Ʈ�� ������ ũ�⸦ ȭ�鿡 �����
	printf("offset : %d\n", hf.bfOffBits); // �Է¹��� ��Ʈ�� ���Ͽ��� ���� �����Ͱ� �����ϴ� ������
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight); // �Է¹��� ��Ʈ�� ������ �ȼ� ������ ȭ�鿡 �����
	printf("%d BPP \n", hinfo.biBitCount); // �Է¹��� ��Ʈ�� ������ �ȼ��� ��Ʈ���� ���

	ohf = hf;
	ohinfo = hinfo;
	// ���� ���ϰ� ��� ������ ���� �����ϹǷ� ��������� �����ؼ� ����Ѵ�.
	// ��, �Ϻ� ���� �ٲ�� �͵��� �����Ƿ�, ���߿� �ݵ�� ��������� �Ѵ�.(bfOffBits, biBitCount ��...)

	rwsize = WIDTHBYTES(hinfo.biBitCount*hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//�Է� ���ϰ� ��� ���Ͽ��� ���� �� �ٴ� �����Ͱ� ���Ʈ���� �����Ѵ�
	//�̶� �Է����Ͽ��� ��������(=�������� �ִ� �� �ȼ� ����)
	//�� �ȼ��� ����Ʈ ���� ���ϸ�, �� ���� �� ��Ʈ�� �����ϴ��� �� �� �ִ�.
	//rwsize2�� ����� ���� �Է� ���ϰ� ��� ������ �ȼ� ������� �����ϱ� ������ �Է� ������ �������� �״�� ����
	//8BPP ������ �ȼ��� ��Ʈ���� 8��Ʈ�̹Ƿ� 8�� ���Ѵ�.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//��Ʈ�� ���Ͽ��� ���� ������ ����� �ִ� ��ġ�� �����͸� �̵��Ѵ�

	lpImg = (BYTE*)malloc(rwsize*hinfo.biHeight);
	//�Է� ���� ������ ���� �޸𸮸� �Ҵ��Ѵ�

	fread(lpImg, sizeof(char), rwsize*hinfo.biHeight, file);
	//�����ʹ� ���� ���� ������ ���� ����� ���� �� ó������ �̵��� ��Ȳ�̴�. �̶� �̹����� ��������(=�������� �ִ� �� �ȼ� ����)
	//�� �ٴ� ��Ʈ���� ���ϸ�, ��ü �������� ũ�Ⱑ ���´�. fread�Լ��� �̿��� �̹����� �����͸� char������ ũ�⸸ŭ
	//������ �����Ѵ�.

	fclose(file);
	//���ϻ���� �Ϸ�Ǿ����Ƿ� �ݴ´�.

	lpOutImg = (BYTE*)malloc(rwsize2*ohinfo.biHeight);
	//����� ������ ���� �޸𸮸� �Ҵ��Ѵ�

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			B = lpImg[i*rwsize + 3 * j + 0];
			G = lpImg[i*rwsize + 3 * j + 1];
			R = lpImg[i*rwsize + 3 * j + 2];
			//�ռ� ����ߵ� rwsize�� ���� ������ ������ ũ���. ���� ���⿡ i�� ���Ѵٴ°��� i+1��° ���� �����͸�
			//������� �ǹ��Ѵ�. ���� �÷����� �� �ȼ��� �����ʹ� 3����Ʈ�� �ʿ��ϹǷ� 3*j�� �ؼ� j+1��° �ȼ��� �̵��Ѵ�.
			//�� ���� ������ ����  i+1��° ���� j+1��°ĭ�� �ȼ��� �����͸� ������ �迭�� ���� Ȯ���ϰ� �ȴ�.
			//�̶� �迭�� ��ġ�� +0,+1,+2�� �ؼ� �������� B G R���� ���� �����Ѵ�.

			GRAY = (BYTE)(0.299*R + 0.587*G + 0.114*B);
			//���� ������ R,G,B���� ������ ���� ���ϰ� ���ؼ� ��Ⱚ�� �����
			//�� ������ ��� ���������ΰ�? -> ã�Ƽ� ����Ʈ ÷��
			lpOutImg[i*rwsize2 + j] = GRAY;
			//���� ��Ⱚ�� lpOutImg�� i+1��° ���� j+1��°ĭ�� �ȼ��� �����͸� ������ �迭�� �����Ѵ�.
		}
	}
	ohf.bfOffBits += 1024;
	//bfOffBits�� ���� ������ ȭ�� �����Ͱ� ���۵Ǵ� ���� ��ġ�̴�.
	//��Ʈ�����Ͽ��� ��Ʈ���� ������(1 ~ 8BPP)
	//��Ʈ���� ���� ����(8BPP �ʰ�) �޸� ColorTable�� ������ ȭ�� �����;տ� �ִ�.
	//���� bfOffBits�� 1024��ŭ �ڷ� �о�� �Ѵ�.
	//1024�� RGBQUAD�� ũ��(4����Ʈ) * 256�� �ȷ�Ʈ = 1024��.

	ohinfo.biBitCount = 8;
	//8BPP�̴ϱ� 8�̴�.

	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//�ռ� ���� ColorTable�� ���� �޸𸮸� �����Ѵ�.

	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//����̴ϱ� �׳� 0���� 255���� ���������� �����Ѵ�.

	file = fopen("BW.bmp", "wb");
	//���� ����� ������ ������� ����.

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	//��Ʈ�� ������ �����ϴ� BITMAPFILEHEADER, BITMAPINFOHEADER,RGBQUAD�� ����Ѵ�.
	fwrite(lpOutImg, sizeof(char), rwsize2*hinfo.biHeight, file);
	//�ռ� �츮�� ���� ��� �����͸� ����Ѵ�.
	fclose(file);
	//������ �ݴ´�.

	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//�޸𸮸� ��ȯ�Ѵ�.

	printf("Check BW.bmp!!\n\n");
}


// rgb��Ÿ���� ��Ʈ�� ���� ���� ��ȭ?
// bmp�� ���� ���� �ʴ� ������?
// �ȷ�Ʈ�� ��� ���� �� ��� ������ ���� offset�� ũ�Ⱑ �޶�����.
// bmp ������ ������ 0x4D42
// �ȷ�Ʈ�� 8��Ʈ ������ �߸��� ����? : ��� ��� �� ������ ��ȯ�� 1byte������ �̷������.
// ����� ū bmp������ ��� �ȷ�Ʈ�� ����ϴ� ���� �� ���� ����? : look up table�̶�� ���� ��ü�� �ϵ��� �ִ�. �ش� ������ �������°� �� ������ �׷�
// ����� �����ϴ� ����? : 1. ���ϸ��� ������ �д� ������ �ٸ� 
//						   2. ������ ������ Ư���� �� �ְԵȴ�.
// bmp = ���Ͽ� ���� ���� + �׸��� ���� ����
// bfReversed : ���� ���ο� ����� �߰��ϱ� ���� �ڸ���
// ���� ���� vs ��� ���� : ����� ��� ����������� �� ���� ������ �޴´�.
//							- ����� ���, ���� ������ �Ҿ ��� ������ �״�� ����
// �ڵ� - ��Ʈ���� ������ ���� �ֵ� ����
// ��Ʈ���� ������ �������� ������ ���ϸ� �ش� ������ ������ �ٲ��ִ� ���̴�.