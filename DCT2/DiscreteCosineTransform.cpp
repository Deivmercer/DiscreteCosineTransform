//
// Created by Davide Costantini on 02/07/24.
//

#include "DiscreteCosineTransform.h"

#include <opencv2/imgcodecs.hpp>
#include <iostream>

std::vector<DiscreteCosineTransform::block> DiscreteCosineTransform::DCT2(const QString& imagePath, const int F, const int d)
{
    std::vector<block> blocks;
    cv::Mat image = imread(imagePath.toStdString(), cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cerr << "Could not load image." << std::endl;
        return blocks;
    }

    image.convertTo(image, CV_32FC1);

    int x = 0, y = 0;
    while (y < image.rows)
    {
        int rows = F;
        if (x + F > image.cols)
            rows = image.cols - x;
        int cols = F;
        if (y + F > image.rows)
            cols = image.rows - y;

        cv::Mat submatrix = cv::Mat(rows, cols, CV_32FC1);
        image(cv::Rect(x, y, rows, cols)).copyTo(submatrix);

        if (submatrix.rows < F)
        {
            int missingRows = F - submatrix.rows;
            cv::Mat newRow = cv::Mat::zeros(missingRows, submatrix.cols, CV_32FC1);
            vconcat(submatrix, newRow, submatrix);
        }
        if (submatrix.cols < F)
        {
            int missingCols = F - submatrix.cols;
            cv::Mat newColumn = cv::Mat::zeros(submatrix.rows, missingCols, CV_32FC1);
            hconcat(submatrix, newColumn, submatrix);
        }

        if (submatrix.rows % 2 != 0)
        {
            cv::Mat newRow = cv::Mat::zeros(1, submatrix.cols, CV_32FC1);
            vconcat(submatrix, newRow, submatrix);
        }
        if (submatrix.cols % 2 != 0)
        {
            cv::Mat newColumn = cv::Mat::zeros(submatrix.rows, 1, CV_32FC1);
            hconcat(submatrix, newColumn, submatrix);
        }

        dct(submatrix, submatrix);

        for (int i = 0; i < submatrix.rows; ++i)
            for (int j = 0; j < submatrix.cols; ++j)
                if (i + j > d)
                    submatrix.at<float>(i, j) = 0.0f;

        block b = { submatrix, rows, cols };
        blocks.push_back(b);
        x += F;
        if (x >= image.cols)
        {
            x = 0;
            y += F;
        }
    }

    return blocks;
}

cv::Mat DiscreteCosineTransform::IDCT2(std::vector<block>& blocks)
{
    int originalImageSize = 20;

    cv::Mat result(originalImageSize, originalImageSize, CV_32FC1);
    int x = 0, y = 0;
    for (block& b : blocks)
    {
        dct(b.data, b.data, cv::DCT_INVERSE);

        cv::Mat tmp(b.originalHeight, b.originalWidth, CV_32FC1);

        if (b.data.rows != b.originalHeight || b.data.cols != b.originalWidth)
            b.data(cv::Rect(0, 0, b.originalHeight, b.originalWidth)).copyTo(tmp);
        else
            b.data.copyTo(tmp);

        for (int i = 0; i < tmp.rows; ++i)
            for (int j = 0; j < tmp.cols; ++j)
            {
                if (tmp.at<float>(i, j) < 0.0f)
                    tmp.at<float>(i, j) = 0.0f;
                else if (tmp.at<float>(i, j) > 255.0f)
                    tmp.at<float>(i, j) = 255.0f;
            }

        tmp.copyTo(result(cv::Rect(x, y, tmp.cols, tmp.rows)));

        x += tmp.cols;
        if (x >= result.cols)
        {
            x = 0;
            y += tmp.rows;
        }
    }

    result.convertTo(result, CV_8U);

    return result;
}