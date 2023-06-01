#include "AudioSource.h"
#include "Transform.h"
#include "GameObj.h"
#include "AudioClip.h"

namespace dru
{
	CAudioSource::CAudioSource()
		: CComponent(eComponentType::AudioSource)
		, mAudioClip(nullptr) {
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

		mAudioClip->Set3DAttributes(pos, forward);
	}

	void CAudioSource::render()
	{
	}

	void CAudioSource::Play()
	{
		mAudioClip->Play();
	}

	void CAudioSource::Stop()
	{
		mAudioClip->Stop();
	}

	void CAudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}

	void CAudioSource::SetClipByKey(const std::wstring& _key)
	{
		mAudioClip = CResources::Find<CAudioClip>(_key);
	}


}