

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>

cv::Vec2d genWB(cv::Mat& whiteColor);

int test_presetwb_main(void){
    cv::Mat testingWBImage = cv::imread("./whiteCalibImage.png", cv::IMREAD_UNCHANGED); // MONOCHROME
    cv::cvtColor(testingWBImage, testingWBImage, cv::COLOR_BayerBG2BGR);

    double expectedRFactor = 1.4495851453792237;
    double expectedBFactor = 0.47584357278590383;
    auto wb = genWB(testingWBImage);

    assert((float)wb[0] == (float)expectedBFactor);
    assert((float)wb[1] == (float)expectedRFactor);

    return 0;
}

/*
 This function calculates the correction values for the blue and red 
 channels of the image by comparing the means of these channels to the mean of the 
 green channel, which is less affected by the color temperature of the lighting.
*/
cv::Vec2d genWB(cv::Mat& whiteColor){
    cv::Vec2d wb { 0, 0 };

    cv::Mat bgr[3];
    cv::split(whiteColor, bgr);

    // In perfect white image color gMean will peak value of 255
    double gMean = cv::mean(bgr[1])[0]; // mean of the green channel is less affected by the color temperature of the lighting.
    double bMean = cv::mean(bgr[0])[0];
    double rMean = cv::mean(bgr[2])[0];

    wb[0] = gMean / bMean - 1;
    wb[1] = gMean / rMean - 1;

    return wb;
}

