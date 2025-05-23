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
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    doOperations(&m_ctx, OP_INIT);

    QWidget* central = new QWidget(this);
    QVBoxLayout* vlay = new QVBoxLayout(central);

    QHBoxLayout* fLay = new QHBoxLayout;
    m_chooseBtn = new QPushButton("Выбрать файл", this);
    m_fileEdit  = new QLineEdit(this);
    fLay->addWidget(m_chooseBtn);
    fLay->addWidget(m_fileEdit);

    QHBoxLayout* rLay = new QHBoxLayout;
    rLay->addWidget(new QLabel("Регион:", this));
    m_regionEdit = new QLineEdit(this);
    rLay->addWidget(m_regionEdit);

    QHBoxLayout* cLay = new QHBoxLayout;
    cLay->addWidget(new QLabel("Колонка:", this));
    m_colEdit = new QLineEdit(this);
    cLay->addWidget(m_colEdit);

    m_loadBtn = new QPushButton("Load data", this);
    m_calcBtn = new QPushButton("Calculate and Draw", this);
    m_table   = new QTableWidget(this);

    QHBoxLayout* resLay = new QHBoxLayout;
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

    connect(m_chooseBtn, &QPushButton::clicked, this, &MainWindow::onChooseFileClicked);
    connect(m_loadBtn,   &QPushButton::clicked, this, &MainWindow::onLoadDataClicked);
    connect(m_calcBtn,   &QPushButton::clicked, this, &MainWindow::onCalculateMetricsClicked);
}

MainWindow::~MainWindow()
{
    doOperations(&m_ctx, OP_CLEANUP);
}

void MainWindow::onChooseFileClicked()
{
    QString fn = QFileDialog::getOpenFileName(this, "Выберите CSV-файл", QString(), "CSV Files (*.csv)");
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
    doOperations(&m_ctx, OP_SET_FILE, path.toUtf8().constData());
    if (doOperations(&m_ctx, OP_LOAD) != OK) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить CSV");
        return;
    }
    fillTable();
}

void MainWindow::fillTable()
{
    m_table->clear();
    m_table->setColumnCount(7);
    m_table->setHorizontalHeaderLabels({"year","region","npg","birth","death","gdw","urban"});
    m_table->setRowCount(0);

    size_t cnt = doOperations(&m_ctx, OP_COUNT);
    for (size_t i = 0; i < cnt; ++i) {
        const DemographicRecord* r = opAt(&m_ctx, i);
        if (!r) continue;
        if (!m_regionEdit->text().isEmpty() &&
            strcmp(r->region, m_regionEdit->text().toUtf8().constData()) != 0)
            continue;

        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(r->year));
        m_table->setItem(row, 1, new QTableWidgetItem(r->region));
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(r->npg)));
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(r->birthRate)));
        m_table->setItem(row, 4, new QTableWidgetItem(QString::number(r->deathRate)));
        m_table->setItem(row, 5, new QTableWidgetItem(QString::number(r->gdw)));
        m_table->setItem(row, 6, new QTableWidgetItem(QString::number(r->urbanization)));
    }
}

void MainWindow::onCalculateMetricsClicked()
{
    bool ok;
    int col = m_colEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер колонки");
        return;
    }
    if (col < 0 || col > 6) {
        QMessageBox::warning(this, "Ошибка", "Номер колонки вне диапазона (0-6)");
        return;
    }

    doOperations(&m_ctx, OP_SET_REGION,  m_regionEdit->text().toUtf8().constData());
    doOperations(&m_ctx, OP_SET_COLUMN, nullptr, col);
    if (doOperations(&m_ctx, OP_METRICS) != OK) {
        QMessageBox::warning(this, "Ошибка", "Не удалось вычислить метрики");
        return;
    }

    double mn = m_ctx.minValue;
    double mx = m_ctx.maxValue;
    double md = m_ctx.medianValue;

    m_minLbl->setText(QString::number(mn));
    m_maxLbl->setText(QString::number(mx));
    m_medLbl->setText(QString::number(md));

    m_yearsCache.clear();
    m_valsCache.clear();

    size_t cnt2 = doOperations(&m_ctx, OP_COUNT);
    for (size_t i = 0; i < cnt2; ++i) {
        const DemographicRecord* r = opAt(&m_ctx, i);
        if (!r) continue;
        if (!m_regionEdit->text().isEmpty() &&
            strcmp(r->region, m_regionEdit->text().toUtf8().constData()) != 0)
            continue;
        m_yearsCache.push_back(atoi(r->year));
        m_valsCache.push_back(get_field(r, col));
    }

    if (m_yearsCache.empty() || m_valsCache.empty()) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для построения графика");
        return;
    }

    std::vector<std::pair<int,double>> combined;
    for (size_t i=0; i<m_yearsCache.size(); ++i)
        combined.emplace_back(m_yearsCache[i], m_valsCache[i]);
    std::sort(combined.begin(), combined.end(), [](auto& a, auto& b) { return a.first < b.first; });
    for (size_t i=0; i<combined.size(); ++i) {
        m_yearsCache[i] = combined[i].first;
        m_valsCache[i] = combined[i].second;
    }

    m_chart->setData(&m_yearsCache, &m_valsCache, mn, mx, md);
}
