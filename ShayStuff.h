#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"



/*
    It is accessing BGR only!
*/
uchar& accessPixelWithAt(cv::Mat& mat, int i, int j, int channelIdx);
uchar& accessPixelWithPtr(cv::Mat& mat, int i, int j, int channelIdx);
uchar& accessPixelWithData(cv::Mat& mat, int i, int j, int channelIdx);


cv::Mat cvtColorRGGB(cv::Mat& img);
void wbImage(cv::Mat& img, double r = 0, double g = 0, double b = 0);

cv::Vec2d genWB(cv::Mat& whiteColor);
cv::Mat calcHist(cv::Mat& img);

int test_presetwb_main(void);
int test_cvtcolor_main(void);
int test_accessingPixels_main(void);

