#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_selectImageButton_clicked();

    private:
        void setImagePreview(QString path);
        Ui::MainWindow *ui;
        QDir lastPath;
};

QDir getPath(QString filePath);
#endif // MAINWINDOW_H
