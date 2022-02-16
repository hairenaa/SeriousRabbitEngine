#pragma once

static const char* TEXTURE_DEFAULT_DIFFUSE_PATH ="texture_default_diffuse.png";
static const char* TEXTURE_DEFAULT_SPECULAR_PATH ="texture_default_specular.png";


static const char* SHADER_DEFAULT_FILE_FRAGMENT = "fragmentSource.frag";
static const char* SHADER_DEFAULT_FILE_VERTEX = "vertexSource.vert";

static const char* FRAGMENT_SHADER_VAR_MATERIAL ="material";
static const char* FRAGMENT_SHADER_VAR_CAMERA_POS ="cameraPos";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_AMBIENT_INS =".ambient_ins";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_DIFFUSE_INS =".diffuse_ins";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_SPECULAR_INS =".specular_ins";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_AMBIENT_COLOR =".ambientColor";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_SHININESS= ".shininess";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_DIFFUSE= ".texture_diffuse_";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_SPECULAR = ".texture_specular_";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_NORMAL =".texture_normal_";
static const char* FRAGMENT_SHADER_STRUCT_MATERIAL_TEXTURE_HEIGHT = ".texture_height_";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_POS = ".pos";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_COLOR = ".color";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_DIR = ".dir";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_POINT_CONSTANT = ".constant";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_POINT_LINEAR = ".linear";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_POINT_QUADRATIC = ".quadratic";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_POINT_COS_INNER_PHY = ".cosInnerPhy";
static const char* FRAGMENT_SHADER_STRUCT_LIGHT_POINT_COS_OUTTER_PHY = ".cosOutterPhy";


static const char* FRAGMENT_SHADER_CALL_LIGHT_PREFIX_DIRECTIONAL="finalResult+=CalcLightDirectional(uNormal,dirToCamera,";
static const char* FRAGMENT_SHADER_CALL_LIGHT_PREFIX_POINT = "finalResult+=CalcLightPoint(uNormal,dirToCamera,";
static const char* FRAGMENT_SHADER_CALL_LIGHT_PREFIX_SPOT = "finalResult+=CalcLightSpot(uNormal,dirToCamera,";

static const char* FRAGMENT_SHADER_CALL_LIGHT_AFFIX = ");";
static const char* FRAGMENT_SHADER_DECLARE_LIGHT_DIRECTIONAL = "uniform LightDirectional ";
static const char* FRAGMENT_SHADER_DECLARE_LIGHT_POINT = "uniform LightPoint ";
static const char* FRAGMENT_SHADER_DECLARE_LIGHT_SPOT = "uniform LightSpot ";

static const char* FRAGMENT_SHADER_LIGHT_TAG_AREA_BEGIN = "//#LightAreaBegin";
static const char* FRAGMENT_SHADER_LIGHT_TAG_CALC_BEGIN = "//#LightCalcBegin";

static const char* FRAGMENT_SHADER_LIGHT_TAG_AREA_END = "//#LightAreaEnd";
static const char* FRAGMENT_SHADER_LIGHT_TAG_CALC_END = "//#LightCalcEnd";

static const char* FRAGMENT_SHADER_VAR_SKYBOX = "sky";


static const char* VERTEX_SHADER_VAR_MODEL_MAT ="modelMat";
static const char* VERTEX_SHADER_VAR_VIEW_MAT ="viewMat";
static const char* VERTEX_SHADER_VAR_PROJECTION_MAT ="projectionMat";







class ConstValues
{


};

