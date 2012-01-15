#ifndef MEEGOMAINWINDOW_H
#define MEEGOMAINWINDOW_H

#include <QtGui/QMainWindow>

class MeegoMainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MeegoMainWindow(QWidget *parent = 0);
    virtual ~MeegoMainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();
};

#endif
