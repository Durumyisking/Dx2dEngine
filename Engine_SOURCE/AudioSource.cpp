#include "AudioSource.h"
#include "Transform.h"
#include "GameObj.h"
#include "AudioClip.h"

namespace dru
{
	CAudioSource::CAudioSource()
		: CComponent(eComponentType::AudioSource)
		, mAudioClips{}
	{
	}

	CAudioSource::~CAudioSource()
	{
	}

	void CAudioSource::Initialize()
	{
	}

	void CAudioSource::update()
	{
	}

	void CAudioSource::fixedUpdate()
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>();
		Vector3 pos = tr->GetPosition();
		Vector3 forward = tr->Forward();
		for (std::pair<const std::wstring, CAudioClip*> clip : mAudioClips)
		{
			CAudioClip* audioClip = clip.second;
			if (audioClip->IsPlaying())
			{
				audioClip->Set3DAttributes(pos, forward);
			}
		}
	}

	void CAudioSource::render()
	{
	}

	void CAudioSource::Play(const std::wstring& _key, bool _loop)
	{
		GetClip(_key)->SetLoop(_loop);
		GetClip(_key)->Play();
	}

	void CAudioSource::Stop(const std::wstring& _key)
	{
		GetClip(_key)->Stop();
	}

	void CAudioSource::SetLoop(const std::wstring& _key, bool loop)
	{
		GetClip(_key)->SetLoop(loop);
	}

	void CAudioSource::AddClipByKey(const std::wstring& _key)
	{
		std::shared_ptr<CAudioClip> resource = CResources::Find<CAudioClip>(_key);
		mAudioClips.insert(std::make_pair(_key, resource.get()));

	}

	CAudioClip* CAudioSource::GetClip(const std::wstring& _key)
	{
		std::map<std::wstring, CAudioClip*>::iterator iter = mAudioClips.find(_key);

		if (iter != mAudioClips.end())
		{
			return iter->second;
		}

		return nullptr;
	}


}