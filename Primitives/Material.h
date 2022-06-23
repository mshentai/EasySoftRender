#pragma once
#include "ShaderReference.h"
class Sampler2D;
typedef unsigned char BYTE;
class Material
{
private:
	float m_EmisRate;//材质自发光率
	float m_AmbiRate;//材质环境光率
	float m_DiffRate;//材质漫反射率
	float m_SpecRate;//材质镜面反射率
	float m_ShadowRate;//材质阴影混合阿尔发
	Vector3 m_AmbiColor;//环境光颜色
	Vector3 m_DiffColor;//漫反射颜色
	Vector3 m_SpecColor;//镜面反射颜色
	Vector3 m_LightColor;//光的颜色
	Vector3 m_ShadowColor;//阴影颜色
	const BYTE* m_SpPixels;//散射纹理
	const BYTE* m_SpNormals;//法线纹理
	int m_Width;//散射像素宽度
	int m_Height;//散射像素高度
	int m_WidthN;//法线纹理宽度
	int m_HeightN;//法线纹理高都
	std::shared_ptr<Sampler2D> m_Sp2D;
	std::shared_ptr<Sampler2D> m_Nor2D;
public:
	//顶点着色器
	void Vertex(const float3& modelPos, const Float4x4& mvp, float3& projPos) const;
	//片元着色器（只有像素）
	void Fragment(const int px, const int py, const float x, const float y, BYTE* retColor) const;
	//片元着色器（像素+光照）
	void Fragment(
		const int px, const int py, const float x, const float y, 
		const Vector3& lightDir, const Vector3& viewDir,const Vector3& normal,
		BYTE* retColor) const;

	void Shadow(const int px, const int py, BYTE* retColor) const;

	//void ComputeLightRate(const float3& L_Ambi, const float3& L_Diff, const float3& L_Spec, const float diffRate, const float specRate);

	Material(): 
		m_EmisRate(1.0f), m_AmbiRate(0.3f),m_DiffRate(0.7f), m_SpecRate(0.1f), m_ShadowRate(0.5f), m_LightColor(1.0f, 1.0f, 1.0f),
		m_AmbiColor(1.0f, 1.0f, 1.0f), m_DiffColor(1.0f, 1.0f, 1.0f), m_SpecColor(1.0f, 1.0f, 1.0f),m_Width(0),m_Height(0) {}
	//设置纹理图像
	void SetSampler2D(const std::shared_ptr<Sampler2D>& sp);
	void SetSamplerNor(const std::shared_ptr<Sampler2D>& sp);
	//纹理采集函数
	const BYTE* Tex2D(float x, float y) const;
	Vector3 TexNormal(float x, float y) const;

	bool HasNorTexture() const;
	
	
};

