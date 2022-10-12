#ifndef __K_SQUARE_H__
#define __K_SQUARE_H__

#include "kshape.h"

class KSquare : public KShape
{
public:
	KSquare();
	KSquare(std::string name);
	KSquare(std::string name, double length);
	virtual std::string getType(void) override;
	virtual double getPerimeter(void) override;
	virtual double getArea(void) override;

protected:
	double m_length = 0;
};

#endif
