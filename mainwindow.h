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
enum PLAYMODE
{
    ORDER_MODE,
    RANDOM_MODE,
    CIRCLE_MODE
};
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
    void handlePlaySlot();
    void loadAppointMusicDir(const QString & filepath);
    void handleModleSlot();
    void handleNextSlot();
    void handlePreSlot();
    void startPlayMusic();
    void handlemusiclistSlot();
    void showAnimation(QWidget * window);
    void hideAnimation(QWidget * window);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_player;

    PLAYMODE m_modle;
    QString m_musicListPath;
    bool m_isShowFlag;
};
#endif // MAINWINDOW_H
