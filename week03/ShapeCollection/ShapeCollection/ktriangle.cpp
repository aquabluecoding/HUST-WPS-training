#include "ktriangle.h"

KTriangle::KTriangle() :
	KShape("Triangle")
{
}
KTriangle::KTriangle(std::string name):
	KShape("Triangle")
{
	m_name.append(name);
}
KTriangle::KTriangle(std::string name, double a, double b, double c):
	KShape("Triangle")
{
	m_name.append(name);
	if (a + b > c && a + c > b && b + c > a)
	{
		m_a = a;
		m_b = b;
		m_c = c;
	}
	else
	{
		m_a = m_b = m_c = 0;
	}
}
std::string KTriangle::getType()
{
	return m_name;
}
double KTriangle::getArea(void)
{
	double p = 0.5 * (m_a + m_b + m_c);
	return  sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
}
double KTriangle::getPerimeter(void)
{
	return m_a + m_b + m_c;
}