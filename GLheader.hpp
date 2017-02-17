#ifdef _WIN32
#include<windows.h>
#endif

#include<GL\gl.h> // ���������� OpenGL
#include <GL\glu.h> // ���������� GLU
#include <SDL2\SDL.h> // ���������� SDL 2

#ifndef _GLheader
#define _GLheader
namespace Gl
{
	double WinW; //������ ����
	double WinH; //������ ����
	SDL_Window *window;
	void init(int *argc, char **argv); //������������� ����� ��� ����� ��� ������ glut
	void MainLoop(); //������� ����
	void start(); //���������� ������ ���� 
	void keydown(SDL_Scancode code);//��������� ������� ������
	void display(); //�������� - ���������� ����
	void reshape(); //������� ������������� ��� ��������� ������� ����
	void Quit(); //������� � �����
}
#endif