#ifndef _MASHOBJECT
#define _MASHOBJECT
#include<vector>
#include<string>
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
#include<fstream>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifndef _GLEWINCLUDE
#define _GLEWINCLUDE
#include <GL/glew.h>
#include <GL/glu.h>
#endif 
/* TODO:
�� ������ ����� �� �������� ���������� ��� ������, ����������� ���������� � ����������
*/
class MashObject 
{
private:
	std::string path = ""; //���� �������
	std::vector < glm::dvec3 >  vertices; // ���������� �������
	std::vector < glm::dvec2 >  uvs; //���������� ���������� �������
	std::vector < glm::dvec3 >  normals;// ���������� �������
	std::vector <glm::dvec3 > verColor;// ����� ������, �������� ��������
	std::vector <GLuint> vbo;
	GLuint vao = 0;
	bool drawable = false;
	bool texture = true;
	bool inormals = true;
public:
	bool is_drawable() { return drawable; }//  ������ �� �? �)
	bool is_textures() { return drawable && texture; } // ���� �� ��������
	bool is_normals() { return drawable && inormals; } // ���� �� �������
	void draw(); // ���������� ����
	void parser(std::string&); // ������� ������ �� obj �����, �������� ���� � obj �����
	MashObject();
	MashObject(std::string&);
	~MashObject();
};

#endif