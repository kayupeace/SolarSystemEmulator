#ifndef VISITOR_H
#define VISITOR_H

// Predeclaring of Part Classes
#include "string"
class UniverseBody;
class UniverseComposite;
//#include <universebody.h>
class Visitor
{
public:

    /**
     * @brief Visitor default constructor
     */
    Visitor();

    /**
     * @brief ~Visitor destructor
     */
    virtual ~Visitor();

    /**
     * @brief visit process UniverseBody using Visitor class
     */
    virtual void visit(UniverseBody* body,int event)=0;
    virtual void visit(UniverseBody* body,double x, double y)=0;
    /**
     * @brief visit process UniverseComposite using Visitor class
     */
    virtual void visit(UniverseComposite* composite,int event) = 0;
    virtual void visit(UniverseComposite* composite,double x, double y) = 0;
};


#endif // VISITOR_H
