#version 330 core											
layout (location = 0) in vec3 aPos;					   	
layout(location=1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;						
layout (location = 3) in vec2 aTexCoord;	

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
out vec4 vertexColor;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
void main()											   	
{													   	
	gl_Position =projectionMat * viewMat * modelMat * vec4(aPos,1.0f);	   	
	FragPos = vec3(modelMat * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(modelMat)))* aNormal;
	vertexColor= vec4(aColor,1.0f);		
	TexCoord=aTexCoord;
}															