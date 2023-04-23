#pragma once
#include "BaseRenderer.h"

namespace dru
{
	class CAfterImageRenderer :
		public CBaseRenderer
	{
	public:
		CAfterImageRenderer();
		virtual ~CAfterImageRenderer();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

	//private:
	//	CPlayerAfterImage* mAfterImageOwner;
	};

}