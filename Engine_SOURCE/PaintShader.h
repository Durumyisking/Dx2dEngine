#pragma once
#include "ComputeShader.h"
#include "Texture.h"

namespace dru::graphics
{
    class CPaintShader :
        public CComputeShader
    {
	public:
		CPaintShader();
		virtual ~CPaintShader();

		virtual void Bind();
		virtual void Clear();

		void SetTarget(std::shared_ptr<CTexture> _target) { mTarget = _target; }

	private:
		std::shared_ptr<CTexture> mTarget;
    };

}