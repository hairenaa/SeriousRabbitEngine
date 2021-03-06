#version 330 core        

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

uniform vec3 cameraPos;


//#LightAreaBegin
//uniform LightPoint lightP0;
//uniform LightPoint lightP1;
//uniform LightPoint lightP2;
//uniform LightPoint lightP3;
//uniform LightSpot lightSpot;
//uniform LightDirectional lightDirectional;
//#LightAreaEnd

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

vec3 CalcLightDirectional(vec3 uNormal,vec3 dirToCamera,LightDirectional light){
	 
	 float diffIntensity=max(dot(light.dir,uNormal),0);
	 vec3 diffColor=diffIntensity* light.color*GetDiffuseTextureRGB()* material.diffuse_ins;
	 vec3 ref=reflect(-light.dir,uNormal);
	 float specIntensity=pow(max(dot(ref,dirToCamera),0),material.shininess);
	 vec3 specColor=specIntensity*light.color * GetSpecularTextureRGB() * material.specular_ins ;
	 vec3 result=diffColor+specColor;
	 return max(result,vec3(0,0,0));
}




vec3 CalcLightPoint(vec3 uNormal,vec3 dirToCamera,LightPoint light){

	float dist=length(light.pos-FragPos);
	float attenuation=1/(light.constant+light.linear*dist+light.quadratic*dist*dist);
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation;
	vec3 diffColor=diffIntensity* light.color * GetDiffuseTextureRGB()* material.diffuse_ins;
	vec3 ref=reflect(normalize(FragPos-light.pos),uNormal);
	float specIntensity=pow(max(dot(ref,dirToCamera),0),material.shininess)* attenuation;
	vec3 specColor=specIntensity*light.color * GetSpecularTextureRGB()* material.specular_ins;
	vec3 result=diffColor+specColor;
	return max(result,vec3(0,0,0));
}




vec3 CalcLightSpot(vec3 uNormal,vec3 dirToCamera,LightSpot light){

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
	return max(result,vec3(0,0,0));
}

vec3 CalcAmbient()
{
 vec3 result= material.ambient_ins *material.ambientColor * GetDiffuseTextureRGB();
 return max(result,vec3(0,0,0));
}

void main()                      
{
	vec3 finalResult=vec3(0,0,0);
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera=normalize(cameraPos-FragPos);
	//#LightCalcBegin
//	finalResult+=CalcLightDirectional(uNormal,dirToCamera,lightDirectional);
//	finalResult+=CalcLightPoint(uNormal,dirToCamera,lightP0);
//	finalResult+=CalcLightPoint(uNormal,dirToCamera,lightP1);
//	finalResult+=CalcLightPoint(uNormal,dirToCamera,lightP2);
//	finalResult+=CalcLightPoint(uNormal,dirToCamera,lightP3);
//	finalResult+=CalcLightSpot(uNormal,dirToCamera,lightSpot);
	//LightCalcEnd
	finalResult+=CalcAmbient();
	finalResult+=vertexColor.rgb;
	FragColor=vec4(finalResult,1.0f);


}	
