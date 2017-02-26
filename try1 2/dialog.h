#ifndef DIALOG_H
#define DIALOG_H
#include "config.h"
#include "universecomponent.h"
#include "zodiac.h"
#include <QDialog>
#include <QTimer>
#include <list>
#include "universecomposite.h"
#include <QLabel>
#include <iostream>
#include <visitablepart.h>
#include <visitor.h>
#include <concretevisitor.h>
#include <QMessageBox>
#include <QMouseEvent>
#define HEIGHT (400)
#define WIDTH (800)

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    virtual ~Dialog();
    void button();

private slots:
    //prepare the next frame, called by the timer
    void nextFrame();
    //toggle the simultation's pause state
    void togglePause();
    //toggle rendering of Zodiacs
    void toggleZodiacs();
    //toggle rendering of labels
    void toggleLabels();

    void toggleZomein();
    void toggleZomeout();
    void toggleTimeUp();
    void toggleTimeDown();
    void toggleBG();
    void reset();
    void toggleAdjust();
    void toggleBackground();

private:
    //method called when the window is being redrawn
    void paintEvent(QPaintEvent *event);
    //pause (or unpause) the simulation
    void pause(bool pause);
    //handle key presses
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::Dialog* ui;
    QTimer* m_timer; //Timer object for triggering updates

    //buttons
    QPushButton* m_buttonPause;
    QPushButton* m_buttonZodiacs;
    QPushButton* m_buttonLabels;
    QPushButton* m_zomein;
    QPushButton* m_zomeout;
    QPushButton* m_timestepUp;
    QPushButton* m_timestepDown;
    QPushButton* m_BG;
    QPushButton* m_reset;
    QPushButton* m_adjust;
    QPushButton* m_background;
    QLabel *label;
    QLabel *label2;

    double m_moveX;//mouse position x
    double m_moveY;//mouse position y
    int counter;//movie play rate

    bool m_movie;//background movie
    int zoming = 0;
    int m_width; //width of the window
    int m_height; //height of the window
    bool m_paused; //is the simulation paused?
    bool m_renderZodiacs; //should Zodiacs be rendered?
    bool m_renderLabels; //should labels be rendered?
    bool m_backgroundOn;//random background
    long m_timestamp; //simulation time since simulation start
    UniverseComponent* m_universe; //The universe
    std::list<Zodiac>* m_zodiacs; //Vector of zodiac lines
    Config* m_config; //the singleton config instance

};

#endif // DIALOG_H
