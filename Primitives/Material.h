#pragma once
#include "ShaderReference.h"
class Sampler2D;
typedef unsigned char BYTE;
class Material
{
private:
	float m_EmisRate;//�����Է�����
	float m_AmbiRate;//���ʻ�������
	float m_DiffRate;//������������
	float m_SpecRate;//���ʾ��淴����
	float m_ShadowRate;//������Ӱ��ϰ�����
	Vector3 m_AmbiColor;//��������ɫ
	Vector3 m_DiffColor;//��������ɫ
	Vector3 m_SpecColor;//���淴����ɫ
	Vector3 m_LightColor;//�����ɫ
	Vector3 m_ShadowColor;//��Ӱ��ɫ
	const BYTE* m_SpPixels;//ɢ������
	const BYTE* m_SpNormals;//��������
	int m_Width;//ɢ�����ؿ��
	int m_Height;//ɢ�����ظ߶�
	int m_WidthN;//����������
	int m_HeightN;//��������߶�
	std::shared_ptr<Sampler2D> m_Sp2D;
	std::shared_ptr<Sampler2D> m_Nor2D;
public:
	//������ɫ��
	void Vertex(const float3& modelPos, const Float4x4& mvp, float3& projPos) const;
	//ƬԪ��ɫ����ֻ�����أ�
	void Fragment(const int px, const int py, const float x, const float y, BYTE* retColor) const;
	//ƬԪ��ɫ��������+���գ�
	void Fragment(
		const int px, const int py, const float x, const float y, 
		const Vector3& lightDir, const Vector3& viewDir,const Vector3& normal,
		BYTE* retColor) const;

	void Shadow(const int px, const int py, BYTE* retColor) const;

	//void ComputeLightRate(const float3& L_Ambi, const float3& L_Diff, const float3& L_Spec, const float diffRate, const float specRate);

	Material(): 
		m_EmisRate(1.0f), m_AmbiRate(0.3f),m_DiffRate(0.7f), m_SpecRate(0.1f), m_ShadowRate(0.5f), m_LightColor(1.0f, 1.0f, 1.0f),
		m_AmbiColor(1.0f, 1.0f, 1.0f), m_DiffColor(1.0f, 1.0f, 1.0f), m_SpecColor(1.0f, 1.0f, 1.0f),m_Width(0),m_Height(0) {}
	//��������ͼ��
	void SetSampler2D(const std::shared_ptr<Sampler2D>& sp);
	void SetSamplerNor(const std::shared_ptr<Sampler2D>& sp);
	//����ɼ�����
	const BYTE* Tex2D(float x, float y) const;
	Vector3 TexNormal(float x, float y) const;

	bool HasNorTexture() const;
	
	
};

