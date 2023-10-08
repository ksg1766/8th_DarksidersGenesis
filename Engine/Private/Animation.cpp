#include "..\Public\Animation.h"
#include "Model.h"
#include "Bone.h"
#include "Channel.h"

CAnimation::CAnimation()
{
}

CAnimation::CAnimation(const CAnimation & rhs)
	: m_fDuration(rhs.m_fDuration)
	, m_Channels(rhs.m_Channels)
	, m_fTickPerSecond(rhs.m_fTickPerSecond)
	, m_fPlayTime(rhs.m_fPlayTime)
{
	for (auto& pChannel : m_Channels)
		Safe_AddRef(pChannel);
}

HRESULT CAnimation::Initialize_Prototype(const _float& fDuration, const _float& fTickPerSecond, vector<class CChannel*>& Channels)
{
	m_fDuration = fDuration;
	m_fTickPerSecond = fTickPerSecond;

	/* 벡터에 사이즈도 안 채우고 멤카피 하면 큰일난다. */
	//memcpy(&m_Channels, &Channels, sizeof(Channels)); 

	m_Channels.reserve(Channels.size());
	for (auto& iter : Channels)
		m_Channels.push_back(iter);

	return S_OK;
}

HRESULT CAnimation::Initialize(CModel* pModel)
{
	/* 애니메이션을 재생하기 위해 사용되는 뼈를 모두 저장한다.  */
	for (_uint i = 0; i < m_Channels.size(); ++i)
	{
		m_ChannelKeyFrames.push_back(0);

		CBone*	pBone = pModel->GetBone(m_Channels[i]->Get_Name().c_str());
		{
			if (nullptr == pBone)
				return E_FAIL;		

			m_Bones.push_back(pBone);
		}
		Safe_AddRef(pBone);
	}
	return S_OK;
}

HRESULT CAnimation::Play_Animation(_float fTimeDelta)
{
	/* 현재 재생 시간을 구한다. */
	m_fPlayTime += m_fTickPerSecond * fTimeDelta;

	/* 애니메이션이 끝났다면 */
	if (m_fPlayTime >= m_fDuration)
	{
		m_fPlayTime = 0.f;

		for (auto& pChannel : m_Channels)
		{
			for (auto& iCurrentKeyFrame : m_ChannelKeyFrames)
				iCurrentKeyFrame = 0;			
		}
	}

	/* 이 애니메이션의 모든 채널의 키프레임을 보간한다. (아직 부모 기준)*/
	_uint iChannelIndex = 0;
	for (auto& pChannel : m_Channels)
	{	// iChannelIndex를 늘려가며 순회하면서 트랜스폼 업데이트 해 주고, 현재 키프레임도 다시 계산해서 저장 해 주는듯.
		m_ChannelKeyFrames[iChannelIndex] = pChannel->Update_Transformation(m_fPlayTime, m_ChannelKeyFrames[iChannelIndex], m_Bones[iChannelIndex]);

		++iChannelIndex;
	}

	return S_OK;
}

CAnimation* CAnimation::Create(const _float& fDuration, const _float& fTickPerSecond, vector<class CChannel*>& Channels)
{
	CAnimation* pInstance = new CAnimation();

	if (FAILED(pInstance->Initialize_Prototype(fDuration, fTickPerSecond, Channels)))
	{
		MSG_BOX("Failed To Created : CAnimation");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CAnimation * CAnimation::Clone(CModel* pModel)
{
	CAnimation*			pInstance = new CAnimation(*this);

	if (FAILED(pInstance->Initialize(pModel)))
	{
		MSG_BOX("Failed To Cloned : CAnimation");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CAnimation::Free()
{
	/* Channel */
	for (auto& pChannel : m_Channels)
		Safe_Release(pChannel);
	m_Channels.clear();

	/* HierarachyNode */
	for (auto& pBone : m_Bones)
		Safe_Release(pBone);
	m_Bones.clear();
}
