//
// Created by Davide Costantini on 02/07/24.
//

#include "DiscreteCosineTransform.h"

#include <opencv2/imgcodecs.hpp>
#include <iostream>

cv::Mat DiscreteCosineTransform::DCT2(const QString& imagePath)
{
    cv::Mat image = imread(imagePath.toStdString(), cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cerr << "Could not load image." << std::endl;
        return image;
    }

    // image.convertTo(image, CV_32FC1, 1.0 / 255.0);
    image.convertTo(image, CV_32FC1);

    cv::Mat result = cv::Mat(image.rows, image.cols, CV_32FC1);
    dct(image, result);

    return result;
}

cv::Mat DiscreteCosineTransform::IDCT2(const cv::Mat& matrix)
{
    cv::Mat result = cv::Mat(matrix.rows, matrix.cols, CV_32FC1);
    dct(matrix, result, cv::DCT_INVERSE);
    result.convertTo(result, CV_8U);
    return result;
}