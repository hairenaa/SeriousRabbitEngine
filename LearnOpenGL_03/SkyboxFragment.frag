#version 330 core        

in vec3 TexCoord;

uniform samplerCube sky;


out vec4 FragColor;


void main()                      
{
	FragColor=texture(sky, TexCoord);
}	
