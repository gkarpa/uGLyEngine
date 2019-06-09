#include "Mesh.h"

namespace uGLy
{

	Mesh::Mesh()
	{
		this->transformationMatrix = glm::mat4(1.0f);
	}

	Mesh::~Mesh()
	{
		this->renderingProgram.Delete();
		glDeleteVertexArrays(1, &this->vao);
		glDeleteBuffers(1, &this->vbo);
		glDeleteBuffers(1, &this->ibo);
	}

	void Mesh::Draw()
	{
		if (this->material.HasAmbientMap())
		{
			glBindSampler(0, this->material.ambientMap->samplerId);
			glBindTextureUnit(0, this->material.ambientMap->id);
		}
		if (this->material.HasDiffuseMap())
		{
			glBindSampler(1, this->material.diffuseMap->samplerId);
			glBindTextureUnit(1, this->material.diffuseMap->id);
		}
		if (this->material.HasSpecularMap())
		{
			glBindSampler(2, this->material.specularMap->samplerId);
			glBindTextureUnit(2, this->material.specularMap->id);
		}
		if (this->material.HasNormalMap())
		{
			glBindSampler(3, this->material.normalMap->samplerId);
			glBindTextureUnit(3, this->material.normalMap->id);
		}

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::calculateAABB()
	{
		aabb.construct(this->vertices);
	}

}