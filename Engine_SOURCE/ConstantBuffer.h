#pragma once
#include "Graphics.h"

using namespace dru::enums;

namespace dru::graphics
{
	class CConstantBuffer : GpuBuffer
	{
		friend class CMaterial;

	public:
		CConstantBuffer();
		CConstantBuffer(eCBType _Type);
		virtual ~CConstantBuffer();	

		bool Create(UINT _Size);
		void SetData(void* _Data);
		void Bind(eShaderStage _Stage);
		void Clear();


	private:
		const eCBType mType;
	};

}