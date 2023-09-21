#include "Engine_Defines.h"
#include "GameObject.h"
#include "Transform.h"
#include "ColliderSphere.h"
#include "ColliderAABB.h"
#include "ColliderOBB.h"
#include "ColliderCylinder.h"

COBBCollider::COBBCollider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: Super(pDevice, pContext, ColliderType::OBB)
{

}

COBBCollider::COBBCollider(const COBBCollider& rhs)
	: Super(rhs)
	, m_tBoundingBox(rhs.m_tBoundingBox)
{
}

HRESULT COBBCollider::Initialize_Prototype()
{
	return S_OK;
}

HRESULT COBBCollider::Initialize(void* pArg)
{
	//Vec3 scale = GetGameObject()->GetTransform()->GetLocalScale();
	//m_tBoundingBox.Extents = scale;
	//m_pRigidBody = m_pGameObject->GetRigidBody();
	CTransform* pTransform = GetGameObject()->GetTransform();

	m_tBoundingBox.Center = pTransform->GetPosition();
	m_tBoundingBox.Extents = 0.5f * pTransform->GetLocalScale();
	m_tBoundingBox.Orientation = pTransform->GetRotationQuaternion();



	return S_OK;
}

void COBBCollider::Tick(const _float& fTimeDelta)
{
	CTransform* pTransform = GetGameObject()->GetTransform();

	m_tBoundingBox.Center = pTransform->GetPosition();
	m_tBoundingBox.Extents = 0.5f * pTransform->GetLocalScale();
	m_tBoundingBox.Orientation = pTransform->GetRotationQuaternion();
}

void COBBCollider::LateTick(const _float& fTimeDelta)
{
}

void COBBCollider::DebugRender()
{

}

_bool COBBCollider::Intersects(Ray& ray, OUT _float& distance)
{
	return m_tBoundingBox.Intersects(ray.position, ray.direction, OUT distance);
}

_bool COBBCollider::Intersects(Super* other)
{
	ColliderType type = other->GetColliderType();

	switch (type)
	{
	case ColliderType::Sphere:
		return m_tBoundingBox.Intersects(dynamic_cast<CSphereCollider*>(other)->GetBoundingSphere());
	case ColliderType::AABB:
		return m_tBoundingBox.Intersects(dynamic_cast<CAABBCollider*>(other)->GetBoundingBox());
	case ColliderType::OBB:
		return m_tBoundingBox.Intersects(dynamic_cast<COBBCollider*>(other)->GetBoundingBox());
	//case ColliderType::Cylinder:
	//	return m_tBoundingBox.Intersects(dynamic_cast<CCylinderCollider*>(other)->GetBoundingCylinder());
	}

	return false;
}

COBBCollider* COBBCollider::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	COBBCollider* pInstance = new COBBCollider(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : COBBCollider");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* COBBCollider::Clone(CGameObject* pGameObject, void* pArg)
{
	COBBCollider* pInstance = new COBBCollider(*this);
	pInstance->m_pGameObject = pGameObject;
	pInstance->m_pRigidBody = pInstance->m_pGameObject->GetRigidBody();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : COBBCollider");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void COBBCollider::Free()
{
	Super::Free();
}
