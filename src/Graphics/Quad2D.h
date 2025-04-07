#ifndef QUAD_2D_H
#define QUAD_2D_H

#include <vector>

#include <Graphics/Mesh.h>

namespace Engine {

struct Quad2D : public Mesh {
	Quad2D(float x, float y, float width, float height, float r, float g, float b);

	void updateX(float x);
	void updateY(float y);
	
	void updateR(float r);
	void updateG(float g);
	void updateB(float b);

private:
	float width, height;
};

} // Engine

#endif // !QUAD_2D_H
