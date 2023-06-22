#pragma once
#include "Component.h"
#include "Animation.h"

namespace dru
{
	class CAnimator : public CComponent
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> _func)
				{
					mEvent = std::move(_func);
				}
				void operator()()
				{
					if (mEvent)
						mEvent();
					
				}
				std::function<void()> mEvent;
			};

			Event mStartEvent;
			Event mCompleteEvent; // �ִϸ��̼� �� ����Ŭ ���� �� ����
			Event mEndEvent; // �ִϸ��̼� ��ü�� interrupt �ɸ��� ȣ��

			std::vector<Event> mFrameEvents; // �ش� ��������Ʈ(�ε���) ���� ����� �̺�Ʈ
		};

		CAnimator();
		virtual ~CAnimator();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		bool Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset,  UINT _spriteLength, Vector2 _Ratio, float _duration, bool _Reverse = false);
		
		CAnimation* FindAnimation(const std::wstring& _name);
		Events* FindEvents(const std::wstring& _name);
		CAnimation* GetCurrentAnimation() const { return mCurrentAnimation; }

		bool IsPlaying(const std::wstring& _name) { if (mCurrentAnimation->GetAnimationName() == _name) return true; return false; }

		void Play(std::wstring _name, bool _bLoop = true);
		void PauseOn() { mbPause = true; }
		void PauseOff() { mbPause = false; }
		bool IsPause() const { return mbPause; }

		void Binds();
		void BindSprite(renderer::AnimationCB _Sprite);
		void Reset();
		void Clear();

		std::function<void()>& GetStartEvent(const std::wstring& _name);
		std::function<void()>& GetCompleteEvent(const std::wstring& _name);
		std::function<void()>& GetEndEvent(const std::wstring& _name);
		std::function<void()>& GetFrameEvent(const std::wstring& _name, UINT _idx);

	private:
		std::map<std::wstring, CAnimation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		CAnimation* mCurrentAnimation;

		bool mbLoop;
		bool mbPause;
	};
}


