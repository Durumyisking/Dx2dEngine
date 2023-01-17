#pragma once
#include "Engine.h"


namespace dru
{
	class CEntity
	{
	public:
		CEntity();
		virtual ~CEntity();

		void SetName(const std::wstring name) { mName = name; }
		std::wstring GetName() { return mName; }
		UINT32 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT32 mID;
	};

}

