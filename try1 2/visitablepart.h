#ifndef VISITABLEPART_H
#define VISITABLEPART_H
#include "visitor.h"

class visitablePart
{
public:
    /**
     * @brief VisitablePart default constructor
     */
    visitablePart();
    virtual ~visitablePart();
    /**
     * @brief accept this method permits a visitor to access to this class
     * and any classes which may inherit from it.
     * @param visitor the visitor instance which is permitted to access to this class
     */
    virtual void accept(Visitor* visitor,int event) = 0;
    virtual void accept(Visitor *visitor, double x, double y) =0;
};

#endif // VISITABLEPART_H
