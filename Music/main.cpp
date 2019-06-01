#include <string>
#include <iostream>
#include "mainwindow.h"
#include "music-common-dbus.h"
#include <QApplication>
#include <QIcon>
#include <QString>
#include <QLockFile>
#include <QDir>
#include <QtDBus/QtDBus>
#include <QMessageBox>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(":/" + locale);
    a.installTranslator(&translator);
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, QObject::tr("Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`").toStdString().c_str());
        QMessageBox::critical(NULL, "Music", QObject::tr("Cannot connect to the D-Bus session bus.\nTo start it, run:\n\teval `dbus-launch --auto-syntax`"), QMessageBox::Ok);
        return 1;
    }
    QString tmpDir = QDir::tempPath();
    QLockFile lockFile(tmpDir + "/jagudev-music.lock");
    if (lockFile.tryLock(50))
    {
        if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
            fprintf(stderr, "%s\n",
                    qPrintable(QDBusConnection::sessionBus().lastError().message()));
            QMessageBox::critical(NULL, "Music", QObject::tr("Could not register service to D-Bus session bus."), QMessageBox::Ok);
            exit(1);
        }
        MainWindow w;
        w.setWindowIcon(QIcon::fromTheme("multimedia-player"));
        QDBusConnection::sessionBus().registerObject("/", &w, QDBusConnection::ExportAllSlots);
        w.show();
        if (argc == 2)
        {
            std::string path(argv[1]);
            w.loadAudioFromFileAndPlayIt(QString::fromStdString(path));
        }
        else if (argc > 2)
        {
            std::string path(argv[1]);
            w.loadAudioFromFileAndPlayIt(QString::fromStdString(path));
            QStringList filesToEnqueue;
            for (int i = 2; i < argc; i++){
                std::string s(argv[i]); // Required so that I can see the damn variable in the log
                std::cout << s << std::endl;
                filesToEnqueue.append(QString::fromStdString(s));
            }
            w.addSongListToQueue(filesToEnqueue, false);
        }
        else
        {
            w.showSelectDialogAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol();
        }
        return a.exec();
    }
    else
    {
        if (argc == 2)
        {
            QDBusInterface iface(SERVICE_NAME, "/", "", QDBusConnection::sessionBus());
            if (iface.isValid()) {
                iface.call("addSongListToQueue", QStringList(argv[1]), true);
            } else {
                QMessageBox::critical(NULL, "Music", QObject::tr("Interface invalid."), QMessageBox::Ok);
            }
        }
        else if(argc > 2)
        {
            QDBusInterface iface(SERVICE_NAME, "/", "", QDBusConnection::sessionBus());
            if (iface.isValid()) {
                QStringList filesToEnqueue;
                for (int i = 1; i < argc; i++){
                    std::string s(argv[i]); // Required so that I can see the damn variable in the log
                    std::cout << s << std::endl;
                    filesToEnqueue.append(QString::fromStdString(s));
                }
                iface.call("addSongListToQueue", filesToEnqueue, true);
            } else {
                QMessageBox::critical(NULL, "Music", QObject::tr("Interface invalid."), QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::critical(NULL, "Music", QObject::tr("An instance of Music is already running!"), QMessageBox::Ok);
        }
        return 0;
    }
}
