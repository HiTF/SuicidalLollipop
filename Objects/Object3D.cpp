#include "Object3D.hpp"
#include "../GLfunc.hpp"

Object3D::Object3D()
{
}
Object3D::Object3D(std::string path)
{
	model = MashObject(path);

}
Object3D::Object3D(const Object3D & obj)
{
	coord = obj.coord;
	A = obj.A;
	ex = A[0];
	ey = A[1];
    ez = A[2];
	model = obj.model;
}
void Object3D::draw()
{
	if (!model.is_drawable())
		return;
	Gl::shaders.useProgram();
	glm::mat4 MVP = Gl::Projection * Gl::View*Model();
	Gl::shaders.store_MVP(&MVP[0][0]);
	model.draw();
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection, glm :: dvec3 upperdirection)
{
	coord = position;
	ex = lookdirection;
	ez = upperdirection;
	if(glm ::dot(ex, ex) != 1.0)
		ex /= sqrt(glm:: dot(ex, ex));
	if(glm ::dot(ex, ex) != 1.0)
		ez /= sqrt(glm:: dot(ez, ez));
	ey = ez*ex;
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection)
{
	coord = position;
	ex = lookdirection;
	if(glm ::dot(ex, ex) != 1.0)
		ex /= sqrt(glm:: dot(ex, ex));
	ey = ez*ex;
}
glm::mat4 Object3D::Model()
{
	return glm::mat4(glm::vec4(A[0], 0), glm::vec4(glm::vec3(ey), 0), glm::vec4(glm::vec3(ez), 0), glm::vec4(glm::vec3(coord), 1));
}

void Object3D:: set(glm :: dvec3 position)
{
	coord = position;
}

glm :: dvec3 Object3D:: getPosition()
{
	return coord;
}
glm :: dvec3 Object3D:: getLookDirection()
{
	return ex;
}
glm :: dvec3 Object3D:: getUpperDirection()
{
	return ez;
}

Object3D::~Object3D()
{
}
