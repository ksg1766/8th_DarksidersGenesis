#pragma once
#include "Client_Defines.h"
#include "BT_Decorator.h"

BEGIN(Client)

class CHellHound_BT_IF_Dead : public CBT_Decorator
{
	using Super = CBT_Decorator;
private:
	CHellHound_BT_IF_Dead() = default;
	CHellHound_BT_IF_Dead(const CHellHound_BT_IF_Dead& rhs) = delete;
	virtual ~CHellHound_BT_IF_Dead() = default;

	virtual void OnStart() override
	{

	}

	virtual BT_RETURN OnUpdate(const _float& fTimeDelta) override
	{
		return BT_FAIL;	// �ϴ� �ӽ÷� ���� ����� ������ �׻� FAIL;
	}

	virtual void OnEnd() override
	{

	}

public:
	static	CHellHound_BT_IF_Dead* Create(CGameObject* pGameObject, CBehaviorTree* pBehaviorTree, CMonoBehaviour* pController, DecoratorType eDecoratorType)
	{
		CHellHound_BT_IF_Dead* pInstance = new CHellHound_BT_IF_Dead;

		if (FAILED(pInstance->Initialize(pGameObject, pBehaviorTree, pController, eDecoratorType)))
		{
			MSG_BOX("Failed to Created : CHellHound_BT_IF_Dead");
			Safe_Release(pInstance);
		}

		return pInstance;
	}
	virtual void Free() override
	{
		Super::Free();
	}
};

END