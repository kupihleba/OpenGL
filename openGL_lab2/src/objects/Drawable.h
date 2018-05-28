#pragma once
#include <objects/Object.h>
#include <memory>
#include <lib/Texture.h>
#include <set>
#include <utils/kupihleba.h>

namespace obj {
	class Drawable : public Object
	{
	public:
		Drawable(std::shared_ptr<Shader> shader);

		void draw();

		/// <summary>
		/// Switches between GL_FILL, GL_LINE, etc
		/// </summary>
		void setView(GLint view);

		/// <returns>
		/// Current gl view (GL_FILL, GL_LINE, etc)
		/// </returns>
		GLint getView() const;

		static GLint loadTexture(const string & path);
		void setTexture(const GLint id);

	protected:

		void loadVertices();

		GLuint _vao;

		GLuint _vbo;

		std::shared_ptr<Shader> _shader;

		GLint _view;

		virtual void _draw();
		virtual void _defineVao();

		void _setBindings();

		
		GLint _activeTextureId;

	private:
		friend Drawable & operator << (Drawable & drawable, Chunk && dataChunk);
		vector<Chunk> _attributeMapping;
		GLsizei _attributeSize = 0;
		static vector<std::shared_ptr<tdogl::Texture>> _textures;
		static std::set<GLint> _textureIds;
	};
}
