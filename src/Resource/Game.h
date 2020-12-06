#include <memory>
#include <SDL.h>

class Background;
class hero;

class Game {
public:
	Game();
	void init();
	void bind();
	void unbind_back();
	void render();
	void update(float delta);
private:
	std::unique_ptr<Background> m_background;
	//std::unique_ptr<hero> m_Hero;
	std::shared_ptr<hero> m_Hero;
	bool m_mirrored;
};