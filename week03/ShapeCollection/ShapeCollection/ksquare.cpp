#include "ksquare.h"

KSquare::KSquare() :
	KShape("Square")
{
}

KSquare::KSquare(std::string name):
	KShape("Square")
{
	m_name.append(name);
}

KSquare::KSquare(std::string name, double length):
	KShape("Square")
{
	m_name.append(name);
	if (length > 0)
		m_length = length;
	else
		m_length = 0;
}
std::string KSquare::getType()
{
	return m_name;
}
double KSquare::getArea(void)
{
	return  m_length * m_length;
}
double KSquare::getPerimeter(void)
{
	return 4 * m_length;
}