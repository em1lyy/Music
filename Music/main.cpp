#include <string>
#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon::fromTheme("multimedia-player"));
    w.show();
    if (argc == 2)
    {
        std::string path(argv[1]);
        w.loadAudioFromFileAndPlayIt(path);
        std::cout << "abcdef" << endl;
    }
    else if (argc >= 2)
    {
        std::cout << "ARGUMENT LENGTH MUST BE 0 OR 1!\n EXITING!" << endl;
        return 1;
    }
    else
    {
        w.showSelectDialogueAndPlaySelectedFileAfterwardsUsingTheLoadAudioFromFileAndPlayItThisIsTheLongestMethodNameIveEverSeenLol();
        std::cout << "abcdef" << endl;
    }
    return a.exec();
}
