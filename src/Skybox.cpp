#include "Skybox.h"

namespace uGLy
{

	Skybox::Skybox(const std::vector<std::string> & textures)
	{
		initialize(textures);
	}

	Skybox::Skybox(const std::string & rightSide, const std::string & leftSide, const std::string & topSide, const std::string & bottomSide, const std::string & backSide, const std::string & frontSide)
	{
		std::vector<std::string> textures;

		textures.push_back(rightSide);
		textures.push_back(leftSide);
		textures.push_back(topSide);
		textures.push_back(bottomSide);
		textures.push_back(backSide);
		textures.push_back(frontSide);

		initialize(textures);
	}

	Skybox::~Skybox()
	{
	}


	void Skybox::initialize(const std::vector<std::string>& textures)
	{
		int width, height, faceNumOfChannels;

		glGenTextures(1, &this->cubemapID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapID);

		for (size_t i = 0; i < textures.size(); i++)
		{
			stbi_set_flip_vertically_on_load(false);
			unsigned char *data = stbi_load(textures.at(i).c_str(), &width, &height, &faceNumOfChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "Error loading texture from " << textures.at(i) << std::endl;
			}
			stbi_image_free(data);
		}
		glCreateSamplers(1, &samplerID);
		glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glCreateBuffers(1, &vbo);
		glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));

		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);

		//glCreateBuffers(1, &ibo);
		//glNamedBufferStorage(ibo, sizeof(indices), indices, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//glVertexArrayElementBuffer(vao, ibo);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		Shader vertexShader, fragmentShader;
		vertexShader.CreateShaderFromSource(GL_VERTEX_SHADER, vertexShaderSource);
		fragmentShader.CreateShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderSource);

		renderingProgram.AttachShader(vertexShader);
		renderingProgram.AttachShader(fragmentShader);
		renderingProgram.Link();
	}

	void Skybox::Draw(const glm::mat4 &viewProjection)
	{
		glDepthMask(GL_FALSE);
		renderingProgram.Use();
		renderingProgram.SetUniformMat4("viewProjection", viewProjection);
		//glUniformMatrix4fv(glGetUniformLocation(renderingProgram.id, "viewProjection"), 1, false, glm::value_ptr(viewProjection));

		glBindVertexArray(vao);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
		glBindSampler(0, samplerID);
		glBindTextureUnit(0, cubemapID);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 108);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);
		renderingProgram.Unuse();
	}

}