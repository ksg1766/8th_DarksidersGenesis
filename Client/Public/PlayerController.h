#pragma once

#include "Client_Defines.h"
#include "MonoBehaviour.h"

BEGIN(Client)

class CPlayerController : public CMonoBehaviour
{
	using Super = CMonoBehaviour;

private:
	CPlayerController(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPlayerController(const CPlayerController& rhs);
	virtual ~CPlayerController() = default;

public:
	virtual HRESULT Initialize_Prototype()				override;
	virtual HRESULT Initialize(void* pArg)				override;
	virtual void	Tick(const _float& fTimeDelta)		override;
	virtual void	LateTick(const _float& fTimeDelta)	override;
	virtual void	DebugRender()						override;

private:
	void	Input(const _float& fTimeDelta);
	void	LimitAllAxisVelocity();

private:
	class CRigidDynamic*	m_pRigidBody;

	Vec3			m_vMaxLinearSpeed;
	Vec3			m_vLinearSpeed;

	Vec3			m_vMaxAngularSpeed;
	Vec3			m_vAngularSpeed;

public:
	static	CPlayerController* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(CGameObject* pGameObject, void* pArg) override;
	virtual void Free() override;
};

END