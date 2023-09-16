#pragma once

#include "Component.h"

/* Ŭ���̾�Ʈ���� ������ �پ��� ���ӿ�����Ʈ���� �θ𰡵ȴ�. */

BEGIN(Engine)

class CMonoBehaviour;
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	/* ������ ������ �� */
	CGameObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	/* �纻�� ������ �� */
	CGameObject(const CGameObject& rhs); /* ���� ������. */
	virtual ~CGameObject() = default;

public:
	virtual HRESULT			Initialize_Prototype();
	virtual HRESULT			Initialize(void* pArg);
	virtual void			Tick(_float fTimeDelta);
	virtual void			LateTick(_float fTimeDelta);
	virtual HRESULT			Render();

	CComponent* GetFixedComponent(ComponentType type);
	CTransform* GetTransform();
	//CCamera* GetCamera();
	//CMeshRenderer* GetMeshRenderer();
	//CModelRenderer* GetModelRenderer();
	//CModelAnimator* GetModelAnimator();
	//CLight* GetLight();
	//CBaseCollider* GetCollider();
	//CTerrain* GetTerrain();
	//CButton* GetButton();

	CTransform*				GetOrAddTransform();
	void					AddComponent(CComponent* component);

	void					SetLayerIndex(uint8 layer) { m_i8LayerIndex = layer; }
	uint8					GetLayerIndex() { return m_i8LayerIndex; }

protected:
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };

protected:
	array<CComponent*, FIXED_COMPONENT_COUNT> m_arrComponents;
	vector<CMonoBehaviour*> m_vecScripts;

	uint8 m_i8LayerIndex = 0;

public:
	virtual CGameObject* Clone(void* pArg) PURE;
	virtual void Free() override;
};

END