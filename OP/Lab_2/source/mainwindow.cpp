#include "mainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QStringList>
#include <cstring>

MainWindow::MainWindow(QWidget* p)
    : QMainWindow(p)
{
    doOperations(OP_INIT, nullptr, nullptr, nullptr, nullptr, nullptr);
    QWidget* c = new QWidget(this);
    QVBoxLayout* v = new QVBoxLayout(c);

    QHBoxLayout* fLay = new QHBoxLayout();
    m_chooseBtn = new QPushButton("Выбрать файл", this);
    m_fileEdit  = new QLineEdit(this);
    fLay->addWidget(m_chooseBtn);
    fLay->addWidget(m_fileEdit);

    QHBoxLayout* rLay = new QHBoxLayout();
    rLay->addWidget(new QLabel("Регион:", this));
    m_regionEdit = new QLineEdit(this);
    rLay->addWidget(m_regionEdit);

    QHBoxLayout* cLay = new QHBoxLayout();
    cLay->addWidget(new QLabel("Колонка:", this));
    m_colEdit = new QLineEdit(this);
    cLay->addWidget(m_colEdit);

    m_loadBtn = new QPushButton("Load data", this);
    m_calcBtn = new QPushButton("Calculate metrics", this);
    m_table   = new QTableWidget(this);

    QHBoxLayout* res = new QHBoxLayout();
    res->addWidget(new QLabel("Min:", this));
    m_minLbl = new QLabel("-", this);
    res->addWidget(m_minLbl);
    res->addWidget(new QLabel("Max:", this));
    m_maxLbl = new QLabel("-", this);
    res->addWidget(m_maxLbl);
    res->addWidget(new QLabel("Med:", this));
    m_medLbl = new QLabel("-", this);
    res->addWidget(m_medLbl);

    v->addLayout(fLay);
    v->addLayout(rLay);
    v->addLayout(cLay);
    v->addWidget(m_loadBtn);
    v->addWidget(m_table);
    v->addWidget(m_calcBtn);
    v->addLayout(res);
    setCentralWidget(c);

    connect(m_chooseBtn, &QPushButton::clicked,
            this, &MainWindow::onChooseFileClicked);
    connect(m_loadBtn, &QPushButton::clicked,
            this, &MainWindow::onLoadDataClicked);
    connect(m_calcBtn, &QPushButton::clicked,
            this, &MainWindow::onCalcClicked);
}

MainWindow::~MainWindow()
{
    doOperations(OP_CLEANUP, nullptr, nullptr, nullptr, nullptr, nullptr);
}

void MainWindow::onChooseFileClicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this, "Выберите CSV-файл", QString(), "CSV Files (*.csv)");
    if (!fn.isEmpty())
        m_fileEdit->setText(fn);
}

void MainWindow::onLoadDataClicked()
{
    QString path = m_fileEdit->text();
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Путь к файлу пуст");
        return;
    }
    if (doOperations(OP_LOAD, (void*)path.toUtf8().constData(),
                     nullptr, nullptr, nullptr, nullptr) != OK) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить CSV");
        return;
    }
    size_t tot, bad;
    doOperations(OP_STATS, &tot, &bad, nullptr, nullptr, nullptr);
    QMessageBox::information(this, "Информация",
                             QString("Строк: %1\nОшибок: %2").arg(tot).arg(bad));
    fillTable(m_regionEdit->text().toUtf8().constData());
}

void MainWindow::fillTable(const char* reg)
{
    m_table->clear();
    m_table->setColumnCount(7);
    m_table->setHorizontalHeaderLabels(
        {"year","region","npg","birth","death","gdw","urban"});

    size_t cnt = 0;
    doOperations(OP_COUNT, &cnt, nullptr, nullptr, nullptr, nullptr);
    m_table->setRowCount(0);

    for (size_t i = 0; i < cnt; ++i) {
        DemographicRecord rec;
        doOperations(OP_AT, &i, &rec, nullptr, nullptr, nullptr);
        if (reg && *reg && strcmp(rec.region, reg) != 0) continue;
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(rec.year));
        m_table->setItem(row, 1, new QTableWidgetItem(rec.region));
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(rec.npg)));
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(rec.birthRate)));
        m_table->setItem(row, 4, new QTableWidgetItem(QString::number(rec.deathRate)));
        m_table->setItem(row, 5, new QTableWidgetItem(QString::number(rec.gdw)));
        m_table->setItem(row, 6, new QTableWidgetItem(QString::number(rec.urbanization)));
    }
}

void MainWindow::onCalcClicked()
{
    bool ok = false;
    int col = m_colEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер колонки");
        return;
    }
    double mn, mx, md;
    doOperations(OP_METRICS,
                 (void*)m_regionEdit->text().toUtf8().constData(),
                 &col,
                 &mn,
                 &mx,
                 &md);
    m_minLbl->setText(QString::number(mn));
    m_maxLbl->setText(QString::number(mx));
    m_medLbl->setText(QString::number(md));
}
