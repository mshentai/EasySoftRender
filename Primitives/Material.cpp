#include "Material.h"
#include "Sampler2D.h"
#include <math.h>
#include <Windows.h>
//static inline void saturate(float& val)
//{
//	if (val < 0)
//	{
//		val = 0.0f;
//	}
//	else if(val > 1)
//	{
//		val = 1.0f;
//	}
//}
static inline float saturate(float val)
{
	float res = val > 0.0f ? val : 0.0f;
	res = res < 1.0f ? res : 1.0f;
	return res;
}
static inline void CopyColor(BYTE* dest, const BYTE* src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}
static void GetLightPara(const Vector3& lightDir, const Vector3& viewDir, const Vector3& normal, const float gloss, float& R_diff, float& R_spec)
{
	Vector3 H = -((lightDir + viewDir).Normalize());
	float tmp = saturate(normal * H);
	R_diff = (-normal * lightDir) > 0.0f ? (-normal * lightDir) : 0.0f;
	R_spec = saturate(powf(tmp, gloss));
}

void Material::Vertex(const float3& modelPos, const Float4x4& mvp, float3& projPos) const
{
	projPos = modelPos * mvp;
}

void Material::Fragment(const int px, const int py, float x, float y, BYTE* retColor) const
{
	BYTE color[3];
	const BYTE* tex = Tex2D(x, y);
	CopyColor(color, tex);
	CopyColor(retColor, color);
}

void Material::Fragment(const int px, const int py, const float x, const float y, const Vector3& lightDir, const Vector3& viewDir, const Vector3& normal, BYTE* retColor) const
{
	const BYTE* tex = Tex2D(x, y);
	float3 color1(tex[0] / 255.0f, tex[1] / 255.0f, tex[2] / 255.0f);
	float R_diff, R_spec;
	GetLightPara(lightDir, viewDir, normal, 8.0f, R_diff, R_spec);
	float3 color2(1.0f, 1.0f, 1.0f);

	float3 color = color1;
	
	float3 ambient = m_AmbiColor.OX(color);
	float3 diffuse =  color* R_diff;
	float3 specular = m_SpecColor * R_spec;
	
	float3 finalColor = ambient + diffuse + specular;

	retColor[0] = finalColor[0] < 1.0f ? finalColor[0] * 255.0f : 255;
	retColor[1] = finalColor[1] < 1.0f ? finalColor[1] * 255.0f : 255;
	retColor[2] = finalColor[2] < 1.0f ? finalColor[2] * 255.0f : 255;
	//retColor[0] = 255;
	//retColor[1] = 255;
	//retColor[2] = 255;
}

//void Material::Fragment(const int px, const int py, const float x, const float y, const float diffRate, const float specRate, 
//	const float3& ambiColor, const float3& diffColor, const float3& specColor, BYTE* retColor) const
//{
// 	const BYTE* tex = Tex2D(x, y);
//	float3 color((tex[0] / 255.0f), (tex[1] / 255.0f), (tex[2] / 255.0f));
//}



void Material::SetSampler2D(std::shared_ptr<Sampler2D>& sp)
{
	m_Sp2D = sp;
	m_SpPixels = sp->GetData();
	m_Height = sp->GetHeight() - 1;
	m_Width = sp->GetWidth();
}

const BYTE* Material::Tex2D(float x, float y) const
{
	//x = abs(x);
	//y = abs(y);
	x = fminf(x, 1);
	x = fmaxf(0, x);
	y = fminf(y, 1);
	y = fmaxf(0, y);
	//float xx = x - ((int)x);
	//float yy = y - ((int)y);
	int a = y * m_Height;
	int b = a * m_Width * 3;
	int id = (((int)(y * m_Height)) * m_Width + ((int)(x * m_Width))) *  3;
	return (m_SpPixels + id);
}

