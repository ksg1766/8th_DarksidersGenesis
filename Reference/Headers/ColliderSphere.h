#pragma once
#include "ColliderBase.h"

BEGIN(Engine)

class ENGINE_DLL CSphereCollider : public CCollider
{
	using Super = CCollider;
private:
	CSphereCollider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSphereCollider(const CSphereCollider& rhs);
	virtual ~CSphereCollider() = default;

public:
	virtual HRESULT Initialize_Prototype()					override;
	virtual HRESULT Initialize(void* pArg)					override;
	virtual void	Tick(_float fTimeDelta)					override;
	virtual void	LateTick(_float fTimeDelta)				override;
	virtual void	DebugRender()							override;

	virtual _bool	Intersects(Ray& ray, OUT _float& distance)	override;
	virtual _bool	Intersects(Super*& other)					override;

	void			SetRadius(_float radius)	{ m_fRadius = radius; }
	BoundingSphere&	GetBoundingSphere()			{ return m_tBoundingSphere; }

	virtual void	OnTriggerEnter(const CCollider* pOther)	override;
	virtual void	OnTriggerStay(const CCollider* pOther)	override;
	virtual void	OnTriggerExit(const CCollider* pOther)	override;

private:
	_float			m_fRadius = 1.f;
	BoundingSphere	m_tBoundingSphere;

public:
	static CSphereCollider* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(void* pArg)	override;
	virtual void Free()						override;
};

END