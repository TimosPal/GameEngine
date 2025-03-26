#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <vector>
#include <Utility/Assertions.h>

namespace Engine {

// Since GL needs a buffer of type T, we cant have different types for various attributes.
template<typename T = float>
class VertexData
{
public:
	struct AttributeInfo {
		int startingOffset = 0;
		int elementsCount = 0;
		int attributeLocation = 0;
	};

	using VertexAttribute = std::vector<T>;
	using Vertex = std::vector<VertexAttribute>;

	VertexData(std::vector<Vertex>& data) 
		: m_vertexSize(0)
	{
		int prevOffset = 0;
		int location = 0;
		if (!data.empty()) 
		{
			for (const VertexAttribute& attribute : data[0]) {
				m_info.push_back(
					{
						prevOffset, // Offset
						int(attribute.size()), // #elements
						location++ // Location
					}
				);

				prevOffset += attribute.size();
				m_vertexSize += int(attribute.size()) * sizeof(T);
			}
		}

		for (const auto& vert : data)
		{
			for (const auto& attribute : vert)
			{
				m_data.insert(m_data.end(), attribute.begin(), attribute.end());
			}
		}
	}

	const std::vector<AttributeInfo>& getInfo() const { return m_info; }
	const std::vector<T>& getFlatVec() const { return m_data; }
	const int getVertexSize() const { return m_vertexSize; }
private:
	std::vector<T> m_data;
	std::vector<AttributeInfo> m_info;

	int m_vertexSize;
};

} // Engine

#endif // !VERTEX_DATA_H