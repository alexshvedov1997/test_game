#include "../Renderer/ResourceManager.h"
#include "../Renderer/Texture2D.h"
#include "PhysicsManager.h"

 std::map<std::string, std::pair<glm::vec2, glm::vec2>> PhysicsManager::mObjectSizeCords;


 std::pair<glm::vec2, glm::vec2> PhysicsManager::loadObjectSizeCords(const std::string& name,
	  glm::vec2 position, glm::vec2  scale) {
	 std::pair<float, float> size = ResourceManager::getSizeObject(name);
	 std::pair<glm::vec2, glm::vec2> result;
	 result.first.x = position.x - ((size.first / 2) * scale.x * 0.01f);
	 result.second.x = position.x + ((size.first / 2) * scale.x * 0.01f);
	 result.first.y =  position.y - ((size.second) * scale.y * 0.01f);
	 result.second.y = position.y + ((size.second) * scale.y * 0.01f);
	 return result;
}

