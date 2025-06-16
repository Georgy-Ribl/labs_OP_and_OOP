#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSizePolicy>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    setCentralWidget(central);

    auto *mainV = new QVBoxLayout(central);
    mainV->setContentsMargins(8,8,8,8);
    mainV->setSpacing(8);

    // Display
    display = new QLineEdit;
    display->setReadOnly(true);
    display->setMinimumHeight(50);
    QFont dispFont = display->font(); dispFont.setPointSize(16);
    display->setFont(dispFont);
    mainV->addWidget(display);

    // Panels container
    auto *hbox = new QHBoxLayout;
    hbox->setSpacing(12);
    mainV->addLayout(hbox);

    // --- Left grid: scientific + pi + parentheses + EXP key ---
    auto *leftGrid = new QGridLayout;
    leftGrid->setSpacing(6);

    auto mkSci = [&](const QString &txt, int r, int c){
        QPushButton *b = new QPushButton(txt);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setStyleSheet("background:#e0e0e0; color:#000; border-radius:4px;");
        QFont f = b->font(); f.setPointSize(12); b->setFont(f);
        leftGrid->addWidget(b, r, c);
        connect(b, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
        return b;
    };

    // Row 0
    mkSci("sin",  0,0);
    mkSci("cos",  0,1);
    mkSci("tg",   0,2);
    mkSci("ctg",  0,3);
    // Row 1
    mkSci("ln",   1,0);
    mkSci("log",  1,1);
    mkSci("exp",  1,2);  // EXP: will insert "10^"
    mkSci("sqrt", 1,3);
    // Row 2
    mkSci("pi",   2,0);
    mkSci("e",    2,1);
    mkSci("(",    2,2);
    mkSci(")",    2,3);

    hbox->addLayout(leftGrid, 1);

    // --- Right grid: digits & basic ops ---
    auto *rightGrid = new QGridLayout;
    rightGrid->setSpacing(6);

    auto mkBtn = [&](const QString &txt, int r, int c,
                     int rs=1, int cs=1,
                     const QString &bg="#ffffff",
                     const QString &fg="#000000"){
        QPushButton *b = new QPushButton(txt);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setStyleSheet(QString("background:%1; color:%2; border-radius:4px;")
                             .arg(bg).arg(fg));
        QFont f = b->font(); f.setPointSize(14); b->setFont(f);
        rightGrid->addWidget(b, r, c, rs, cs);
        connect(b, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
        return b;
    };

    QString opBg = "#888888", opFg = "#ffffff";
    QString clearBg = "#ff4444", equalBg = "#1e90ff";

    // Row 0
    mkBtn("7",0,0); mkBtn("8",0,1); mkBtn("9",0,2); mkBtn("/",0,3,1,1,opBg,opFg);
    // Row 1
    mkBtn("4",1,0); mkBtn("5",1,1); mkBtn("6",1,2); mkBtn("*",1,3,1,1,opBg,opFg);
    // Row 2
    mkBtn("1",2,0); mkBtn("2",2,1); mkBtn("3",2,2); mkBtn("-",2,3,1,1,opBg,opFg);
    // Row 3
    mkBtn("0",3,0,1,2); mkBtn(".",3,2); mkBtn("+",3,3,1,1,opBg,opFg);
    // Row 4
    mkBtn("!",4,0);
    mkBtn("←",4,1,1,1,"#ffcc00","#000000");
    mkBtn("C",4,2,1,1,clearBg,"#ffffff");
    mkBtn("=",4,3,1,1,equalBg,"#ffffff");

    hbox->addLayout(rightGrid, 2);
}

void MainWindow::onButtonClicked() {
    auto *b = qobject_cast<QPushButton*>(sender());
    QString t = b->text();

    if (t == "exp") {
        // EXP key: raise 10 to the next number
        facade.input("10^");
    }
    else if (t == "=") {
        facade.evaluate();
    }
    else if (t == "C") {
        facade.input("C");
    }
    else if (t == "←") {
        facade.input("Del");
    }
    else {
        // digits, operators, pi, e, parentheses, factorial, ln, log, sqrt, sin/cos/tg/ctg
        facade.input(t.toLower().toStdString());
    }

    display->setText(QString::fromStdString(facade.getExpression()));
}
