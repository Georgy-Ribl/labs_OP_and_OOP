/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *translateButton;
    QLabel *errorMessageLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *inputLineEdit;
    QComboBox *sourceComboBox;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *outputLineEdit;
    QComboBox *targetComboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        translateButton = new QPushButton(centralwidget);
        translateButton->setObjectName("translateButton");
        translateButton->setGeometry(QRect(340, 330, 131, 51));
        errorMessageLabel = new QLabel(centralwidget);
        errorMessageLabel->setObjectName("errorMessageLabel");
        errorMessageLabel->setGeometry(QRect(350, 470, 221, 51));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(70, 160, 671, 171));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        inputLineEdit = new QLineEdit(horizontalLayoutWidget);
        inputLineEdit->setObjectName("inputLineEdit");

        verticalLayout_3->addWidget(inputLineEdit);

        sourceComboBox = new QComboBox(horizontalLayoutWidget);
        sourceComboBox->setObjectName("sourceComboBox");

        verticalLayout_3->addWidget(sourceComboBox);


        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        outputLineEdit = new QLineEdit(horizontalLayoutWidget);
        outputLineEdit->setObjectName("outputLineEdit");
        outputLineEdit->setReadOnly(true);

        verticalLayout_4->addWidget(outputLineEdit);

        targetComboBox = new QComboBox(horizontalLayoutWidget);
        targetComboBox->setObjectName("targetComboBox");

        verticalLayout_4->addWidget(targetComboBox);


        horizontalLayout_5->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        translateButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\262\320\265\321\201\321\202\320\270", nullptr));
        errorMessageLabel->setText(QCoreApplication::translate("MainWindow", "\320\235\320\265\321\202 \320\276\321\210\320\270\320\261\320\276\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
