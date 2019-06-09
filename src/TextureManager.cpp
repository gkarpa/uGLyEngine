#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace uGLy
{

	TextureManager::TextureManager()
	{

	}

	TextureManager::~TextureManager()
	{
		this->Clear();
	}

	void TextureManager::Clear()
	{
		for (auto t : this->textures)
		{
			delete t;
		}
		this->textures.clear();
	}

	Texture* TextureManager::CheckIfTextureAlreadyExists(std::string &pathName)
	{
		for (auto t : this->textures)
		{
			if (t->fullPathName == pathName)
			{
				return t;
			}
		}
		return nullptr;
	}

	Texture* TextureManager::CreateTextureFromFile(std::string &pathName)
	{
		Texture *tex = this->CheckIfTextureAlreadyExists(pathName);

		if (tex == nullptr)
		{
			stbi_set_flip_vertically_on_load(true);
			int x, y, comp;
			unsigned char *data = stbi_load(pathName.c_str(), &x, &y, &comp, 0);

			if (data)
			{
				tex = new Texture();
				tex->fullPathName = pathName;
				tex->xDimension = x;
				tex->yDimension = y;
				tex->numChannels = comp;

				GLenum internalFormat, format;
				if (tex->numChannels == 1)
				{
					internalFormat = GL_R8;
					format = GL_RED;
				}
				else if (tex->numChannels == 2)
				{
					internalFormat = GL_RG8;
					format = GL_RG;
				}
				else if (tex->numChannels == 3)
				{
					internalFormat = GL_RGB8;
					format = GL_RGB;
				}
				else
				{
					internalFormat = GL_RGBA8;
					format = GL_RGBA;
				}
				glCreateTextures(GL_TEXTURE_2D, 1, &tex->id);

				GLsizei numOfMipmaps = static_cast<GLsizei>(log2(std::max(tex->xDimension, tex->yDimension))) + 1;
				glTextureStorage2D(tex->id, numOfMipmaps, internalFormat, tex->xDimension, tex->yDimension);
				glTextureSubImage2D(tex->id, 0, 0, 0, tex->xDimension, tex->yDimension, format, GL_UNSIGNED_BYTE, data);
				glGenerateTextureMipmap(tex->id);
				stbi_image_free(data);

				glCreateSamplers(1, &tex->samplerId);
				glSamplerParameteri(tex->samplerId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glSamplerParameteri(tex->samplerId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glSamplerParameteri(tex->samplerId, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glSamplerParameteri(tex->samplerId, GL_TEXTURE_WRAP_T, GL_REPEAT);

				this->textures.push_back(tex);
			}
		}
		return tex;
	}

}