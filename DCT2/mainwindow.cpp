#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "DiscreteCosineTransform.h"
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastPath = QDir("/");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectImageButton_clicked()
{
    QString filter = "Images (*.bmp)";
    QString filePath = QFileDialog::getOpenFileName(this, "Select image", lastPath.path(), filter);

    if (filePath == "")
        return;

    setImagePreview(filePath);
    ui->filePathLineEdit->setText(filePath);
    lastPath = getPath(filePath);
}

void MainWindow::on_runButton_clicked()
{
    cv::Mat c = DiscreteCosineTransform::DCT2(ui->filePathLineEdit->text());
    cv::Mat result = DiscreteCosineTransform::IDCT2(c);

    QImage image(result.data, result.cols, result.rows, QImage::Format_Grayscale8);
    QPixmap resultImage = QPixmap::fromImage(image);
    setPixmap(ui->resultPreviewLabel, resultImage);
}

void MainWindow::setImagePreview(const QString& path)
{
    QPixmap pixmap(path);
    if (pixmap.isNull())
    {
        qDebug("Pixmap creation failed.");
        return;
    }

    setPixmap(ui->imagePreviewLabel, pixmap);
}

void MainWindow::setPixmap(QLabel* label, QPixmap pixmap)
{
    int imageWidth = label->width();
    int imageHeight = label->height();
    label->setPixmap(pixmap.scaled(imageWidth, imageHeight, Qt::KeepAspectRatio));
}

QDir getPath(const QString& filePath)
{
    QFileInfo file(filePath);
    return file.absoluteDir();
}
