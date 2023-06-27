#include "AsyncLoad.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "AudioClip.h"

namespace dru
{
	void LoadTexture()
	{

		// title
		CResources::Load<CTexture>(L"default", L"default.png");
		CResources::Load<CTexture>(L"Black", L"TitleScene/bgBlack.png");
		CResources::Load<CTexture>(L"Steel", L"TitleScene/bgSteel.png");
		CResources::Load<CTexture>(L"TitleKatana", L"TitleScene/bgTitleKatana.png");
		CResources::Load<CTexture>(L"TitleZer_1", L"TitleScene/bgTitleZer_1.png");
		CResources::Load<CTexture>(L"TitleO_1", L"TitleScene/bgTitleO_1.png");
		CResources::Load<CTexture>(L"Fence", L"TitleScene/bgFence.png");
		CResources::Load<CTexture>(L"Grass", L"TitleScene/bgGrass.png");
		CResources::Load<CTexture>(L"Grass2", L"TitleScene/bgGrass2.png");
		CResources::Load<CTexture>(L"TitleButton", L"TitleScene/TitleButtons.png");

		// main
		CResources::Load<CTexture>(L"texCursor", L"MainScene/Cursor.png");
		CResources::Load<CTexture>(L"stagetutorial", L"MainScene/Background/Tutorialbg.png");
		CResources::Load<CTexture>(L"stage1", L"MainScene/Background/Stage1bg.png");
		CResources::Load<CTexture>(L"stage2", L"MainScene/Background/Stage2bg.png");
		CResources::Load<CTexture>(L"stage3", L"MainScene/Background/Stage3bg.png");
		CResources::Load<CTexture>(L"bossStage1", L"MainScene/Background/Boss1bg.png");
		CResources::Load<CTexture>(L"bossStage2", L"MainScene/Background/Boss2_2bg.png");
		CResources::Load<CTexture>(L"mask", L"MainScene/Background/transition_mask.png");


		// Objs
		CResources::Load<CTexture>(L"tutorialtxt", L"MainScene/Font/tutorial.png");
		CResources::Load<CTexture>(L"particle_spark", L"MainScene/spark_particle.png");
		CResources::Load<CTexture>(L"bullet", L"MainScene/bullet.png");
		CResources::Load<CTexture>(L"halogen", L"MainScene/Background/Object/halogen.png");
		CResources::Load<CTexture>(L"desk", L"MainScene/Background/Object/desk.png");
		CResources::Load<CTexture>(L"plant", L"MainScene/Background/Object/plant.png");
		CResources::Load<CTexture>(L"door", L"MainScene/Background/Object/door.png");


		// player
		CResources::Load<CTexture>(L"player", L"MainScene/Player.png");
		// monster
		CResources::Load<CTexture>(L"grunt", L"MainScene/Monster/Grunt.png");
		CResources::Load<CTexture>(L"pomp", L"MainScene/Monster/Pomp.png");
		CResources::Load<CTexture>(L"cop", L"MainScene/Monster/Cop.png");
		CResources::Load<CTexture>(L"cop_gun", L"MainScene/Monster/Cop_Gun.png");

		CResources::Load<CTexture>(L"kissyface", L"MainScene/Monster/Kissyface.png");
		CResources::Load<CTexture>(L"kissyface_axe", L"MainScene/Monster/kissyface_axe.png");

		CResources::Load<CTexture>(L"headhunter", L"MainScene/Monster/HeadHunter.png");

		CResources::Load<CTexture>(L"laserTurret", L"MainScene/Monster/laserTurret.png");
		CResources::Load<CTexture>(L"laserShoot", L"MainScene/Monster/laserShoot.png");

		CResources::Load<CTexture>(L"beam", L"MainScene/beam.png");

		CResources::Load<CTexture>(L"hud_top", L"MainScene/Hud/hud_top.png");
		CResources::Load<CTexture>(L"hud_timer", L"MainScene/Hud/hud_timer.png");
		CResources::Load<CTexture>(L"hud_timerbar", L"MainScene/Hud/hud_timerbar.png");
		CResources::Load<CTexture>(L"hud_battery", L"MainScene/Hud/hud_battery.png");
		CResources::Load<CTexture>(L"hud_batterypart", L"MainScene/Hud/hud_batterypart.png");
		CResources::Load<CTexture>(L"hud_inventory", L"MainScene/Hud/hud_inventory.png");
		CResources::Load<CTexture>(L"hud_keys", L"MainScene/Hud/hud_keys.png");
		CResources::Load<CTexture>(L"icon_hand", L"MainScene/Hud/Itemicons/Hand.png");
		CResources::Load<CTexture>(L"icon_katana", L"MainScene/Hud/Itemicons/Katana.png");
		CResources::Load<CTexture>(L"icon_Butcher", L"MainScene/Hud/Itemicons/Butcher.png");


		CResources::Load<CTexture>(L"tutorialtxt", L"MainScene/Font/tutorial.png");
		CResources::Load<CTexture>(L"wall", L"MainScene/wall.png");

		CResources::Load<CTexture>(L"blood", L"MainScene/Blood/Blood.png");
		CResources::Load<CTexture>(L"smallBlood1", L"MainScene/Blood/Decal/smallBlood1.png");
		CResources::Load<CTexture>(L"smallBlood2", L"MainScene/Blood/Decal/smallBlood2.png");
		CResources::Load<CTexture>(L"smallBlood3", L"MainScene/Blood/Decal/smallBlood3.png");
		CResources::Load<CTexture>(L"smallBlood4", L"MainScene/Blood/Decal/smallBlood4.png");
		CResources::Load<CTexture>(L"bloodDecal1", L"MainScene/Blood/Decal/bigBlood1.png");
		CResources::Load<CTexture>(L"bloodDecal2", L"MainScene/Blood/Decal/bigBlood2.png");
		CResources::Load<CTexture>(L"bloodDecal3", L"MainScene/Blood/Decal/bigBlood3.png");
		CResources::Load<CTexture>(L"bloodDecal4", L"MainScene/Blood/Decal/bigBlood4.png");
		CResources::Load<CTexture>(L"bloodDecal5", L"MainScene/Blood/Decal/bigBlood5.png");
		CResources::Load<CTexture>(L"bloodDecal6", L"MainScene/Blood/Decal/bigBlood6.png");

		// FX
		CResources::Load<CTexture>(L"fx_dust", L"MainScene/FX/fx_dust.png");
		CResources::Load<CTexture>(L"fx_slashPlayer", L"MainScene/FX/fx_slash.png");
		CResources::Load<CTexture>(L"fx_slash", L"MainScene/FX/slash.png");
		CResources::Load<CTexture>(L"fx_landdust", L"MainScene/FX/fx_landdust.png");
		CResources::Load<CTexture>(L"fx_bulletReflect", L"MainScene/FX/fx_bulletReflect.png");
		CResources::Load<CTexture>(L"fx_gunSmoke", L"MainScene/FX/fx_gunSmoke.png");
		CResources::Load<CTexture>(L"fx_gunFire", L"MainScene/FX/fx_gunFire.png");
		CResources::Load<CTexture>(L"fx_gunFire_2", L"MainScene/FX/fx_gunSpark2.png");
		CResources::Load<CTexture>(L"fx_explosion", L"MainScene/FX/fx_explosion.png");


		// mission
		CResources::Load<CTexture>(L"job_corner", L"MissionScene/job_corner.png");
		CResources::Load<CTexture>(L"job_front", L"MissionScene/job_front.png");
		CResources::Load<CTexture>(L"job_frontshoadow", L"MissionScene/job_frontshoadow.png");
		CResources::Load<CTexture>(L"job_left", L"MissionScene/job_left.png");
		CResources::Load<CTexture>(L"job_right", L"MissionScene/job_right.png");
		CResources::Load<CTexture>(L"job_profile", L"MissionScene/job_profile.png");

		// ending
		CResources::Load<CTexture>(L"endingBg", L"EndingScene/endingBg.png");
		CResources::Load<CTexture>(L"endingSmoke", L"EndingScene/smoke.png");

		CResources::Load<CTexture>(L"burn", L"noise/burn.png");
		CResources::Load<CTexture>(L"glitch", L"noise/glitch.png");
	}

	void LoadMaterial()
	{

		std::shared_ptr<CTexture> Meshtexture = CResources::Find<CTexture>(L"default");
		std::shared_ptr<CShader> MeshShader = CResources::Find<CShader>(L"MeshShader");
		std::shared_ptr<CMaterial> MeshMaterial = std::make_shared<CMaterial>();
		MeshMaterial->SetRenderingMode(eRenderingMode::Transparent);
		MeshMaterial->SetShader(MeshShader);
		MeshMaterial->SetTexture(Meshtexture);
		CResources::Insert<CMaterial>(L"MeshMaterial", MeshMaterial);

		std::shared_ptr<CTexture> Spritetexture = CResources::Find<CTexture>(L"default");
		std::shared_ptr<CShader> SpriteShader = CResources::Find<CShader>(L"SpriteShader");
		std::shared_ptr<CMaterial> SpriteMaterial = std::make_shared<CMaterial>();
		SpriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		SpriteMaterial->SetShader(SpriteShader);
		SpriteMaterial->SetTexture(Spritetexture);
		CResources::Insert<CMaterial>(L"SpriteMaterial", SpriteMaterial);

		std::shared_ptr<CTexture> UItexture = CResources::Find<CTexture>(L"Title");
		std::shared_ptr<CShader> UIShader = CResources::Find<CShader>(L"UIShader");
		std::shared_ptr<CMaterial> UIMaterial = std::make_shared<CMaterial>();
		UIMaterial->SetRenderingMode(eRenderingMode::Transparent);
		UIMaterial->SetShader(UIShader);
		UIMaterial->SetTexture(UItexture);
		CResources::Insert<CMaterial>(L"UIMaterial", UIMaterial);

		std::shared_ptr<CShader> GridShader = CResources::Find<CShader>(L"GridShader");
		std::shared_ptr<CMaterial> GridMaterial = std::make_shared<CMaterial>();
		GridMaterial->SetRenderingMode(eRenderingMode::Opaque);
		GridMaterial->SetShader(GridShader);
		CResources::Insert<CMaterial>(L"GridMaterial", GridMaterial);

		std::shared_ptr<CTexture> Fadetexture = CResources::Find<CTexture>(L"default");
		std::shared_ptr<CShader> FadeShader = CResources::Find<CShader>(L"FadeShader");
		std::shared_ptr<CMaterial> FadeMaterial = std::make_shared<CMaterial>();
		FadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		FadeMaterial->SetShader(FadeShader);
		FadeMaterial->SetTexture(Fadetexture);
		CResources::Insert<CMaterial>(L"FadeMaterial", FadeMaterial);

		std::shared_ptr<CTexture> Colortexture = CResources::Find<CTexture>(L"Black");
		std::shared_ptr<CShader> ColorShader = CResources::Find<CShader>(L"ColorShader");
		std::shared_ptr<CMaterial> ColorMaterial = std::make_shared<CMaterial>();
		ColorMaterial->SetRenderingMode(eRenderingMode::Transparent);
		ColorMaterial->SetShader(ColorShader);
		ColorMaterial->SetTexture(Colortexture);
		CResources::Insert<CMaterial>(L"ColorMaterial", ColorMaterial);

		std::shared_ptr <CTexture> Painttexture = CResources::Find<CTexture>(L"PaintTexture");
		std::shared_ptr<CShader> PaintShader = CResources::Find<CShader>(L"MeshShader");
		std::shared_ptr<CMaterial> PaintMaterial = std::make_shared<CMaterial>();
		PaintMaterial->SetShader(PaintShader);
		PaintMaterial->SetTexture(Painttexture);
		CResources::Insert<CMaterial>(L"PaintMaterial", PaintMaterial);

		std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"ParticleShader");
		std::shared_ptr<CMaterial> particleMaterial = std::make_shared<CMaterial>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		CResources::Insert<CMaterial>(L"ParticleMaterial", particleMaterial);

		// etc
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"Black", L"ColorShader");
			CResources::Insert<CMaterial>(L"UITitleBgMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"texCursor", L"UIShader");
			CResources::Insert<CMaterial>(L"CursorMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"hud_keys", L"SpriteShader");
			CResources::Insert<CMaterial>(L"keys", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_dust", L"SpriteShader");
			CResources::Insert<CMaterial>(L"dustMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_landdust", L"SpriteShader");
			CResources::Insert<CMaterial>(L"landdustMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_slashPlayer", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerSlashMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_slashPlayer", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BodySlashMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_gunFire", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GunFireMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_gunFire_2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GunFire2Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_gunSmoke", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GunSmokeMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_bulletReflect", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BulletReflectMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"fx_explosion", L"SpriteShader");
			CResources::Insert<CMaterial>(L"ExplosionMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"wall", L"SpriteShader");
			CResources::Insert<CMaterial>(L"wallMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bullet", L"SpriteShader");
			CResources::Insert<CMaterial>(L"Bullet", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"blood", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BloodMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerBulletTimeMat", Material);
			Vector4 color = Vector4(0.f, 2.f, 2.f, 0.5f);
			Material->SetData(eGPUParam::Vector4_1, &color);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PlayerLaserMat", Material);
			Vector4 color = Vector4(3.f, 3.f, 0.f, 1.f);
			Material->SetData(eGPUParam::Vector4_1, &color);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"halogen", L"SpriteShader");
			CResources::Insert<CMaterial>(L"halogenMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"desk", L"SpriteShader");
			CResources::Insert<CMaterial>(L"deskMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"plant", L"SpriteShader");
			CResources::Insert<CMaterial>(L"plantMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"grunt", L"SpriteShader");
			CResources::Insert<CMaterial>(L"GruntMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"pomp", L"SpriteShader");
			CResources::Insert<CMaterial>(L"PompMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop", L"SpriteShader");
			CResources::Insert<CMaterial>(L"CopMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"cop", L"SpriteShader");
			CResources::Insert<CMaterial>(L"CopMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"laserTurret", L"SpriteShader");
			CResources::Insert<CMaterial>(L"laserTurretMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"laserShoot", L"SpriteShader");
			CResources::Insert<CMaterial>(L"laserBeamMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"beam", L"SpriteShader");
			CResources::Insert<CMaterial>(L"BeamMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal1Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal2Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal3", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal3Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal4", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal4Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal5", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal5Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"bloodDecal6", L"SpriteShader");
			CResources::Insert<CMaterial>(L"bloodDecal6Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood1", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood1Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood2", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood2Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood3", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood3Mat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood4", L"SpriteShader");
			CResources::Insert<CMaterial>(L"smallBlood4Mat", Material);
		}
		//{
		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood5", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"smallBlood5Mat", Material);
		//}
		//{
		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood6", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"smallBlood6Mat", Material);
		//}
		//{
		//	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"smallBlood7", L"SpriteShader");
		//	CResources::Insert<CMaterial>(L"smallBlood7Mat", Material);
		//}
		{
			std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"AimParticleShader");
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"particle_spark", L"SpriteShader");
			Material->SetShader(particleShader);
			CResources::Insert<CMaterial>(L"LaserTurretParticleMat", Material);
		}
		{
			std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"LaserParticleShader");
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"particle_spark", L"SpriteShader");
			Material->SetShader(particleShader);
			CResources::Insert<CMaterial>(L"PlayerParticleMat", Material);
		}
		{
			std::shared_ptr<CShader> particleShader = CResources::Find<CShader>(L"LaserParticleShader");
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"particle_spark", L"SpriteShader");
			Material->SetShader(particleShader);
			CResources::Insert<CMaterial>(L"BatteryParticleMat", Material);
		}
	
	}

	void CAsyncLoad::LoadAfterImageMaterial1(bool* _flag)
	{
		for (int i = 0; i <= 250000; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"player", L"AfterImageShader");
			std::wstring matName = L"PlayerMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
		for (int i = 0; i <= 25000; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface", L"AfterImageShader");
			std::wstring matName = L"kissyfaceMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
		for (int i = 0; i <= 25000; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"AfterImageShader");
			std::wstring matName = L"AxeMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
		*_flag = true;
	}

	void CAsyncLoad::LoadAfterImageMaterial2(bool* _flag)
	{
		for (int i = 0; i <= 25000; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"kissyface_axe", L"AfterImageShader");
			std::wstring matName = L"AxeMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}
		for (int i = 0; i <= 25000; ++i)
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"headhunter", L"AfterImageShader");
			std::wstring matName = L"HeadhunterMatAfterImage_";
			std::wstring idx = std::to_wstring(i);
			matName += idx;
			CResources::Insert<CMaterial>(matName, Material);
		}

		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"endingBg", L"SpriteShader");
			CResources::Insert<CMaterial>(L"endingBgMat", Material);
		}
		{
			std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>(L"endingSmoke", L"SpriteShader");
			CResources::Insert<CMaterial>(L"endingSmokeMat", Material);
		}
		*_flag = true;
	}


	void LoadAudio()
	{
		// song
		CResources::Load<CAudioClip>(L"song_title_bgm", L"Sound/Song/song_title.ogg");
		CResources::Load<CAudioClip>(L"song_main_bgm", L"Sound/Song/song_main.ogg");
		CResources::Load<CAudioClip>(L"song_tutorial_bgm", L"Sound/Song/song_tutorial.ogg");
		CResources::Load<CAudioClip>(L"song_china_bgm", L"Sound/Song/song_chinatown.ogg");
		CResources::Load<CAudioClip>(L"song_boss_bgm", L"Sound/Song/song_boss.ogg");
		////////////////////////////////////////////////////////////////////////////

		// sound effect

		// title scene
		CResources::Load<CAudioClip>(L"SE_title_neon", L"Sound/title_neon.wav");
		CResources::Load<CAudioClip>(L"SE_title_rain", L"Sound/title_rain.wav");
		CResources::Load<CAudioClip>(L"SE_title_select", L"Sound/title_select.wav");
		CResources::Load<CAudioClip>(L"SE_title_splash", L"Sound/title_splash.wav");
		CResources::Load<CAudioClip>(L"SE_title_updown", L"Sound/title_updown.wav");


		// play scene
		CResources::Load<CAudioClip>(L"SE_rewind", L"Sound/rewind.wav");
		CResources::Load<CAudioClip>(L"SE_replay", L"Sound/replay_play.wav");
		CResources::Load<CAudioClip>(L"SE_mp3rewind", L"Sound/mp3rewind.wav");
		CResources::Load<CAudioClip>(L"SE_correct", L"Sound/correct.wav");

		// player
		CResources::Load<CAudioClip>(L"player_die", L"Sound/Player/player_die.wav");
		CResources::Load<CAudioClip>(L"player_footstep", L"Sound/Player/player_footstep.wav");
		CResources::Load<CAudioClip>(L"player_jump", L"Sound/Player/player_jump.wav");
		CResources::Load<CAudioClip>(L"player_land", L"Sound/Player/player_land.wav");
		CResources::Load<CAudioClip>(L"player_prerun", L"Sound/Player/player_prerun.wav");
		CResources::Load<CAudioClip>(L"player_roll", L"Sound/Player/player_roll.wav");
		CResources::Load<CAudioClip>(L"player_roll_real", L"Sound/Player/player_roll_real.wav");
		CResources::Load<CAudioClip>(L"player_run1", L"Sound/Player/player_run1.wav");
		CResources::Load<CAudioClip>(L"player_run2", L"Sound/Player/player_run2.wav");
		CResources::Load<CAudioClip>(L"player_run3", L"Sound/Player/player_run3.wav");
		CResources::Load<CAudioClip>(L"player_run4", L"Sound/Player/player_run4.wav");
		CResources::Load<CAudioClip>(L"player_slash1", L"Sound/Player/player_slash1.wav");
		CResources::Load<CAudioClip>(L"player_slash2", L"Sound/Player/player_slash2.wav");
		CResources::Load<CAudioClip>(L"player_slash3", L"Sound/Player/player_slash3.wav");
		CResources::Load<CAudioClip>(L"player_wallkick1", L"Sound/Player/player_wallkick1.wav");
		CResources::Load<CAudioClip>(L"player_wallkick2", L"Sound/Player/player_wallkick2.wav");
		CResources::Load<CAudioClip>(L"player_wallkick3", L"Sound/Player/player_wallkick3.wav");
		CResources::Load<CAudioClip>(L"player_wallslide", L"Sound/Player/player_wallslide.wav");


		// monster
		CResources::Load<CAudioClip>(L"monser_walk1", L"Sound/Monster/monser_walk1.wav");
		CResources::Load<CAudioClip>(L"monser_walk2", L"Sound/Monster/monser_walk2.wav");
		CResources::Load<CAudioClip>(L"monser_walk3", L"Sound/Monster/monser_walk3.wav");
		CResources::Load<CAudioClip>(L"monser_walk4", L"Sound/Monster/monser_walk4.wav");
		CResources::Load<CAudioClip>(L"monster_death_bullet", L"Sound/Monster/monster_death_bullet.wav");
		CResources::Load<CAudioClip>(L"monster_death1", L"Sound/Monster/monster_death1.wav");
		CResources::Load<CAudioClip>(L"monster_death2", L"Sound/Monster/monster_death2.wav");
		CResources::Load<CAudioClip>(L"monster_death3", L"Sound/Monster/monster_death3.wav");
		CResources::Load<CAudioClip>(L"monster_reload", L"Sound/Monster/monster_reload.wav");
		CResources::Load<CAudioClip>(L"monster_run1", L"Sound/Monster/monster_run1.wav");
		CResources::Load<CAudioClip>(L"monster_run2", L"Sound/Monster/monster_run2.wav");
		CResources::Load<CAudioClip>(L"monster_run3", L"Sound/Monster/monster_run3.wav");
		CResources::Load<CAudioClip>(L"monster_run4", L"Sound/Monster/monster_run4.wav");
		CResources::Load<CAudioClip>(L"monster_shot", L"Sound/Monster/monster_shot.wav");
		CResources::Load<CAudioClip>(L"monstser_slide", L"Sound/Monster/monstser_slide.wav");

		// kissyface
		CResources::Load<CAudioClip>(L"kissyface_axecatch", L"Sound/Kissyface/kissyface_axecatch.wav");
		CResources::Load<CAudioClip>(L"kissyface_axeimpact", L"Sound/Kissyface/kissyface_axeimpact.wav");
		CResources::Load<CAudioClip>(L"kissyface_axelunge", L"Sound/Kissyface/kissyface_axelunge.wav");
		CResources::Load<CAudioClip>(L"kissyface_axeprepare", L"Sound/Kissyface/kissyface_axeprepare.wav");
		CResources::Load<CAudioClip>(L"kissyface_axereturn", L"Sound/Kissyface/kissyface_axereturn.wav");
		CResources::Load<CAudioClip>(L"kissyface_axethrow", L"Sound/Kissyface/kissyface_axethrow.wav");
		CResources::Load<CAudioClip>(L"kissyface_axeturn", L"Sound/Kissyface/kissyface_axeturn.wav");
		CResources::Load<CAudioClip>(L"kissyface_clash", L"Sound/Kissyface/kissyface_clash.wav");
		CResources::Load<CAudioClip>(L"kissyface_crouch", L"Sound/Kissyface/kissyface_crouch.wav");
		CResources::Load<CAudioClip>(L"kissyface_death", L"Sound/Kissyface/kissyface_death.wav");
		CResources::Load<CAudioClip>(L"kissyface_jump", L"Sound/Kissyface/kissyface_jump.wav");
		CResources::Load<CAudioClip>(L"kissyface_sharpen", L"Sound/Kissyface/kissyface_sharpen.wav");
		CResources::Load<CAudioClip>(L"kissyface_struggle", L"Sound/Kissyface/kissyface_struggle.wav");

		CResources::Load<CAudioClip>(L"kissyface_voice_axethrow", L"Sound/Kissyface/kissyface_voice_axethrow.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_chop", L"Sound/Kissyface/kissyface_voice_chop.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_crouch", L"Sound/Kissyface/kissyface_voice_crouch.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_hurt", L"Sound/Kissyface/kissyface_voice_hurt.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_jump", L"Sound/Kissyface/kissyface_voice_jump.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_lunge", L"Sound/Kissyface/kissyface_voice_lunge.wav");
		CResources::Load<CAudioClip>(L"kissyface_voice_prepare", L"Sound/Kissyface/kissyface_voice_prepare.wav");

		// headhunter
		CResources::Load<CAudioClip>(L"appear1", L"Sound/Headhunter/appear1.wav");
		CResources::Load<CAudioClip>(L"appear2", L"Sound/Headhunter/appear2.wav");
		CResources::Load<CAudioClip>(L"appear3", L"Sound/Headhunter/appear3.wav");
		CResources::Load<CAudioClip>(L"deadground", L"Sound/Headhunter/deadground.wav");
		CResources::Load<CAudioClip>(L"gatling", L"Sound/Headhunter/gatling.wav");
		CResources::Load<CAudioClip>(L"hurt1", L"Sound/Headhunter/hurt1.wav");
		CResources::Load<CAudioClip>(L"hurt2", L"Sound/Headhunter/hurt2.wav");
		CResources::Load<CAudioClip>(L"jump", L"Sound/Headhunter/jump.wav");
		CResources::Load<CAudioClip>(L"lasershot", L"Sound/Headhunter/lasershot.wav");
		CResources::Load<CAudioClip>(L"lasershot_swipe", L"Sound/Headhunter/lasershot_swipe.wav");
		CResources::Load<CAudioClip>(L"lasershot_vertical", L"Sound/Headhunter/lasershot_vertical.wav");
		CResources::Load<CAudioClip>(L"lockon", L"Sound/Headhunter/lockon.wav");
		CResources::Load<CAudioClip>(L"vanish", L"Sound/Headhunter/vanish.wav");
		CResources::Load<CAudioClip>(L"walljump1", L"Sound/Headhunter/walljump1.wav");
		CResources::Load<CAudioClip>(L"walljump2", L"Sound/Headhunter/walljump2.wav");
		CResources::Load<CAudioClip>(L"walljump3", L"Sound/Headhunter/walljump3.wav");

		// blood
		CResources::Load<CAudioClip>(L"blood_splat1", L"Sound/Blood/blood_splat1.wav");
		CResources::Load<CAudioClip>(L"blood_splat2", L"Sound/Blood/blood_splat2.wav");
		CResources::Load<CAudioClip>(L"blood_splat3", L"Sound/Blood/blood_splat3.wav");
		CResources::Load<CAudioClip>(L"blood_splat4", L"Sound/Blood/blood_splat4.wav");
		CResources::Load<CAudioClip>(L"blood_squirt1", L"Sound/Blood/blood_squirt1.wav");
		CResources::Load<CAudioClip>(L"blood_squirt2", L"Sound/Blood/blood_squirt2.wav");
		CResources::Load<CAudioClip>(L"blood_squirt3", L"Sound/Blood/blood_squirt3.wav");

		// bullet
		CResources::Load<CAudioClip>(L"bullethit1", L"Sound/Bullet/bullethit1.wav");
		CResources::Load<CAudioClip>(L"bullethit2", L"Sound/Bullet/bullethit2.wav");
		CResources::Load<CAudioClip>(L"bullethit3", L"Sound/Bullet/bullethit3.wav");
		CResources::Load<CAudioClip>(L"bullet_die", L"Sound/Bullet/bullet_die.wav");
		CResources::Load<CAudioClip>(L"bullet_slash", L"Sound/Bullet/bullet_slash.wav");

		// laser
		CResources::Load<CAudioClip>(L"laser_blast", L"Sound/Laser/laser_blast.wav");
		CResources::Load<CAudioClip>(L"laser_evaporate1", L"Sound/Laser/laser_evaporate1.wav");
		CResources::Load<CAudioClip>(L"laser_evaporate2", L"Sound/Laser/laser_evaporate2.wav");
		CResources::Load<CAudioClip>(L"laser_evaporate3", L"Sound/Laser/laser_evaporate3.wav");
		CResources::Load<CAudioClip>(L"laser_explosion", L"Sound/Laser/laser_explosion.wav");


		////////////////////////////////////////////////////////////////////////////

	}

	void CAsyncLoad::Initialize(bool* _flag)
	{
		LoadTexture();
		LoadMaterial();
		LoadAudio();

		*_flag = true;
	}

}