#pragma once
#include <string>
#include <utils/kupihleba.h>

namespace proto {	
	enum AttributeType {
		COLOR,
		POSITION,
		NORMAL,
		TEXTURE
	};

	/*string mapUniform(const UniformType & t) {
		switch (t) {
		case TRANSFORMATION:
			return "myTransformation";
		case COLOR:
			return "myColor";
		case CAMERA:
			return "camera";
		default:
			throw std::exception("Unknown uniform type!");
		}
	};*/
	static string mapAttribute(const AttributeType & t) {
		switch (t)
		{
		case POSITION:
			return "position";
		case COLOR:
			return "color";
		case NORMAL:
			return "normal";
		case TEXTURE:
			return "textureCoords";
		default:
			break;
		}
	}
}