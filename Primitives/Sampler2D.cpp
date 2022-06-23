#include "Sampler2D.h"
#include <stdio.h>
#include <Windows.h>

Sampler2D* Sampler2D::white = nullptr;
BYTE* Sampler2D::color_Table = nullptr;

void Sampler2D::Init()
{
	FILE* fp;
	auto er = fopen_s(&fp, m_BmpName, "rb");
	if (er != 0) throw er;
	BITMAPINFOHEADER head;
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	m_Width = head.biWidth;
	m_Height = head.biHeight;
	int bitCount = head.biBitCount;

	int lineByte = (m_Width * bitCount / 8 + 3) / 4 * 4;

	m_BufferPtr = new BYTE[lineByte * m_Height];
	fread(m_BufferPtr, 1, lineByte * m_Height, fp);

	fclose(fp);
}

const BYTE* Sampler2D::GetData() const
{
	return m_BufferPtr;
}

const BYTE* Sampler2D::GetData()
{
	return m_BufferPtr;
}

int Sampler2D::GetWidth() const
{
	return m_Width;
}

int Sampler2D::GetHeight() const
{
	return m_Height;
}

Sampler2D* Sampler2D::GetWhite()
{
	if (!white) WhiteStaticStructor();
	return white;
}

Sampler2D::~Sampler2D()
{
	delete m_BufferPtr;
	m_BufferPtr = nullptr;
}

void Sampler2D::WhiteStaticStructor()
{
	white = new Sampler2D("White");
	color_Table = new BYTE[3]{ 255,255,255 };
	white->m_BufferPtr = color_Table;
}
