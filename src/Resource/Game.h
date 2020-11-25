#include <memory>


class Background;

class Game {
public:
	Game();
	void init();
	void bind();

private:
	std::unique_ptr<Background> m_background;

};