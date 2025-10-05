#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <Qpalette>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("一个朴实无华的播放器");
    m_player=new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.8);
    setBackground(":/res/background5.png");
    setFixedSize(this->width(),this->height());
    initbuttons();
    QString musicPath="qrc:/res/song1.mp3";
    m_player->setSource(QUrl(musicPath));
    m_player->play();
}


void MainWindow::setbuttonstyle(QPushButton * button,const QString & filename)
{
    button->setFixedSize(50,50);
    button->setIcon(QIcon(filename));
    button->setIconSize(QSize(ui->prebutton->width(),ui->prebutton->height()));
    button->setStyleSheet("background-color:transparent;border: none;");
}//设置按钮样式
void MainWindow::initbuttons(){
    setbuttonstyle(ui->prebutton,":/res/pre.png");
    setbuttonstyle(ui->startbutton,":/res/start.png");
    setbuttonstyle(ui->nextbutton,":/res/next.png");
    setbuttonstyle(ui->modlebutton,":/res/recycle.png");
    setbuttonstyle(ui->allbutton,":/res/all.png");

}//初始化按钮
void MainWindow::setBackground(const QString &filename){
    QPixmap pixmap(filename);
    QSize windowSize=this->size();
    QPixmap scalePixmap = pixmap.scaled(windowSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Window,QBrush(scalePixmap));
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}
