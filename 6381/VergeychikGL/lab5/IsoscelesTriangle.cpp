
#include "IsoscelesTriangle.h"


void isoscelesTriangle::scale(int k)
{

	side *= k;
	side2 *= k;
	zoom(k);
}
void isoscelesTriangle::printOUT(std::ostream& out) {
	out << "�������������� �����������!" << std::endl;
	out << "���������� ������: (" << center.getX() << ", " << center.getY() << ")" << std::endl;
	out << "����� ������ ��������������� ������������: " << side << " " << side2 << std::endl;
	out << "���� ��������������� ������������: " << angleOfTriangle << std::endl;
	out << "����� ��������������� ������������:" << std::endl;
	for (int i = 0; i < points.size(); i++)
	{
		out << "(" << points[i].getX() << ", " << points[i].getY() << ")\n";
	}
	out << "����: " << color << std::endl;
	out << "����: " << angle << std::endl;

}
