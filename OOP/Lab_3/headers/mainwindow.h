#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include "CalculatorFacade.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onButtonClicked();

private:
    QWidget*       central;
    QGridLayout*   grid;
    QLineEdit*     display;
    CalculatorFacade facade;
};

#endif // MAINWINDOW_H
