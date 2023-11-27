#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Client)

class CFire;
class CSwordTrail;
class CMoloch_Sword final : public CGameObject
{
	using Super = CGameObject;
private:
	/* 원형을 생성할 때 */
	CMoloch_Sword(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	/* 사본을 생성할 때 */
	CMoloch_Sword(const CMoloch_Sword& rhs);
	virtual ~CMoloch_Sword() = default;

public:
	virtual HRESULT Initialize_Prototype()				override;
	virtual HRESULT Initialize(void* pArg)				override;
	virtual void	Tick(const _float& fTimeDelta)		override;
	virtual void	LateTick(const _float& fTimeDelta)	override;
	virtual void	DebugRender()						override;
	virtual HRESULT Render()							override;

private:
	HRESULT			Ready_FixedComponents();
	HRESULT			Ready_Scripts();
	HRESULT			Bind_ShaderResources(); /* 셰이더 전역변수에 값 던진다. */
	HRESULT			Bind_FireResources();

	void			SwordTrailEmittor(const _float& fLifeTIme = 0.3f);

	vector<CFire*>	m_vecFires;

	deque<CSwordTrail*>	m_deqTrailsPool;
	deque<CSwordTrail*>	m_deqSwordTrails;

	Matrix			m_matOffsetTop;
	Matrix			m_matOffsetBottom;

	Matrix			m_matPreWorld = Matrix::Identity;
	TWEENDESC		m_tPreTweenDesc;

	//For CatmullRom
	TWEENDESC		m_tPrePreTweenDesc;
	TWEENDESC		m_tPrePrePreTweenDesc;

public:
	static	CMoloch_Sword* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override; /* 사본객체를 생성할때 원본데이터로부터 복제해올 데이터외에 더 추가해 줘야할 데이터가 있다라면 받아오겠다. */
	virtual void Free() override;
};

END