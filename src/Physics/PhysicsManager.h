#include <map>
#include <glm/vec2.hpp>
#include<string>
class PhysicsManager {
public:
	
	static std::pair<glm::vec2, glm::vec2> loadObjectSizeCords(const std::string& name,
		 glm::vec2 position, glm::vec2  scale);
	static std::pair<glm::vec2, glm::vec2> getObjectSizeCords(const std::string& name);
	static void intersectionObject(const std::string& nameObj1, const std::string& nameObj2);
private:
	static std::map<std::string, std::pair<glm::vec2, glm::vec2>> mObjectSizeCords;
};