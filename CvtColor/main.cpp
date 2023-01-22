

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>

cv::Mat cvtColorRGGB(cv::Mat& img);
void wbImage(cv::Mat& img, double r = 0, double g = 0, double b = 0);


int test_cvtcolor_main(void){
    cv::Mat sampleImg = cv::imread("/home/shay/tmp/testing-white-img.png", cv::IMREAD_UNCHANGED); // MONOCHROME
    cv::Mat colorImg = cvtColorRGGB(sampleImg);
    wbImage(colorImg, 0.835, 0, 0.608);
    cv::imwrite("MyCVTRes.png", colorImg);
    return 0;
}

void wbImage(cv::Mat& img, double r, double g, double b){
    std::vector<cv::Mat> bgr(3);
    std::vector<double> wb {b,g,r};
    
    cv::split(img, bgr);
    for (cv::Mat& ch : bgr){
        ch.convertTo(ch, CV_32FC1);
    }
    for (int chIdx = 0 ; chIdx < bgr.size() ; chIdx++){
        cv::Mat& ch = bgr[chIdx];
        for (int i = 0 ; i < ch.rows; i ++){
            for (int j = 0; j < ch.cols ; j ++){
                ch.ptr<float>(i)[j] *= (1 + wb[chIdx]);
            }
        }
    }
    for (cv::Mat& ch : bgr){
        ch.convertTo(ch, CV_8UC1);
    }

    cv::merge(bgr.data(), bgr.size(), img);
}

cv::Mat cvtColorRGGB(cv::Mat& img){
    cv::Mat colorImg;

    colorImg.create(img.rows, img.cols, CV_8UC3);

    std::vector<cv::Mat> rggb(4);
    cv::Mat& r = rggb[0];
    cv::Mat& g1 = rggb[1];
    cv::Mat& g2 = rggb[2];
    cv::Mat& b = rggb[3];

    for (auto& ch : rggb)
        ch.create(img.rows / 2, img.cols / 2, CV_8U);
    for (int row = 0, i = 0; i < img.rows; i += 2, row++){
        for (int col = 0, j = 0; j < img.cols; j += 2, col++){
            r.ptr<uchar>(row)[col] = img.ptr<uchar>(i)[j];
            g1.ptr<uchar>(row)[col] = img.ptr<uchar>(i)[j + 1];
        }
    }
    for (int r = 0, i = 1; i < img.rows; i += 2, r++){
        for (int col = 0, j = 0; j < img.cols; j += 2, col++){
            g2.ptr<uchar>(r)[col] = img.ptr<uchar>(i)[j];
            b.ptr<uchar>(r)[col] = img.ptr<uchar>(i)[j + 1];
        }
    }

    cv::Mat g = cv::max(g1, g2);
    
    // linear opencv interpolation
    cv::resize(r, r, colorImg.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(g, g, colorImg.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(b, b, colorImg.size(), 0, 0, cv::INTER_LINEAR);
    std::vector<cv::Mat> bgr {b, g, r};
    cv::merge(bgr.data(), 3, colorImg);

    return colorImg;
}
