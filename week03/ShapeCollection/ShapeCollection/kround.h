#ifndef __K_ROUND_H__
#define __K_ROUND_H__

#include "kshape.h"

class KRound :public KShape
{
public:
	KRound();
	KRound(std::string name);
	KRound(std::string name, double radius);
	virtual std::string getType(void) override;
	virtual double getPerimeter(void) override;
	virtual double getArea(void) override;

protected:
	double m_radius = 0;
};

#endif
