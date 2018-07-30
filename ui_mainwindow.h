/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(256, 256);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(256, 256));
        MainWindow->setMaximumSize(QSize(256, 256));
        QIcon icon;
        QString iconThemeName = QStringLiteral("multimedia-player");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        imgCover = new QLabel(centralwidget);
        imgCover->setObjectName(QStringLiteral("imgCover"));
        imgCover->setGeometry(QRect(0, 0, 256, 256));
        imgCover->setText(QStringLiteral(""));
        imgCover->setPixmap(QPixmap(QString::fromUtf8(":/nocover.png")));
        imgCover->setScaledContents(true);
        lblTrack = new QLabel(centralwidget);
        lblTrack->setObjectName(QStringLiteral("lblTrack"));
        lblTrack->setGeometry(QRect(0, 0, 256, 16));
        lblTrack->setText(QStringLiteral("Unknown Track"));
        lblAlbum = new QLabel(centralwidget);
        lblAlbum->setObjectName(QStringLiteral("lblAlbum"));
        lblAlbum->setGeometry(QRect(0, 10, 256, 15));
        lblAlbum->setText(QStringLiteral("Unknown Ablum"));
        lblArtist = new QLabel(centralwidget);
        lblArtist->setObjectName(QStringLiteral("lblArtist"));
        lblArtist->setGeometry(QRect(0, 20, 256, 15));
        lblArtist->setText(QStringLiteral("Unknown Artist"));
        btnPlayPause = new QToolButton(centralwidget);
        btnPlayPause->setObjectName(QStringLiteral("btnPlayPause"));
        btnPlayPause->setGeometry(QRect(112, 220, 32, 32));
        btnPlayPause->setText(QStringLiteral(""));
        QIcon icon1;
        iconThemeName = QStringLiteral("media-playback-pause");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        btnPlayPause->setIcon(icon1);
        btnPlayPause->setIconSize(QSize(16, 16));
        positionSlider = new QSlider(centralwidget);
        positionSlider->setObjectName(QStringLiteral("positionSlider"));
        positionSlider->setEnabled(true);
        positionSlider->setGeometry(QRect(3, 200, 250, 20));
        positionSlider->setMouseTracking(false);
        positionSlider->setMaximum(10000);
        positionSlider->setOrientation(Qt::Horizontal);
        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setGeometry(QRect(150, 226, 101, 20));
        volumeSlider->setMaximum(100);
        volumeSlider->setPageStep(5);
        volumeSlider->setValue(100);
        volumeSlider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Music", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
