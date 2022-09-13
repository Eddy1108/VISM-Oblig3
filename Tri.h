#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include <string>
#include <vector>

class Tri 
{
public:

	Tri();
	Tri(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	~Tri();

	glm::vec3 m_a;
	glm::vec3 m_b;
	glm::vec3 m_c;
	glm::vec3 N;

	std::vector<Tri> TriVector;
 
	static std::vector<Tri> TriangleVectorFromFile(const std::string& path);

	void TriangleVectorFromFileLocal(const std::string& path);

//protected:
//
//	void init(GLint matrixUniform);
//	void draw();
};

