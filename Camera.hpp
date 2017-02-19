#ifndef _CAMERA
#define _CAMERA
#include <cmath>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
class Camera
{
private:
	double x, y, z; //���������� ������
	double angleX, angleY; // ��������� ������ � ������������ (����) DEGREES (�������)!!!
	double height;//���� ������;
	double PlayerSpeed;// �������� ������
public:
	void Look(); // ������� ��������� ������� ������
	void MoveForward(); // �������� ������
	void MoveBackward(); // �������� �����
	void MoveRight(); // �������� ������
	void MoveLeft(); // �������� ����� 
	void ChangePlayerSpeed(double speed);// �������� �������� ������
	void RotaterRightLeft(double angleX1);// ������� ������ ������/����� input:���� � ��������!!
	void RotateHighDown(double angleY1);// ������� ������ �����/���� input: ���� � ��������
	Camera();
	Camera(double x, double y, double z, double height, double PlayerSpeed, double AngleX, double AngleY); // x,y,z,height, PlayerSpeed angleX,AngleY
	~Camera();
};

#endif