#include "mainwindow.h"
#include "./ui_mainwindow.h"
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

void MainWindow::setImagePreview(QString path)
{
    QPixmap pixmap(path);
    if (pixmap.isNull())
        return;

    int imageWidth = ui->imagePreviewLabel->width();
    int imageHeight = ui->imagePreviewLabel->height();
    ui->imagePreviewLabel->setPixmap(pixmap.scaled(imageWidth, imageHeight, Qt::KeepAspectRatio));
}

QDir getPath(QString filePath)
{
    QFileInfo file(filePath);
    return file.absoluteDir();
}
