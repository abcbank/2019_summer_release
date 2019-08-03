#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
using namespace cv;
void main()
{
	//test row : 177, test cols : 284
	// You can set the path of an image file
	Mat imgColor = imread("test.jfif", CV_LOAD_IMAGE_COLOR);
	Mat imgGray = imread("test.jfif", CV_LOAD_IMAGE_GRAYSCALE);
	
	for(int i = 150; i < 220; i++)
		for (int j = 60; j < 120; j++) {
			imgColor.at<Vec3b>(j, i)[2] = 255;
			imgColor.at<Vec3b>(j, i)[1] = 125;
			imgColor.at<Vec3b>(j, i)[0] = 0;
			imgGray.at<uchar>(j, i) = 255;
		}
	
	imshow("color", imgColor);
	imshow("gray", imgGray);
	waitKey(5000);
}