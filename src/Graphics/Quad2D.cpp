#include "Quad2D.h"

namespace Engine {

Quad2D::Quad2D(float x, float y, float width, float height, float r, float g, float b)
	: width(width), height(height),
	Mesh(
        // Vertex data
        std::vector<float>({
		/*  pos   colors   uvs          */
			x - width, y - height, r, g, b, 0.0f, 0.0f, // Bottom-left  
			x - width, y + height, r, g, b, 0.0f, 1.0f, // Top-left  
			x + width, y + height, r, g, b, 1.0f, 1.0f, // Top-right  
			x + width, y - height, r, g, b, 1.0f, 0.0f  // Bottom-right  
		}),

        // Indexing data. (Reduces 6 vertices to 4)
        std::vector<unsigned int>({
            0, 2, 1,  // First triangle (Clockwise)  
            0, 3, 2   // Second triangle (Clockwise)  
        }),

        // Define the attribute information for the quad
        {
            { 0, 1, 2 }, // Shader Location0 Location1 Location2
            { 2, 3, 2 }, // Vec2(X, Y), Vec3(R, G, B), Vec2(U, V)
            7, // Total elements per vertex
            
        },

        // Enabled attributes
        VertexAttrib::ATTRIB_POS | VertexAttrib::ATTRIB_COLOR | VertexAttrib::ATTRIB_UV,

        // 4 vertices for the quad
        4 
	)
{}

void Quad2D::updateX(float x)
{
    int vertSize = info.totalElementsPerVertex;
    int offset = 0;  // Offset for x

    // Update the x positions of the vertices (considering width)
    vertices[0 * vertSize + offset] = x - width; // Bottom-left
    vertices[1 * vertSize + offset] = x - width; // Top-left
    vertices[2 * vertSize + offset] = x + width; // Top-right
    vertices[3 * vertSize + offset] = x + width; // Bottom-right
}

void Quad2D::updateY(float y)
{
    int vertSize = info.totalElementsPerVertex;
    int offset = 1;  // Offset for y

    // Update the y positions of the vertices (considering height)
    vertices[0 * vertSize + offset] = y - height; // Bottom-left
    vertices[1 * vertSize + offset] = y + height; // Top-left
    vertices[2 * vertSize + offset] = y + height; // Top-right
    vertices[3 * vertSize + offset] = y - height; // Bottom-right
}

void Quad2D::updateR(float r)
{
    int vertSize = info.totalElementsPerVertex;
    int offset = 2;  // Offset for r

    // Update the red color value for all 4 vertices
    vertices[0 * vertSize + offset] = r; // Bottom-left
    vertices[1 * vertSize + offset] = r; // Top-left
    vertices[2 * vertSize + offset] = r; // Top-right
    vertices[3 * vertSize + offset] = r; // Bottom-right
}

void Quad2D::updateG(float g)
{
    int vertSize = info.totalElementsPerVertex;
    int offset = 3;  // Offset for g

    // Update the green color value for all 4 vertices
    vertices[0 * vertSize + offset] = g; // Bottom-left
    vertices[1 * vertSize + offset] = g; // Top-left
    vertices[2 * vertSize + offset] = g; // Top-right
    vertices[3 * vertSize + offset] = g; // Bottom-right
}

void Quad2D::updateB(float b)
{
    int vertSize = info.totalElementsPerVertex;
    int offset = 4;  // Offset for b

    // Update the blue color value for all 4 vertices
    vertices[0 * vertSize + offset] = b; // Bottom-left
    vertices[1 * vertSize + offset] = b; // Top-left
    vertices[2 * vertSize + offset] = b; // Top-right
    vertices[3 * vertSize + offset] = b; // Bottom-right
}

} // Engine