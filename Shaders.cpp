#include "Shaders.hpp"
#include"Error.hpp"


Shaders::Shaders()
{
}

Shaders::Shaders(std::vector<std::pair<std::string, GLuint> >& shaderPaths)
{
	Load(shaderPaths);
}

void Shaders::Load(std::vector<std::pair<std::string, GLuint> >& shaderPaths)
{
	for (std::pair<std::string, GLuint> shader : shaderPaths)
	{
		std::ifstream in(shader.first); //���� �������
		if (!in.is_open())
			throw(Error(SHADER));
		in.seekg(0, in.end);// �������� � ����� �����
		unsigned int lenght = (unsigned int)in.tellg();// �� ����� �� �������?
		in.seekg(0, in.beg);
		char* fileData = new char[lenght];
		in.read(fileData, lenght); // ��������� ���� � 1 ������
		in.close();
		shaderid[shader.second] = glCreateShader(shader.second);//������� ������
		if (shaderid[shader.second] == 0)
			throw(Error(SHADER));
		glShaderSource(shaderid[shader.second], 1, &fileData, nullptr);// 1- ���������� ����
		glCompileShader(shaderid[shader.second]);// ������������ ������
		GLint status;
		glGetShaderiv(shaderid[shader.second], GL_COMPILE_STATUS, &status);// �������� ����������
		if (status == GL_FALSE)
			throw(Error(SHADER));
		type.push_back(shader.second);
	}
	programid = glCreateProgram();// ������� ��������� ������� � ID
	for (GLuint shaderType : type)
	{
		glAttachShader(programid, shaderid[shaderType]); // ����������� �������
	}
	glLinkProgram(programid);// ������� ��������� ��������
	GLint status;
	glGetProgramiv(programid, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
		throw(Error(SHADER));
	GLuint colour_loc = glGetUniformLocation(programid, "inputColour");
	glUseProgram(programid); ////add, CHECK
	glUniform4f(colour_loc, 1.0f, 0.0f, 0.0f, 1.0f);

	for (GLuint shaderType : type)
	{
		glDeleteShader(shaderid[shaderType]); // ������� ������ (��� ��������)
	}
}
Shaders::~Shaders()
{
}
