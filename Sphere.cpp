#include "Sphere.h"
#include <vector>

Sphere::Sphere()
: InstancedDrawable() {

}

void Sphere::createVBO() {
	std::vector<GLuint> idx;
	std::vector<glm::vec4> pos;
	std::vector<glm::vec4> nor;
	std::vector<glm::vec4> col;

	unsigned int count = 0;

	for (int i = 0; i < SPHERE_DETAIL; i++) {
		float theta1 = ((float)i / (float)SPHERE_DETAIL) * TAU;
		float theta2 = ((float)(i + 1) / (float)SPHERE_DETAIL) * TAU;

		for (int j = 0; j < SPHERE_DETAIL; j++) {
			float phi1 = ((float)j / (float)SPHERE_DETAIL) * PI;
			float phi2 = ((float)(j + 1) / (float)SPHERE_DETAIL) * PI;

			glm::vec4 a = glm::vec4(SPHERE_RADIUS * glm::sin(phi1) * glm::cos(theta1), 
									SPHERE_RADIUS * glm::sin(phi1) * glm::sin(theta1),
									SPHERE_RADIUS * glm::cos(phi1), 1.f);

			glm::vec4 b = glm::vec4(SPHERE_RADIUS * glm::sin(phi1) * glm::cos(theta2),
									SPHERE_RADIUS * glm::sin(phi1) * glm::sin(theta2),
									SPHERE_RADIUS * glm::cos(phi1), 1.f);

			glm::vec4 c = glm::vec4(SPHERE_RADIUS * glm::sin(phi2) * glm::cos(theta2),
									SPHERE_RADIUS * glm::sin(phi2) * glm::sin(theta2),
									SPHERE_RADIUS * glm::cos(phi2), 1.f);

			glm::vec4 d = glm::vec4(SPHERE_RADIUS * glm::sin(phi2) * glm::cos(theta1),
									SPHERE_RADIUS * glm::sin(phi2) * glm::sin(theta1),
									SPHERE_RADIUS * glm::cos(phi2), 1.f);

			glm::vec4 n = glm::vec4(a.x / SPHERE_RADIUS, a.y / SPHERE_RADIUS, a.z / SPHERE_RADIUS, 0.f);

			glm::vec4 sphereColor = glm::vec4(0.f, 0.f, 1.f, 1.f);
			pos.insert(pos.end(), { a,b,c,d });
			nor.insert(nor.end(), { n,n,n,n });
			col.insert(col.end(), { sphereColor,sphereColor,sphereColor,sphereColor });
			idx.insert(idx.end(), { count, count + 1,count + 2,count,count + 2,count + 3 });

			count += 4;
		}
	}

	numElems = idx.size();

	generateIdx();
	if (bindIdx()) glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElems * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

	generatePos();
	if (bindPos()) 	glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(GLuint), pos.data(), GL_STATIC_DRAW);

	generateNor();
	if (bindNor()) 	glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(GLuint), nor.data(), GL_STATIC_DRAW);

	generateCol();
	if (bindCol()) 	glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(GLuint), col.data(), GL_STATIC_DRAW);
}