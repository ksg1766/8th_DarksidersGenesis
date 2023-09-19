#pragma once

#include "Component.h"

/* 1. 화면에 그려져야하는 객체들을 그리는 순서대로 모아서 보관한다. */
/* 2. 보관하고 있는 객체들의 렌더콜(드로우콜)을 수행한다. */

BEGIN(Engine)

class ENGINE_DLL CRenderer final : public CComponent
{
public:
	/* RG_NONBLEND : 이후 그려지는 Blend오브젝트들의 섞는 연산을 위해 반드시 불투명한 애들을 먼저 그려야한다. */
	/* RG_BLEND : 반투명하게 그려지는 객체들도 반드시 멀리있는 놈부터 그린다. */
	enum RENDERGROUP { RG_PRIORITY, RG_NONLIGHT, RG_NONBLEND, RG_BLEND, RG_UI, RG_END };
private:
	CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);	
	CRenderer(const CRenderer& rhs) = delete;
	virtual ~CRenderer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Add_RenderGroup(RENDERGROUP eRenderGroup, class CGameObject* pGameObject);
	HRESULT Draw_RenderObjects();


private:
	list<class CGameObject*>			m_RenderObjects[RG_END];

private:
	HRESULT Render_Priority();
	HRESULT Render_NonLight();
	HRESULT Render_NonBlend();
	HRESULT Render_Blend();
	HRESULT Render_UI();

public:
	static CRenderer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(CGameObject* pGameObject, void* pArg) override;
	virtual void Free() override;
};

END