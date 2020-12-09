#include "Hero.h"
#include "../Renderer/AnimatedSprite.h"
#include "../Renderer/ShaderProgram.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

hero::hero(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, glm::vec2 position):
m_position(position),
 m_pSprite(pSprite),
m_velocity(velocity),
m_moveOffset(glm::vec2(0.f, 1.f)),
m_move(false),
m_orienation(eOrientation::Right)
{


}

void hero::render(bool mirrored, float level) {
	m_pSprite->renderer(mirrored, level);
}

void hero::setOrientation(eOrientation orientation) {
	if (m_orienation == orientation) return;
	m_orienation = orientation;
	switch (m_orienation)
	{
	case eOrientation::Right:
		m_pSprite->setState("heroRightState");
		m_moveOffset.x = 1.0f;
		m_moveOffset.y = 0.0f;
		break;
	case eOrientation::Left:
		//m_pSprite->setState("heroLeftState");
		m_pSprite->setState("heroRightState");
		m_moveOffset.x = -1.0f;
		m_moveOffset.y = 0.0f;
		break;
	case eOrientation::Stand:
		//m_pSprite->setState("heroLeftState");
		m_pSprite->setState("heroStand");
		m_moveOffset.x = 0.0f;
		m_moveOffset.y = 0.0f;
		break;

	default:
		break;
	}
}

void hero::move(bool move) {
	m_move = move;
}

void hero::update(uint64_t delta) {
	if (m_move) {
		m_position += delta * m_velocity * m_moveOffset;
		m_pSprite->setPosition(m_position);
		m_pSprite->update(delta);
	}
}