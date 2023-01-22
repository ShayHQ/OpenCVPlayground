#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>


#define test_histogram_main main

cv::Mat calcHist(cv::Mat& img);

void drawHistogram(cv::Mat& hist, cv::Scalar color = cv::Scalar(255, 255, 255));



int test_histogram_main(void){
    cv::Mat sampleImg = cv::imread(cv::samples::findFile("starry_night.jpg")); // color image
    cv::Mat bgr[3];
    cv::Mat histsBGR[3];

    cv::split(sampleImg, bgr);
    for (int i = 0; i < 3; i ++){
        auto& ch = bgr[i];
        histsBGR[i] = calcHist(ch);
    }

    drawHistogram(histsBGR[2], cv::Scalar(0, 0, 255));
    drawHistogram(histsBGR[1], cv::Scalar(0, 255, 0));
    drawHistogram(histsBGR[0], cv::Scalar(255, 0, 0));
    cv::waitKey();
    return 0;
}



cv::Mat calcHist(cv::Mat& img){
    cv::Mat hist;
    if (img.channels() != 1)
        throw std::runtime_error("Custom calcHist Bad channel count");
    hist.create(1, 256, CV_32FC1);
    
    for (int i = 0; i < img.rows; i ++)
        for (int j = 0; j < img.cols; j++)
            hist.ptr<float>(0)[img.ptr<uchar>(i)[j]]++;

    return hist;
}


void drawHistogram(cv::Mat& hist,  cv::Scalar color){
    using namespace cv;
    static int count = 0;
    count ++;
    int histSize = 256;
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize);
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
              color, 2, 8, 0  );
    }
    imshow(std::string("calcHist Demo " + count), histImage );
}
