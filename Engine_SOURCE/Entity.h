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
		UINT32 GetID() { return mID; }

	private:
		std::wstring mName;
		const UINT32 mID;

	};

}

