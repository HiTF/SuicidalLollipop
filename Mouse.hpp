#ifndef _MOUSE
#define _MOUSE
#include "Camera.hpp"
//#include "GLfunc.hpp"
class Mouse
{
private:
	int X, Y, Sensity; // ���������� ��������� ����, ����������������

public:
	void MouseMotion(int x, int y); // �������� ����, ���������� ���������� ����������
	void ChangeSensity(int Sens); // �������� ����������������
	Mouse(int x, int y, int Sens);
	Mouse();
	
	~Mouse();
};
#endif