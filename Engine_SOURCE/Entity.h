#pragma once
#include "Engine.h"


namespace dru
{
	class CEntity
	{
	public:
		CEntity();
		CEntity(const CEntity& other);
		virtual ~CEntity();

		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() { return mName; }
		uintptr_t GetID() { return mID; }

	private:
		std::wstring mName;
		const uintptr_t mID;

	};

}

