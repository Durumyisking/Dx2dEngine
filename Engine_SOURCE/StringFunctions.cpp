#include "StringFunctions.h"
#include "SimpleMath.h"

namespace dru
{
	void SetRandIndex(std::wstring& _String, UINT _Range)
	{
		std::wstring idx =  std::to_wstring(math::GetRandomNumber(1, _Range));
		_String += idx;
	}
	

}