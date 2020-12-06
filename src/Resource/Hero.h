#include <memory>
#include <glm/vec2.hpp>

namespace Renderer {
	class AnimatedSprite;
}

class hero {
public:
	enum class eOrientation {
		Left,
		Right
	};

	hero(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, glm::vec2 position);
	void render(bool mirrored = false);
	void update(uint64_t delta);
	void setOrientation(eOrientation orientation);
	void move(bool move);
private:
	eOrientation m_orienation;
	bool m_move;
	glm::vec2 m_moveOffset;
	glm::vec2 m_position;
	std::shared_ptr<Renderer::AnimatedSprite> m_pSprite;
	float m_velocity;

};
