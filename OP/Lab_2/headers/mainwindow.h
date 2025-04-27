#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entrypoint.h"

class QLineEdit;
class QPushButton;
class QLabel;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent=nullptr);
    ~MainWindow();

private slots:
    void onChooseFileClicked();
    void onLoadDataClicked();
    void onCalcClicked();

private:
    void fillTable(const char* region);

    QLineEdit*    m_fileEdit;
    QPushButton*  m_chooseBtn;
    QLineEdit*    m_regionEdit;
    QLineEdit*    m_colEdit;
    QPushButton*  m_loadBtn;
    QPushButton*  m_calcBtn;
    QTableWidget* m_table;
    QLabel*       m_minLbl;
    QLabel*       m_maxLbl;
    QLabel*       m_medLbl;
};

#endif
