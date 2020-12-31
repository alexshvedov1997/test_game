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
	void intersectObject();
	void PrintHeroCoord();
	bool is_quit() {
		return m_quit;
	}
private:
	std::unique_ptr<Background> m_background;
	//std::unique_ptr<hero> m_Hero;
	std::shared_ptr<hero> m_Hero;
	bool m_mirrored;
	bool m_quit = false;
};