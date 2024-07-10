//
// Created by Davide Costantini on 02/07/24.
//

#include "DiscreteCosineTransform.h"

#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace DiscreteCosineTransform;

DCT2::DCT2(const QString& imagePath)
{
    loadImage(imagePath);
}

DCT2::~DCT2()
{
    blocks.clear();
}

void DCT2::loadImage(const QString& imagePath)
{
    originalImage = imread(imagePath.toStdString(), cv::IMREAD_GRAYSCALE);
    if (originalImage.empty())
    {
        std::cerr << "Could not load image." << std::endl;
        originalHeight = 0;
        originalWidth = 0;
        return;
    }

    originalHeight = originalImage.rows;
    originalWidth = originalImage.cols;

#ifdef QT_DEBUG
    QFileInfo file(imagePath);
    debugOutputPath = file.absoluteDir();
    if (!debugOutputPath.exists("output") && !debugOutputPath.mkdir("output"))
        qDebug("Could not create output folder");
#endif
}

const cv::Mat& DCT2::getOriginalImage() const
{
    return originalImage;
}

const cv::Mat& DCT2::getResultImage() const
{
    return resultImage;
}

int DCT2::getOriginalHeight() const
{
    return originalHeight;
}

int DCT2::getOriginalWidth() const
{
    return originalWidth;
}

void DCT2::setBlockSize(const int blockSize)
{
    this->blockSize = blockSize;
}

int DCT2::getBlockSize() const
{
    return blockSize;
}

void DCT2::setThreshold(int threshold)
{
    this->threshold = threshold;
}

int DCT2::getThreshold() const
{
    return threshold;
}

void DCT2::performDCT2()
{
    originalImage.convertTo(resultImage, CV_32FC1);

    int x = 0, y = 0;
    while (y < resultImage.rows)
    {
        int rows = blockSize;
        if (x + blockSize > resultImage.cols)
            rows = resultImage.cols - x;
        int cols = blockSize;
        if (y + blockSize > resultImage.rows)
            cols = resultImage.rows - y;

        cv::Mat submatrix = cv::Mat(rows, cols, CV_32FC1);
        resultImage(cv::Rect(x, y, rows, cols)).copyTo(submatrix);

#ifdef QT_DEBUG
        std::string filename = std::to_string(x) + std::to_string(y) + "_before" + ".bmp";
        std::string test = debugOutputPath.path().toStdString() + "/output/" + filename;
        imwrite(debugOutputPath.path().toStdString() + "/output/" + filename, submatrix);
#endif

        if (submatrix.rows < blockSize)
        {
            int missingRows = blockSize - submatrix.rows;
            cv::Mat newRow = cv::Mat::zeros(missingRows, submatrix.cols, CV_32FC1);
            vconcat(submatrix, newRow, submatrix);
        }
        if (submatrix.cols < blockSize)
        {
            int missingCols = blockSize - submatrix.cols;
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
                if (i + j > threshold)
                    submatrix.at<float>(i, j) = 0.0f;

        block b = { submatrix, rows, cols };
        blocks.push_back(b);
        x += blockSize;
        if (x >= resultImage.cols)
        {
            x = 0;
            y += blockSize;
        }
    }
}

void DCT2::performIDCT2()
{
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

#ifdef QT_DEBUG
        std::string filename = std::to_string(x) + std::to_string(y) + "_after" + ".bmp";
        imwrite(debugOutputPath.path().toStdString() + "/output/" + filename, tmp);
#endif

        tmp.copyTo(resultImage(cv::Rect(x, y, tmp.cols, tmp.rows)));

        x += tmp.cols;
        if (x >= resultImage.cols)
        {
            x = 0;
            y += tmp.rows;
        }
    }

    resultImage.convertTo(resultImage, CV_8U);
}

void DCT2::reset()
{
    blocks.clear();
    resultImage = cv::Mat();
}
