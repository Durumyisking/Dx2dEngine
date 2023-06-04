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
		void Stop(const std::wstring& _key);
		void SetLoop(const std::wstring& _key, bool loop);

//		void AddClip(std::shared_ptr<CAudioClip> clip) { mAudioClip = clip; }
		void AddClipByKey(const std::wstring& _key);
		CAudioClip* GetClip(const std::wstring& _key);

	private:
		std::map<std::wstring, CAudioClip*> mAudioClips;
	};
}
