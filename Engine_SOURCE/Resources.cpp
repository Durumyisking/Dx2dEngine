#include "Resources.h"

namespace dru
{
	std::map<std::wstring, CResource*> CResources::mResources;

	void CResources::Release()
	{
		std::map<std::wstring, CResource*>::iterator iter = mResources.begin();
		for (; iter != mResources.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}

}