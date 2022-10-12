#ifndef __K_COMPOUND_SHAPE_H__
#define __K_COMPOUND_SHAPE_H__

#include "kshape.h"

class KCompoundShape : public KShape
{
public:
	KCompoundShape();
	KCompoundShape(std::string name);
	KCompoundShape(std::string name, std::vector<KShape*> parts);
	virtual std::string getType(void) override;
	virtual double getPerimeter(void) override;
	virtual double getArea(void) override;
	void showComponent(void);
	int showComponentNumber(void);

protected:
	double m_perimeter = 0;
	double m_area = 0;
	std::vector<std::string> m_log;
};

#endif