#include "MashObject.hpp"
#include <glm/glm.hpp>
void MashObject :: parser(std::string& file_path)
{
	path = file_path; // ��������� obj ����
	std::ifstream forread;
	forread.open(file_path);
	if (!forread.is_open())
		return;
	std::vector < glm::dvec3 >  time_vertices; // ���������� �������
	std::vector < glm::dvec2 >  time_uvs; //���������� ���������� �������
	std::vector < glm::dvec3 >  time_normals;// ���������� �������
	std::vector <long int > time_vertexIndices, time_uvIndices, time_normalIndices; // ������ ���������, �������, ��������
	long int vertexindex, uvindex, normalindex;
	std::string lineHeader = ""; //������ � ������� ����� ���������	
	while (!forread.eof())  // ������ ����
	{
		 forread >>lineHeader;
		 if (lineHeader == "v") //���������� �������
		 {
			 glm::dvec3 vertex; // ��������� ������ ���������� �������
			 forread >> vertex.x >> vertex.y >> vertex.z;
			 time_vertices.push_back(vertex);
			 continue;
		 }
		 if (lineHeader == "vt") // ���������� ���������� �������
		 {
			 glm::dvec2 uv; // ��������� ������ ��������
			 forread >> uv.x >> uv.y;
			 time_uvs.push_back(uv);
			 continue;
		 }
		 if (lineHeader == "vn") // ������ �������
		 {
			 glm::dvec3 normal;// ��������� ������ �������
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
		glm::dvec3 vertex = time_vertices[vertexindex - 1];
		vertices.push_back(vertex);
		uvindex = time_uvIndices[i];
		if (uvindex != 0)
		{
			glm::dvec2 uv = time_uvs[uvindex - 1];
			uvs.push_back(uv);
		}
		normalindex = time_normalIndices[i];
		if (normalindex != 0)
		{
			glm::dvec3 normal = time_normals[normalindex - 1];
			normals.push_back(normal);
		}
		
	}
	// ������� ���������� OpenGL ����� � ��������� ��������� �� ���� � vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// ������ �����
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// ������������� ���� ������� � OpenG
	glBufferData(GL_ARRAY_BUFFER,3*sizeof(glm::dvec3), &vertices[0], GL_STATIC_DRAW);
	drawable = true;
	return;
}
void MashObject::draw()
{
	if (!drawable)
		return;
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // ������� 0. ����������� ������ � ���� ���, �� ����� ������ ��������� � ������ � �������
		vertices.size(),                  // ����������
		GL_FLOAT,           // ���
		GL_FALSE,           // ��������������� ��?
		0,                  // ���
		(void*)0            // �������� � ������
		);

	// ������ ����������� !
	
	glDrawArrays(GL_TRIANGLES, 0, 3); //������� � ������� 0 � ������ N ����. ����� => 1 �����������
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
}
