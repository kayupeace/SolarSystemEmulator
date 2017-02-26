#include "dialog.h"
#include <QApplication>
#include "concretevisitor.h"
#include "config.h"
#include "universebody.h"
#include "universecomponent.h"
#include "universecomposite.h"
#include "zodiac.h"

bool configTestFramesPerSecond()
{
    Config* config = Config::getInstance();
    double framesPerSecond = config->getFramesPerSecond();
    double expectedFramesPerSecond = 60;
    return framesPerSecond == expectedFramesPerSecond;
}
bool configTestPhysicsStepSize()
{
    Config* config = Config::getInstance();
    int expectResult = 40320;
    return expectResult == config->getPhysicsStepSize();
}

bool configTestOvercalculatePhysicsAmount(){
    Config* config = Config::getInstance();
    int expectResult = 10;
    return expectResult == config->getOvercalculatePhysicsAmount();
}

bool configTestDistanceScale(){
    Config* config = Config::getInstance();
    double expectResult = 1.0e10;
    return expectResult == config->getDistanceScale();
}
bool configTestRadiusScale(){
    Config* config = Config::getInstance();
    double expectResult = 1.0e7;
    return expectResult == config->getRadiusScale();
}
bool configTestUseLogRadius(){
    Config* config = Config::getInstance();
    return config->getUseLogRadius();
}
bool configTestLogPointRadius(){
    Config* config = Config::getInstance();
    double expectResult = 1.0e6;
    return expectResult == config->getLogPointRadius();
}

bool UniverseCompositeTestSet(){
    Config* config = Config::getInstance();
    UniverseComponent* universe = config->parseUniverseBlocks();
    universe->setName("nameIs");
    return universe->getName() == "nameIs";
}

bool UniverseCompositeTstAdd(){
    UniverseComposite* universe = new UniverseComposite(planet,"0","0");
    UniverseComponent* universe1 = new UniverseBody(planet,"1","1");
    UniverseComponent* universe2 = new UniverseBody(planet,"1","2");
    UniverseComponent* universe3 = new UniverseBody(planet,"1","3");
    UniverseComponent* universe4 = new UniverseBody(planet,"1","4");
    UniverseComponent* universe5 = new UniverseBody(planet,"1","5");
    UniverseComponent* universe6 = new UniverseBody(planet,"1","6");
    UniverseComponent* universe7 = new UniverseBody(planet,"1","7");
    UniverseComponent* universe8 = new UniverseBody(planet,"1","8");

    universe->add(universe1);
    universe->add(universe2);
    universe->add(universe3);
    universe->add(universe4);
    universe->add(universe5);
    universe->add(universe6);
    universe->add(universe7);
    universe->add(universe8);

    for(UniverseComponent* aa : universe->getChild()){
        if(aa->getName() != "1"){
            return false;
        }
    }
    return true;
}

bool universeBodyTestPosition(){
    UniverseBody* universe = new UniverseBody(planet,"1","1");
    double expectX = 666;
    double expectY = 666;
    universe->setPosition(expectX,expectY);
    return universe->getPositionX() == expectX && universe->getPositionY() == expectY;
}

bool universeBodyTestMass(){
    UniverseBody* universe = new UniverseBody(planet,"1","1");
    double expectMass = 326;
    universe->setMass(expectMass);
    return expectMass == universe->getMass();
}

bool universeBodyTestRadius(){
    UniverseBody* universe = new UniverseBody(planet,"1","1");
    double expectMass = 123;
    universe->setRadius(expectMass);
    return expectMass == universe->getRadius();
}

bool universeBodyTestVeloctity(){
    UniverseBody* universe = new UniverseBody(planet,"1","1");
    double expectX = 126;
    double expectY = 326;
    universe->setVelocity(expectX,expectY);
    return universe->getVelocityX() == expectX && universe->getVelocityY() == expectY;
}


bool universeBodyTestVisit(){
    UniverseComponent* universe = new UniverseBody(planet,"asd","asd");
    concreteVisitor* visit = new concreteVisitor();
    universe->accept(visit,0);
    if(visit->getBody() == NULL){
        return false;
    }
    return true;
}

bool univrseCompositeTestVisit(){
    Config* config = Config::getInstance();
    UniverseComponent* universe = config->parseUniverseBlocks();
    concreteVisitor* visit = new concreteVisitor();
    universe->accept(visit,0);
    if(visit->getComposite() == NULL){
        return false;
    }
    return true;
}


bool visitorNumberOfBody(){
    int number = 0;
    UniverseComposite* universe = new UniverseComposite(planet,"0","0");

    UniverseComponent* universe1 = new UniverseBody(planet,"1","1");
    UniverseComponent* universe2 = new UniverseBody(planet,"2","2");
    UniverseComponent* universe3 = new UniverseBody(planet,"3","3");
    UniverseComponent* universe4 = new UniverseBody(planet,"4","4");
    UniverseComponent* universe5 = new UniverseBody(planet,"5","5");
    UniverseComponent* universe6 = new UniverseBody(planet,"6","6");
    UniverseComponent* universe7 = new UniverseBody(planet,"7","7");
    UniverseComponent* universe8 = new UniverseBody(planet,"8","8");

    universe->add(universe1);
    universe->add(universe2);
    universe->add(universe3);
    universe->add(universe4);
    universe->add(universe5);
    universe->add(universe6);
    universe->add(universe7);
    universe->add(universe8);
    concreteVisitor* visit = new concreteVisitor();
    for(UniverseComponent* aa : universe->getChild()){
        aa->accept(visit,0);
        if(visit->getBody() != NULL){
            number ++;
        }
    }
    return number == 8;
}

bool visitorGetValue(){
    UniverseComposite* universe = new UniverseComposite(planet,"0","0");

    UniverseComponent* universe1 = new UniverseBody(planet,"planet","1");
    UniverseComponent* universe2 = new UniverseBody(planet,"planet","2");
    UniverseComponent* universe3 = new UniverseBody(planet,"planet","3");
    UniverseComponent* universe4 = new UniverseBody(planet,"planet","4");
    UniverseComponent* universe5 = new UniverseBody(planet,"planet","5");
    UniverseComponent* universe6 = new UniverseBody(planet,"planet","6");
    UniverseComponent* universe7 = new UniverseBody(planet,"planet","7");
    UniverseComponent* universe8 = new UniverseBody(planet,"planet","8");

    universe->add(universe1);
    universe->add(universe2);
    universe->add(universe3);
    universe->add(universe4);
    universe->add(universe5);
    universe->add(universe6);
    universe->add(universe7);
    universe->add(universe8);
    concreteVisitor* visit = new concreteVisitor();
    for(UniverseComponent* aa : universe->getChild()){
        aa->accept(visit,0);
        if(visit->getBody()->getName() != "planet"){
            return false;
        }
    }
    return true;
}

bool visitorSetValue(){
    UniverseComposite* universe = new UniverseComposite(planet,"0","0");

    UniverseComponent* universe1 = new UniverseBody(planet,"planet","1");
    UniverseComponent* universe2 = new UniverseBody(planet,"planet","2");
    UniverseComponent* universe3 = new UniverseBody(planet,"planet","3");
    UniverseComponent* universe4 = new UniverseBody(planet,"planet","4");
    UniverseComponent* universe5 = new UniverseBody(planet,"planet","5");
    UniverseComponent* universe6 = new UniverseBody(planet,"planet","6");
    UniverseComponent* universe7 = new UniverseBody(planet,"planet","7");
    UniverseComponent* universe8 = new UniverseBody(planet,"planet","8");

    universe->add(universe1);
    universe->add(universe2);
    universe->add(universe3);
    universe->add(universe4);
    universe->add(universe5);
    universe->add(universe6);
    universe->add(universe7);
    universe->add(universe8);
    concreteVisitor* visit = new concreteVisitor();
    for(UniverseComponent* aa : universe->getChild()){
        aa->accept(visit,0);
        visit->getBody()->setName("not planet this time");
    }
    for(UniverseComponent* aa : universe->getChild()){
        aa->accept(visit,0);
        if(visit->getBody()->getName() != "not planet this time"){
            return false;
        }
    }
    return true;
}



int main(int argc, char *argv[])
{
    int numberOfError = 0;
    if(!configTestFramesPerSecond()){
        numberOfError++;
    }
    if(!configTestPhysicsStepSize()){
        numberOfError++;
    }
    if(!configTestOvercalculatePhysicsAmount()){
        numberOfError++;
    }
    if(!configTestDistanceScale()){
        numberOfError++;
    }
    if(!configTestRadiusScale()){
        numberOfError++;
    }
    if(!configTestUseLogRadius()){
        numberOfError++;
    }
    if(!configTestLogPointRadius()){
        numberOfError++;
    }
    if(!univrseCompositeTestVisit()){
        numberOfError++;
    }
    if(!UniverseCompositeTestSet()){
        numberOfError++;
    }
    if(!UniverseCompositeTstAdd()){
        numberOfError++;
    }
    if(!universeBodyTestVisit()){
        numberOfError++;
    }
    if(!visitorNumberOfBody()){
        numberOfError++;
    }
    if(!universeBodyTestPosition()){
        numberOfError++;
    }
    if(!universeBodyTestMass()){
        numberOfError++;
    }
    if(!universeBodyTestRadius()){
        numberOfError++;
    }
    if(!universeBodyTestVeloctity()){
        numberOfError++;
    }
    if(!visitorGetValue()){
        numberOfError++;
    }
    if(!visitorSetValue()){
        numberOfError++;
    }

    std::cout <<"Has "<<numberOfError <<" errors" << std::endl;

    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
