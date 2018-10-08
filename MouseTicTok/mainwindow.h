#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadStyleSheet(const QString &styleSheetFile);

public slots:
    void btnClick();
    void mouseClickToDownCPU();


protected:
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QDesktopWidget* desktop;

    int button_width;
    int button_height;
};

#endif // MAINWINDOW_H
