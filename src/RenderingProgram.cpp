#include "RenderingProgram.h"


namespace uGLy
{

	RenderingProgram::RenderingProgram()
	{
		id = glCreateProgram();
	}


	RenderingProgram::~RenderingProgram()
	{
	}


	void RenderingProgram::AttachShader(const Shader &shader)
	{
		glAttachShader(this->id, shader.id);
	}


	void RenderingProgram::Link()
	{
		glLinkProgram(this->id);
	}


	void RenderingProgram::Use()
	{
		glUseProgram(this->id);
	}


	void RenderingProgram::Unuse()
	{
		glUseProgram(0);
	}


	void RenderingProgram::FreeResources()
	{
	}


	void RenderingProgram::Delete()
	{
		if (glIsProgram(this->id))
		{
			glDeleteProgram(this->id);
		}
	}


	void RenderingProgram::SetUniformFloat(const std::string & uniformName, const float value)
	{
		glUniform1f(GetUniformLocation(uniformName), value);
	}


	void RenderingProgram::SetUniformInt(const std::string & uniformName, const int value)
	{
		glUniform1i(GetUniformLocation(uniformName), value);
	}


	void RenderingProgram::SetUniformVec3(const std::string & uniformName, const glm::vec3 & vec)
	{
		glUniform3fv(GetUniformLocation(uniformName), 1, glm::value_ptr(vec));
	}


	void RenderingProgram::SetUniformVec4(const std::string & uniformName, const glm::vec4 & vec)
	{
		glUniform4fv(GetUniformLocation(uniformName), 1, glm::value_ptr(vec));
	}


	void RenderingProgram::SetUniformMat3(const std::string & uniformName, const glm::mat3 & mat, const bool transpose)
	{
		glUniformMatrix3fv(GetUniformLocation(uniformName), 1, transpose, glm::value_ptr(mat));
	}


	void RenderingProgram::SetUniformMat4(const std::string & uniformName, const glm::mat4 & mat, const bool transpose)
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, transpose, glm::value_ptr(mat));
	}


	int RenderingProgram::GetUniformLocation(const std::string & uniformName)
	{
		if (uniformLocationsMap.find(uniformName) == uniformLocationsMap.end())
		{
			uniformLocationsMap[uniformName] = glGetUniformLocation(id, uniformName.c_str());
		}
		//return glGetUniformLocation(id, uniformName.c_str());
		return uniformLocationsMap[uniformName];
	}

}