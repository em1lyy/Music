/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *imgCover;
    QLabel *lblTrack;
    QLabel *lblAlbum;
    QLabel *lblArtist;
    QToolButton *btnPlayPause;
    QSlider *positionSlider;
    QSlider *volumeSlider;
    QToolButton *btnRepeat;
    QToolButton *btnNext;
    QToolButton *btnPrevious;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(256, 256);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(256, 256));
        MainWindow->setMaximumSize(QSize(256, 256));
        MainWindow->setWindowTitle(QString::fromUtf8("Music"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("multimedia-player");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        imgCover = new QLabel(centralwidget);
        imgCover->setObjectName(QString::fromUtf8("imgCover"));
        imgCover->setGeometry(QRect(0, 0, 256, 256));
        imgCover->setText(QString::fromUtf8(""));
        imgCover->setPixmap(QPixmap(QString::fromUtf8(":/nocover.png")));
        imgCover->setScaledContents(true);
        lblTrack = new QLabel(centralwidget);
        lblTrack->setObjectName(QString::fromUtf8("lblTrack"));
        lblTrack->setGeometry(QRect(0, 0, 256, 16));
        lblTrack->setText(QString::fromUtf8("Unknown Track"));
        lblAlbum = new QLabel(centralwidget);
        lblAlbum->setObjectName(QString::fromUtf8("lblAlbum"));
        lblAlbum->setGeometry(QRect(0, 10, 256, 15));
        lblAlbum->setText(QString::fromUtf8("Unknown Ablum"));
        lblArtist = new QLabel(centralwidget);
        lblArtist->setObjectName(QString::fromUtf8("lblArtist"));
        lblArtist->setGeometry(QRect(0, 20, 256, 15));
        lblArtist->setText(QString::fromUtf8("Unknown Artist"));
        btnPlayPause = new QToolButton(centralwidget);
        btnPlayPause->setObjectName(QString::fromUtf8("btnPlayPause"));
        btnPlayPause->setGeometry(QRect(112, 220, 32, 32));
        btnPlayPause->setText(QString::fromUtf8(""));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("media-playback-pause");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnPlayPause->setIcon(icon1);
        btnPlayPause->setIconSize(QSize(16, 16));
        positionSlider = new QSlider(centralwidget);
        positionSlider->setObjectName(QString::fromUtf8("positionSlider"));
        positionSlider->setEnabled(true);
        positionSlider->setGeometry(QRect(3, 200, 250, 20));
        positionSlider->setMouseTracking(false);
        positionSlider->setMaximum(10000);
        positionSlider->setOrientation(Qt::Horizontal);
        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setGeometry(QRect(174, 226, 80, 20));
        volumeSlider->setMaximum(100);
        volumeSlider->setPageStep(5);
        volumeSlider->setValue(100);
        volumeSlider->setOrientation(Qt::Horizontal);
        btnRepeat = new QToolButton(centralwidget);
        btnRepeat->setObjectName(QString::fromUtf8("btnRepeat"));
        btnRepeat->setGeometry(QRect(10, 222, 28, 28));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("media-repeat-all");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnRepeat->setIcon(icon2);
        btnNext = new QToolButton(centralwidget);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setGeometry(QRect(144, 222, 28, 28));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("media-skip-forward");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnNext->setIcon(icon3);
        btnPrevious = new QToolButton(centralwidget);
        btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
        btnPrevious->setGeometry(QRect(84, 222, 28, 28));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("media-skip-backward");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnPrevious->setIcon(icon4);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        btnRepeat->setText(QString());
        btnNext->setText(QString());
        btnPrevious->setText(QString());
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
