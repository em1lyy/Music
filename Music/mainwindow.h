#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QMediaPlayer>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadAudioFromFileAndPlayIt(std::string filename);
    void showSelectDialogueAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol();
    void togglePlayingState();
    void updateMetaData();
    void seekForward();
    void seekBackward();
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void increaseVolume();
    void decreaseVolume();
    void closeEvent(QCloseEvent *event);
    void destruct();
    QMediaPlayer *player;
    bool playing;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
