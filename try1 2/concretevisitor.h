#ifndef CONCRETEVISITOR_H
#define CONCRETEVISITOR_H
#include "visitor.h"
#include "universebody.h"
#include "universecomposite.h"
#include <QLabel>

#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include "dialog.h"
#include <QInputDialog>
#include <QPushButton>

// class to create new windows for each of Information panels
class myLabel: public QLabel
{
  public:
    myLabel()
    {
      this->setAlignment(Qt::AlignCenter);

      //Default Label Value
      this->setText("No Value");

      //set MouseTracking true to capture mouse event even its key is not pressed
      this->setMouseTracking(true);
    }

    ~ myLabel(){}

};


class myMainWindow: public QMainWindow
{
  public:
    myMainWindow()
    {}
    ~ myMainWindow(){}
    void mouseReleaseEvent(QMouseEvent * event)
    {
        event->button();
          QInputDialog* inputDialog = new QInputDialog();
          inputDialog->setOptions(QInputDialog::NoButtons);
          bool pressOk;
          QString text =  inputDialog->getText(NULL ,"Set Value",
                                                        "Value parameter=\n{Mass,Radius,Colour\nXPosition,YPosition\nXVelocity,YVelocity}", QLineEdit::Normal,
                                                        "Radius=2.44e6", &pressOk);
          if(pressOk && !text.isEmpty()){
              std::string result = text.toStdString();
              if(result.substr(0,result.find("=")) == "XPosition"){
                 // std::cout << atof(result.substr(result.find("=")+1,result.length()).c_str()) << std::endl;
                  body->setPosition(atof(result.substr(result.find("=")+1,result.length()).c_str()),body->getPositionY());
              }else if(result.substr(0,result.find("=")) == "YPosition"){
                  body->setPosition(body->getPositionX(),atof(result.substr(result.find("=")+1,result.length()).c_str()));
              }else if(result.substr(0,result.find("=")) == "Mass"){
                  body->setMass(atof(result.substr(result.find("=")+1,result.length()).c_str()));
              }else if(result.substr(0,result.find("=")) == "Radius"){
                  body->setRadius(atof(result.substr(result.find("=")+1,result.length()).c_str()));
              }else if(result.substr(0,result.find("=")) == "XVelocity"){
                  body->setVelocity(atof(result.substr(result.find("=")+1,result.length()).c_str()),body->getVelocityY());
              }else if(result.substr(0,result.find("=")) == "YVelocity"){
                  body->setVelocity(body->getVelocityX(),atof(result.substr(result.find("=")+1,result.length()).c_str()));
              }else if(result.substr(0,result.find("=")) == "Colour"){
                  body->setColor(result.substr(result.find("=")+1,result.length()).c_str());
              }
      }
    }
    void setBody(UniverseBody* v){
        body = v;
    }
private:
    UniverseBody* body;
};


class concreteVisitor : public Visitor
{
public:
    /**
     * @brief VisitablePart default constructor
     */
    concreteVisitor();

    ~concreteVisitor();

    virtual void visit(UniverseBody* body,int event);
    virtual void visit(UniverseComposite* composite,int event);

    virtual void visit(UniverseBody *body, double x, double y);
    virtual void visit(UniverseComposite *composite, double x, double y);

    UniverseBody* getBody(){
        return m_body;
    }
    UniverseComposite* getComposite(){
        return m_composite;
    }

protected:
    UniverseBody* m_body;
    UniverseComposite* m_composite;
};

#endif // CONCRETEVISITOR_H
