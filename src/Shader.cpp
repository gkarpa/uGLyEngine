#include "Shader.h"

namespace uGLy
{

	Shader::Shader()
	{
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
	}

	bool Shader::CreateShaderFromFile(GLenum shaderType, const char *shaderPath)
	{
		std::ifstream shaderStream(shaderPath);
		std::string shaderSource((std::istreambuf_iterator<char>(shaderStream)), std::istreambuf_iterator<char>());
		const char *shaderSourcePtr = shaderSource.c_str();

		return this->CreateShaderFromSource(shaderType, shaderSourcePtr);
	}

	bool Shader::CreateShaderFromSource(GLenum shaderType, const char *shaderSource)
	{
		this->id = glCreateShader(shaderType);
		GLint  shaderCompileStatus;
		glShaderSource(this->id, 1, &shaderSource, NULL);
		glCompileShader(this->id);
		glGetShaderiv(this->id, GL_COMPILE_STATUS, &shaderCompileStatus);
		if (shaderCompileStatus == 0)
		{
			std::cout << "Shader compilation problem!" << std::endl;
			return false;
		}

		return true;
	}

}