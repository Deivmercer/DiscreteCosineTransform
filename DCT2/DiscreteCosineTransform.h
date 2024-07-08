//
// Created by Davide Costantini on 02/07/24.
//

#ifndef DCT2_H
#define DCT2_H

#include <QDir>
#include <opencv2/core.hpp>

namespace DiscreteCosineTransform
{
    struct block
    {
        cv::Mat data;
        int originalHeight;
        int originalWidth;
    };

    std::vector<block> DCT2(const QString& imagePath, int F, int d);

    cv::Mat IDCT2(std::vector<block>& blocks);
}

#endif //DCT2_H
