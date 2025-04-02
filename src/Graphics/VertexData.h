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

	VertexData()
		: m_vertexSize(0)
	{}

	VertexData(std::vector<Vertex>& data) 
		: m_vertexSize(0)
	{
		updateData(data);
	}

	void addData(std::vector<Vertex>& data)
	{
		if (!data.empty() && m_info.empty())
		{
			initAttributeInfo(data[0]);
		}

		for (const auto& vert : data)
		{
			for (const auto& attribute : vert)
			{
				m_data.insert(m_data.end(), attribute.begin(), attribute.end());
			}
		}
	}

	void initAttributeInfo(const Vertex& vertex)
	{
		int prevOffset = 0;
		int location = 0;
		for (const VertexAttribute& attribute : vertex) {
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