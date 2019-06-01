#include <iostream>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QCloseEvent>
#include <QMediaMetaData>
#include <QShortcut>
#include <QLocale>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
    player->setPlaylist(playlist);
    player->setVolume(100);
    connect(ui->btnPlayPause, &QToolButton::clicked, this, &MainWindow::togglePlayingState);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateDuration);
    connect(ui->positionSlider, &QAbstractSlider::valueChanged, this, &MainWindow::setPosition);
    connect(ui->volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
    connect(ui->btnRepeat, &QToolButton::clicked, this, &MainWindow::toggleRepeatMode);
    connect(this->ui->btnNext, &QToolButton::clicked, playlist, &QMediaPlaylist::next);
    connect(this->ui->btnPrevious, &QToolButton::clicked, this, &MainWindow::smartPrevious);
    connect(this->playlist, &QMediaPlaylist::currentMediaChanged, this, &MainWindow::updateWindowTitle);
    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, this, &MainWindow::togglePlayingState);
    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, this, &MainWindow::seekForward);
    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, this, &MainWindow::seekBackward);
    QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, this);
    connect(increaseShortcut, &QShortcut::activated, this, &MainWindow::increaseVolume);
    QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, this);
    connect(decreaseShortcut, &QShortcut::activated, this, &MainWindow::decreaseVolume);
    QShortcut *repeatShortcut = new QShortcut(Qt::Key_R, this);
    connect(repeatShortcut, &QShortcut::activated, this, &MainWindow::toggleRepeatMode);
    QShortcut *prevShortcut = new QShortcut(Qt::Key_P, this);
    connect(prevShortcut, &QShortcut::activated, this, &MainWindow::smartPrevious);
    QShortcut *nextShortcut = new QShortcut(Qt::Key_N, this);
    connect(nextShortcut, &QShortcut::activated, playlist, &QMediaPlaylist::next);
}

void MainWindow::loadAudioFromFileAndPlayIt(QString filename)
{
    cout << filename.toStdString() << endl;
    QUrl file = QUrl::fromLocalFile(filename);
    playlist->addMedia(QMediaContent(file));
    if (file.isValid() && !playlist->isEmpty()) // fix window title (said " - Music" after cancelling)
    {
        playing = true;
        this->setWindowTitle(file.fileName() + " - Music");
        player->play();
    }
    else
    {
        playlist->clear();
    }
    connect(player, &QMediaPlayer::metaDataAvailableChanged, this, &MainWindow::updateMetaData);
    updateMetaData();
    updateButtons();
}

void MainWindow::addSongListToQueue(QStringList fileNames, bool switchToNewSong)
{
    QList<QUrl> filelist;
    foreach(QString sfile, fileNames)
    {
        filelist.append(QUrl::fromLocalFile(sfile));
    }
    foreach (QUrl file, filelist)
    {
        playlist->addMedia(QMediaContent(file));
    }
    if (!playing) // Also a bit of a fix, bug hard to explain
    {
        playing = true;
        player->play();
    }
    // Aaaand we want the newly added song to play if switchToNewSong is true
    if (switchToNewSong)
    {
        playlist->setCurrentIndex(playlist->mediaCount() - fileNames.length());
    }
    updateButtons();
}

void MainWindow::showSelectDialogAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open song"), QString(), "*.mp3, *.wav, *.ogg, *.aiff, *.flac");
    loadAudioFromFileAndPlayIt(file);
}

void MainWindow::togglePlayingState()
{
    if (playing)
    {
        player->pause();
        ui->btnPlayPause->setIcon(QIcon::fromTheme("media-playback-start"));
        playing = false;
    }
    else
    {
        player->play();
        ui->btnPlayPause->setIcon(QIcon::fromTheme("media-playback-pause"));
        playing = true;
    }
}

void MainWindow::toggleRepeatMode()
{
    if (playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Loop)
    {
        ui->btnRepeat->setIcon(QIcon::fromTheme("media-repeat-track-amarok"));
        playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
    }
    else if (playlist->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential)
    {
        ui->btnRepeat->setIcon(QIcon::fromTheme("media-playlist-repeat"));
        playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
    }
    else
    {
        ui->btnRepeat->setIcon(QIcon::fromTheme("media-repeat-none"));
        playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
    }
}

void MainWindow::updateMetaData()
{
    if (player->isMetaDataAvailable())
    {
        QString trackName = player->metaData(QMediaMetaData::Title).toString();
        QString albumName = player->metaData(QMediaMetaData::AlbumTitle).toString();
        QString artistName = player->metaData(QMediaMetaData::AlbumArtist).toString();
        QImage coverArtwork = player->metaData(QMediaMetaData::CoverArtImage).value<QImage>();
        qInfo() << "Track name: " << trackName;
        qInfo() << "Album name: " << albumName;
        qInfo() << "Artist name: " << artistName;
        if (!trackName.compare("") == 0)
        {
            ui->lblTrack->setText(trackName);
        }
        else
        {
            ui->lblTrack->setText(tr("Unknown Track"));
        }
        if (!albumName.compare("") == 0)
        {
            ui->lblAlbum->setText(albumName);
        }
        else
        {
            ui->lblAlbum->setText(tr("Unknown Album"));
        }
        if (!artistName.compare("") == 0)
        {
            ui->lblArtist->setText(artistName);
        }
        else
        {
            ui->lblArtist->setText(tr("Unknown Artist"));
        }
        if (!coverArtwork.isNull())
        {
            ui->imgCover->setPixmap(QPixmap::fromImage(coverArtwork));
        }
        else
        {
            ui->imgCover->setPixmap(QPixmap(":/nocover.png"));
        }
    }
    updateButtons();
}

void MainWindow::updateWindowTitle(QMediaContent newTrack)
{
    this->setWindowTitle(newTrack.canonicalUrl().fileName() + " - Music");
    updateButtons();
}

void MainWindow::updateButtons()
{
    if (playing)
        ui->btnPlayPause->setIcon(QIcon::fromTheme("media-playback-pause"));
    else
        ui->btnPlayPause->setIcon(QIcon::fromTheme("media-playback-start"));
}

void MainWindow::seekForward()
{
    ui->positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::seekBackward()
{
    ui->positionSlider->triggerAction(QSlider::SliderPageStepSub);
}

void MainWindow::smartPrevious() // I was really annoyed by the fact that playlist::previous skips to the previous track, no matter how long the track has been playing.
{ //                                This function only skips to the previous track if the current one has benn playing for less than 3 seconds and else restarts the current track.
    if (player->position() <= 3000) // According to the Qt Docs, the value is specified in milliseconds. Still not sure if that's true due to previous experiments, but we'll see.
    {
        playlist->previous();
    }
    else
    {
        player->setPosition(0);
    }
}

void MainWindow::updatePosition(qint64 position)
{
    ui->positionSlider->setValue(position);
}

void MainWindow::updateDuration(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
    ui->positionSlider->setEnabled(duration > 0);
    ui->positionSlider->setPageStep(duration / 10);
}

void MainWindow::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(player->position() - position) > 99)
    {
        player->setPosition(position);
    }
}

void MainWindow::increaseVolume()
{
    ui->volumeSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::decreaseVolume()
{
    ui->volumeSlider->triggerAction(QSlider::SliderPageStepSub);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    player->stop();
    qApp->exit();
}

void MainWindow::destruct()
{
    delete this;
}

MainWindow::~MainWindow()
{
    /*delete ui; // This caused the "Crash on Close" bug.
    delete &playing;
    player->stop();
    delete player;*/
}
