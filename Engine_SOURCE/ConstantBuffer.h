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
		void Bind(void* _Data);
		void SetPipeline(eShaderStage _Stage);


	private:
		const eCBType mType;
		int iData;
	};


}

