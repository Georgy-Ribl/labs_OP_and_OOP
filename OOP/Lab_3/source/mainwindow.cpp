#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSizePolicy>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *cw = new QWidget(this);
    setCentralWidget(cw);

    auto *mainV = new QVBoxLayout(cw);
    mainV->setContentsMargins(10,10,10,10);
    mainV->setSpacing(8);

    display_ = new QLineEdit;
    display_->setReadOnly(true);
    display_->setMinimumHeight(40);
    QFont df = display_->font(); df.setPointSize(14);
    display_->setFont(df);
    mainV->addWidget(display_);

    auto *grid = new QGridLayout;
    grid->setSpacing(6);

    auto mk = [&](const QString &txt, int r, int c,
                  int rs=1, int cs=1,
                  const QString &bg="#ffffff",
                  const QString &fg="#000000")
    {
        auto *b = new QPushButton(txt);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setStyleSheet(
            QString("background:%1; color:%2; border-radius:4px;")
                .arg(bg).arg(fg)
            );
        QFont bf = b->font(); bf.setPointSize(12); b->setFont(bf);
        grid->addWidget(b, r, c, rs, cs);
        connect(b, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
        return b;
    };

    const QString opBg   = "#888888";
    const QString opFg   = "#ffffff";
    const QString cBg    = "#ff4444";
    const QString delBg  = "#ffcc00";
    const QString eqBg   = "#1e90ff";

    mk("C",    0,0,1,1, cBg,   "#ffffff");
    mk("Del",  0,1,1,1, delBg, "#000000");
    mk("(",    0,2);
    mk(")",    0,3);
    mk("^",    0,4,1,1, opBg, opFg);

    mk("7", 1,0);
    mk("8", 1,1);
    mk("9", 1,2);
    mk("/", 1,4,1,1, opBg, opFg);

    mk("4", 2,0);
    mk("5", 2,1);
    mk("6", 2,2);
    mk("*", 2,4,1,1, opBg, opFg);

    mk("1", 3,0);
    mk("2", 3,1);
    mk("3", 3,2);
    mk("-", 3,4,1,1, opBg, opFg);

    mk("0",   4,0);
    mk(".",   4,1);
    mk("=",   4,2,1,2, eqBg, "#ffffff");
    mk("+",   4,4,1,1, opBg, opFg);

    mainV->addLayout(grid);
}

void MainWindow::onButtonClicked() {
    auto *b = qobject_cast<QPushButton*>(sender());
    QString t = b->text();

    if      (t == "C")    facade_.input("C");
    else if (t == "Del")  facade_.input("Del");
    else if (t == "=")    facade_.evaluate();
    else                  facade_.input(t.toStdString());

    display_->setText(QString::fromStdString(facade_.getExpression()));
}
