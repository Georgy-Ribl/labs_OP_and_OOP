#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "operations.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onChooseFileClicked();
    void onLoadDataClicked();
    void onCalculateMetricsClicked();

private:
    void fillTable();

    OperationsContext m_ctx;

    QPushButton*  m_chooseButton;
    QLineEdit*    m_fileLineEdit;
    QLineEdit*    m_regionLineEdit;
    QLineEdit*    m_columnLineEdit;
    QPushButton*  m_loadButton;
    QPushButton*  m_calcButton;
    QTableWidget* m_tableWidget;
    QLabel*       m_minLabel;
    QLabel*       m_maxLabel;
    QLabel*       m_medianLabel;
};

#endif // MAINWINDOW_H
