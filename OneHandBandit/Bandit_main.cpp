#include "banditwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BanditWindow game;

    game.show();

    return app.exec();
}
