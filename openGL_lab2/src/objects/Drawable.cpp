#include "Drawable.h"
#include <utils/Proto.h>
#include <lib/Texture.h>

using namespace obj;

vector<std::shared_ptr<tdogl::Texture>> Drawable::_textures;
std::set<GLint> Drawable::_textureIds;

Drawable::Drawable(std::shared_ptr<Shader> shader)
{
	_shader = shader;
	glGenBuffers(1, &_vbo);
	glGenVertexArrays(1, &_vao);
	_view = GL_LINE;
	_activeTextureId = -1;
}

void Drawable::loadVertices() {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindVertexArray(_vao); // Bind VAO properties to VBO
	{
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
	
		cout << "vertices " << _vertices.size() << "loaded" << endl;

		_defineVao();
		_setBindings();

	}
	glBindVertexArray(0); // Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}

void Drawable::setView(GLint view) {
	_view = view;
}

GLint Drawable::getView() const {
	return _view;
}



GLint obj::Drawable::loadTexture(const string & path)
{
	auto bitmap = tdogl::Bitmap(tdogl::Bitmap::bitmapFromFile(path));
	cout << "bitmap loaded\tsize = " << bitmap.width() << " x " << bitmap.height() << endl;
	auto texture(std::shared_ptr<tdogl::Texture>(new tdogl::Texture(bitmap)));
	//_textureIds.insert(texture->object());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	obj::Drawable::_textures.push_back(texture);
	return texture->object();
}

void Drawable::setTexture(const GLint id)
{
	if (_textureIds.find(id) != _textureIds.end()) {
		throw std::exception("Wrong texture id!");
	}
	this->_activeTextureId = id;
}

void Drawable::_draw()
{
	cout << "DEFAULT DRAW USED!" << endl;
	if (_vertices.size() > std::numeric_limits<GLsizei>::max())
		throw std::exception("vertices size is too big");
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertices.size() / 3));
}

void Drawable::draw()
{
	_shader->enable();
	glBindBuffer(GL_ARRAY_BUFFER, _vbo); // Bind VBO first
	glBindVertexArray(_vao); // Turns on all attributes
	{
		_shader->tranformation(_getTransformations())
			.tex(0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, _view);
		glBindTexture(GL_TEXTURE_2D, _activeTextureId);

		_draw();

	}
	glBindVertexArray(0); // Turn everything back off
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Bind VBO first
	_shader->disable();
}

void Drawable::_setBindings()
{
#if 1
		int offset = 0;
		for (Chunk & i : _attributeMapping) {
			string name = proto::mapAttribute(i.type);
			cout << name << ' ' << i.size << "offset: " << offset << endl;
			GLint id = prt(glGetAttribLocation(_shader->getId(), name.c_str()));
			glEnableVertexAttribArray(id);
			glVertexAttribPointer(id, i.size, GL_FLOAT, GL_FALSE, _attributeSize * sizeof(float), (GLvoid*)offset);
			offset += i.size * sizeof(float);
		}
#endif
			//for ever;
	/*const GLsizei DIM = 3;
	const GLsizei RGBA = 4;
	glBindBuffer(GL_ARRAY_BUFFER, _data.vbo); // Bind VBO first
	glBindVertexArray(_data.vao); // Bind VAO properties to VBO
	{
	GLsizei packSize = DIM * sizeof(GLfloat) * 2 +
	+ 2 * sizeof(GL_FLOAT);

	glEnableVertexAttribArray(_position);
	glVertexAttribPointer(_position, DIM, GL_FLOAT, GL_FALSE, packSize, (GLvoid*)0);

	glEnableVertexAttribArray(_normal);
	glVertexAttribPointer(_normal, DIM, GL_FLOAT, GL_FALSE, packSize, (GLvoid*)3);

	glEnableVertexAttribArray(_texture);
	glVertexAttribPointer(_texture, 2, GL_FLOAT, GL_FALSE, packSize, (GLvoid*)6);

	//glEnableVertexAttribArray(_color);
	//glVertexAttribPointer(_color, RGBA, GL_FLOAT, GL_FALSE, RGBA * sizeof(GLfloat) + DIM * sizeof(GLfloat) * 2, (GLvoid*)6);
	}
	glBindVertexArray(0); // Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO*/
}

void Drawable::_defineVao()
{
	const GLsizei DIM = 3;
	const GLsizei RGBA = 4;

	using proto::AttributeType;
	*this << Chunk{ AttributeType::POSITION, DIM } 
	      << Chunk{ AttributeType::NORMAL, DIM }
	      << Chunk{ AttributeType::TEXTURE, 2 }
	      << Chunk{ AttributeType::COLOR, RGBA };
}

Drawable & obj::operator << (Drawable & drawable, Chunk && dataChunk)
{
	drawable._attributeSize += dataChunk.size;
	drawable._attributeMapping.push_back(std::move(dataChunk));
	return drawable;
}
