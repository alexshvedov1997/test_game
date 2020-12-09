#pragma once
#include "Sprite.h"
#include <map>
#include <utility>
#include <vector>
namespace Renderer {
	

	class AnimatedSprite:public Sprite {
	public:
		AnimatedSprite(std::shared_ptr<ShaderProgram> program, 
			const std::string& initialSubTexture,
			std::shared_ptr<Texture2D> texture,
			glm::vec2 position, glm::vec2 size, float rotation = 0);
		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTextureDuartion);
		void renderer(bool mirrored = false, float level = 0.1f) override;
		void update(uint64_t delta);
		void setState(std::string state);
	protected:
		std::map < std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		uint64_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		std::map < std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_currentAnimationDurations;
		bool m_dirty = false;
	};

}