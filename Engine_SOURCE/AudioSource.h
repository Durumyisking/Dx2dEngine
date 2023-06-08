#pragma once
#include "Component.h"
#include "AudioClip.h"

namespace dru
{
	class CAudioSource : public CComponent
	{
	public:
		CAudioSource();
		~CAudioSource();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		void Play(const std::wstring& _key, bool _loop = false);
		void Play_NoInterrupt(const std::wstring& _key, bool _loop = false);
		void Stop(const std::wstring& _key);
		void SetLoop(const std::wstring& _key, bool loop);

//		void AddClip(std::shared_ptr<CAudioClip> clip) { mAudioClip = clip; }
		void AddClipByKey(const std::wstring& _key);
		CAudioClip* GetClip(const std::wstring& _key);

		void SetWholeVolume(float _Volume);
		void SetWholePitch(float _Pitch);

		void SetWholeVolume_Ratio(float _Volume);
		void SetWholePitch_Ratio(float _Pitch);

		void SetVolume(const std::wstring& _key, float _Volume);
		void SetPitch(const std::wstring& _key, float _Pitch);

		float GetVolume(const std::wstring& _key);
		float GetPitch(const std::wstring& _key);

		

	private:
		std::map<std::wstring, CAudioClip*> mAudioClips;
		
	};
}
