#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QLabel>

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

        void on_runButton_clicked();

    private:
        void setImagePreview(const QString& path);
        void setPixmap(QLabel* label, QPixmap pixmap);
        Ui::MainWindow *ui;
        QDir lastPath;
};

QDir getPath(const QString& filePath);
#endif // MAINWINDOW_H
