#pragma once
#include "GameObj.h"

namespace dru
{
	enum class ePlatformType
	{
		Floor,
		Wall,
		Ceiling,
		Stair,
		OutWall,
		OutWallSide,
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
		void SetColliderCenter(Vector2 _Pos);

	private:
		ePlatformType mType;
	};

}

