#include <iostream>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QCloseEvent>
#include <QMediaMetaData>
#include <QShortcut>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    player->setVolume(100);
    connect(ui->btnPlayPause, &QToolButton::clicked, this, &MainWindow::togglePlayingState);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateDuration);
    connect(ui->positionSlider, &QAbstractSlider::valueChanged, this, &MainWindow::setPosition);
    connect(ui->volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
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
}

void MainWindow::loadAudioFromFileAndPlayIt(string filename)
{
    cout << filename << endl;
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(filename)));
    playing = true;
    player->play();
    connect(player, &QMediaPlayer::metaDataAvailableChanged, this, &MainWindow::updateMetaData);
    updateMetaData();
    cout << "all done and dusted" << endl;
}

void MainWindow::showSelectDialogueAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open song"), QString(), "*.mp3, *.wav, *.ogg, *.aiff, *.flac");
    string filepath = file.toStdString();
    loadAudioFromFileAndPlayIt(filepath);
    cout << "im done" << endl;
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
        if (!albumName.compare("") == 0)
        {
            ui->lblAlbum->setText(albumName);
        }
        if (!artistName.compare("") == 0)
        {
            ui->lblArtist->setText(artistName);
        }
        if (!coverArtwork.isNull())
        {
            ui->imgCover->setPixmap(QPixmap::fromImage(coverArtwork));
        }
    }
}

void MainWindow::seekForward()
{
    ui->positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::seekBackward()
{
    ui->positionSlider->triggerAction(QSlider::SliderPageStepSub);
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
        qDebug("Setting position!");
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
    this->destruct();
}

void MainWindow::destruct()
{
    delete this;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete &playing;
    player->stop();
    delete player;
}
