#pragma once
#include "BaseRenderer.h"

namespace dru
{
	class CPlayerAfterImage;
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

		void SetAfterImageOwner(CPlayerAfterImage* _Owner) { mAfterImageOwner = _Owner; }

	private:
		CPlayerAfterImage* mAfterImageOwner;
	};

}