#ifndef RENDERER_2D_HPP
#define RENDERER_2D_HPP

#include "core/pch.hpp"
#include "renderer/SpriteQuad.hpp"
#include "renderer/DrawCommand2D.hpp"
#include "resources/SystemResourceHub.hpp"
#include "renderer/IGPUAssets.hpp"
#include "renderer/TextureSlotManager.hpp"
#include "renderer/camera/CameraController.hpp"

namespace Engine {

class Renderer2D {
public:
	virtual bool init() { return false; }
	virtual bool terminate() { return false; }

    virtual void clearScreen() {}
    virtual void render(CameraController& camera) {}

	virtual IGPUAssets& getGPUAssets() = 0;

	void drawQuad(SpriteQuad&& spriteQuad)
	{
		m_spriteDrawCommands.emplace_back(std::move(spriteQuad));
	}

	void drawTilemap(TilemapMesh&& quadMesh)
	{
		m_tilemapDrawCommands.emplace_back(std::move(quadMesh));
	}

	void drawLine(Line&& line)
	{
		m_lineDrawCommands.emplace_back(std::move(line));
	}

	void drawSquare(glm::vec2 min, glm::vec2 max, const glm::vec4& color)
	{
		glm::vec2 topLeft = { min.x, max.y };
		glm::vec2 topRight = { max.x, max.y };
		glm::vec2 bottomLeft = { min.x, min.y };
		glm::vec2 bottomRight = { max.x, min.y };
		drawLine({ topLeft, topRight, color });
		drawLine({ topRight, bottomRight, color });
		drawLine({ bottomRight, bottomLeft, color });
		drawLine({ bottomLeft, topLeft, color });
	}

	virtual void setViewportSize(uint32_t width, uint32_t height) {}

	static std::unique_ptr<Renderer2D> createRenderer2D(SystemResourceHub& systemResourceHub);

protected:
	std::vector<SpriteQuad> m_spriteDrawCommands;
	std::vector<TilemapMesh> m_tilemapDrawCommands;
	std::vector<Line> m_lineDrawCommands;

	TextureSlotManager m_textureSlotManager;
};

} // Engine

#endif // !RENDERER_2D_HPP