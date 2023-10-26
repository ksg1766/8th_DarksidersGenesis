#pragma once
#include "Client_Defines.h"
#include "MonoBehaviour.h"
#include "RigidDynamic.h"
#include "Transform.h"
#include "NavMeshAgent.h"

BEGIN(Engine)

class CTransform;
class CNavMeshAgent;

END

BEGIN(Client)

class CMonsterController : public CMonoBehaviour
{
	using Super = CMonoBehaviour;

private:
	CMonsterController(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMonsterController(const CMonsterController& rhs);
	virtual ~CMonsterController() = default;

public:
	virtual HRESULT Initialize_Prototype()				override;
	virtual HRESULT Initialize(void* pArg)				override;
	virtual void	Tick(const _float& fTimeDelta)		override;
	virtual void	LateTick(const _float& fTimeDelta)	override;
	virtual void	DebugRender()						override;

public:
	void	GetMoveMessage(const Vec3& vDir)		{ m_vNetMove += vDir; }
	void	GetTranslateMessage(const Vec3& vDir)	{ m_vNetTrans += vDir; }
	void	GetAttackMessage()						{ Attack(); }
	void	GetChaseMessage(_bool bMax)				{ m_bMax = bMax; }

	void	ForceHeight()							{ m_pTransform->Translate(Vec3(0.f, m_pNavMeshAgent->GetHeightOffset(), 0.f)); }
	_float	GetHeightOffset()						{ return m_pNavMeshAgent->GetHeightOffset(); }
	_bool	Walkable(_fvector vPoint)				{ return m_pNavMeshAgent->Walkable(vPoint); }

	void	Look(const Vec3& vPoint, const _float& fTimeDelta);

	void	SetTarget(CGameObject* pTarget)			{ m_pTarget = pTarget; }	// �Ⱦ��� ��. BlackBoard���� ó��
	void	SetTargetPoint(Vec3& vTargetPoint)		{ m_vTargetPoint = vTargetPoint; }

	// functor
	_bool	MyMemberFunction()
	{
		
		return true;
	}

private:
	void	Move(const _float& fTimeDelta);
	void	Translate(const _float& fTimeDelta);
	void	Attack();

	void	LimitAllAxisVelocity();

private:
	CTransform*		m_pTransform = nullptr;
	CRigidDynamic*	m_pRigidBody = nullptr;
	CNavMeshAgent*	m_pNavMeshAgent = nullptr;
	Vec3			m_vPrePos;

	Vec3			m_vNetMove;
	Vec3			m_vNetTrans;

	Vec3			m_vMaxLinearSpeed;
	Vec3			m_vLinearSpeed;
	_bool			m_bMax = false;

	Vec3			m_vMaxAngularSpeed;
	Vec3			m_vAngularSpeed;

	CGameObject*	m_pTarget = nullptr;
	Vec3			m_vTargetPoint;

public:
	static	CMonsterController* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(CGameObject* pGameObject, void* pArg) override;
	virtual void Free() override;
};

END