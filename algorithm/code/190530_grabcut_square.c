#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void main()
{
	Mat image = imread("test.jfif");
	Rect rectangle(10, 20, 100, 200);
	Mat result;
	Mat bg, fg;
	grabCut(image, result, rectangle, bg, fg, 5, GC_INIT_WITH_RECT);
	compare(result, GC_PR_FGD, result, CMP_EQ);
	Mat foreground(image.size(), CV_8UC3, Scalar(255, 255, 255));
	image.copyTo(foreground, result);
	imshow("Foreground", foreground);
	waitKey(0);
}