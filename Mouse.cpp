#include "Mouse.hpp"
#include "GLfunc.hpp"


Mouse::Mouse(int x, int y, int Sens)
{
	X = x;
	Y = y;
	if ((x < 0) || (y < 0))
	{
		x = 320;
		y = 240;
	}
	
	SetCursorPos(x, y); // ������������� ������� �������
}
Mouse::Mouse()
{
	X = 320;
	Y = 240;
	Sensity = 20;
	SetCursorPos(X, Y);
}

void Mouse::MouseMotion(int x, int y)
{
	Gl::Cam.RotaterRightLeft((X - x) / Sensity); // ������� ������ �� �
	Gl::Cam.RotateHighDown((Y - y) / Sensity); // ������� ������ �� �
	SetCursorPos(X, Y); // ������������� ������� �������
	return;
}
void Mouse::ChangeSensity(int sense)
{
	sense < 0 ? Sensity = 20 : Sensity = sense;
	return;
}

Mouse::~Mouse()
{
}
