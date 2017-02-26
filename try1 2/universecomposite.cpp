#include "universecomposite.h"
#include "config.h"

UniverseComposite::UniverseComposite(
        UniverseComponentType type,
        const std::string& name,
        const std::string& parentName)
        : UniverseComponent(type, name, parentName)
        , m_xVelocity(0.0)
        , m_yVelocity(0.0)
        , m_xPosition(0.0)
        , m_yPosition(0.0)
        ,m_radiu(1)
{ }

UniverseComposite::~UniverseComposite()
{
    for(UniverseComponent* child : m_children) {
        delete child;
    }
}


//render the subtree
void UniverseComposite::render(QPainter& painter) const
{
    for(UniverseComponent* child : m_children)
    {
        child->render(painter);
    }
}

void UniverseComposite::renderLabel(QPainter& painter) const
{
    for(UniverseComponent* child : m_children)
    {
        child->renderLabel(painter);
    }
}


//apply the attraction from this component, to the specified leaf
void UniverseComposite::addAttractionTo(UniverseBody& other) const
{
    for(UniverseComponent* child : m_children)
    {
        child->addAttractionTo(other);
    }
}

void UniverseComposite::resetForces()
{
    for(UniverseComponent* child : m_children)
    {
        child->resetForces();
    }
}

//update attractive forces to all components of this object, from the specified component
void UniverseComposite::addAttractionFrom(const UniverseComponent& component)
{
    for(UniverseComponent* child : m_children)
    {
        child->addAttractionFrom(component);
    }
}

//update the positions of all components of this object
void UniverseComposite::updatePosition(int timestep)
{
    for(UniverseComponent* child : m_children)
    {
        child->updatePosition(timestep);
    }
}

void UniverseComposite::convertRelativeToAbsolute(double xp, double yp, double xv, double yv)
{
    xp += m_xPosition;
    yp += m_yPosition;
    xv += m_xVelocity;
    yv += m_yVelocity;
    for(UniverseComponent* child : m_children)
    {
        child->convertRelativeToAbsolute(xp, yp, xv, yv);
    }
}

//composite visite all component body using vistor
void UniverseComposite::accept(Visitor* visitor,int event)
{
    visitor->visit(this,event);
    if(event != 7){
        concreteVisitor* x = new concreteVisitor();
        for(UniverseComponent* child : m_children)
        {
            child->accept(x,event);
        }
    }else {
        concreteVisitor* x = new concreteVisitor();
        Config* config = Config::getInstance();
        double scale = config->getDistanceScale();

        for(UniverseComponent* child : m_children){
            child->accept(x,event);
            if(x->getComposite() == NULL){
                while(scale * HEIGHT/2 - abs(x->getBody()->getPositionX()) < 0){
                    config->setDistanceScale(config->getDistanceScale()*1.25);
                    scale = config->getDistanceScale();
                }
                while(scale * WIDTH/2 - abs(x->getBody()->getPositionY()) < 0){
                    config->setDistanceScale(config->getDistanceScale()*1.25);
                    scale = config->getDistanceScale();
                }
            }
        }
    }
   // std::cout << distance << std::endl;
    ///////
}

void UniverseComposite::accept(Visitor *visitor, double x, double y){
    visitor->visit(this,x,y);
    concreteVisitor* temp = new concreteVisitor();
    for(UniverseComponent* child : m_children)
    {
        child->accept(temp,x,y);
    }
}
