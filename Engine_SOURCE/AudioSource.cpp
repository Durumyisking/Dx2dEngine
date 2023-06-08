#include "AudioSource.h"
#include "Transform.h"
#include "GameObj.h"
#include "AudioClip.h"
#include "TimeMgr.h"

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
		pos.z = 0.f;
		Vector3 forward = tr->Forward();
		for (std::pair<const std::wstring, CAudioClip*> clip : mAudioClips)
		{
			CAudioClip* audioClip = clip.second;
			if (audioClip->IsPlaying())
			{
				if (CTimeMgr::IsPlayerBulletTimeOn())
				{
					audioClip->SetPitch(0.333f);
				}
				else
				{
					audioClip->SetPitch(1.f);
				}
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

	void CAudioSource::Play_NoInterrupt(const std::wstring& _key, bool _loop)
	{
		if (!GetClip(_key)->IsPlaying())
		{
			GetClip(_key)->SetLoop(_loop);
			GetClip(_key)->Play();
		}
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

	void CAudioSource::SetWholeVolume(float _Volume)
	{
		for (std::pair<const std::wstring, CAudioClip*> clip : mAudioClips)
		{
			CAudioClip* audioClip = clip.second;
			audioClip->SetVolume(_Volume);
		}
	}

	void CAudioSource::SetWholePitch(float _Pitch)
	{
		for (std::pair<const std::wstring, CAudioClip*> clip : mAudioClips)
		{
			CAudioClip* audioClip = clip.second;
			audioClip->SetPitch(_Pitch);
		}
	}

	void CAudioSource::SetWholeVolume_Ratio(float _Volume)
	{
		for (std::pair<const std::wstring, CAudioClip*> clip : mAudioClips)
		{
			CAudioClip* audioClip = clip.second;
			float vol = audioClip->GetVolume();
			vol *= _Volume;
			audioClip->SetVolume(vol);
		}
	}

	void CAudioSource::SetWholePitch_Ratio(float _Pitch)
	{
		for (std::pair<const std::wstring, CAudioClip*> clip : mAudioClips)
		{
			CAudioClip* audioClip = clip.second;
			float pitch = audioClip->GetPitch();
			pitch *= _Pitch;
			audioClip->SetPitch(pitch);
		}
	}

	void CAudioSource::SetVolume(const std::wstring& _key, float _Volume)
	{
		mAudioClips.find(_key)->second->SetVolume(_Volume);
	}

	void CAudioSource::SetPitch(const std::wstring& _key, float _Pitch)
	{
		mAudioClips.find(_key)->second->SetPitch(_Pitch);
	}

	float CAudioSource::GetVolume(const std::wstring& _key)
	{
		return mAudioClips.find(_key)->second->GetVolume();
	}

	float CAudioSource::GetPitch(const std::wstring& _key)
	{
		return mAudioClips.find(_key)->second->GetPitch();
	}


}