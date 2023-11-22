#include "stdafx.h"
#include "..\Public\TremorCrystal.h"
#include "GameInstance.h"
#include "Particle.h"
#include "ParticleController.h"

CTremorCrystal::CTremorCrystal(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: Super(pDevice, pContext)
{
}

CTremorCrystal::CTremorCrystal(const CTremorCrystal& rhs)
	: Super(rhs)
{
}

HRESULT CTremorCrystal::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTremorCrystal::Initialize(void* pArg)
{
	if (FAILED(Ready_FixedComponents()))
		return E_FAIL;

	if (FAILED(Ready_Scripts()))
		return E_FAIL;

	GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));
	GetTransform()->RotateYAxisFixed(Vec3(0.f, 90.f, 0.f));
	GetTransform()->Translate(Vec3(0.f, 0.6f, 0.f));

	EFFECT_DESC pDesc = *reinterpret_cast<EFFECT_DESC*>(pArg);
	m_fLifeTime = pDesc.fLifeTime;

	return S_OK;
}

void CTremorCrystal::Tick(const _float& fTimeDelta)
{
	m_fLifeTime -= fTimeDelta;

	if (m_fLifeTime < 0.f)
	{
		m_pGameInstance->DeleteObject(this);
		CParticleController::PARTICLE_DESC tParticleDesc;
		tParticleDesc.eType = CParticleController::ParticleType::EXPLODE;
		tParticleDesc.vSpeedMax = _float3(5.f, 10.f, 5.f);
		tParticleDesc.vSpeedMin = _float3(-5.f, 7.f, -5.f);
		tParticleDesc.vCenter = GetTransform()->GetPosition();
		tParticleDesc.iPass = 1;
		for (_int i = 0; i < 25; ++i)
			m_pGameInstance->CreateObject(TEXT("Prototype_GameObject_Particle"), LAYERTAG::IGNORECOLLISION, &tParticleDesc);

		return;
	}

	Super::Tick(fTimeDelta);
}

void CTremorCrystal::LateTick(const _float& fTimeDelta)
{
	Super::LateTick(fTimeDelta);

	GetRenderer()->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

void CTremorCrystal::DebugRender()
{
	Super::DebugRender();
}

HRESULT CTremorCrystal::Render()
{
	if (nullptr == GetModel() || nullptr == GetShader())
		return E_FAIL;

	if (FAILED(GetTransform()->Bind_ShaderResources(GetShader(), "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	GetModel()->Render();

#ifdef _DEBUG
	Super::DebugRender();
#endif

	return S_OK;
}

HRESULT CTremorCrystal::Ready_FixedComponents()
{
	/* Com_Shader */
	if (FAILED(Super::AddComponent(LEVEL_STATIC, ComponentType::Shader, TEXT("Prototype_Component_Shader_VtxMesh"))))
		return E_FAIL;

	/* Com_Model */
	if (FAILED(Super::AddComponent(LEVEL_STATIC, ComponentType::Model, TEXT("Prototype_Component_Model_") + GetObjectTag())))
		return E_FAIL;

	/* Com_Texture */
	if (FAILED(Super::AddComponent(LEVEL_STATIC, ComponentType::Texture, TEXT("Prototype_Component_Texture_TremorCrystal_A_emissive"))))
		return E_FAIL;

	/* Com_Transform */
	if (FAILED(Super::AddComponent(LEVEL_STATIC, ComponentType::Transform, TEXT("Prototype_Component_Transform"))))
		return E_FAIL;

	/* Com_Renderer */
	if (FAILED(Super::AddComponent(LEVEL_STATIC, ComponentType::Renderer, TEXT("Prototype_Component_Renderer"))))
		return E_FAIL;

	/* Com_RigidBody */
	if (FAILED(Super::AddComponent(LEVEL_STATIC, ComponentType::RigidBody, TEXT("Prototype_Component_RigidStatic"))))
		return E_FAIL;

	if (LEVEL_GAMETOOL == m_pGameInstance->GetCurrentLevelIndex())
		if(FAILED(GetRigidBody()->InitializeCollider()))
			return E_FAIL;

	return S_OK;
}

HRESULT CTremorCrystal::Ready_Scripts()
{
	return S_OK;
}

HRESULT CTremorCrystal::Bind_ShaderResources()
{
	/* ���̴� ���������� ������ �� ������ ������. */
	if (FAILED(m_pGameInstance->Bind_TransformToShader(GetShader(), "g_ViewMatrix", CPipeLine::D3DTS_VIEW)) ||
		FAILED(m_pGameInstance->Bind_TransformToShader(GetShader(), "g_ProjMatrix", CPipeLine::D3DTS_PROJ)))
	{
		return E_FAIL;
	}

	if (FAILED(GetTexture()->Bind_ShaderResource(GetShader(), "g_EmissiveTexture", 0)))
		return E_FAIL;

	return S_OK;
}

CTremorCrystal* CTremorCrystal::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTremorCrystal* pInstance = new CTremorCrystal(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTremorCrystal");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CTremorCrystal::Clone(void* pArg)
{
	CTremorCrystal* pInstance = new CTremorCrystal(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTremorCrystal");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTremorCrystal::Free()
{
	Super::Free();
}