#pragma once
#include "Component.h"
#include "Animation.h"

namespace dru
{
	class CAnimator : public CComponent
	{
	public:
		struct Event
		{



		};


	private:
		std::map<std::wstring, CAnimation*> mAnimations;
		std::map<std::wstring, Event*> mEvents;

	};
}


