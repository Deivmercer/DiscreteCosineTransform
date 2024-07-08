#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "DiscreteCosineTransform.h"
#include <QFileDialog>

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
    QString lineEditContent = ui->blockSizeLineEdit->text();
    if (lineEditContent.isNull() || lineEditContent.isEmpty())
    {
        qDebug("Block size not set.");
        return;
    }
    int F = lineEditContent.toInt();

    lineEditContent = ui->thresholdLineEdit->text();
    if (lineEditContent.isNull() || lineEditContent.isEmpty())
    {
        qDebug("Threshold not set.");
        return;
    }
    int d = lineEditContent.toInt();
    if (d < 0 || d > 2 * F - 2)
    {
        qDebug("Threshold out of range.");
        return;
    }

    std::vector<DiscreteCosineTransform::block> blocks = DiscreteCosineTransform::DCT2(ui->filePathLineEdit->text(), F, d);
    cv::Mat result = IDCT2(blocks);

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
