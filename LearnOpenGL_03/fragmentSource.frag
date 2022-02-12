#version 330 core        
//in vec4 vertexColor;			
//uniform vec4 timeColor;			
//in vec2 TexCoord;
in  vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
in vec4 vertexColor;

struct Material{
float ambient_ins;
float diffuse_ins;
float specular_ins;
vec3 ambientColor;
float shininess;
sampler2D texture_diffuse_1;
sampler2D texture_diffuse_2;
sampler2D texture_diffuse_3;
sampler2D texture_specular_1;
sampler2D texture_specular_2;
sampler2D texture_specular_3;
sampler2D texture_normal_1;
sampler2D texture_normal_2;
sampler2D texture_height_1;

};

struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dir;
};

struct LightPoint{
	vec3 pos;
	vec3 color;
	vec3 dir;
	float constant;
	float linear;
	float quadratic;
};
struct LightSpot{
	vec3 pos;
	vec3 color;
	vec3 dir;
	float cosInnerPhy;
	float cosOutterPhy;
};

uniform Material material;
//uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform vec3 objColor;
//uniform vec3 ambientColor;
//uniform vec3 lightPos;
//uniform vec3 lightDirUniform;
//uniform vec3 lightColor;
uniform vec3 cameraPos;
//uniform LightPoint lightPoint;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightSpot;
uniform LightDirectional lightDirectional;
out vec4 FragColor;


vec3 GetDiffuseTextureRGB()
{
//if you have another texture add it 
//+texture(material.texture_diffuse_2,TexCoord).rgb+texture(material.texture_diffuse_3,TexCoord).rgb;
	return texture(material.texture_diffuse_1,TexCoord).rgb;
	//return vec3(1.0,1.0,1.0);
}

vec3 GetSpecularTextureRGB()
{
//+texture(material.texture_specular_2,TexCoord).rgb
	return  texture(material.texture_specular_1,TexCoord).rgb;
	//return vec3(0.5f,0.5f,0.5f);
}

vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera){
	 
	 float diffIntensity=max(dot(light.dir,uNormal),0);
	 vec3 diffColor=diffIntensity* light.color*GetDiffuseTextureRGB()* material.diffuse_ins;
	 vec3 ref=reflect(-light.dir,uNormal);
	 float specIntensity=pow(max(dot(ref,dirToCamera),0),material.shininess);
	 vec3 specColor=specIntensity*light.color * GetSpecularTextureRGB() * material.specular_ins ;
	 vec3 result=diffColor+specColor;
	 return result;
}




vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera){

	float dist=length(light.pos-FragPos);
	float attenuation=1/(light.constant+light.linear*dist+light.quadratic*dist*dist);
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation;
	vec3 diffColor=diffIntensity* light.color* GetDiffuseTextureRGB()* material.diffuse_ins;
	vec3 ref=reflect(normalize(FragPos-light.pos),uNormal);
	float specIntensity=pow(max(dot(ref,dirToCamera),0),material.shininess)* attenuation;
	vec3 specColor=specIntensity*light.color * GetSpecularTextureRGB()* material.specular_ins;
	vec3 result=diffColor+specColor;
	return result;
}




vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera){

	float spotRadio=1.0f;
	float cosTheta= dot(normalize(FragPos-light.pos),-light.dir);
	if(cosTheta>light.cosInnerPhy){
		spotRadio=1.0f;
	}else if(cosTheta>light.cosOutterPhy){
		spotRadio=(cosTheta- light.cosOutterPhy)/(light.cosInnerPhy-light.cosOutterPhy);
	}else{
		spotRadio=0.0f;
	}

	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0);
	 vec3 diffColor=diffIntensity* light.color*GetDiffuseTextureRGB()*material.diffuse_ins;
	 vec3 ref=reflect(normalize(FragPos-light.pos),uNormal);
	float specIntensity=pow(max(dot(ref,dirToCamera),0),material.shininess);
	vec3 specColor=specIntensity*light.color * GetSpecularTextureRGB() *material.specular_ins;
	vec3 result=(diffColor+specColor)*spotRadio;
	return result;
}



void main()                      
{
	vec3 finalResult=vec3(0,0,0);
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera=normalize(cameraPos-FragPos);
	finalResult+=CalcLightDirectional(lightDirectional,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP0,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP1,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP2,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP3,uNormal,dirToCamera);
	finalResult+=CalcLightSpot(lightSpot,uNormal,dirToCamera);
	finalResult+=material.ambient_ins *material.ambientColor * GetDiffuseTextureRGB();
	finalResult+=vertexColor.rgb;
	FragColor=vec4(finalResult,1.0f);


}	
