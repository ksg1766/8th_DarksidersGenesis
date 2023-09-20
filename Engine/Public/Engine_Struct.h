#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef struct tagGraphicDesc
	{
		enum WINMODE { WINMODE_FULL, WINMODE_WIN, WINMODE_END };

		HWND		hWnd;
		WINMODE		eWinMode;
		unsigned int	iWinSizeX, iWinSizeY;

	}GRAPHIC_DESC;

	typedef struct tagFaceIndices16
	{
		unsigned short		_0, _1, _2;
	}FACEINDICES16;

	typedef struct tagFaceIndices32
	{
		unsigned long		_0, _1, _2;
	}FACEINDICES32;

	typedef struct ENGINE_DLL tagVertex_Position_Texcoord
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexcoord;

		static const _uint				iNumElements = 2;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];

	}VTXPOSTEX;

	typedef struct ENGINE_DLL tagVertex_Position_Normal_Texcoord
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexcoord;

		static const _uint				iNumElements = 3;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[iNumElements];

	}VTXNORTEX;

	typedef struct ENGINE_DLL tagVertex_Cube_Texture
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vTexture;

		static const _uint				iNumElements = 2;
		static const D3D11_INPUT_ELEMENT_DESC Elements[iNumElements];

	}VTXCUBETEX;

	typedef struct tagVertexAnimModel
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexture;
		XMFLOAT3		vTangent;
		XMUINT4			vBlendIndex; /* 이 정점에 영향을 주는 뼈의 인덱스 네개. */
		XMFLOAT4		vBlendWeight; /* 영향르 주고 있는 각 뼈대의 영향 비율 */
	}VTXANIMMODEL;

	typedef struct tagCollision
	{
		class CRigidBody* pOther;
		// Vec3		vImpulse;
		 Vec3		vResultVelocity;
		//_float fTimeDelta;
	}COLLISION_DESC;
}


#endif // Engine_Struct_h__
