#ifndef SCENE_HPP
#define SCENE_HPP

#include "core/pch.hpp"
#include "core/EngineContext.hpp"
#include "ecs/World.hpp"
#include "renderer/camera/CameraController.hpp"
#include "ecs/SystemManager.hpp"
#include "physics/PhysicsEngine.hpp"
#include "events/EventCallback.hpp"

namespace Engine {

class Scene : public InjectEngineContext {
public:
	void init();

	World& getWorld() { return m_world; }
	PhysicsEngine& getPhysicsEngine() { return m_physicsEngine; } // TODO: maybe return a protected interface instead of the whole physics engine?
	
	std::shared_ptr<CameraController> getCameraController() const { return m_cameraController; }
	
	void onUpdate(float deltaTime);
	void updateWorldActions() { m_world.executeDeferredActions(); }

	virtual void onLoad() {};
protected:
	void setCameraController(std::shared_ptr<CameraController> cameraController) { m_cameraController = cameraController; }

	SystemManager& getSystemManager() { return m_systemManager; } // TODO: make a more protective interface for client side use.
private:
	// NOTE: each scene has its own world and own physics colliders.
	World m_world;
	PhysicsEngine m_physicsEngine;

	std::shared_ptr<CameraController> m_cameraController;
	SystemManager m_systemManager;
};

} // Engine

#endif // !SCENE_HPP