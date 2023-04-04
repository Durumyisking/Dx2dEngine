#pragma once
#include "ComputeShader.h"
#include "StructedBuffer.h"

namespace dru::graphics
{
    class CParticleShader :
        public CComputeShader
    {

	public:
		CParticleShader();
		~CParticleShader();

		virtual void Bind() override;
		virtual void Clear() override;

		void SetStrcutedBuffer(CStructedBuffer* buffer) { mBuffer = buffer; }
		void SetSharedStrutedBuffer(CStructedBuffer* buffer) { mSharedBuffer = buffer; }

	private:
		CStructedBuffer* mBuffer;
		CStructedBuffer* mSharedBuffer;
	};
}


