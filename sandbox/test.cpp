#include <Core/EntryPoint.h>
#include <iostream>

#include <Core/World.h>
#include <GameObjects/EngineComponents/SpriteComponent.h>

#include <GameObjects/IComponent.h>
#include <Input/InputManager.h>

#include <cmath>    // For sin() and cos()

Configuration config{ 1000, 800, "MyAppTest" };

class Unit : public GameObjects::IComponent<Unit>
{
public:
	void getDirection(float m_x, float m_y, float mouse_x, float mouse_y, float& dir_x, float& dir_y) {
		dir_x = mouse_x - m_x;
		dir_y = mouse_y - m_y;

		float length = std::sqrt(dir_x * dir_x + dir_y * dir_y);
		if (length > 0.0f) {
			dir_x /= length;
			dir_y /= length;
		}
	}

	std::shared_ptr<GameObjects::SpriteComponent> spriteRend;

	virtual void start() override
	{
		startingR = 0.5f + static_cast<float>(rand()) / RAND_MAX;
		startingG = 0.5f + static_cast<float>(rand()) / RAND_MAX;
		startingB = 0.5f + static_cast<float>(rand()) / RAND_MAX;

		spriteRend = getOwner().getComponent<GameObjects::SpriteComponent>();
	};

	virtual void update() override
	{
		// Update colors (unchanged)
		float percentage = 0.7f;
		spriteRend->m_r = startingR * (1 - percentage) + spriteRend->m_y * percentage;
		spriteRend->m_g = startingG * (1 - percentage) + spriteRend->m_x * percentage;
		spriteRend->m_b = startingB * (1 - percentage);

		// Generate random angle change
		float newAngle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14f * 0.02f;
		startAngle += newAngle; // Keeps the movement continuous

		float speed = 0.005f;

		// Compute orbit movement
		float moveX = speed * cos(startAngle);
		float moveY = speed * sin(startAngle);

		// Get mouse position from InputManager
		float mouse_x_screen = InputManager::getInstance().getMousePosX();
		float mouse_y_screen = InputManager::getInstance().getMousePosY();

		// Get screen dimensions (assumed to be available in your system)
		float screenWidth = 1000;  // Example screen width in pixels
		float screenHeight = 800; // Example screen height in pixels

		// Convert mouse position to normalized coordinates (-1 to 1)
		float mouse_x = (mouse_x_screen / screenWidth) * 2.0f - 1.0f;
		float mouse_y = 1.0f - (mouse_y_screen / screenHeight) * 2.0f;  // In OpenGL, Y is flipped

		// Compute direction to mouse
		float dir_x = mouse_x - spriteRend->m_x;
		float dir_y = mouse_y - spriteRend->m_y;
		float length = std::sqrt(dir_x * dir_x + dir_y * dir_y);

		// Normalize and scale toward mouse (correct for all quadrants)
		if (length > 0.0f) {
			dir_x /= length;
			dir_y /= length;
		}

		float attractionStrength = 0.005f; // Small pull towards mouse
		moveX += dir_x * attractionStrength;
		moveY += dir_y * attractionStrength;

		// Apply movement
		spriteRend->m_x += moveX;
		spriteRend->m_y += moveY;

	};

	float startAngle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14f;
	
	float startingR;
	float startingG;
	float startingB;

};

class Controller : public GameObjects::IComponent<Controller>
{
public:

	virtual void start() override {};

	virtual void update() override
	{
		if (InputManager::getInstance().isActionTriggered(Action("Spawn", Key::Space, KeyState::Type::Hold)))
		{
			float mX = InputManager::getInstance().getMousePosX() / 1000.0f;
			float mY = InputManager::getInstance().getMousePosY() / 800.0f;

			// 0 - 1 -> x2 - 1 = 0 - 2 = -1 1

			for (size_t i = 0; i < 20; i++)
			{
				GameObjects::GameObject newGo;
				auto& go = Application::getInstance()->getWorld().getGOManager().createGameObject(newGo);
				GameObjects::SpriteComponent spriteComponent(
					"./assets/textures/bee.png",
					0.0f,
					0.0f,
					0.0f,
					2 * mX - 1,
					2 * (1 - mY) - 1
				);
				go.addComponent<GameObjects::SpriteComponent>(spriteComponent);
				go.addComponent<Unit>();

				count++;
				if (count % 50 == 0)
					LOG_INFO("Count: {}", count);
			}
		}
	};

	int count = 0;

};

class Test : public Application
{
public:
	Test() : Application(config) {}

	void start() override
	{
		InputManager::getInstance().registerAction(Action("Spawn", Key::Space, KeyState::Type::Hold));

		GameObjects::GameObject newGo;
		auto& go = Application::getWorld().getGOManager().createGameObject(newGo);
		go.addComponent<Controller>();

		//for (size_t i = 0; i < 100; i++)
		//{
		//	for (size_t j = 0; j < 100; j++)
		//	{
		//		GameObjects::GameObject newGo2;
		//		auto& go2 = Application::getWorld().getGOManager().createGameObject(newGo2);
		//		GameObjects::SpriteComponent spriteComponent(
		//			"./assets/textures/bee.png",
		//			0.0f,
		//			0.0f,
		//			0.0f,
		//			-0.5 + i * 0.01f,
		//			-0.5 + j * 0.01f
		//		);
		//		go2.addComponent<GameObjects::SpriteComponent>(spriteComponent);
		//	}
		//}
	}

};

CREATE_APPLICATION(Test)