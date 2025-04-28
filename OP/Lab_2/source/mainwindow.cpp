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
    initOperationsContext(&m_ctx);

    auto* central = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(central);

    auto* fileLayout = new QHBoxLayout;
    m_chooseButton   = new QPushButton(tr("Выбрать файл"), this);
    m_fileLineEdit   = new QLineEdit(this);
    fileLayout->addWidget(m_chooseButton);
    fileLayout->addWidget(m_fileLineEdit);

    auto* regionLayout = new QHBoxLayout;
    regionLayout->addWidget(new QLabel(tr("Регион:"), this));
    m_regionLineEdit = new QLineEdit(this);
    regionLayout->addWidget(m_regionLineEdit);

    auto* columnLayout = new QHBoxLayout;
    columnLayout->addWidget(new QLabel(tr("Колонка:"), this));
    m_columnLineEdit = new QLineEdit(this);
    columnLayout->addWidget(m_columnLineEdit);

    m_loadButton   = new QPushButton(tr("Load data"), this);
    m_tableWidget  = new QTableWidget(this);

    m_calcButton   = new QPushButton(tr("Calculate metrics"), this);

    auto* resultLayout = new QHBoxLayout;
    resultLayout->addWidget(new QLabel(tr("Min:"), this));
    m_minLabel    = new QLabel("-", this);
    resultLayout->addWidget(m_minLabel);
    resultLayout->addWidget(new QLabel(tr("Max:"), this));
    m_maxLabel    = new QLabel("-", this);
    resultLayout->addWidget(m_maxLabel);
    resultLayout->addWidget(new QLabel(tr("Med:"), this));
    m_medianLabel = new QLabel("-", this);
    resultLayout->addWidget(m_medianLabel);

    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(regionLayout);
    mainLayout->addLayout(columnLayout);
    mainLayout->addWidget(m_loadButton);
    mainLayout->addWidget(m_tableWidget);
    mainLayout->addWidget(m_calcButton);
    mainLayout->addLayout(resultLayout);

    setCentralWidget(central);

    connect(m_chooseButton, &QPushButton::clicked,
            this, &MainWindow::onChooseFileClicked);
    connect(m_loadButton, &QPushButton::clicked,
            this, &MainWindow::onLoadDataClicked);
    connect(m_calcButton, &QPushButton::clicked,
            this, &MainWindow::onCalculateMetricsClicked);
}

MainWindow::~MainWindow()
{
    cleanupOperationsContext(&m_ctx);
}

void MainWindow::onChooseFileClicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this, tr("Выберите CSV-файл"), QString(), tr("CSV Files (*.csv)"));
    if (!fn.isEmpty()) {
        m_fileLineEdit->setText(fn);
    }
}

void MainWindow::onLoadDataClicked()
{
    QString path = m_fileLineEdit->text();
    if (path.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Путь к файлу пуст"));
        return;
    }

    setFileName(&m_ctx, path.toUtf8().constData());
    int status = loadData(&m_ctx);
    if (status != OK) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось загрузить CSV"));
        return;
    }

    size_t total = 0, bad = 0;
    getLoadStats(&m_ctx, &total, &bad);

    QMessageBox::information(
        this,
        tr("Информация"),
        tr("Всего строк: %1\nОшибок: %2")
            .arg((int)total)
            .arg((int)bad)
        );

    fillTable();
}

void MainWindow::fillTable()
{
    m_tableWidget->clear();
    m_tableWidget->setColumnCount(CSV_FIELDS_COUNT);
    m_tableWidget->setHorizontalHeaderLabels(
        QStringList{"year","region","npg","birth","death","gdw","urban"});

    size_t count = countRecords(&m_ctx);
    m_tableWidget->setRowCount(0);

    std::string filter = m_regionLineEdit->text().toStdString();
    for (size_t i = 0; i < count; ++i) {
        const DemographicRecord* r = getRecordAt(&m_ctx, i);
        if (!filter.empty() &&
            std::strcmp(r->region, filter.c_str()) != 0)
        {
            continue;
        }
        int row = m_tableWidget->rowCount();
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(r->year));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(r->region));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(r->npg)));
        m_tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(r->birthRate)));
        m_tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(r->deathRate)));
        m_tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(r->gdw)));
        m_tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(r->urbanization)));
    }
}

void MainWindow::onCalculateMetricsClicked()
{
    bool ok = false;
    int col = m_columnLineEdit->text().toInt(&ok);
    if (!ok || col < COL_NPG || col > COL_URBANIZATION) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Неверный номер колонки"));
        return;
    }

    setFilterRegion(&m_ctx, m_regionLineEdit->text().toUtf8().constData());
    setColumnIndex(&m_ctx, col);

    int status = computeMetrics(&m_ctx);
    if (status != OK) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось вычислить метрики"));
        return;
    }

    double mn, mx, md;
    getMetrics(&m_ctx, &mn, &mx, &md);

    m_minLabel->setText(QString::number(mn));
    m_maxLabel->setText(QString::number(mx));
    m_medianLabel->setText(QString::number(md));
}
