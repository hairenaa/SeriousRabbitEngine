#include "Material.h"



Material::Material(Shader * _shader, float _ambient_ins,float _diffuse_ins, float _specular_ins, float _shininess)
	:
	shader(_shader),
	ambient_ins(_ambient_ins),
	diffuse_ins(_diffuse_ins),
	specular_ins(_specular_ins),
	shininess(_shininess)
{
}



Material::Material(Shader* _shader) 
	:
	shader(_shader)
{
}



void Material::Draw() 
{
	shader->SetUniform1f("material.ambient_ins",ambient_ins);
	shader->SetUniform1f("material.shininess", shininess);
	shader->SetUniform1f("material.diffuse_ins", diffuse_ins);
	shader->SetUniform1f("material.specular_ins", specular_ins);

}

