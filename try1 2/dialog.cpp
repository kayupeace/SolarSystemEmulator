#include "dialog.h"
#include "ui_dialog.h"
#include "universecomposite.h"
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QMovie>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_width(WIDTH)
    , m_height(HEIGHT)
    , m_paused(false)
    , m_renderZodiacs(true)
    , m_renderLabels(true)
    , m_timestamp(0)
    , m_config(Config::getInstance())
    , m_moveX(0)
    , m_moveY(0)
    , zoming(0)
    , m_backgroundOn(false)
    , counter(0)
    , m_movie(false)
{
    //set backdrop to black
    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    //make the window appear
    ui->setupUi(this);
    this->resize(m_width, m_height);

    button();
    //call config to get data from confi.txt and load data into object
    m_config->read("/Users/kevinyu/Documents/info3220/try1 2/config.txt");
    m_universe = m_config->parseUniverseBlocks();
    m_zodiacs = m_config->parseZodiacBlocks();
    m_universe->convertRelativeToAbsolute(0,0,0,0);

    //setup timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    pause(false);
}

void Dialog::button(){
    //Label for timer
    label = new QLabel(this);
    label->setStyleSheet("QLabel { background-color : yellow; color : blue; }");
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Time:--");
    label->setGeometry(QRect(QPoint(this->width()-100,0), QSize(100, 25)));

    label2 = new QLabel(this);
    label2->setStyleSheet("QLabel { background-color : yellow; color : blue; }");
    label2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label2->setText("Location:--");
    label2->setGeometry(QRect(QPoint(this->width()-100,25), QSize(100, 25)));

    //create the buttons
    m_buttonPause = new QPushButton("Pause", this);
    m_buttonZodiacs = new QPushButton("Zodiacs", this);
    m_buttonLabels = new QPushButton("Labels", this);
    m_reset = new QPushButton("Reset", this);
    m_adjust = new QPushButton("Adjust",this);
    m_background = new QPushButton("background",this);

    m_buttonPause->setGeometry(QRect(QPoint(0, 0), QSize(100, 50)));
    m_buttonZodiacs->setGeometry(QRect(QPoint(100, 0), QSize(100, 50)));
    m_buttonLabels->setGeometry(QRect(QPoint(200, 0), QSize(100, 50)));
    m_reset->setGeometry(QRect(QPoint(this->width()-150,0), QSize(50, 25)));
    m_adjust->setGeometry(QRect(QPoint(this->width()-150,25), QSize(50, 25)));
    m_background->setGeometry(QRect(QPoint(500,25), QSize(100, 25)));
    connect(m_buttonPause, SIGNAL(released()), this, SLOT(togglePause()));
    connect(m_buttonZodiacs, SIGNAL(released()), this, SLOT(toggleZodiacs()));
    connect(m_buttonLabels, SIGNAL(released()), this, SLOT(toggleLabels()));
    connect(m_reset, SIGNAL(released()), this, SLOT(reset()));
    connect(m_adjust, SIGNAL(released()), this, SLOT(toggleAdjust()));
    connect(m_background, SIGNAL(released()), this, SLOT(toggleBackground()));

    m_zomein = new QPushButton("Zome in: "+QString::number(zoming), this);
    m_zomeout = new QPushButton("Zome out: "+QString::number(zoming), this);
    m_BG = new QPushButton("BG Movie",this);
    m_zomein->setGeometry(QRect(QPoint(300, 0), QSize(100, 25)));
    m_zomeout->setGeometry(QRect(QPoint(300, 25), QSize(100, 25)));
    m_BG->setGeometry(QRect(QPoint(500, 0), QSize(100, 25)));
    connect(m_zomein,SIGNAL(pressed()), this, SLOT(toggleZomein()));
    connect(m_zomeout,SIGNAL(pressed()), this, SLOT(toggleZomeout()));
    connect(m_BG,SIGNAL(released()),this,SLOT(toggleBG()));

    m_timestepUp = new QPushButton("TimeStep up", this);
    m_timestepDown = new QPushButton("TimeStep down", this);
    m_timestepUp->setGeometry(QRect(QPoint(400, 0), QSize(100, 25)));
    m_timestepDown->setGeometry(QRect(QPoint(400, 25), QSize(100, 25)));
    connect(m_timestepUp,SIGNAL(pressed()), this, SLOT(toggleTimeUp()));
    connect(m_timestepDown,SIGNAL(pressed()), this, SLOT(toggleTimeDown()));
}

Dialog::~Dialog()
{
    delete ui;
    delete m_timer;
    delete m_buttonPause;
    delete m_buttonZodiacs;
    delete m_buttonLabels;
    delete m_universe;
    delete m_zodiacs;
}

void Dialog::toggleZodiacs()
{
    m_renderZodiacs = !m_renderZodiacs;
}

void Dialog::toggleLabels()
{
    m_renderLabels = !m_renderLabels;
}

void Dialog::togglePause()
{
    pause(!m_paused);
}

void Dialog::pause(bool pause)
{
    if(pause)
    {
        m_timer->stop();
        m_paused = true;
    }
    else
    {
        m_timer->start(1000 / m_config->getFramesPerSecond());
        m_paused = false;
    }
}

void Dialog::toggleZomein(){
    if(m_config->getDistanceScale() > 1*1.0e9){
        zoming++;
        m_zomein->setText("Zoom in: "+QString::number(zoming));
        m_zomeout->setText("Zoom out: "+QString::number(zoming));
        m_config->setDistanceScale(m_config->getDistanceScale() *0.8);
        concreteVisitor* visit = new concreteVisitor();
        m_universe->accept(visit,1);
        delete visit;
    }
    //m_config->setRadiusScale(m_config->getRadiusScale() - zoming);
    //std::cout << m_config->getDistanceScale() << std::endl;
}

void Dialog::toggleZomeout(){

   // if(m_config->getDistanceScale() < 1*1.0e9 * 20){
        zoming --;
        m_zomein->setText("Zoom in: "+QString::number(zoming));
        m_zomeout->setText("Zoom out: "+QString::number(zoming));
        m_config->setDistanceScale(m_config->getDistanceScale() *1.25);
        concreteVisitor* visit = new concreteVisitor();
        m_universe->accept(visit,2);
        delete visit;
   // }
   // m_config->setRadiusScale(m_config->getRadiusScale() - zoming);
   // std::cout << m_config->getDistanceScale() << std::endl;
}

void Dialog::toggleTimeUp(){
    //40320
    //std::cout << m_config->getPhysicsStepSize() << std::endl;
    if(m_config->getPhysicsStepSize() < 300000){
        m_config->setPhysicsStepSize(m_config->getPhysicsStepSize() + 10000);
    }
    //10
   // m_config->setOvercalculatePhysicsAmount(m_config->getOvercalculatePhysicsAmount()+1);
}

void Dialog::toggleTimeDown(){
    //std::cout << m_config->getPhysicsStepSize() << std::endl;
    if(m_config->getPhysicsStepSize() < 10000){
        m_config->setPhysicsStepSize(1000);
    }else {
        m_config->setPhysicsStepSize(m_config->getPhysicsStepSize() - 10000);
    }
    //m_config->setOvercalculatePhysicsAmount(m_config->getOvercalculatePhysicsAmount()-1);
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Space:
        pause(!m_paused);
        return;
    default:
        return;
    }
}

void Dialog::nextFrame()
{
    if(m_movie == true){
        QString detail = "p";
        std::ostringstream strs;
        strs << this->counter % 20;
        std::string str = strs.str();
        char *cstr = new char[str.length() + 1];
        std::strcpy(cstr, str.c_str() );
        detail.append(cstr);
        str.clear();
        counter ++;
        this->setStyleSheet("background-image: url( /Users/kevinyu/Documents/info3220/try1 2/pp/" + detail +".gif);");
    }
    //reset the forces stored in every object to 0
    m_universe->resetForces();

    //update the forces acting on every object in the universe,
    //from every object in the universe
    m_universe->addAttractionFrom(*m_universe);

    //update the velocity and position of every object in the universe
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize(); i += step)
    {
        //update physics
        m_universe->updatePosition(step);
        //some time has passed
        m_timestamp += step;
    }
    //update the window (this will trigger paintEvent)
    update();
}

void Dialog::paintEvent(QPaintEvent *event)
{
    //suppress 'unused variable' warning
    Q_UNUSED(event);

    //redraw the universe
    QPainter painter(this);

    //offset the painter so (0,0) is the center of the window
    painter.translate(m_width/2, m_height/2);

    if(m_renderZodiacs)
    {
        for(auto zodiac : *m_zodiacs)
        {
            zodiac.render(painter);
        }
    }

    m_universe->render(painter);

    if(m_renderLabels)
    {
        m_universe->renderLabel(painter);
    }

    QString detail = "Time: ";
    std::ostringstream strs;
    strs << this->m_timestamp / 100000;
    std::string str = strs.str();
    char *cstr = new char[str.length() + 1];
    std::strcpy(cstr, str.c_str() );
    detail.append(cstr);
    str.clear();
    label->setText(detail);
}

void Dialog::mousePressEvent(QMouseEvent * event )
{

  if(event->button() == Qt::LeftButton){
    double locationX = event->x() - this->width()/2;
    double locationY = event->y() - this->height()/2;
    //double locationX = m_moveX - this->width()/2;
    //double locationY= m_moveY- this->height()/2;

    concreteVisitor* visit = new concreteVisitor();
    m_universe->accept(visit,locationX,locationY);
    delete visit;
  }

}

void Dialog::mouseMoveEvent ( QMouseEvent * event )
{
  //Show x and y coordinate values of mouse cursor here
  //label2->setText("X:"+QString::number(event->x()-this->width()/2)+"-- Y:"+QString::number(event->y()-this->height()/2));
  label2->setText("X:"+QString::number(m_moveX)+"-- Y: "+QString::number(m_moveY));
  concreteVisitor* visit = new concreteVisitor();
  if(event->x()-this->width()/2 > 0){
      m_universe->accept(visit,3);
      m_moveX ++;
  }else if(event->x()-this->width()/2 < 0){
      m_universe->accept(visit,4);
      m_moveX --;
  }
  if(event->y()-this->height()/2 < 0){
      m_universe->accept(visit,6);
      m_moveY ++;
  }else if(event->y()-this->height()/2 > 0){
      m_universe->accept(visit,5);
      m_moveY --;
  }
  delete visit;
  //std::cout << "x = " << m_moveX <<"y = " << m_moveY << std::endl;
}

void Dialog::reset(){
    m_config->read("/Users/kevinyu/Documents/info3220/try1 2/config.txt");
    m_universe = m_config->parseUniverseBlocks();
    m_zodiacs = m_config->parseZodiacBlocks();
    m_universe->convertRelativeToAbsolute(0,0,0,0);
    m_timestamp = 0;
    zoming =0;
    m_moveY =0;
    m_moveX =0;
    label2->setText("Location:--");
}

void Dialog::toggleAdjust(){
    concreteVisitor* visit = new concreteVisitor();

    int tracker =0;
    int event = 0;
    if(m_moveX < 0){
        tracker =1;
        event = 3;
    }else if(m_moveX > 0){
        tracker =-1;
        event =4;
    }

    while(m_moveX != 0) {
        m_moveX += tracker;
        m_universe->accept(visit,event);
    }
    tracker =0;
    event =0;
    if(m_moveY < 0){
        tracker = 1;
        event = 6;
    }else if(m_moveY > 0){
        tracker = -1;
        event = 5;
    }
    while(m_moveY !=0){
        m_moveY += tracker;
        m_universe->accept(visit,event);
    }

    m_universe->accept(visit,7);
    //UniverseComposite* x = visit->getComposite();

   /*
    pause(true);
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();
    pause(false);
    */
    delete visit;
    label2->setText("X:"+QString::number(m_moveX)+"-- Y: "+QString::number(m_moveY));

}

void Dialog::toggleBG(){
    /*
    QMovie *movie = new QMovie(":/images/other/images/16x16/loading.gif");
    QLabel *processLabel = new QLabel(this);
    //this->setStyleSheet(" background-image: url(C:/Users/kaibin/Desktop/info3220_2016/assignment3/try1/background.gif);");
    processLabel->setGeometry(QRect(QPoint(this->width()-100,0), QSize(1000, 250)));
    movie->start();
    */
    if(m_movie == false){
        m_movie = true;
    }else {
        m_movie = false;
        this->setStyleSheet("");
    }

}

//button.setStyleSheet('QPushButton {background-color: #A3C1DA; color: red;}')
void Dialog::toggleBackground(){
//    movie->destroyed();
    //QPixmap bkgnd("C:/Users/kaibin/Desktop/info3220_2016/assignment3/try1/background.gif");
    if(m_backgroundOn == false){
        int x = rand() % 4;
        if(x == 0){
            this->setStyleSheet(" background-image: url(/Users/kevinyu/Documents/info3220/try1 2/bb.jpg);");
        }else if(x == 1){
            this->setStyleSheet(" background-image: url(/Users/kevinyu/Documents/info3220/try1 2/bbb.jpg);");
        }else if(x == 2){
            this->setStyleSheet(" background-image: url(/Users/kevinyu/Documents/info3220/try1 2/bbbb.jpg);");
        }else if(x == 3){
            this->setStyleSheet(" background-image: url(/Users/kevinyu/Documents/info3220/try1 2/bbbbb.jpg);");
        }
        m_buttonPause->setStyleSheet("QLabel { background-color : yellow; color : blue; }");
        m_backgroundOn = true;
    }else {
        QPalette Pal(palette());
      //  QPixmap bkgnd;
      //  bkgnd.load("C:/Users/kaibin/Desktop/info3220_2016/assignment3/try1/config.txt/bb.jpg");
        this->setStyleSheet("");
        m_backgroundOn = false;
    }
}












