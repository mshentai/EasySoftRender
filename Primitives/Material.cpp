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
	R_diff = (-normal * lightDir) * 0.5f + 0.5f;
	R_spec = saturate(powf(tmp, gloss));
}

void Material::Vertex(const float3& modelPos, const Float4x4& mvp, float3& projPos) const
{
	projPos = Dot(modelPos, mvp, true);
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
	
	float3 ambient = (m_AmbiColor * m_AmbiRate).OX(color);
	float3 diffuse = color * R_diff;
	float3 specular = m_SpecColor * R_spec * m_SpecRate;
	
	float3 finalColor = ambient + diffuse + specular;

	retColor[0] = finalColor[0] < 1.0f ? finalColor[0] * 255.0f : 255;
	retColor[1] = finalColor[1] < 1.0f ? finalColor[1] * 255.0f : 255;
	retColor[2] = finalColor[2] < 1.0f ? finalColor[2] * 255.0f : 255;
	//retColor[0] = 255;
	//retColor[1] = 255;
	//retColor[2] = 255;
}

void Material::Shadow(const int px, const int py, BYTE* retColor) const
{
	float3 color1(retColor[0] / 255.0f, retColor[1] / 255.0f, retColor[2] / 255.0f);

	float3 color = color1;

	float shadowRate = m_ShadowRate;
	float3 finalColor = m_ShadowColor * shadowRate + color * (1 - shadowRate);
	float f = finalColor[0];

	retColor[0] = finalColor[0] < 1.0f ? finalColor[0] * 255.0f : 255;
	retColor[1] = finalColor[1] < 1.0f ? finalColor[1] * 255.0f : 255;
	retColor[2] = finalColor[2] < 1.0f ? finalColor[2] * 255.0f : 255;
}

//void Material::Fragment(const int px, const int py, const float x, const float y, const float diffRate, const float specRate, 
//	const float3& ambiColor, const float3& diffColor, const float3& specColor, BYTE* retColor) const
//{
// 	const BYTE* tex = Tex2D(x, y);
//	float3 color((tex[0] / 255.0f), (tex[1] / 255.0f), (tex[2] / 255.0f));
//}



void Material::SetSampler2D(const std::shared_ptr<Sampler2D>& sp)
{
	m_Sp2D = sp;
	m_SpPixels = sp->GetData();
	m_Height = sp->GetHeight() - 1;
	m_Width = sp->GetWidth();
}

void Material::SetSamplerNor(const std::shared_ptr<Sampler2D>& sp)
{
	m_Nor2D = sp;
	m_SpNormals = sp->GetData();
	m_HeightN = sp->GetHeight() - 1;
	m_WidthN = sp->GetWidth();
}

const BYTE* Material::Tex2D(float x, float y) const
{
	//x = abs(x);
	//y = abs(y);
	x = fminf(x, 0.9999999f);
	x = fmaxf(0.0000001f, x);
	y = fminf(y, 0.9999999f);
	y = fmaxf(0.0000001f, y);
	//float xx = x - ((int)x);
	//float yy = y - ((int)y);
	//int a = y * m_Height;
	//int b = a * m_Width * 3;
	int id = (((int)(y * m_Height)) * m_Width + ((int)(x * m_Width))) *  3;
	return (m_SpPixels + id);
}

Vector3 Material::TexNormal(float x, float y) const
{
	x = fminf(x, 0.9999999f);
	x = fmaxf(0.0000001f, x);
	y = fminf(y, 0.9999999f);
	y = fmaxf(0.0000001f, y);
	//int a = y * m_Height;
	//int b = a * m_Width * 3;
	int id = (((int)(y * m_HeightN)) * m_WidthN + ((int)(x * m_WidthN))) * 3;
	float diff = 0.0078125f;
	return Vector3((m_SpPixels[id] - 128) * diff, (m_SpPixels[id + 1] - 128) * diff, (m_SpPixels[id + 2] - 128) * diff);
}

bool Material::HasNorTexture() const
{
	return m_Nor2D.use_count();
}

