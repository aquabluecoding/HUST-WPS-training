#ifndef __K_TRAPEZIUM_H__
#define __K_TRAPEZIUM_H__

#include "kshape.h"

class KTrapezium : public KShape
{
public:
	KTrapezium();
	KTrapezium(std::string name);
	KTrapezium(std::string name, double base1, double base2, double height, double bias);
	virtual std::string getType(void) override;
	virtual double getPerimeter(void) override;
	virtual double getArea(void) override;

protected:
	double m_upperBase=0;	//上底
	double m_bottomBase=0;//下底
	double m_height=0;	//高
	double m_bias=0;		//上下底中心点偏移量
	double m_leftLeg=0;	//左腰
	double m_rightLeg=0;	//右腰
};

#endif
