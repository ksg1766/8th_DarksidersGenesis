#include "stdafx.h"
#include "DebugTerrainGrid.h"
#include "GameInstance.h"
#include "GameObject.h"

CDebugTerrainGrid::CDebugTerrainGrid(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:Super(pDevice, pContext)
{
}

CDebugTerrainGrid::CDebugTerrainGrid(const CDebugTerrainGrid& rhs)
	:Super(rhs)
{
}

HRESULT CDebugTerrainGrid::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CDebugTerrainGrid::Initialize(void* pArg)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	//m_pBufferGrid = static_cast<CVIBuffer_Grid*>(m_pGameObject->GetBuffer());
	m_pBufferGrid = dynamic_cast<CVIBuffer_Grid*>(pGameInstance->Clone_Component(m_pGameObject, LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Grid"), pArg));
	m_pShader = dynamic_cast<CShader*>(pGameInstance->Clone_Component(m_pGameObject, LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxDebug"), pArg));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CDebugTerrainGrid::Tick(const _float& fTimeDelta)
{
	// Input(fTimeDelta);
}

void CDebugTerrainGrid::LateTick(const _float& fTimeDelta)
{
}

void CDebugTerrainGrid::DebugRender()
{
	Bind_ShaderResources();

	m_pShader->Begin(1);

	m_pBufferGrid->Render();
}

HRESULT CDebugTerrainGrid::Bind_ShaderResources()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pGameObject->GetTransform()->Bind_ShaderResources(m_pShader, "g_WorldMatrix")) ||
		FAILED(pGameInstance->Bind_TransformToShader(m_pShader, "g_ViewMatrix", CPipeLine::D3DTS_VIEW)) ||
		FAILED(pGameInstance->Bind_TransformToShader(m_pShader, "g_ProjMatrix", CPipeLine::D3DTS_PROJ)))
	{
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

CDebugTerrainGrid* CDebugTerrainGrid::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDebugTerrainGrid* pInstance = new CDebugTerrainGrid(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDebugTerrainGrid");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CDebugTerrainGrid::Clone(CGameObject* pGameObject, void* pArg)
{
	CDebugTerrainGrid* pInstance = new CDebugTerrainGrid(*this);
	pInstance->m_pGameObject = pGameObject;

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CDebugTerrainGrid");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDebugTerrainGrid::Free()
{
	Super::Free();

	Safe_Release(m_pBufferGrid);
	Safe_Release(m_pShader);
}