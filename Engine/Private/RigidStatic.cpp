#include "RigidStatic.h"
#include "GameObject.h"

CRigidStatic::CRigidStatic(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: Super(pDevice, pContext, RigidBodyType::STATIC)
	, m_fFrictionCoef(0.5f)
{
}

CRigidStatic::CRigidStatic(const CRigidStatic& rhs)
	: Super(rhs)
	, m_fFrictionCoef(rhs.m_fFrictionCoef)
{
}

HRESULT CRigidStatic::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRigidStatic::Initialize(void* pArg)
{
	return S_OK;
}

void CRigidStatic::Tick(_float fTimeDelta)
{
}

void CRigidStatic::LateTick(_float fTimeDelta)
{
}

void CRigidStatic::DebugRender()
{
}

void CRigidStatic::OnCollisionEnter(const COLLISION_DESC& desc)
{
	// friction
}

void CRigidStatic::OnCollisionStay(const COLLISION_DESC& desc)
{
}

void CRigidStatic::OnCollisionExit(const COLLISION_DESC& desc)
{
}


CRigidStatic* CRigidStatic::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRigidStatic* pInstance = new CRigidStatic(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRigidStatic");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CRigidStatic::Clone(void* pArg)
{
	CRigidStatic* pInstance = new CRigidStatic(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CRigidStatic");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRigidStatic::Free()
{
	Super::Free();
}