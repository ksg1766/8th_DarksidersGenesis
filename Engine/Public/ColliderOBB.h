#pragma once
#include "ColliderBase.h"

BEGIN(Engine)

class ENGINE_DLL COBBCollider : public CCollider
{
	using Super = CCollider;
private:
	COBBCollider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	COBBCollider(const COBBCollider& rhs);
	virtual ~COBBCollider() = default;

public:
	virtual HRESULT Initialize_Prototype()					override;
	virtual HRESULT Initialize(void* pArg)					override;
	virtual void	Tick(_float fTimeDelta)					override;
	virtual void	LateTick(_float fTimeDelta)				override;
	virtual void	DebugRender()							override;

	virtual _bool	Intersects(Ray& ray, OUT _float& distance)	override;
	virtual _bool	Intersects(Super*& other)					override;

	BoundingOrientedBox& GetBoundingBox() { return m_tBoundingBox; }

private:	
	BoundingOrientedBox m_tBoundingBox;

public:
	static COBBCollider* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(void* pArg)	override;
	virtual void Free()						override;
};

END