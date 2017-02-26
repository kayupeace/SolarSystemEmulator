#include "concretevisitor.h"
#include "config.h"
#include <QMovie>

concreteVisitor::concreteVisitor() : m_body(NULL),m_composite(NULL)
{

}
concreteVisitor::~concreteVisitor(){

}

/*
 * Function to set up data as required
 * Event 1 & 2 is for zoom in and out
 * Event 3,4,5,6 is move up donw left right
*/

void concreteVisitor::visit(UniverseBody *body,int event){
    if(body == NULL){
        return;
    }
    Config* config = Config::getInstance();
    double scale = config->getDistanceScale();
    m_body = body;
    int moveX =0;
    int moveY =0;
    //could be composite some times
    if(body != NULL){
        if(event == 1){
            body->setRadius(body->getRadius() * 2);
        }else if (event == 2){
            body->setRadius(body->getRadius() * 0.5);
        }else if (event == 3){
            moveX = -1;
        }else if(event == 4){
            moveX = 1;
        }else if(event ==5){
            moveY = -1;
        }else if (event ==6){
            moveY = 1;
        }
        //check if it's loading well;
        body->setPosition(body->getPositionX()+(2*moveX*scale),body->getPositionY()+(2*moveY*scale));
        //std::cout << body->getName() << std::endl;
    }
}
void concreteVisitor::visit(UniverseComposite *composite, int event){
    //do nothing
    m_composite = composite;
    if(composite != NULL && event == 0) {
        //std::cout << "Visiting composite" << " at event " << event << std::endl;
    }
}
void concreteVisitor::visit(UniverseComposite *composite, double x, double y){
    //do nothing
    m_composite = composite;
    if(composite != NULL && x !=0 && y !=0) {
        //std::cout << "Visiting composite" << " at x " << x << " at y " << y << std::endl;
    }
}


//for getting detail of each star/planet
void concreteVisitor::visit(UniverseBody *body, double x, double y){
    m_body = body;
    double locationX =0;
    double locationY =0;
    if(body != NULL){
        locationX = body->getPositionX();
        locationY = body->getPositionY();
        Config* config = Config::getInstance();
        double scale = config->getDistanceScale();

        if(abs(abs(x) -abs(locationX / scale)) < 10  && abs(abs(y)- abs(locationY / scale)) < 10){
            //std::cout << body->getName() << std::endl;
            //std::cout << body->getPositionX() << std::endl;
            //std::cout << body->getPositionY() << std::endl;
            std::cout << "at x = " << x*scale << " ,at y = " << y*scale << std::endl;
            std::cout << "locationX" << locationX << " ,locationY"<< locationY << " ," << 1*scale*10<<std::endl;
            std::cout << abs(abs(x) -abs(locationX / scale)) << " " << abs(abs(y)- abs(locationY / scale)) << std::endl;

            myMainWindow *window = new myMainWindow();
            window->setWindowTitle("Inoforamtion");
            window->resize(200,200);
            QWidget *centralWidget = new QWidget(window);
            QHBoxLayout* layout = new QHBoxLayout(centralWidget);
            myLabel* CoordinateLabel = new myLabel();

            QString detail = "Name: ";
           // std::string information = body->getName();

            std::ostringstream strs;
            strs << body->getName() << "\n";
            strs << "X Position: " << body->getPositionX() << "\n";
            strs << "Y Position: " << body->getPositionY() << "\n";
            strs << "X Velocity: " << body->getVelocityX() << "\n";
            strs << "Y Velocity: " << body->getVelocityY() << "\n";
            strs << "Radius: " << body->getRadius() << "\n";
            strs << "Mass: " << body->getMass() << "\n";
           // strs << "Color: " << body->getColor().name() << "\n";
            strs << "Parent: " << body->getParentName() << "\n";
            strs << "Type: ";
            if(body->getType() == planet){
                strs << "Planet";
            }else if(body->getType() == star){
                strs << "Star";
            }else if(body->getType() == blackhole){
                strs << "BlackHole";
            }
            strs << "\n";
            std::string str = strs.str();
            char *cstr = new char[str.length() + 1];
            std::strcpy(cstr, str.c_str() );

            detail.append(cstr);
            str.clear();

            CoordinateLabel->setText(detail);
            window->setBody(body);

            layout->addWidget(CoordinateLabel);
            window->setCentralWidget(centralWidget);
            window->show();
        }
    }else {

    }
}
