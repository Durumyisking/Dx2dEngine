#pragma once
#include "GameObj.h"

namespace dru
{
	enum class ePlatformType
	{
		Floor,
		Wall,
		Stair,
		End,
	};

	class CPlatforms :
		public CGameObj
	{
	public:
		CPlatforms(ePlatformType _Type);
		virtual ~CPlatforms();

		virtual void Initialize() = 0;
		virtual void update() = 0;
		virtual void fixedUpdate() = 0;
		virtual void render() = 0;

		void SetColliderScale(Vector2 _Scale);

	private:
		ePlatformType mType;
	};

}

