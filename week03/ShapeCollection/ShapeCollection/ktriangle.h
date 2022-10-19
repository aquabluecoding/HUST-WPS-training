#ifndef __K_TRIANGLE_H__
#define __K_TRIANGLE_H__

#include "kshape.h"

class KTriangle : public KShape
{
public:
	KTriangle();
	KTriangle(std::string name);
	KTriangle(std::string name, double a, double b, double c);
	virtual std::string getType(void) override;
	virtual double getPerimeter(void) override;
	virtual double getArea(void) override;

protected:
	double m_a=0;
	double m_b=0;
	double m_c=0;
};

#endif
