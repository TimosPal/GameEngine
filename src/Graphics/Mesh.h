#ifndef MESH_H
#define MESH_H

#include <vector>

namespace Engine {

struct Mesh {
	struct AttributeInfo {
		std::vector<int> shaderLocations;
		std::vector<int> elementsCount;
		int totalElementsPerVertex;
	};

	AttributeInfo& getAttributeInfo() { return info; }

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	AttributeInfo info;

	Mesh(std::vector<float>&& vertices, std::vector<unsigned int>&& indices, AttributeInfo info) 
		: vertices(vertices), indices(indices), info(info)
	{}
};

} // Engine

#endif // !MESH_H
