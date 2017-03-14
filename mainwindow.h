#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtmosq.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    qtmosq* mosq = NULL;
    QStringList subed;
    QString currentTopic;
    Ui::MainWindow *ui;

private slots:
    void setMessageStatus(bool on);
    void connectPressed();
    void sendPressed();
    void connectEnabled();
    void subscribePressed();
    void subscribed();
    void unsubscribed();
    void connected();
    void disconnected(int rc);
    void showMessage(QString);
    void on_pushButton_released();
    void on_Unsubscribe_released();
};

#endif // MAINWINDOW_H
