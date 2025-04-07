#ifndef EBO_H
#define EBO_H

#include <vector>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class EBO
{
public:
	EBO(int drawingType);
	EBO(std::vector<unsigned int>* indices, int drawingType);
	~EBO();

	void bind();
	void unbind();

	void updateData(std::vector<unsigned int>* data);
	int getIndicesCount() const { return int(m_indices->size()); }
private:
	static EBO* boundEBO;

	unsigned int m_glEBO;

	std::vector<unsigned int>* m_indices;
	int m_drawingType;
};

} // Engine

#endif // !EBO_H
