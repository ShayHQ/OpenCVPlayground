

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

uchar& accessPixelWithAt(cv::Mat& mat, int i, int j, int channelIdx);
uchar& accessPixelWithPtr(cv::Mat& mat, int i, int j, int channelIdx);
uchar& accessPixelWithData(cv::Mat& mat, int i, int j, int channelIdx);


void TestPixelAccessFunctions(cv::Mat& mat, int channel){
    for (int i = 0; i < mat.rows; i ++){
        for (int j = 0; j < mat.cols; j ++){
            auto& channelComponent = accessPixelWithData (mat, i, j, channel);
            auto& channelComponentByPtr = accessPixelWithPtr(mat, i, j, channel);
            auto& channelComponentByAt = accessPixelWithAt(mat, i, j, channel);

            if (&channelComponent != &channelComponentByAt || &channelComponent != &channelComponentByPtr){
                throw std::runtime_error("Bad pixel access");
            }
        }
    }
}

int main(void){
    cv::Mat sampleImg = cv::imread(cv::samples::findFile("starry_night.jpg")); // color image
    
    for (int i = 0; i < 3; i ++) TestPixelAccessFunctions(sampleImg, i);

    return 0;
}


uchar& accessPixelWithAt(cv::Mat& mat, int i, int j, int channelIdx){
    return mat.at<cv::Vec3b>(i, j)[channelIdx];
}
uchar& accessPixelWithPtr(cv::Mat& mat, int i, int j, int channelIdx){
    return mat.ptr<cv::Vec3b>(i)[j][channelIdx];
}
uchar& accessPixelWithData(cv::Mat& mat, int i, int j, int channelIdx){
    cv::Vec3b *bgrPtr = (cv::Vec3b*)mat.data;
    cv::Vec3b& pixel = bgrPtr[i * mat.cols + j];
    return pixel[channelIdx];
}