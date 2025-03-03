#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "inputhandler.h"
#include "calculator.h"
#include "outputhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Связываем нажатие кнопки с нашим слотом
    connect(ui->computeSumButton, &QPushButton::clicked,
            this, &MainWindow::onComputeSumClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onComputeSumClicked()
{
    // Считываем текст из QLineEdit
    QString firstString = ui->firstNumberLineEdit->text();
    QString secondString = ui->secondNumberLineEdit->text();

    // Парсим введённые данные как целые числа
    InputHandler inputHandler;
    bool okFirst = false;
    bool okSecond = false;

    int firstNumber = inputHandler.parseInteger(firstString, &okFirst);
    int secondNumber = inputHandler.parseInteger(secondString, &okSecond);

    if (!okFirst || !okSecond) {
        ui->resultLabel->setText("Invalid input. Please enter valid integers.");
        return;  // Допустим один return в начале для валидации
    }

    // Вычисляем сумму
    Calculator calculator;
    int sum = calculator.computeSum(firstNumber, secondNumber);

    // Формируем строку результата
    OutputHandler outputHandler;
    QString resultMessage = "The sum is: ";
    QString resultText = outputHandler.generateResultString(resultMessage, sum);

    // Выводим результат в QLabel
    ui->resultLabel->setText(resultText);
}
