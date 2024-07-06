//
// Created by Davide Costantini on 02/07/24.
//

#ifndef DCT2_H
#define DCT2_H

#include <QDir>
#include <opencv2/core.hpp>

namespace DiscreteCosineTransform
{
    cv::Mat DCT2(const QString& imagePath, int F, int d);

    void IDCT2(cv::Mat& matrix, int F);
}

#endif //DCT2_H
