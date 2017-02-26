#ifndef UNIVERSECOMPOSITE_H
#define UNIVERSECOMPOSITE_H
#include <iostream>
#include "universecomponent.h"
#include "visitablepart.h"
#include "concretevisitor.h"
#include <string>
#include <vector>


class UniverseComposite : public UniverseComponent, public visitablePart {

public:
    UniverseComposite(
            UniverseComponentType type,
            const std::string& name,
            const std::string& parentName = "");
    virtual ~UniverseComposite();

    //build up the composition
    virtual void add(UniverseComponent* component) { m_children.push_back(component); }

    /*********************************************
     * Inherited methods from UniverseComponent
     * *******************************************/
    virtual void render(QPainter& painter) const;
    virtual void renderLabel(QPainter& painter) const;
    virtual void addAttractionTo(UniverseBody& other) const;
    virtual void resetForces();
    virtual void addAttractionFrom(const UniverseComponent& component);
    virtual void updatePosition(int timestep);

    /*********************************************
     * Methods used to enable construction of the universe with relative positions
     * *******************************************/
    void setPosition(double x, double y) { m_xPosition = x; m_yPosition = y; }
    void setVelocity(double x, double y) { m_xVelocity = x; m_yVelocity = y; }
    //propagates the position and velocity of each object down to it's children
    //this should only be called ONCE
    void convertRelativeToAbsolute(double xp, double yp, double xv, double yv);
    //visitor method to allow visit this class
    std::vector<UniverseComponent*> getChild(){
        return m_children;
    }

    virtual void accept(Visitor* visitor,int event);
    virtual void accept(Visitor *visitor, double x, double y);
private:
    std::vector<UniverseComponent*> m_children;

    //used only to enable construction of the universe with relative positions
    double m_xVelocity;
    double m_yVelocity;
    double m_xPosition;
    double m_yPosition;
    float m_radiu;
};

#endif // UNIVERSECOMPOSITE_H
