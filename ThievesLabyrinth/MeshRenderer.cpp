#include "MeshRenderer.h"
#include "EnumTypes.h"

CMeshRenderer::CMeshRenderer(IEntity* pcOwner) : IComponent(pcOwner)
{
	m_nComponentType = eComponent::MESH_RENDERER;
	m_pnTexture = nullptr;
}

int CMeshRenderer::GetVertexBuffer()
{
	return m_nVertices;
}

int CMeshRenderer::GetIndexBuffer()
{
	return m_nIndices;
}

int CMeshRenderer::GetTextureCount()
{
	return m_nTextureCount;
}

int CMeshRenderer::GetTextureAt(int nSlot)
{
	return m_pnTexture[nSlot];
}

int CMeshRenderer::GetVertexShader()
{
	return m_nVS;
}

int CMeshRenderer::GetPixelShader()
{
	return m_nPS;
}

int CMeshRenderer::GetSampler()
{
	return m_nSampler;
}

int CMeshRenderer::GetInputLayout()
{
	return m_nInputLayout;
}

void CMeshRenderer::SetVertexBuffer(int nBuffer)
{
	m_nVertices = nBuffer;
}

void CMeshRenderer::SetIndexBuffer(int nBuffer)
{
	m_nIndices = nBuffer;
}

void CMeshRenderer::SetTextureCount(int nTextureCount)
{
	m_nTextureCount = nTextureCount;

	if(m_nTextureCount > 0)
	{
		if(m_pnTexture != nullptr)
		{
			delete[] m_pnTexture;
		}

		m_pnTexture = new int[m_nTextureCount];
	}
}

void CMeshRenderer::SetTexture(int nTexture, int nSlot)
{
	m_pnTexture[nSlot] = nTexture;
}

void CMeshRenderer::SetVertexShader(int nVS)
{
	m_nVS = nVS;
}

void CMeshRenderer::SetPixelShader(int nPS)
{
	m_nPS = nPS;
}

void CMeshRenderer::SetSampler(int nSampler)
{
	m_nSampler = nSampler;
}

void CMeshRenderer::SetInputLayout(int nInputLayout)
{
	m_nInputLayout = nInputLayout;
}

CMeshRenderer & CMeshRenderer::operator=(CMeshRenderer & cCopy)
{
	SetVertexBuffer(cCopy.m_nVertices);
	SetIndexBuffer(cCopy.m_nIndices);
	SetVertexShader(cCopy.m_nVS);
	SetPixelShader(cCopy.m_nPS);
	SetSampler(cCopy.m_nSampler);
	SetInputLayout(cCopy.m_nInputLayout);
	SetTextureCount(cCopy.m_nTextureCount);
	for(int i = 0; i < m_nTextureCount; i++)
	{
		SetTexture(cCopy.m_pnTexture[i], i);
	}
	return *this;

}

CMeshRenderer::~CMeshRenderer()
{
	if (m_pnTexture)
	delete[] m_pnTexture;
	m_pnTexture = nullptr;
}


