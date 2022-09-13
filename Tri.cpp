#include "Tri.h"

#include <fstream>
#include <sstream>
#include <iostream>

Tri::Tri()
{
}

Tri::Tri(glm::vec3 a, glm::vec3 b, glm::vec3 c) : m_a{ a }, m_b{ b }, m_c{c}
{
	//N.x = ((m_a.y * m_b.z) - (m_a.z * m_b.y));
	//N.y = ((m_a.z * m_b.x) - (m_a.x * m_b.z));
	//N.z = ((m_a.x * m_b.y) - (m_a.y * m_b.x));
}

Tri::~Tri()
{
}

std::vector<Tri> Tri::TriangleVectorFromFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "ERROR! File not found!\n\n";
		return std::vector<Tri>();
	}
	std::cout << "FILE FOUND! \n\n";
    
	uint32_t vertexCount{};
	std::string s;
	std::getline(file, s);
	std::stringstream ssCount(s);
	ssCount >> vertexCount;

	std::vector<glm::vec3> vertexData;
	for (uint32_t i = 0; i < vertexCount; i++)
	{
		std::string line;
		std::getline(file, line);
		std::stringstream ss(line);

		glm::vec3 vertex;
		ss >> vertex.x;
		ss >> vertex.y;
		ss >> vertex.z;

		vertexData.push_back(vertex);
	}

	std::vector<Tri> out;
	for (uint32_t i = 2; i < vertexData.size(); i += 3)
	{
		Tri tri;
		tri.m_a = vertexData[i - 2];
		tri.m_b = vertexData[i - 1];
		tri.m_c = vertexData[i - 0];

		glm::vec3 ac = tri.m_c - tri.m_a;
		glm::vec3 ab = tri.m_b - tri.m_a;

		tri.N = glm::normalize(glm::cross(ab, ac));

		std::cout << "i count: " << i << "\n";
		std::cout << "Tri N: " << tri.N.x << ", " << tri.N.y << ", " << tri.N.z << "\n\n";

		out.push_back(tri);
	}

	return out;
}

void Tri::TriangleVectorFromFileLocal(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "ERROR! File not found!\n\n";
		return;
	}
	std::cout << "FILE FOUND! \n\n";

	uint32_t vertexCount{};
	std::string s;
	std::getline(file, s);
	std::stringstream ssCount(s);
	ssCount >> vertexCount;

	std::vector<glm::vec3> vertexData;
	for (uint32_t i = 0; i < vertexCount; i++)
	{
		std::string line;
		std::getline(file, line);
		std::stringstream ss(line);

		glm::vec3 vertex;
		ss >> vertex.x;
		ss >> vertex.y;
		ss >> vertex.z;

		vertexData.push_back(vertex);
	}

	for (uint32_t i = 2; i < vertexData.size(); i += 3)
	{
		Tri tri;
		tri.m_a = vertexData[i - 2];
		tri.m_b = vertexData[i - 1];
		tri.m_c = vertexData[i - 0];

		glm::vec3 ac = tri.m_c - tri.m_a;
		glm::vec3 ab = tri.m_b - tri.m_a;

		tri.N = glm::normalize(glm::cross(ab, ac));

		std::cout << "Tri N: " << tri.N.x << ", " << tri.N.y << ", " << tri.N.z << "\n\n";

		TriVector.push_back(tri);
	}

	for (int i = 0; i < TriVector.size(); i++)
	{

	}

}

//void Tri::init(GLint matrixUniform)
//{
//	//mMatrixUniform = matrixUniform;
//	//initializeOpenGLFunctions();
//
//	////Vertex Array Object - VAO
//	//glGenVertexArrays(1, &mVAO);
//	//glBindVertexArray(mVAO);
//
//	////Vertex Buffer Object to hold vertices - VBO
//	//glGenBuffers(1, &mVBO);
//	//glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//
//	//glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(gsml::Vertex), mVertices.data(), GL_STATIC_DRAW);
//
//	//// 1rst attribute buffer : vertices
//	//glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gsml::Vertex), (GLvoid*)0);
//	//glEnableVertexAttribArray(0);
//
//	//// 2nd attribute buffer : colors
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(gsml::Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
//	//glEnableVertexAttribArray(1);
//
//	////enable the matrixUniform
//	//// mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );
//
//	//glBindVertexArray(0);
//}
//
//void Tri::draw()
//{
//	//glBindVertexArray(mVAO);
//	//glUniformMatrix4fv(mMatrixUniform, 1, GL_TRUE, mMatrix.constData());
//	//glDrawArrays(GL_TRIANGLES, 0, mVertices.size());//mVertices.size());
//
//}
