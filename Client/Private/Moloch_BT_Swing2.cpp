#include "stdafx.h"
#include "Moloch_BT_Swing2.h"
#include "GameInstance.h"
#include "Layer.h"
#include "GameObject.h"
#include "BossController.h"

CMoloch_BT_Swing2::CMoloch_BT_Swing2()
{
}

void CMoloch_BT_Swing2::OnStart()
{
	Super::OnStart(0);

	const Vec3& vTargetPos = GetTarget()->GetTransform()->GetPosition();

	CBossController* pController = static_cast<CBossController*>(m_pController);
	pController->Look(vTargetPos);
}

CBT_Node::BT_RETURN CMoloch_BT_Swing2::OnUpdate(const _float& fTimeDelta)
{
	if (IsZeroHP())
		return BT_FAIL;

	if (m_fTimeSum > m_vecAnimIndexTime[0].second * 0.6f)
	{
		return BT_SUCCESS;
	}

	m_fTimeSum += fTimeDelta;

	return BT_RUNNING;
}

void CMoloch_BT_Swing2::OnEnd()
{
	static_cast<CRigidDynamic*>(m_pGameObject->GetRigidBody())->IsKinematic(true);
	Super::OnEnd();
}

void CMoloch_BT_Swing2::ConditionalAbort(const _float& fTimeDelta)
{
}

_bool CMoloch_BT_Swing2::IsZeroHP()
{
	if (static_cast<CBossController*>(m_pController)->IsZeroHP())
		return true;

	return false;
}

CGameObject* CMoloch_BT_Swing2::GetTarget()
{
	BLACKBOARD& hashBlackBoard = m_pBehaviorTree->GetBlackBoard();
	const auto& target = hashBlackBoard.find(TEXT("Target"));
	CGameObject* pPlayer = GET_VALUE(CGameObject, target);

	return pPlayer;
}

CMoloch_BT_Swing2* CMoloch_BT_Swing2::Create(CGameObject* pGameObject, CBehaviorTree* pBehaviorTree, const BEHAVEANIMS& tBehaveAnim, CMonoBehaviour* pController)
{
	CMoloch_BT_Swing2* pInstance = new CMoloch_BT_Swing2;

	if (FAILED(pInstance->Initialize(pGameObject, pBehaviorTree, tBehaveAnim, pController)))
	{
		MSG_BOX("Failed to Created : CMoloch_BT_Swing2");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMoloch_BT_Swing2::Free()
{
	Super::Free();
}