#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <cstring>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    doOperations(&m_ctx, OP_INIT);

    QWidget* central = new QWidget(this);
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
    m_table   = new QTableWidget(this);
    m_calcBtn = new QPushButton("Calculate metrics", this);

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

    vlay->addLayout(fLay);
    vlay->addLayout(rLay);
    vlay->addLayout(cLay);
    vlay->addWidget(m_loadBtn);
    vlay->addWidget(m_table);
    vlay->addWidget(m_calcBtn);
    vlay->addLayout(resLay);
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
    QString fn = QFileDialog::getOpenFileName(this,
                                              "Выберите CSV-файл", {}, "CSV Files (*.csv)");
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

    doOperations(&m_ctx, OP_STATS);
    size_t total = m_ctx.totalLines;
    size_t bad   = m_ctx.errorLines;
    QMessageBox::information(this, "Информация",
                             QString("Всего строк: %1\nОшибок: %2")
                                 .arg((int)total).arg((int)bad));

    fillTable();
}

void MainWindow::fillTable()
{
    m_table->clear();
    m_table->setColumnCount(CSV_FIELDS_COUNT);
    m_table->setHorizontalHeaderLabels(
        {"year","region","npg","birth","death","gdw","urban"});

    size_t cnt = (size_t)doOperations(&m_ctx, OP_COUNT);
    m_table->setRowCount(0);

    const char* filter = nullptr;
    std::string tmp;
    if (!m_regionEdit->text().isEmpty()) {
        tmp = m_regionEdit->text().toStdString();
        filter = tmp.c_str();
    }

    for (size_t i = 0; i < cnt; ++i) {
        const DemographicRecord* r = &m_ctx.data.records[i];
        if (filter && std::strcmp(r->region, filter) != 0)
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
    bool ok = false;
    int col = m_colEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный номер колонки");
        return;
    }

    doOperations(&m_ctx, OP_SET_REGION, m_regionEdit->text().toUtf8().constData());
    doOperations(&m_ctx, OP_SET_COLUMN, nullptr, col);

    if (doOperations(&m_ctx, OP_METRICS) != OK) {
        QMessageBox::warning(this, "Ошибка", "Не удалось вычислить метрики");
        return;
    }

    m_minLbl->setText(QString::number(m_ctx.minValue));
    m_maxLbl->setText(QString::number(m_ctx.maxValue));
    m_medLbl->setText(QString::number(m_ctx.medianValue));
}
