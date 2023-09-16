#pragma once

#include "Base.h"
#include "Client_Defines.h"
#include "GameObject.h"

class CBasicTerrain : public CGameObject
{
	using Super = CGameObject;
protected:
	/* ������ ������ �� */
	CBasicTerrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	/* �纻�� ������ �� */
	CBasicTerrain(const CBasicTerrain& rhs); /* ���� ������. */
	virtual ~CBasicTerrain() = default;

public:
	virtual HRESULT			Initialize_Prototype()		override;
	virtual HRESULT			Initialize(void* pArg)		override;
	virtual void			Tick(_float fTimeDelta)		override;
	virtual void			LateTick(_float fTimeDelta)	override;
	virtual void			DebugRender()				override;
	virtual HRESULT			Render()					override;

protected:
	HRESULT Ready_Components(void* pArg);
	HRESULT Bind_ShaderResources();

public:
	static CBasicTerrain* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CBasicTerrain* Clone(void* pArg);
	virtual void Free() override;
};