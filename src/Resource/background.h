
#include <glad/glad.h>
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"
#include <string>
#include "../Renderer/ResourceManager.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/Texture2D.h"
#include <memory>
#include <string>


class Background {
public:
	Background(const std::string& path, const std::string& vertex_path,
		const std::string& fragment_path, const std::string& background_path);
	void bind();
	void unbind();
private:
	std::shared_ptr<Renderer::ShaderProgram> m_program;
	std::shared_ptr<Renderer::Texture2D> m_texture;
	std::shared_ptr<Renderer::ElementBuffer> m_elemenBuffer;
	std::shared_ptr<Renderer::VertexArray> m_vertexArray;
};