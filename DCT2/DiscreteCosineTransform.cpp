//
// Created by Davide Costantini on 02/07/24.
//

#include "DiscreteCosineTransform.h"

#include <opencv2/imgcodecs.hpp>
#include <iostream>

cv::Mat DiscreteCosineTransform::DCT2(const QString& imagePath, const int F, const int d)
{
    cv::Mat image = imread(imagePath.toStdString(), cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cerr << "Could not load image." << std::endl;
        return image;
    }

    image.convertTo(image, CV_32FC1);

    int x = 0, y = 0;
    while (y < image.rows)
    {
        cv::Mat submatrix = image(cv::Rect(x, y, F, F));
        dct(submatrix, submatrix);

        for (int i = 0; i < submatrix.rows; ++i)
            for (int j = 0; j < submatrix.cols; ++j)
                if (i + j > d)
                    submatrix.at<float>(i, j) = 0.0f;

        x += F;
        if (x >= image.cols)
        {
            x = 0;
            y += F;
        }
    }

    return image;
}

void DiscreteCosineTransform::IDCT2(cv::Mat& matrix, const int F)
{
    int x = 0, y = 0;
    while (y < matrix.rows)
    {
        cv::Mat submatrix = matrix(cv::Rect(x, y, F, F));
        dct(submatrix, submatrix, cv::DCT_INVERSE);

        for (int i = 0; i < submatrix.rows; ++i)
            for (int j = 0; j < submatrix.cols; ++j)
            {
                if (submatrix.at<float>(i, j) < 0.0f)
                    submatrix.at<float>(i, j) = 0.0f;
                else if (submatrix.at<float>(i, j) > 255.0f)
                    submatrix.at<float>(i, j) = 255.0f;
            }

        x += F;
        if (x >= matrix.cols)
        {
            x = 0;
            y += F;
        }
    }

    matrix.convertTo(matrix, CV_8U);
}