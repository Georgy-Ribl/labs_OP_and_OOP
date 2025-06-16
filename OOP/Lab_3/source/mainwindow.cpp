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

    display = new QLineEdit;
    display->setReadOnly(true);
    display->setMinimumHeight(50);
    QFont dispFont = display->font();
    dispFont.setPointSize(16);
    display->setFont(dispFont);
    mainV->addWidget(display);

    auto *hbox = new QHBoxLayout;
    hbox->setSpacing(12);
    mainV->addLayout(hbox);

    auto *leftGrid = new QGridLayout;
    leftGrid->setSpacing(6);
    auto mkSci = [&](const QString &txt, int r, int c){
        auto *b = new QPushButton(txt);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setStyleSheet("background:#e0e0e0; color:#000; border-radius:4px;");
        QFont f = b->font(); f.setPointSize(12); b->setFont(f);
        leftGrid->addWidget(b, r, c);
        connect(b, &QPushButton::clicked, this, [=](){ onButtonClicked(txt); });
        return b;
    };
    // mkSci("MC",0,0); mkSci("MR",0,1); mkSci("M+",0,2); mkSci("M-",0,3);
    mkSci("sin",1,0); mkSci("cos",1,1); mkSci("tg",1,2); mkSci("ctg",1,3);
    mkSci("ln",2,0); mkSci("log",2,1); mkSci("exp",2,2); mkSci("sqrt",2,3);
    mkSci("pi",3,0); mkSci("e",3,1); mkSci("(",3,2); mkSci(")",3,3);
    hbox->addLayout(leftGrid,1);

    auto *rightGrid = new QGridLayout;
    rightGrid->setSpacing(6);
    auto mkBtn = [&](const QString &txt, int r, int c,
                     int rs=1,int cs=1,
                     const QString &bg="#ffffff", const QString &fg="#000000"){
        auto *b=new QPushButton(txt);
        b->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        b->setStyleSheet(QString("background:%1; color:%2; border-radius:4px;")
                             .arg(bg).arg(fg));
        QFont f=b->font(); f.setPointSize(14); b->setFont(f);
        rightGrid->addWidget(b,r,c,rs,cs);
        connect(b, &QPushButton::clicked, this, [=](){ onButtonClicked(txt); });
        return b;
    };
    const QString opBg="#888888", opFg="#ffffff", delBg="#ffcc00", cBg="#ff4444", eqBg="#1e90ff";
    mkBtn("7",0,0); mkBtn("8",0,1); mkBtn("9",0,2); mkBtn("/",0,3,1,1,opBg,opFg);
    mkBtn("4",1,0); mkBtn("5",1,1); mkBtn("6",1,2); mkBtn("*",1,3,1,1,opBg,opFg);
    mkBtn("1",2,0); mkBtn("2",2,1); mkBtn("3",2,2); mkBtn("-",2,3,1,1,opBg,opFg);
    mkBtn("0",3,0,1,2); mkBtn(".",3,2); mkBtn("+",3,3,1,1,opBg,opFg);
    /*mkBtn("!",4,0);*/ mkBtn("←",4,1,1,1,delBg,"#000000");
    mkBtn("C",4,2,1,1,cBg,"#ffffff"); mkBtn("=",4,3,1,1,eqBg,"#ffffff");
    hbox->addLayout(rightGrid,2);
}

void MainWindow::onButtonClicked(const QString &t) {
    if      (t=="exp")   facade.input("10^");
    else if (t=="sin")   facade.input("sin(");
    else if (t=="cos")   facade.input("cos(");
    else if (t=="tg")   facade.input("tg(");
    else if (t=="ctg")   facade.input("ctg(");
    else if (t=="ln")   facade.input("ln(");
    else if (t=="log")   facade.input("log(");
    else if (t=="sqrt")   facade.input("sqrt(");
    else if (t=="MC")    facade.memoryClear();
    else if (t=="MR")    facade.memoryRecall();
    else if (t=="M+")    facade.memoryAdd();
    else if (t=="M-")    facade.memorySub();
    else if (t=="=")     facade.evaluate();
    else if (t=="C")     facade.input("C");
    else if (t=="←")     facade.input("Del");
    else                  facade.input(t.toLower().toStdString());
    display->setText(QString::fromStdString(facade.getExpression()));
}
