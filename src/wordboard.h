#ifndef WORDBOARD_H
#define WORDBOARD_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>
#include <QRandomGenerator>
#include <QTimer>
#include <QMenu>

namespace Ui {
class WordBoard;
}

class WordBoard : public QDialog
{
    Q_OBJECT

public:
    explicit WordBoard(QSqlDatabase& sql, QWidget *parent = nullptr);
    ~WordBoard();

public slots:
    void updateWord(void);


private:
    Ui::WordBoard *ui;
    QPoint dPos;
    QSqlDatabase sqlite;
    QSystemTrayIcon* tray;
    QTimer* timer;
    QMenu* menu;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // WORDBOARD_H
