#ifndef __K_RECTANGLE_H__
#define __K_RECTANGLE_H__

#include "kshape.h"

class KRectangle :public KShape
{
public:
	KRectangle();
	KRectangle(std::string name);
	KRectangle(std::string name, double length, double width);
	virtual std::string getType(void) override;
	virtual double getPerimeter(void) override;
	virtual double getArea(void) override;

protected:
	double m_length = 0;
	double m_width = 0;
};

#endif
