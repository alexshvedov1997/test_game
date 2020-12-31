#include "../Renderer/ResourceManager.h"
#include "../Renderer/Texture2D.h"
#include "PhysicsManager.h"
#include <iostream>

 std::map<std::string, std::pair<glm::vec2, glm::vec2>> PhysicsManager::mObjectSizeCords;


 std::pair<glm::vec2, glm::vec2> PhysicsManager::loadObjectSizeCords(const std::string& name,
	  glm::vec2 position, glm::vec2  scale) {
	 std::pair<float, float> size = ResourceManager::getSizeObject(name);
	 std::pair<glm::vec2, glm::vec2> result;
	 result.first.x = position.x - ((size.first / 2) * scale.x * 0.01f);
	 result.second.x = position.x + ((size.first / 2) * scale.x * 0.01f);
	 result.first.y =  position.y - ((size.second) * scale.y * 0.01f);
	 result.second.y = position.y + ((size.second) * scale.y * 0.01f);
	 mObjectSizeCords.emplace(name, result);
	 return result;
}


 std::pair<glm::vec2, glm::vec2> PhysicsManager::getObjectSizeCords(const std::string& name) {
	 std::map<std::string, std::pair<glm::vec2, glm::vec2>>::const_iterator it = mObjectSizeCords.find(name);
	 if (it == mObjectSizeCords.end()) {
		 std::cerr << "Can't find objectSizeCoords: " << name << std::endl;
	 }
	 return it->second;
 }

 void PhysicsManager::intersectionObject(const std::string& nameObj1, const std::string& nameObj2) {
	 std::pair<glm::vec2, glm::vec2> object1 = getObjectSizeCords(nameObj1);
	 std::pair<glm::vec2, glm::vec2> object2 = getObjectSizeCords(nameObj2);
	 if ((object1.first.x < object2.first.x) &&
		// (object1.first.y >= object2.first.y && object1.first.y >= object2.second.y))
		 (object1.first.y >= -3 && object1.first.y <= 3))
		 std::cout << "Intersection :: " << nameObj1 << " and object2:: " << nameObj2 << std::endl;

 }