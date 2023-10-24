#include "BehaviorTree.h"
#include "GameObject.h"
#include "BT_Node.h"

CBehaviorTree::CBehaviorTree(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: Super(pDevice, pContext)
{

}

CBehaviorTree::CBehaviorTree(const CBehaviorTree& rhs)
	:Super(rhs)
{
}

HRESULT CBehaviorTree::Initialize_Prototype()
{


	return S_OK;
}

HRESULT CBehaviorTree::Initialize(void* pArg)
{

	return S_OK;
}

void CBehaviorTree::Tick(const _float& fTimeDelta)
{
	if (m_NodeStack.size())
	{
		if (CBT_Node::BT_RETURN::BT_RUNNING != m_NodeStack.top()->Tick(fTimeDelta))
			m_NodeStack.pop();
	}
	else
	{
		m_pRootNode->Tick(fTimeDelta);
	}
}

void CBehaviorTree::LateTick(const _float& fTimeDelta)
{
	
}

void CBehaviorTree::DebugRender()
{
}

CBehaviorTree* CBehaviorTree::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CBehaviorTree* pInstance = new CBehaviorTree(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBehaviorTree");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CBehaviorTree::Clone(CGameObject* pGameObject, void* pArg)
{
	CBehaviorTree* pInstance = new CBehaviorTree(*this);
	pInstance->m_pGameObject = pGameObject;

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CBehaviorTree");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBehaviorTree::Free()
{
	Super::Free();
}