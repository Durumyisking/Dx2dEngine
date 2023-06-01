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

		void Play();
		void Stop();
		void SetLoop(bool loop);

		void SetClip(std::shared_ptr<CAudioClip> clip) { mAudioClip = clip; }
		void SetClipByKey(const std::wstring& _key);
		std::shared_ptr<CAudioClip> GetClip() { return mAudioClip; }

	private:
		std::shared_ptr<CAudioClip> mAudioClip;
	};
}
