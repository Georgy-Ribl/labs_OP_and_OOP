#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include "chartwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onChooseFileClicked();
    void onLoadDataClicked();
    void onCalculateMetricsClicked();

private:
    QPushButton *m_chooseBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_calcBtn;
    QLineEdit    *m_fileEdit;
    QLineEdit    *m_regionEdit;
    QLineEdit    *m_colEdit;
    QTableWidget *m_table;
    QLabel       *m_minLbl;
    QLabel       *m_maxLbl;
    QLabel       *m_medLbl;
    ChartWidget  *m_chart;

    void fillTable();
};

#endif // MAINWINDOW_H
