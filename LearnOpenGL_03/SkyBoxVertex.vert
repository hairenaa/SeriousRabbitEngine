#version 330 core											
layout (location = 0) in vec3 aPos;					   	
layout(location=1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;						
layout (location = 3) in vec2 aTexCoord;	

//uniform mat4 transform;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
out vec3 TexCoord;

void main()											   	
{				
	vec4 pos=projectionMat * viewMat* modelMat  * vec4(aPos,1.0f);	   	
	gl_Position= pos.xyww;
	TexCoord=aPos;
}															