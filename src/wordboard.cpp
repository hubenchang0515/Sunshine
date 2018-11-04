#include "wordboard.h"
#include "ui_wordboard.h"

WordBoard::WordBoard(QSqlDatabase& sql, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WordBoard)
{
    ui->setupUi(this);

    sqlite = sql;
    updateWord();
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint);
    setWindowFlags(windowFlags()|Qt::Tool);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(":/res/icon.png"));
    tray->setToolTip(tr("Sunshine"));
    tray->show();

    menu = new QMenu(this);
    menu->addAction(ui->action_show);
    menu->addAction(ui->action_hide);
    menu->addAction(ui->action_quit);
    tray->setContextMenu(menu);

    connect(ui->action_show, QAction::triggered, this, WordBoard::show);
    connect(ui->action_hide, QAction::triggered, this, WordBoard::hide);
    connect(ui->action_quit, QAction::triggered, qApp, QApplication::quit);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WordBoard::updateWord);
    timer->setSingleShot(false);
    timer->setInterval(15000);
    timer->start();
}

void WordBoard::updateWord(void)
{
    QSqlQuery query(sqlite);
    QString str;
    query.exec("SELECT COUNT(*) FROM words;");
    query.first();
    int n = QRandomGenerator::global()->generate() % query.value(0).toInt();
    query.exec(str.sprintf("SELECT * FROM words LIMIT %d,1;", n));
    query.first();
    ui->english->setText(query.value("english").toString());
    ui->chinese->setText(query.value("chinese").toString());
}

WordBoard::~WordBoard()
{
    delete ui;
}



void WordBoard::mousePressEvent(QMouseEvent *event)
{
    this->dPos = event->pos();//鼠标相对窗口的坐标
}

void WordBoard::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mousePos = event->globalPos();//鼠标相对显示器的坐标
    this->move(mousePos - this->dPos);   //移动窗口
}
