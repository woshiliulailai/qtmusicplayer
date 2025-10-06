#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <Qpalette>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QTimer>
#include <QMainWindow>

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <QMessageBox>

#include <time.h>

#include <QDebug>

#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,m_isShowFlag(false)
    ,m_modle(ORDER_MODE)
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
    QString musicPath="qrc:/music/ljjyuanyvchou.mp3";
    m_player->setSource(QUrl(musicPath));
    m_player->play();
    m_musicListPath=":/music/";
    loadAppointMusicDir(m_musicListPath);
    srand(time(NULL));
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
    setbuttonstyle(ui->modlebutton,":/res/set.png");
    setbuttonstyle(ui->allbutton,":/res/all.png");
    ui->musicList->setStyleSheet(R"(
    QListWidget {
        border: none;
        border-radius: 20px;
        background-color: rgba(255, 255, 255, 0.7);
        font-size: 14px;
        outline: none;
    }
    QListWidget::item {
        border-bottom: 1px solid rgba(0, 0, 0, 0.1);
        padding: 10px 15px;
        background-color: transparent;
    }
    QListWidget::item:hover {
        background-color: rgba(0, 150, 255, 0.1);
        border-radius: 10px;
    }
    QListWidget::item:selected {
        background-color: rgba(0, 150, 255, 0.3);
        border-radius: 10px;
        color: #0066cc;
    }
)");
    ui->musicList->hide();
    connect(ui->modlebutton,&QPushButton::clicked,this,&MainWindow::handleModleSlot);
    connect(ui->startbutton,&QPushButton::clicked,this,&MainWindow::handlePlaySlot);
    connect(ui->nextbutton,&QPushButton::clicked,this,&MainWindow::handleNextSlot);
    connect(ui->prebutton,&QPushButton::clicked,this,&MainWindow::handlePreSlot);
    connect(ui->allbutton,&QPushButton::clicked,this,&MainWindow::handlemusiclistSlot);
}//初始化按钮

void MainWindow::showAnimation(QWidget * window)
{
    QPropertyAnimation animation(window,"pos");
    animation.setDuration(100);
    animation.setStartValue(QPoint(this->width(),0));
    animation.setEndValue(QPoint(this->width()-ui->musicList->width(),0));
    animation.start();
    QEventLoop loop;
    connect(&animation,&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
    loop.exec();
}

void MainWindow::hideAnimation(QWidget *window)
{
    QPropertyAnimation animation(window, "pos");
    animation.setDuration(100);
    animation.setStartValue(QPoint(this->width()-ui->musicList->width(), 0));
    animation.setEndValue(QPoint(this->width(), 0));
    animation.start();
    QEventLoop loop;
    connect(&animation, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
    loop.exec();
}
void MainWindow::handlemusiclistSlot()
{
    if(m_isShowFlag==false)
    {
        ui->musicList->show();
        showAnimation(ui->musicList);
        m_isShowFlag=true;
    }
    else{
        hideAnimation(ui->musicList);
        ui->musicList->hide();
        m_isShowFlag=false;
    }
}

void MainWindow::startPlayMusic()
{
    //QString musicName=ui->musicList->currentItem()->text();
    //QString absMusicPath="qrc"+m_musicListPath+musicName+".mp3";
    //m_player->setSource(QUrl(absMusicPath));
    QTimer::singleShot(1000, this, [this]() {
        QString musicName=ui->musicList->currentItem()->text();
        QString absMusicPath="qrc"+m_musicListPath+musicName+".mp3";
        m_player->setSource(QUrl(absMusicPath));
        m_player->play();
    });
    handlePlaySlot();
}
void MainWindow::handlePreSlot()
{
    int currentRow=ui->musicList->currentRow();
    int preRow=0;
    if(m_modle==ORDER_MODE)
    {
        preRow=currentRow-1;
        if(preRow<0)
        {
            preRow=ui->musicList->count()-1;
        }
    }
    else if(m_modle==RANDOM_MODE)
    {
        int cnt=0;
        do
        {
            preRow=rand()%ui->musicList->count();
            cnt++;
        }while((currentRow==preRow)&&(cnt<=3));

    }
    else if(m_modle==CIRCLE_MODE)
    {
        preRow=currentRow;
    }
    ui->musicList->setCurrentRow(preRow);
    startPlayMusic();
}
void MainWindow::handleNextSlot()
{
    int currentRow=ui->musicList->currentRow();
    int nextRow=0;
    if(m_modle==ORDER_MODE)
    {
        nextRow=(currentRow+1)%ui->musicList->count();
    }
    else if(m_modle==RANDOM_MODE)
    {
        int cnt=0;
        do
        {
            nextRow=rand()%ui->musicList->count();
            cnt++;
        }while((currentRow==nextRow)&&(cnt<=3));

    }
    else if(m_modle==CIRCLE_MODE)
    {
        nextRow=currentRow;
    }
    ui->musicList->setCurrentRow(nextRow);
    startPlayMusic();
}
void MainWindow::handlePlaySlot(){
    if(m_player->playbackState()==QMediaPlayer::PlayingState)
    {
        m_player->pause();
        ui->startbutton->setIcon(QIcon(":/res/start.png"));
    }
    else
    {
        m_player->play();
        ui->startbutton->setIcon(QIcon(":/res/stop.png"));
    }
}

void MainWindow::setBackground(const QString &filename){
    QPixmap pixmap(filename);
    QSize windowSize=this->size();
    QPixmap scalePixmap = pixmap.scaled(windowSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Window,QBrush(scalePixmap));
    this->setPalette(palette);

}

void MainWindow::loadAppointMusicDir(const QString & filepath)
{
    QDir dir(filepath);
    if(dir.exists()==false)
    {
        QMessageBox::warning(this,"文件夹","文件夹打开失败");
        return;
    }
    QFileInfoList fileList=dir.entryInfoList(QDir::Files);
    for(auto it = fileList.constBegin(); it != fileList.constEnd(); ++it) {
        if(it->suffix() == "mp3") {
            ui->musicList->addItem(it->baseName());
        }
    }
    ui->musicList->setCurrentRow(1);
}
void MainWindow::handleModleSlot()
{
    if(m_modle==ORDER_MODE)
    {
        m_modle=RANDOM_MODE;
        ui->modlebutton->setIcon(QIcon(":/res/full.png"));
    }
    else if(m_modle==RANDOM_MODE)
    {
        m_modle=CIRCLE_MODE;
        ui->modlebutton->setIcon(QIcon(":/res/recycle.png"));
    }
    else if(m_modle==CIRCLE_MODE)
    {
        m_modle=ORDER_MODE;
        ui->modlebutton->setIcon(QIcon(":/res/set.png"));
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
