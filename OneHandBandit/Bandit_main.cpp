#include "banditwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTime time = QTime::currentTime();

    qsrand((uint) time.msec());

    BanditWindow game;

    game.show();

    return app.exec();
}
