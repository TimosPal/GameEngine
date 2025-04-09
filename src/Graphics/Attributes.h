#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

namespace Engine {

struct AttributeInfo {
	std::vector<int> shaderLocations;
	std::vector<int> elementsCount;
	int totalElementsPerVertex;

	enum VertexAttrib : uint16_t {
		ATTRIB_POS = 1 << 0,
		ATTRIB_NORM = 1 << 1,
		ATTRIB_UV = 1 << 2,
		ATTRIB_COLOR = 1 << 3,
	};

	using AttributeProgramMask = uint32_t;
	using AttributeMask = uint16_t;
	AttributeMask enabledAttributes;
};

}

#endif // !ATTRIBUTES_H