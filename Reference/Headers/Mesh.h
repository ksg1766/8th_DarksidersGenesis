#pragma once

/* ���� Ư�� ������ �ǹ��ϴ� �޽�. */
/* �� ����(�޽�)���� ����, �ε������۸� ������. */
#include "VIBuffer.h"

BEGIN(Engine)

class CModel;
class CMesh final : public CVIBuffer
{
	using Super = CVIBuffer;
private:
	CMesh(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMesh(const CMesh& rhs);
	virtual ~CMesh() = default;

public:
	HRESULT Initialize_Prototype(string& strName, vector<VTXMESH>& Vertices, vector<_int>& Indices, _uint iMatIndex, vector<_int>& Bones, Matrix& matPivot, CModel* pModel);
	HRESULT Initialize_Prototype(string& strName, vector<VTXANIMMESH>& Vertices, vector<_int>& Indices, _uint iMatIndex, vector<_int>& Bones, CModel* pModel);
	virtual HRESULT Initialize(void* pArg);

public:
	_uint					Get_MaterialIndex() const	{ return m_iMaterialIndex; }

public:
	void					SetUp_BoneMatrices(_float4x4* pBoneMatrices, _fmatrix PivotMatrix); /* �޽��� ������ �׸������� ���̴��� �ѱ������ ������� �迭�� �����Ѵ�. */

private:
	_char					m_szName[MAX_PATH] = "";
	_int					m_iMaterialIndex = 0;	/* �޽ø� �׸� �� ����ϴ� ���¸��� �ε��� */

private:
	vector<class CBone*>	m_Bones;			/* �� �޽ÿ� ������ �ִ� �� ���� (�޽ú��� ��������, �ش� �޽ÿ� ������ �ִ� �� ����� ��Ƽ� �佺 */
	vector<_int>			m_BoneIndices;		/* Cache (Initialize���� ���� ã�ƿ��� ���� �ε�����) */

private:
	HRESULT Ready_StaticVertices(vector<VTXMESH>& Vertices, _fmatrix& PivotMatrix);
	HRESULT Ready_AnimVertices(vector<VTXANIMMESH>& Vertices);
	HRESULT Ready_Indices(vector<_int>& Indices);

public:
	static CMesh* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, string& strName, vector<VTXMESH>& Vertices, vector<_int>& Indices, _uint iMatIndex, vector<_int>& Bones, Matrix& matPivot, CModel* pModel);
	static CMesh* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, string& strName, vector<VTXANIMMESH>& Vertices, vector<_int>& Indices, _uint iMatIndex, vector<_int>& Bones, CModel* pModel);

	virtual CComponent* Clone(CGameObject* pGameObject, void* pArg = nullptr) override;
	virtual void Free() override;
};

END