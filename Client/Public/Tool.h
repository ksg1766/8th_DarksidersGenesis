#pragma once
#include "Base.h"
#include "Client_Defines.h"

#include "../Public/ImGUI/imgui.h"
#include "../Public/ImGUI/imgui_impl_dx11.h"
#include "../Public/ImGUI/imgui_impl_win32.h"

BEGIN(Engine)

class CGameInstance;

END

BEGIN(Client)

class CTool : public CBase
{
	using Super = CBase;

protected:
	CTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CTool() = default;

public:
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Tick()			PURE;
	virtual HRESULT LateTick()		PURE;
	virtual HRESULT	DebugRender()	PURE;

protected:
	CGameInstance*	m_pGameInstance = nullptr;
	class CImGUIManager*	m_pImGUIInstance = nullptr;

	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };

public:
	virtual void Free() override;
};

END