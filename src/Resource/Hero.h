#include <memory>
#include <glm/vec2.hpp>

namespace Renderer {
	class AnimatedSprite;
}

class hero {
public:
	enum class eOrientation {
		Left,
		Right,
		Stand
	};

	hero(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, glm::vec2 position);
	void render(bool mirrored = false, float level = 0.1f);
	void update(uint64_t delta);
	void setOrientation(eOrientation orientation);
	void move(bool move);
	glm::vec2 getPosition() { return m_position; }
	std::shared_ptr<Renderer::AnimatedSprite> getHeroSprite() { return m_pSprite; }
	//glm::vec2 getSizeObjectInSpace();
private:
	eOrientation m_orienation;
	bool m_move;
	glm::vec2 m_moveOffset;
	glm::vec2 m_position;
	std::shared_ptr<Renderer::AnimatedSprite> m_pSprite;
	float m_velocity;

};
