#include "kround.h"

KRound::KRound() :
	KShape("Round")
{
}
KRound::KRound(std::string name):
	KShape("Round")
{
	m_name.append(name);
}
KRound::KRound(std::string name, double radius):
	KShape("Round")
{
	m_name.append(name);
	if (radius > 0)
		m_radius = radius;
	else
		m_radius = 0;
}
std::string KRound::getType()
{
	return m_name;
}
double KRound::getArea(void)
{
	return  3.14159 * m_radius * m_radius;
}
double KRound::getPerimeter(void)
{
	return 2 * 3.14159 * m_radius;
}