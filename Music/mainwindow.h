#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //void loadAudioFromFileAndPlayIt(std::string filename);
    //void showSelectDialogueAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol();
    void togglePlayingState();
    void toggleRepeatMode();
    void updateMetaData();
    void updateWindowTitle(QMediaContent newTrack); // This updates the Window *title only*. Rest of the meta data in updateMetaData()
    void updateButtons(); // Updates the play/pause button because it sometimes doesn't do that automatically
    void seekForward();
    void seekBackward();
    void smartPrevious();
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void increaseVolume();
    void decreaseVolume();
    void closeEvent(QCloseEvent *event);
    void destruct();
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    bool playing;
    ~MainWindow();

public slots:
    void loadAudioFromFileAndPlayIt(QString filename);
    void addSongListToQueue(QStringList fileNames, bool switchToNewSong);
    void showSelectDialogAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
