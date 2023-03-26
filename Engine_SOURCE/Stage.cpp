#include "Stage.h"


namespace dru
{

	CStage::CStage()
	{
	}

	CStage::~CStage()
	{
	}


	void CStage::LoadUI()
	{
		{
			CGameObj* mHudTop = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Top");

			CSpriteRenderer* SpriteRenderer = mHudTop->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_top", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_topMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudTop->SetPos(Vector3(0.f, 4.225f, 1.f));
			mHudTop->SetScale(Vector3(0.25f, 0.25f, 1.f));
		}

		{
			CGameObj* mHudTimer = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timer");

			CSpriteRenderer* SpriteRenderer = mHudTimer->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_timer", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_timerMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudTimer->SetPos(Vector3(0.f, 4.2f, 1.f));
			mHudTimer->SetScale(Vector3(0.275f, 0.275f, 1.f));
		}

		{
			mHudTimerBar = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

			CSpriteRenderer* SpriteRenderer = mHudTimerBar->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_timerbar", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_timerbarMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudTimerBar->SetPos(Vector3(0.23f, 4.25f, 1.f));
			mHudTimerBar->SetScale(Vector3(0.275f, 0.275f, 1.f));

		}

		{
			CGameObj* mHudBattery = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Battery");

			CSpriteRenderer* SpriteRenderer = mHudBattery->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_battery", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_batteryMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudBattery->SetPos(Vector3(-6.9f, 4.2f, 1.f));
			mHudBattery->SetScale(Vector3(0.265f, 0.265f, 1.f));
		}

		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_batterypart", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_batteryMat", Material);

			for (int i = 0; i < 11; ++i)
			{
				std::wstring str = L"Hud_BatteryPart";
				std::wstring num = std::to_wstring(i);
				str += num;

				CGameObj* mHudBatteryPart = object::Instantiate<CBackground>(eLayerType::UI, str);

				mHudBatteryParts.push_back(mHudBatteryPart);

				CSpriteRenderer* SpriteRenderer = mHudBatteryPart->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
				SpriteRenderer->SetMaterial(Material);

				mHudBatteryPart->SetPos(Vector3(-7.6f + (i * 0.14f), 4.22f, 1.f));
				mHudBatteryPart->SetScale(Vector3(0.05f, 0.05f, 1.f));
			}
		}

		{
			CGameObj* mHudInventory = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Inventory");

			CSpriteRenderer* SpriteRenderer = mHudInventory->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_inventory", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_invenMat", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudInventory->SetPos(Vector3(7.f, 4.2f, 1.f));
			mHudInventory->SetScale(Vector3(0.2f, 0.2f, 1.f));
		}

		{
			mHudLeftHand = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

			CSpriteRenderer* SpriteRenderer = mHudLeftHand->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"icon_katana", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_LeftItem", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudLeftHand->SetPos(Vector3(6.625f, 4.2f, 1.f));
			mHudLeftHand->SetScale(Vector3(0.5, 0.5, 1.f));

		}

		{
			mHudRightHand = object::Instantiate<CBackground>(eLayerType::UI, L"Hud_Timerbar");

			CSpriteRenderer* SpriteRenderer = mHudRightHand->AddComponent<CSpriteRenderer>(eComponentType::SpriteRenderer);
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"icon_hand", L"UIShader");
			CResources::Insert<CMaterial>(L"Hud_RightItem", Material);
			SpriteRenderer->SetMaterial(Material);

			mHudRightHand->SetPos(Vector3(7.375f, 4.22f, 1.f));
			mHudRightHand->SetScale(Vector3(0.5f, 0.5, 1.f));

		}
	}

}