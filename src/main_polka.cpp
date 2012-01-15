#include "meegomainwindow.h"

#include <QtGui>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(polka);

    QApplication app(argc, argv);

    MeegoMainWindow mainWindow;
    mainWindow.setOrientation(MeegoMainWindow::ScreenOrientationAuto);
    mainWindow.showExpanded();

    return app.exec();
}
