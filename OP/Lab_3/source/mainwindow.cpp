#include "mainwindow.h"
#include "entrypoint.h"
#include "operations.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <vector>
#include <cstdlib>
#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    doOperations(OP_INIT);

    auto* central = new QWidget(this);
    auto* vlay = new QVBoxLayout(central);

    auto* fLay = new QHBoxLayout;
    m_chooseBtn = new QPushButton("Выбрать файл", this);
    m_fileEdit  = new QLineEdit(this);
    fLay->addWidget(m_chooseBtn);
    fLay->addWidget(m_fileEdit);

    auto* rLay = new QHBoxLayout;
    rLay->addWidget(new QLabel("Регион:", this));
    m_regionEdit = new QLineEdit(this);
    rLay->addWidget(m_regionEdit);

    auto* cLay = new QHBoxLayout;
    cLay->addWidget(new QLabel("Колонка:", this));
    m_colEdit = new QLineEdit(this);
    cLay->addWidget(m_colEdit);

    m_loadBtn = new QPushButton("Load data", this);
    m_calcBtn = new QPushButton("Calculate and Draw", this);
    m_table   = new QTableWidget(this);

    auto* resLay = new QHBoxLayout;
    resLay->addWidget(new QLabel("Min:", this));
    m_minLbl = new QLabel("-", this);
    resLay->addWidget(m_minLbl);
    resLay->addWidget(new QLabel("Max:", this));
    m_maxLbl = new QLabel("-", this);
    resLay->addWidget(m_maxLbl);
    resLay->addWidget(new QLabel("Med:", this));
    m_medLbl = new QLabel("-", this);
    resLay->addWidget(m_medLbl);

    m_chart = new ChartWidget(this);
    m_chart->setMinimumHeight(200);

    vlay->addLayout(fLay);
    vlay->addLayout(rLay);
    vlay->addLayout(cLay);
    vlay->addWidget(m_loadBtn);
    vlay->addWidget(m_table);
    vlay->addWidget(m_calcBtn);
    vlay->addLayout(resLay);
    vlay->addWidget(m_chart);

    setCentralWidget(central);

    connect(m_chooseBtn, &QPushButton::clicked,
            this, &MainWindow::onChooseFileClicked);
    connect(m_loadBtn, &QPushButton::clicked,
            this, &MainWindow::onLoadDataClicked);
    connect(m_calcBtn, &QPushButton::clicked,
            this, &MainWindow::onCalculateMetricsClicked);
}

MainWindow::~MainWindow() {
    doOperations(OP_CLEANUP);
}

void MainWindow::onChooseFileClicked() {
    QString fn = QFileDialog::getOpenFileName(
        this, "Выберите CSV-файл", QString(), "CSV Files (*.csv)");
    if (!fn.isEmpty()) m_fileEdit->setText(fn);
}

void MainWindow::onLoadDataClicked() {
    QString path = m_fileEdit->text();
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Путь к файлу пуст");
        return;
    }
    setOpFileName(path.toUtf8().constData());
    if (doOperations(OP_LOAD) != OK) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить CSV");
        return;
    }
    fillTable();
}

void MainWindow::fillTable() {
    m_table->clear();
    m_table->setColumnCount(7);
    m_table->setHorizontalHeaderLabels(
        {"year","region","npg","birth","death","gdw","urban"});
    m_table->setRowCount(0);
    for (size_t i=0; i<opCount(); ++i) {
        const DemographicRecord* r = opAt(i);
        if (!m_regionEdit->text().isEmpty() &&
            strcmp(r->region, m_regionEdit->text().toUtf8().constData())!=0)
            continue;
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row,0,new QTableWidgetItem(r->year));
        m_table->setItem(row,1,new QTableWidgetItem(r->region));
        m_table->setItem(row,2,new QTableWidgetItem(
            QString::number(r->npg)));
        m_table->setItem(row,3,new QTableWidgetItem(
            QString::number(r->birthRate)));
        m_table->setItem(row,4,new QTableWidgetItem(
            QString::number(r->deathRate)));
        m_table->setItem(row,5,new QTableWidgetItem(
            QString::number(r->gdw)));
        m_table->setItem(row,6,new QTableWidgetItem(
            QString::number(r->urbanization)));
    }
}

void MainWindow::onCalculateMetricsClicked() {
    bool ok;
    int col = m_colEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер колонки");
        return;
    }
    setOpFilterRegion(m_regionEdit->text().toUtf8().constData());
    setOpColumn(col);
    if (doOperations(OP_METRICS) != OK) {
        QMessageBox::warning(this, "Ошибка", "Не удалось вычислить метрики");
        return;
    }
    double mn, mx, md;
    getOpMetrics(&mn, &mx, &md);
    m_minLbl->setText(QString::number(mn));
    m_maxLbl->setText(QString::number(mx));
    m_medLbl->setText(QString::number(md));

    std::vector<int> years;
    std::vector<double> vals;
    for (size_t i=0; i<opCount(); ++i) {
        const DemographicRecord* r = opAt(i);
        if (!m_regionEdit->text().isEmpty() &&
            strcmp(r->region, m_regionEdit->text().toUtf8().constData())!=0)
            continue;
        years.push_back(atoi(r->year));
        vals.push_back(get_field(r, col));
    }
    m_chart->setData(years, vals, mn, mx, md);
}
