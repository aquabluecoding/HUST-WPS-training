#ifndef __K_RECTANGLE_FACTORY_H__
#define __K_RECTANGLE_FACTORY_H__

#include "kshapefactory.h"
#include "krectangle.h"

class KRectangleFactory :public KShapeFactory
{
public:
	virtual KShape* produceShape() override;
	virtual KShape* produceRectangle(std::string name, double length, double width) override;
};


#endif 