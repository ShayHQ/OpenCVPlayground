

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>

cv::Mat cvtColorRGGB(cv::Mat& img);

int main(void){
    cv::Mat sampleImg = cv::imread("/home/shay/tmp/testing-white-img.png", cv::IMREAD_UNCHANGED); // MONOCHROME
    cv::Mat colorImg = cvtColorRGGB(sampleImg);
    cv::imwrite("MyCVTRes.png", colorImg);
    return 0;
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
    cv::resize(r, r, colorImg.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(g, g, colorImg.size(), 0, 0, cv::INTER_LINEAR);
    cv::resize(b, b, colorImg.size(), 0, 0, cv::INTER_LINEAR);
    std::vector<cv::Mat> bgr {b, g, r};
    cv::merge(bgr.data(), 3, colorImg);

    return colorImg;
}
