#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)



END

BEGIN(Client)

class CSkyPlane final : public CGameObject
{
	using Super = CGameObject;
private:
	/* ������ ������ �� */
	CSkyPlane(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	/* �纻�� ������ �� */
	CSkyPlane(const CSkyPlane& rhs); /* ���� ������. */
	virtual ~CSkyPlane() = default;

public:
	virtual HRESULT Initialize_Prototype()				override;
	virtual HRESULT Initialize(void* pArg)				override;
	virtual void	Tick(const _float& fTimeDelta)		override;
	virtual void	LateTick(const _float& fTimeDelta)	override;
	virtual void	DebugRender()						override;
	virtual HRESULT Render()							override;

private:
	HRESULT			Bind_ShaderResources(); /* ���̴� ���������� �� ������. */
	HRESULT			Ready_FixedComponents();
	HRESULT			Ready_Scripts(void* pArg);

public:
	static	CSkyPlane* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override; /* �纻��ü�� �����Ҷ� ���������ͷκ��� �����ؿ� �����Ϳܿ� �� �߰��� ����� �����Ͱ� �ִٶ�� �޾ƿ��ڴ�. */
	virtual void Free() override;
};

END