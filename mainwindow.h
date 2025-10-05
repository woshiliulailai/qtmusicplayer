#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void setBackground(const QString &filename);//设置背景
    void setbuttonstyle(QPushButton * button,const QString & filename);//设置按钮样式
    void initbuttons();//初始化按钮
private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_player;
};
#endif // MAINWINDOW_H
