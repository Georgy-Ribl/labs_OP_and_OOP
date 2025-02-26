#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entry_point.h"
#include "converter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sourceComboBox->addItem("10");
    ui->sourceComboBox->addItem("2");
    ui->sourceComboBox->addItem("16");

    ui->targetComboBox->addItem("10");
    ui->targetComboBox->addItem("2");
    ui->targetComboBox->addItem("16");

    ui->sourceComboBox->setCurrentIndex(0);
    ui->targetComboBox->setCurrentIndex(1);

    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::onTranslateButtonClicked);
    connect(ui->sourceComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onSourceComboBoxChanged);
    connect(ui->targetComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onTargetComboBoxChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTranslateButtonClicked()
{
    int resultFlag = SUCCESS;

    AppContext context;
    initAppContext(&context);

    int sourceBase = ui->sourceComboBox->currentText().toInt();
    int targetBase = ui->targetComboBox->currentText().toInt();

    const char* input = ui->inputLineEdit->text().toStdString().c_str();

    setInputData(&context, input, sourceBase, targetBase);

    resultFlag = performConversion(&context);
    if (resultFlag != SUCCESS) {
        ui->errorMessageLabel->setText(QString::fromUtf8(context.errorMessage));
    } else {
        ui->outputLineEdit->setText(QString::fromUtf8(context.outputString));
    }

    cleanupAppContext(&context);
}

void MainWindow::onSourceComboBoxChanged(const QString& text)
{

}

void MainWindow::onTargetComboBoxChanged(const QString& text)
{

}
