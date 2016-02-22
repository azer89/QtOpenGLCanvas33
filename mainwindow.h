#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
