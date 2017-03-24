#include "MashObject.hpp"
#include <glm/glm.hpp>
#include<SDL2/SDL.h>
#include"../GLfunc.hpp"
void MashObject :: parser(std::string& file_path)
{
	path = file_path; // ��������� obj ����
	std::ifstream forread;
	forread.open(file_path);
	if (!forread.is_open())
		return;
	std::vector < glm::vec3 >  time_vertices; // ���������� �������
	std::vector < glm::vec2 >  time_uvs; //���������� ���������� �������
	std::vector < glm::vec3 >  time_normals;// ���������� �������
	std::vector <long int > time_vertexIndices, time_uvIndices, time_normalIndices; // ������ ���������, �������, ��������
	long int vertexindex, uvindex, normalindex;
	std::string lineHeader = ""; //������ � ������� ����� ���������	
	while (!forread.eof())  // ������ ����
	{
		 forread >>lineHeader;
		 if (lineHeader == "v") //���������� �������
		 {
			 glm::vec3 vertex; // ��������� ������ ���������� �������
			 forread >> vertex.x >> vertex.y >> vertex.z;
			 time_vertices.push_back(vertex);
			 continue;
		 }
		 if (lineHeader == "vt") // ���������� ���������� �������
		 {
			 glm::vec2 uv; // ��������� ������ ��������
			 forread >> uv.x >> uv.y;
			 time_uvs.push_back(uv);
			 continue;
		 }
		 if (lineHeader == "vn") // ������ �������
		 {
			 glm::vec3 normal;// ��������� ������ �������
			 forread >> normal.x >> normal.y >> normal.z;
			 time_normals.push_back(normal);
			 continue;
		 }
		 if (lineHeader == "f")
		 {
			 int stringsize = lineHeader.length();
			 for (int s = 0; s < 3; s++)
			 {
				 std::string VTN[3];// �������, �������� , �������
				 forread >> lineHeader;
				 stringsize = lineHeader.length();
				 int i = 0;
				 while (lineHeader[i] != '/')
				 {
					 VTN[0].push_back(lineHeader[i]);
					 i++;
				 }
				 i++;
				 int j = 0;
				 while (lineHeader[i] != '/')
				 {
					 VTN[1].push_back(lineHeader[i]);
					 j++;
					 i++;
				 }
				 i++;
				 j = 0;
				 while (i < stringsize)
				 {
					 VTN[2].push_back(lineHeader[i]);
					 j++;
					 i++;
				 }

				 vertexindex = strtol(VTN[0].c_str(), NULL, 10);
				 if (vertexindex == 0)
					 return;
				 uvindex = strtol(VTN[1].c_str(), NULL, 10);
				 if (uvindex == 0)
					 texture = false;
				 normalindex = strtol(VTN[2].c_str(), NULL, 10);
				 if (normalindex == 0)
					 inormals = false;
				 time_vertexIndices.push_back(vertexindex);
				 time_uvIndices.push_back(uvindex);
				 time_normalIndices.push_back(normalindex);

			 }

		 } 
		
	}

	forread.close();
	unsigned int VerSize = time_vertexIndices.size();
	for (unsigned int i = 0; i < VerSize; i++) // ������������ ��������� ������
	{
		vertexindex = time_vertexIndices[i];
		glm::vec3 vertex = time_vertices[vertexindex - 1];
		glm::vec3 vcolor;////////time color 
		vcolor.x = 0.95f;
		vcolor.y = 0.6f;
		vcolor.z = 0.3f;
		verColor.push_back(vcolor);//end time color
		vertices.push_back(vertex);
		uvindex = time_uvIndices[i];
		if (uvindex != 0)
		{
			glm::vec2 uv = time_uvs[uvindex - 1];
			uvs.push_back(uv);
		}
		normalindex = time_normalIndices[i];
		if (normalindex != 0)
		{
			glm::vec3 normal = time_normals[normalindex - 1];
			normals.push_back(normal);
		}
		
	}
	/*vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f );
	vertices[1] = glm::vec3(1.0f , -1.0f , 0.0f );
	vertices[2] = glm::vec3(0.0f , 1.0f , 0.0f );  */
	// ������� ���������� OpenGL ����� � ��������� ��������� �� ���� � vertexbuffer
	vbo.resize(2); // ������������� ���������� VBO
	glGenBuffers(2, &vbo[0]);
	// ������ �����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	
	// ������������� ���� ������� � OpenG
	glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*verColor.size(),  &verColor[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao); // ������� VAO
	glBindVertexArray(vao);// Bind VAO
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO

 	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO */

	glBindVertexArray(0); // unbind VAO
	drawable = true;
	return;
}
void MashObject::draw()
{
	if (!drawable)
		return;
	glBindVertexArray(vao);
	
	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()); //������� � ������� 0 � ������ N ����. ����� => 1 ����������� vertices.size()

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	return;
}
MashObject::MashObject()
{
	
}
MashObject::MashObject(std::string& file_path)
{
	parser(file_path);

}


MashObject::~MashObject()
{
	/*if (vao != 0)
	{
		glDeleteVertexArrays(1, &vao);  // ������� VAO
		glDeleteBuffers(vbo.size(), &vbo[0]);// ������� ������ VBO
	}*/
}
