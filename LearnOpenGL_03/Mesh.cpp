#include "Mesh.h"

//unsigned int Mesh::TextureIndex = 0;

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices,std::vector<Texture> _textures,Material* _material)
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
	this->material = _material;
	setupMesh();
}


Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int>_indices, Material* _material) 
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->material = _material;
	setupMesh();
}


Mesh::Mesh(std::vector<Vertex> _vertices, Material* _material)
{
	this->vertices = _vertices;
	this->material = _material;
	setupMesh();
}

void Mesh::Draw(Shader * shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;


	material->Draw();
	if (!textures.empty()) 
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			unsigned int slot = i;
			Texture curTexture = textures[i];
			glActiveTexture(GL_TEXTURE0 + slot);
			std::string name;
			if (curTexture.type == TEXTURE_DIFFUSE)
			{
				name = diffusePrefix + std::to_string(diffuseNr++);
				glBindTexture(GL_TEXTURE_2D, curTexture.id);
				shader->SetUniform1i(name.c_str(), slot);
			}
			else if (curTexture.type == TEXTURE_SPECULAR)
			{
				name = specularPrefix + std::to_string(specularNr++);
				glBindTexture(GL_TEXTURE_2D, curTexture.id);
				shader->SetUniform1i(name.c_str(), slot);
			}
			else if (curTexture.type == TEXTURE_NORMAL)
			{
				name = normalPrefix + std::to_string(normalNr++);
				glBindTexture(GL_TEXTURE_2D, curTexture.id);
				shader->SetUniform1i(name.c_str(), slot);
			}
			else if (curTexture.type == TEXTURE_HEIGHT)
			{
				name = heightPrefix + std::to_string(heightNr++);
				glBindTexture(GL_TEXTURE_2D, curTexture.id);
				shader->SetUniform1i(name.c_str(), slot);
			}
			//std::cout << name << std::endl;
		}
	}
	
	
	

	glBindVertexArray(VAO);
	
	if (!indices.empty()) 
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	if (vertices.empty())
	{
		return;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	if (!indices.empty()) 
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW);
	}
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

}
