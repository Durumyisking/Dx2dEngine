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

		void SetStrcutedBuffer(CStructedBuffer* buffer);

	private:
		CStructedBuffer* mBuffer;
	};
}


