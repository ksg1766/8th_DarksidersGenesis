#include "stdafx.h"
#include "PrefabsView.h"
#include "ViewMediator.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Terrain.h"
#include "Utils.h"

CPrefabsView::CPrefabsView(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:Super(pDevice, pContext)
{
}

HRESULT CPrefabsView::Initialize(void* pArg)
{
	Super::Initialize(pArg);

	m_pTerrainBuffer = reinterpret_cast<CTerrain*>(pArg);
	m_vPickedPosition = Vec3::Zero;

	return S_OK;
}

HRESULT CPrefabsView::Tick()
{
	Input();

	ImGui::Begin("Prefabs");

	InfoView();
	TapGroups();

	ImGui::End();

	return S_OK;
}

HRESULT CPrefabsView::LateTick()
{

	return S_OK;
}

HRESULT CPrefabsView::DebugRender()
{

	return S_OK;
}

void CPrefabsView::Input()
{
	if (ImGui::GetIO().WantCaptureMouse)
		return;

	_float fPickDistance;

	if (m_pGameInstance->Mouse_Down(DIM_LB))
	{
		if (m_IsPickingActivated)
		{
			const POINT& p = m_pGameInstance->GetMousePos();
			if (m_pTerrainBuffer->Pick(p.x, p.y, m_vPickedPosition, fPickDistance))
			{
				PlaceObject(m_ePickedLayerTag, m_strPickedObject, m_vPickedPosition);
			}
		}
	}
}

void CPrefabsView::InfoView()
{
	ImGui::Text("This window has some useful function for Map Tool.");
	ImGui::NewLine();

	const POINT& p = m_pGameInstance->GetMousePos();
	ImGui::Text("Mouse Viewport Position : %d, %d", p.x, p.y);
	ImGui::NewLine();

	ImGui::Text("Picked Position : %.3f, %.3f, %.3f", m_vPickedPosition.x, m_vPickedPosition.y, m_vPickedPosition.z);
	ImGui::NewLine();

	ImGui::Text("Picking ");
	if (m_IsPickingActivated)
	{
		ImGui::SameLine();
		if (ImGui::Button("Deactivate"))
			m_IsPickingActivated = false;
	}
	else
	{
		ImGui::SameLine();
		if (ImGui::Button("Activate"))
		{
			m_IsPickingActivated = true;
			m_pMediator->OnNotifiedPickingOn(this);
		}
	}
	ImGui::NewLine();
}

void CPrefabsView::TapGroups()
{
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("Tool", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Ground"))
		{
			const _char* items[] =
			{
				"Arena", "FloorTiles_A", "FloorTiles_B", "RuinsFloor_A_Half", "RuinsFloor_A_Sqr",
				 "Staircase_A",
				"Stairs_Rock_A", "Stairs_Rock_B", "TileFloor_Mammon", "WallRubble"
			};

			if (m_Item_Current >= IM_ARRAYSIZE(items))
				m_Item_Current = IM_ARRAYSIZE(items) - 1;

			ImGui::ListBox("Ground Objects", &m_Item_Current, items, IM_ARRAYSIZE(items), 5);
			m_ePickedLayerTag = LAYERTAG::GROUND;
			m_strPickedObject = Utils::ToWString(items[m_Item_Current]);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Wall"))
		{
			const _char* items[] = { "Obelisk_A", "Pillar_LG", "RuinsPillar_4m_A", "RuinsPillar_4m_B",
				"RuinsPillar_5m_A", "RuinsPillar_5m_Arch_A", "RuinsPillar_5m_Arch_DMG",
				"RuinsPillar_5m_B", "RuinsWall_A", "RuinsWall_B", "RuinWall_CNR_A", "RuinWall_CNR_B", };

			if (m_Item_Current >= IM_ARRAYSIZE(items))
				m_Item_Current = IM_ARRAYSIZE(items) - 1;

			ImGui::ListBox("Wall Objects", &m_Item_Current, items, IM_ARRAYSIZE(items), 5);
			m_ePickedLayerTag = LAYERTAG::WALL;
			m_strPickedObject = Utils::ToWString(items[m_Item_Current]);
			
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void CPrefabsView::PlaceObject(const LAYERTAG& eLayerTag, const wstring& strObjectTag, const Vec3& vPickPosition)
{
	if (eLayerTag == LAYERTAG::LAYER_END) return;

	const wstring strPrototypeTag = TEXT("Prototype_GameObject_") + strObjectTag;

	CGameObject* pGameObject = m_pGameInstance->CreateObject(strPrototypeTag, eLayerTag);

	pGameObject->GetTransform()->Translate(vPickPosition);
}

CPrefabsView* CPrefabsView::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CTerrain* m_pTerrainBf)
{
	CPrefabsView* pInstance = new CPrefabsView(pDevice, pContext);

	if (FAILED(pInstance->Initialize(m_pTerrainBf)))
	{
		MSG_BOX("Failed to Created : CPrefabsView");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPrefabsView::Free()
{
	Super::Free();
}
