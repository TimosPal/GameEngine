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

	Mesh(std::vector<float>&& vertices, std::vector<unsigned int>&& indices, AttributeInfo info, int vertexCount) 
		: vertices(vertices), indices(indices), info(info), vertexCount(vertexCount)
	{}

	std::vector<float>& getVertices() { return vertices; }
	std::vector<unsigned int>& getIndices() { return indices; }
	AttributeInfo& getAttributeInfo() { return info; }
	int getVertexCount() { return vertexCount; }

protected:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	AttributeInfo info;
	int vertexCount;
};

} // Engine

#endif // !MESH_H
