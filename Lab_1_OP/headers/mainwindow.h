#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entry_point.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onTranslateButtonClicked();
    void onSourceComboBoxChanged(const QString& text);
    void onTargetComboBoxChanged(const QString& text);

private:
    Ui::MainWindow* ui;
    AppContext context;
};

#endif // MAINWINDOW_H
