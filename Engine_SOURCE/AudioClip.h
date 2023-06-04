#pragma once
#include "Resource.h"
#include "Fmod.h"

//#include <Fmod/fmod_studio.hpp>
//#include <Fmod/fmod.hpp>
//#include <Fmod/fmod_common.h>
//#include <Fmod/fmod_codec.h>

//#include "..\External\Include\\DirectXTex\DirectXTex.h"

namespace dru
{
	using namespace math;

	class CAudioClip : public CResource
	{
	public:
		CAudioClip();
		~CAudioClip();

		virtual HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Vector3 pos, const Vector3 vel);
		void SetLoop(bool loop) { mbLoop = loop; }

		bool IsPlaying() const 
		{
			bool playing = false;
			mChannel->isPlaying(&playing);
			return playing;
		}

		void SetVolume(float _Volume)
		{
			mVolume = _Volume;
			mChannel->setVolume(mVolume);
		}
		float GetVolume()  
		{
			mChannel->getVolume(&mVolume);
			return mVolume;
		}
		void SetPitch(float _Pitch)
		{
			mPitch = _Pitch;
			mChannel->setPitch(mPitch);
		}
		float GetPitch()
		{
			mChannel->getPitch(&mPitch);
			return mPitch;
		}

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		float mVolume;
		float mVolumeRatio;
		float mPitch;
		float mPitchRatio;
		bool mbLoop;
	};
}
