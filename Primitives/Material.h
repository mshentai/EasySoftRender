#pragma once
#include "ShaderReference.h"
class Sampler2D;
typedef unsigned char BYTE;
class Material
{
private:
	float m_EmisRate;
	float m_AmbiRate;
	float m_DiffRate;
	float m_SpecRate;
	Vector3 m_AmbiColor;
	Vector3 m_DiffColor;
	Vector3 m_SpecColor;
	Vector3 m_LightColor;
	std::shared_ptr<Sampler2D> m_Sp2D;
	const BYTE* m_SpPixels;
	int m_Width;
	int m_Height;

public:
	void Vertex(const float3& modelPos, const Float4x4& mvp, float3& projPos) const;

	void Fragment(const int px, const int py, const float x, const float y, BYTE* retColor) const;

	void Fragment(
		const int px, const int py, const float x, const float y, 
		const Vector3& lightDir, const Vector3& viewDir,const Vector3& normal,
		BYTE* retColor) const;

	//void ComputeLightRate(const float3& L_Ambi, const float3& L_Diff, const float3& L_Spec, const float diffRate, const float specRate);

	Material(): 
		m_EmisRate(1.0f), m_AmbiRate(1.0),m_DiffRate(1.0f), m_SpecRate(1.0f), m_LightColor(1.0f, 1.0f, 1.0f),
		m_AmbiColor(0.3f, 0.3f, 0.3f), m_DiffColor(0.7f, 0.7f, 0.7f), m_SpecColor(0.3f, 0.3f, 0.3f),m_Width(0),m_Height(0) {}
	void SetSampler2D(std::shared_ptr<Sampler2D>& sp);
	const BYTE* Tex2D(float x, float y) const;
	
	
};

