#include <iostream>
#include <cmath>
#include <random>

#include <core/EntryPoint.hpp>
#include <core/EngineApp.hpp>

#include <utilities/Logger.hpp>
#include <events/types/WindowCloseEvent.hpp>
#include <layers/Layer.hpp>
#include <ecs/types/EngineComponents.hpp>
#include <core/ResourceRegistry.hpp>

using namespace Engine;

inline float quickRandFloat(float min = -1.0f, float max = 1.0f) {
    return min + (max - min) * (rand() / float(RAND_MAX));
}

struct VelocityComponent {
    float vx, vy;
};

class UnitSystem : public ISystem {
public:
    float spawnTimer = 0.0f;
    float currentAngle = 0.0f;
    const float angleStep = 10.0f;  // radians per spawn
    const float circleRadius = 0.5f;
    const float speed = 0.5f;
    const int maxSpawns = 10000;
    int spawnCount = 0;

    void update(float deltaTime) override
    {
        // Move and bounce units
        getWorld()->query<TransformComponent, VelocityComponent>().each([deltaTime](TransformComponent* t, VelocityComponent* v) {
            t->x += v->vx * deltaTime;
            t->y += v->vy * deltaTime;

            if (t->x < -1.0f || t->x > 1.0f) {
                t->x = std::clamp(t->x, -1.0f, 1.0f);
                v->vx *= -1.0f;
            }
            if (t->y < -1.0f || t->y > 1.0f) {
                t->y = std::clamp(t->y, -1.0f, 1.0f);
                v->vy *= -1.0f;
            }
        });

        // Spawn logic every 0.01 seconds
        spawnTimer += deltaTime;
        if (spawnTimer >= 0.1f && spawnCount < maxSpawns) {
            spawnTimer = 0.0f;
            spawnCount++;

            if (spawnCount % 1000 == 0) LOG_INFO("Count: {}", spawnCount);

            // Spawn at center
            float x = 0.0f;
            float y = 0.0f;

            // Velocity radially outward
            float vx = speed * cos(currentAngle);
            float vy = speed * sin(currentAngle);

            // Random color
            float r = quickRandFloat(0.0f, 1.0f);
            float g = quickRandFloat(0.0f, 1.0f);
            float b = quickRandFloat(0.0f, 1.0f);

            float size = 0;

            float textureRNG = quickRandFloat(0.0f, 1.0f);
            ID textureID;
            if (textureRNG < 0.99f)
            {
                textureID = getAssetsManager()->getTexture("bee");
                size = 0.1f;
            }
            else
            {
                textureID = getAssetsManager()->getTexture("ball");
                size = 0.2f;
            }

            ID unit = getWorld()->createEntity();
            getWorld()->addComponents(
                unit,
                SpriteComponent{ r, g, b, 1.0f, textureID},
                TransformComponent{ x, y, size, size },
                VelocityComponent{ vx, vy }
            );
            
            currentAngle += angleStep * deltaTime;
            if (currentAngle > 2.0f * 3.1415926f)
                currentAngle -= 2.0f * 3.1415926f;
        }
    }
};

class GameLayer : public Layer {
public:
    void onAttach() override
    {
        addSystem(std::make_unique<UnitSystem>());
    }
};

class MyApp : public Engine::EngineApp {
    AppConfig config() override { return AppConfig(800, 600, "Balls!"); }

    void setup() override
    {
        getAssetsManager().createTexture("bee", std::string(ResourcePaths::ImagesDir) + "./bee.png");
        getAssetsManager().createTexture("ball", std::string(ResourcePaths::ImagesDir) + "./ball.png");

        pushLayer(std::make_unique<GameLayer>());
    }
};

CREATE_ENGINE_APPLICATION(MyApp)
