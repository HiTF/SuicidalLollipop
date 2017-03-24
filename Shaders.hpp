#ifndef _SHADER
#define _SHADER
#include <string>
#include <fstream>
#include <vector>
#include <map>
#define _GLheader
#ifdef _WIN32
#include <Windows.h>
#endif
#ifndef _GLEWINCLUDE
#define _GLEWINCLUDE
#include <GL/glew.h>
#include <GL/glu.h>
#endif 

class Shaders
{
	std::map<GLuint,GLuint> shaderid; // ����� ������������ ����� ���� ������� � GL � ID �������
	GLuint programid; // ID ���������
	std::vector<GLuint> type; // ������ ����� ���� ������������ ��������

public:
	/*�������� ��������
	1� ������� ���� - ���� � ��������� �������
	2� ������� ���� - ��� ������� GL */
	void Load(std::vector<std::pair<std::string, GLuint> >& ShadersPaths); 
	GLuint Id(GLuint shaderType) { return shaderid.at(shaderType); } // ���������� ID �� ���������� ���� �������
	Shaders(std::vector<std::pair<std::string, GLuint> >& shaderPaths); // ���������� LOAD
	void useProgram() { glUseProgram(programid); };
	Shaders();
	~Shaders();
};
#endif
