#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->send->setDisabled(true);
    ui->message->setDisabled(true);
    ui->subscribe->setDisabled(true);
    ui->topic->setDisabled(true);

    ui->lineIP->setText(QString("127.0.0.1"));
    ui->linePort->setText(QString("1883"));
    ui->topic->setText(QString("debug"));
    ui->lineID->setText(QString("2222"));

    ui->ConStatus->setText(QString("off"));

    lib_init();

    connect (ui->connect, SIGNAL(clicked()), this, SLOT(connectPressed()));
    connect (ui->send, SIGNAL(clicked()), this, SLOT(sendPressed()));
    connect (ui->subscribe, SIGNAL(clicked()), this, SLOT(subscribePressed()));
}

void MainWindow::showMessage(QString message)
{
    ui->text->setText(message + tr("\n") + ui->text->text());
}

void MainWindow::connectPressed()
{
    QByteArray host = ui->lineIP->text().toLocal8Bit();
    QByteArray id = ui->lineID->text().toLocal8Bit();

    int port = 0;
    port = ui->linePort->text().toInt();
    if (!port)
    {
        ui->linePort->clear();
        return ;
    }
    ui->connect->setDisabled(true);

    mosq = new qtmosq(id, false);
    connect (mosq, SIGNAL(connectEnable()), this, SLOT(connectEnabled()));
    connect (mosq, SIGNAL(subscribed()), this ,SLOT(subscribed()));
    connect (mosq, SIGNAL(unsubscribed()), this ,SLOT(unsubscribed()));
    connect (mosq, SIGNAL(connected()), this, SLOT(connected()));
    connect (mosq, SIGNAL(disconnected(int)), this, SLOT(disconnected(int)));
    connect (mosq, SIGNAL(messageSent(bool)), this, SLOT(setMessageStatus(bool)));
    connect (mosq, SIGNAL(messageReceived(QString)), this, SLOT(showMessage(QString)));

    // last will
    currentTopic = ui->topic->text();
    QByteArray topic = currentTopic.toLocal8Bit();
    QString dead = "Am I dead now?";
    QByteArray will = dead.toLocal8Bit();
    mosq->will_set(topic.data(), will.length(), will.data(), 0, true);


    int rc = mosq->connect_async(host.data(), port);
    if (rc == MOSQ_ERR_ERRNO) {
        QString txt = "Errno="+QString::number(errno);
        showMessage(txt);
    }

    if (mosq->loop_start() != MOSQ_ERR_SUCCESS)
      ui->message->setText("No loop");
    else
      ui->message->setText("loop");
}

void MainWindow::subscribePressed()
{
    setMessageStatus(false);
    currentTopic = ui->topic->text();
    QByteArray topic = currentTopic.toLocal8Bit();

    mosq->subscribe(mosq->getMID(), topic.data(), 2);
}

void MainWindow::sendPressed()
{
    setMessageStatus(false);
    //QByteArray payload = QString("[" + ui->lineID->text() + "] " + ui->message->text()).toLocal8Bit();
    QByteArray payload = QString( ui->message->text()).toLocal8Bit();
    currentTopic = ui->topic->text();
    QByteArray topic = currentTopic.toLocal8Bit();

    if (!subed.contains(currentTopic)) mosq->subscribe(mosq->getMID(), topic.data(), 2);
    mosq->publish(mosq->getMID(), topic.data(), payload.size(), payload.data(), 2, false);
}

void MainWindow::connected()
{
    setMessageStatus(true);
    ui->ConStatus->setText(QString("on"));
}

void MainWindow::disconnected(int rc) {
  setMessageStatus(false);
  ui->ConStatus->setText(QString::number(rc));
}

void MainWindow::setMessageStatus(bool on)
{
    ui->message->setEnabled(on);
    ui->send->setEnabled(on);
    ui->subscribe->setEnabled(on);
    ui->topic->setEnabled(on);

    ui->lineID->setDisabled(on);
    ui->lineIP->setDisabled(on);
    ui->linePort->setDisabled(on);

}

void MainWindow::subscribed()
{
    ui->text->setText(QString("Topic ") + currentTopic + QString(" has been subscribed.\n" + ui->text->text()));
    subed.append(currentTopic);
    setMessageStatus(true);
}

void MainWindow::unsubscribed()
{
  ui->topic->setText("gone");
}
void MainWindow::connectEnabled() {ui->connect->setEnabled(true);}

MainWindow::~MainWindow()
{
    mosq->mosquittopp::disconnect();
    mosq->loop_stop();
    lib_cleanup();
    delete mosq;
    delete ui;
}



void MainWindow::on_pushButton_released()
{
//  mosq->loop(15000,1);

//  return;

  QFile file("/home/master/standard");
  if(!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(0,"error",file.errorString());
  }
  QTextStream out(&file);
  QString dd=out.readAll();
  //qDebug() << "im here:" << dd << "\ndone" ;

  setMessageStatus(false);
  QByteArray payload = dd.toLocal8Bit();
  currentTopic = ui->topic->text();
  QByteArray topic = currentTopic.toLocal8Bit();
  if (!subed.contains(currentTopic))
      mosq->subscribe(mosq->getMID(), topic.data(), 2);
  mosq->publish(mosq->getMID(), topic.data(), payload.size(), payload.data(), 2, false);
}

void MainWindow::on_Unsubscribe_released()
{
  currentTopic = ui->topic->text();

  int has = subed.lastIndexOf(currentTopic);
  if (has == -1) {
    showMessage("id not found");
    return;
  }

//  mosq->
  subed.removeAt(has);

}
