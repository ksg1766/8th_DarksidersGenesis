#include "..\Public\VIBuffer.h"

CVIBuffer::CVIBuffer(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CComponent(pDevice, pContext, ComponentType::Buffer)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
{

}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_iStride(rhs.m_iStride)
	, m_iNumVertices(rhs.m_iNumVertices)
	, m_iNumPrimitives(rhs.m_iNumPrimitives)
	, m_iIndexSizeofPrimitive(rhs.m_iIndexSizeofPrimitive)
	, m_iNumIndicesofPrimitive(rhs.m_iNumIndicesofPrimitive)
	, m_eIndexFormat(rhs.m_eIndexFormat)
	, m_eTopology(rhs.m_eTopology)
	, m_iNumVBs(rhs.m_iNumVBs)
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);	
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	ID3D11Buffer*	pVertexBuffers[] = {
		m_pVB, 		
	};

	_uint			iStrides[] = {
		m_iStride,
	};

	_uint			iOffsets[] = {
		0,
	};

	/* 버텍스 버퍼들을 할당한다. */
	m_pContext->IASetVertexBuffers(0, m_iNumVBs, pVertexBuffers, iStrides, iOffsets);

	/* 인덱스 버퍼를 할당한다. */
	m_pContext->IASetIndexBuffer(m_pIB, m_eIndexFormat, 0);

	/* 해당 정점들을 어떤 방식으로 그릴꺼야. */
	m_pContext->IASetPrimitiveTopology(m_eTopology);

	/* 인덱스가 가르키는 정점을 활용하여 그린다. */
	//m_pContext->DrawIndexed(m_iNumIndices, 0, 0);
	m_pContext->DrawIndexed(m_iNumPrimitives * m_iNumIndicesofPrimitive, 0, 0);

	return S_OK;
}


HRESULT CVIBuffer::Create_Buffer(_Inout_ ID3D11Buffer** ppOut)
{
	if (nullptr == m_pDevice)
		return E_FAIL;

	return m_pDevice->CreateBuffer(&m_BufferDesc, &m_SubResourceData, ppOut);	
}

void CVIBuffer::Free()
{
	Super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}
