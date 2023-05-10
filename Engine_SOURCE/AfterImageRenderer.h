#pragma once
#include "BaseRenderer.h"

namespace dru
{
	class CAfterImage;
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

		void SetAfterImageOwner(CAfterImage* _Owner) { mAfterImageOwner = _Owner; }

		float GetIndexAlpha(int _Idx, UINT _MaxCount);
		void ColorSetting();

		void SetMultableColor(Vector4 _Color) { mColor = _Color; }

	private:
		CAfterImage* mAfterImageOwner;
		Vector4 mColor;
	};

}