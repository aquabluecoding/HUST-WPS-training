#ifndef __K_SHAPE_H__
#define __K_SHAPE_H__

#include <string>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>

class KShape
{
public:
	KShape();
	KShape(const  std::string& _name);
	virtual std::string getType(void) = 0;
	virtual double getPerimeter(void) = 0;
	virtual double getArea(void) = 0;

protected:
	std::string m_name;
};


#endif 
