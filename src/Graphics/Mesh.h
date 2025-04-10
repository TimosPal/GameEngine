#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Attributes.h"

namespace Engine {

struct Mesh {

	Mesh(std::vector<float>&& vertices,
		std::vector<unsigned int>&& indices,
		AttributeInfo&& info,
		AttributeInfo::MeshMask attributesMask,
		int vertexCount)
		: vertices(vertices), indices(indices), info(info), vertexCount(vertexCount), m_attributesMask(attributesMask)
	{}

	std::vector<float>& getVertices() { return vertices; }
	std::vector<unsigned int>& getIndices() { return indices; }
	AttributeInfo& getAttributeInfo() { return info; }
	AttributeInfo::MeshMask getAttributesMask() { return m_attributesMask; }
	int getVertexCount() { return vertexCount; }

protected:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	AttributeInfo info;
	AttributeInfo::MeshMask m_attributesMask;

	int vertexCount;
};

} // Engine

#endif // !MESH_H
