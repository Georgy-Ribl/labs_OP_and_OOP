#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entrypoint.h"
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
    OperationsContext m_ctx;

    void fillTable();
    QPushButton*  m_chooseBtn;
    QLineEdit*    m_fileEdit;
    QLineEdit*    m_regionEdit;
    QLineEdit*    m_colEdit;
    QPushButton*  m_loadBtn;
    QPushButton*  m_calcBtn;
    QTableWidget* m_table;
    QLabel*       m_minLbl;
    QLabel*       m_maxLbl;
    QLabel*       m_medLbl;
};

#endif // MAINWINDOW_H
