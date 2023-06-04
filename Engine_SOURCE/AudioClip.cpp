#pragma once
#include "AudioClip.h"
#include "Transform.h"

namespace dru
{
	CAudioClip::CAudioClip()
		: CResource(eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1000.0f)
		, mbLoop(false) 
		, mVolume(0.f)
		, mPitch(0.f)
	{
	}
	CAudioClip::~CAudioClip()
	{
		mSound->release();
		mSound = nullptr;
	}
	HRESULT CAudioClip::Load(const std::wstring& path)
	{
		std::filesystem::path parentPath = std::filesystem::current_path().parent_path();
		std::wstring fullPath = parentPath.wstring() + L"\\..\\Resources\\" + path;

		std::string cPath(fullPath.begin(), fullPath.end());
		if (!CFmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return S_OK;
	}
	void CAudioClip::Play()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		CFmod::SoundPlay(mSound, &mChannel);
	}
	void CAudioClip::Stop()
	{
		mChannel->stop();
	}
	void CAudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
	{
		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}
