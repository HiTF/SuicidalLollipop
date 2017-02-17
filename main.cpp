#include <iostream>
#include "GLheader.hpp"
#include "Error.hpp"
using namespace std;

Error::Error(ErrorType error)
{
	type = error;
}

Error::Error()
{
	type = NONE;
}

void Gl::init(int *argc, char **argv)
{
	SDL_DisplayMode DisMode; //��������� ������
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)//��������� ������������� SDL
	{
		throw(Error(SDL));
	}
	SDL_GetDesktopDisplayMode(0, &DisMode); //�������� ���������� ������
	WinW = DisMode.w; //�������� ������� ������
	WinH = DisMode.h;
	if ((!WinW) || (!WinH))
	{
		WinW = 1280; //���� �� ������� ������ HD
		WinH = 720;
	}
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0) //������� �������� �����
		throw(Error(SDL));
	if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) < 0) //������ ������� �����
		throw(Error(SDL));
	if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0) //������ ������� �����
		throw(Error(SDL));
	if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) < 0) //������ ������� �����
		throw(Error(SDL));
	atexit(SDL_Quit);
}

void Gl::start()
{
	window = SDL_CreateWindow("SuicidalLollipop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WinW, WinH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);//�������� ����
	if (window == NULL)
		throw(Error(SDL));
	if (SDL_GL_CreateContext(window) == NULL) //������� ������� OpenGl 
		throw(Error(SDL));
	glClearColor(0.0, 0.0, 1.0, 1.0);//���� �� �������
	glClearDepth(1.0); //������� �� �������
	glDepthFunc(GL_LESS); //������� ��� ����������� �����
	glEnable(GL_DEPTH_TEST); //��������� ���� �������
	glMatrixMode(GL_PROJECTION); //��������� ��� �� ����� ������ � �������� ��������
	glLoadIdentity(); //���������� ��������� �������
	gluPerspective(70.0 * WinH / WinW, WinW / WinH, 0.1, 1000.0); // ���� ������ �� y, x/y, ��������� � ������� ��������� ���������
	glMatrixMode(GL_MODELVIEW); // ��������� � ����� ������ � 3d
	SDL_ShowCursor(SDL_DISABLE); //��������� ������
	if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) // True Full screen
		throw(Error(SDL));
	MainLoop(); //��������� ������� ����
}

void Gl::MainLoop()
{
	while (true)
	{
		display();
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Quit();
				break;
			case SDL_KEYDOWN:
				keydown(event.key.keysym.scancode);
				break;
			default:
				break;
			}
		}
	}
}

void Gl::Quit()
{
	SDL_Quit();
	exit(0);
}

void Gl::keydown(SDL_Scancode code)
{
	switch (code)
	{
	case SDL_SCANCODE_ESCAPE:
		Quit();
		break;
	default:
		break;
	}
}

void Gl::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������� ����� � ����� �������
	glFlush(); //������������
	SDL_GL_SwapWindow(window);
}

void DealWithErrror(ErrorType err)
{
	switch (err)
	{
	case SDL:
		cout << SDL_GetError() << endl; //������� ��������� �� ������
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	try
	{
		Gl::init(&argc, argv);
		Gl::start();
	}
	catch (ErrorType err)
	{
		DealWithErrror(err);
	}
	return 0;
}