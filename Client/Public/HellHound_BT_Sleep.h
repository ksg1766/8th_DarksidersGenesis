#pragma once
#include "Client_Defines.h"
#include "BT_Action.h"

BEGIN(Client)

class CHellHound_BT_Sleep : public CBT_Action
{
	using Super = CBT_Action;
protected:
	CHellHound_BT_Sleep();
	CHellHound_BT_Sleep(const CHellHound_BT_Sleep& rhs) = delete;
	virtual ~CHellHound_BT_Sleep() = default;
	
	virtual void		ConditionalAbort(const _float& fTimeDelta);

	virtual void		OnStart()							override;
	virtual BT_RETURN	OnUpdate(const _float& fTimeDelta)	override;
	virtual void		OnEnd()								override;

public:
	static	CHellHound_BT_Sleep* Create(CGameObject* pGameObject, CBehaviorTree* pBehaviorTree, const BEHAVEANIMS& tBehaveAnim, CMonoBehaviour* pController);
	virtual void Free() override;
};

END