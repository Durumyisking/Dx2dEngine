#include "PaintShader.h"

namespace dru::graphics
{
	CPaintShader::CPaintShader()
		: mTarget(nullptr)
	{
	}

	CPaintShader::~CPaintShader()
	{
	}

	void CPaintShader::Bind()
	{
		mTarget->BindUnorderedAccessview(0);
		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupX = mTarget->GetHeight() / mThreadGroupCountX + 1;
		mGroupX = 1;
	}

	void CPaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessview(0);
	}


}