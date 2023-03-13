#include "Animator.h"

namespace dru
{
	CAnimator::CAnimator()
		: CComponent(eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mCurrentAnimation(nullptr)
		, mbLoop(false)
	{
	}

	CAnimator::~CAnimator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}
		for (auto evnt : mEvents)
		{
			delete evnt.second;
			evnt.second = nullptr;
		}

	}

	void CAnimator::Initialize()
	{
	}

	void CAnimator::update()
	{
		if (!mCurrentAnimation)
			return;

		if (mCurrentAnimation->IsCompleted())
		{
			Events* events = FindEvents(mCurrentAnimation->GetAnimationName());

			if (events)
				events->mCompleteEvent();

			if(mbLoop)
				mCurrentAnimation->Reset();
		}
		mCurrentAnimation->update();
	}

	void CAnimator::fixedUpdate()
	{
	}

	void CAnimator::render()
	{
	}

	bool CAnimator::Create(const std::wstring& _name, std::shared_ptr<CTexture> _atlas, Vector2 _leftTop, Vector2 _size, Vector2 _offset, UINT _spriteLength, float _duration, bool _Reverse)
	{
		if (!_atlas)
			return false;

		CAnimation* animation = FindAnimation(_name);
		if (animation)
			return false;

		animation = new CAnimation();
		animation->Create(_name, _atlas, _leftTop, _size, _offset, _spriteLength, _duration, _Reverse);

		mAnimations.insert(std::make_pair(_name, animation));

		return true;
	}

	CAnimation* CAnimator::FindAnimation(const std::wstring& _name)
	{
		std::map<std::wstring, CAnimation*>::iterator iter = mAnimations.find(_name);

		if (mAnimations.end() == iter)
		{
			return nullptr;
		}

		return iter->second;
	}

	CAnimator::Events* CAnimator::FindEvents(const std::wstring& _name)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(_name);

		if (mEvents.end() == iter)
		{
			return nullptr;
		}

		return iter->second;
	}

	void CAnimator::Play(std::wstring _name, bool _bLoop)
	{
		CAnimation* prevAnimation = mCurrentAnimation;

		Events* events = FindEvents(mCurrentAnimation->GetAnimationName());

		if (events)
			events->mEndEvent();

		mCurrentAnimation = FindAnimation(_name);
		mCurrentAnimation->Reset();
		mbLoop = _bLoop;

		events = FindEvents(mCurrentAnimation->GetAnimationName());

		if (events)
			events->mStartEvent();
	}

	void CAnimator::Binds()
	{
		if (!mCurrentAnimation)
			return;

		mCurrentAnimation->BindShader();
	}

	void CAnimator::Clear()
	{
		mCurrentAnimation->Clear();
	}

	std::function<void()>& CAnimator::GetStartEvent(const std::wstring& _name)
	{
		Events* events = FindEvents(_name);

		return events->mStartEvent.mEvent;
	}

	std::function<void()>& CAnimator::GetCompleteEvent(const std::wstring& _name)
	{
		Events* events = FindEvents(_name);

		return events->mCompleteEvent.mEvent;
	}

	std::function<void()>& CAnimator::GetEndEvent(const std::wstring& _name)
	{
		Events* events = FindEvents(_name);

		return events->mEndEvent.mEvent;
	}

}