#include "Math/Barycentric.h"

bool Barycentric::barycentricIsInside(glm::vec3 pos)
{
	for (int i = 0; i < 3; i++)
	{
		if (pos[i] < 0.f || pos[i] > 1.f)
			return false;	
	}
	
	return true;
}

glm::vec3 Barycentric::calcBarycentric(glm::vec2 point, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
{

	//Vab & Vac
	glm::vec2 Va = p2 - p1;
	glm::vec2 Vb = p3 - p1;
	glm::vec3 n = glm::cross(glm::vec3(Va.x, Va.y, 0), glm::vec3(Vb.x, Vb.y, 0));
	float areal_123 = glm::length(n);
	glm::vec3 baryc;

	// u
	glm::vec2 p = p2 - point;
	glm::vec2 q = p3 - point;
	n = glm::cross(glm::vec3(p.x, p.y, 0), glm::vec3(q.x, q.y, 0));
	baryc.x = n.z / areal_123;

	// v
	p = p3 - point;
	q = p1 - point;
	n = glm::cross(glm::vec3(p.x, p.y, 0), glm::vec3(q.x, q.y, 0));

	baryc.y = n.z / areal_123;

	// w
	p = p1 - point;
	q = p2 - point;
	n = glm::cross(glm::vec3(p.x, p.y, 0), glm::vec3(q.x, q.y, 0));
	baryc.z = n.z / areal_123;

	return baryc;
}

///Use example from last semester!!!


//float Heightmap::getHeight(glm::vec3 position)
//{
//
//	if (IsInside(position))
//	{
//		int x = position.x / mScale / mDetail + mWidth / 2;
//		int y = position.y / mScale / mDetail + mWidth / 2;
//
//		auto p1 = x + y * mHeight;
//		auto p2 = (x + 1) + (y * mHeight);
//		auto p3 = (x + 1) + ((y + 1) * mHeight);
//		auto p4 = x + ((y + 1) * mHeight);
//
//		if (p3 > mVertices.size())
//			return 1.f;
//
//		glm::vec2 a(mVertices[p1].getXYZ().x, mVertices[p1].getXYZ().y);
//		glm::vec2 b(mVertices[p2].getXYZ().x, mVertices[p2].getXYZ().y);
//		glm::vec2 c(mVertices[p3].getXYZ().x, mVertices[p3].getXYZ().y);
//		glm::vec2 d(mVertices[p4].getXYZ().x, mVertices[p4].getXYZ().y);
//
//		glm::vec3 baryCoords = Barycentric::calcBarycentric(glm::vec2(position.x, position.y), a, b, c);
//
//		//Find triangle to use
//
//		if (Barycentric::barycentricIsInside(baryCoords))
//		{
//			auto p1h = mVertices[p1].getXYZ().z * baryCoords.x;
//			auto p2h = mVertices[p2].getXYZ().z * baryCoords.y;
//			auto p3h = mVertices[p3].getXYZ().z * baryCoords.z;
//
//			RenderWindow::triangle[0] = mVertices[p1].getXYZ();
//			RenderWindow::triangle[1] = mVertices[p2].getXYZ();
//			RenderWindow::triangle[2] = mVertices[p3].getXYZ();
//
//			auto height = p1h + p2h + p3h;
//
//			return height;
//		}
//		else
//		{
//			baryCoords = Barycentric::calcBarycentric(glm::vec2(position.x, position.y), a, c, d);
//
//			auto p1h = mVertices[p1].getXYZ().z * baryCoords.x;
//			auto p2h = mVertices[p3].getXYZ().z * baryCoords.y;
//			auto p3h = mVertices[p4].getXYZ().z * baryCoords.z;
//
//			RenderWindow::triangle[0] = mVertices[p1].getXYZ();
//			RenderWindow::triangle[1] = mVertices[p3].getXYZ();
//			RenderWindow::triangle[2] = mVertices[p4].getXYZ();
//
//			auto height = p1h + p2h + p3h;
//
//			return height;
//
//		}
//	}
//
//}