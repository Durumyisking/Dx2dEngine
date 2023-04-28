#include "GameObj.h"
#include "TimeMgr.h"

namespace dru
{
	
	CGameObj::CGameObj()
		:mState(eState::Active)
		, mType(eLayerType::None)
		, mObjectType(eObjectType::None)
		, mScripts{}
		, mbDestroy(false)
		, mbIsLeft(false)
		, mbBlockRendering(false)
		, mbOnFloor(false)
	{
		mComponents.resize(static_cast<UINT>(eComponentType::End));
		this->AddComponent<CTransform>(eComponentType::Transform);

	}

	CGameObj::~CGameObj()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;

			delete script;
			script = nullptr;
		}

	}

	void CGameObj::Initialize()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->Initialize();		
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
		}
	}

	void CGameObj::update()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;			
			comp->update();
		}
		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->update();
		}
	}

	void CGameObj::fixedUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedUpdate();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->fixedUpdate();
		}
	}

	void CGameObj::render()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->render();
		}
		
		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->render();
		}
	}

	void CGameObj::AddComponent(CComponent* _Component)
	{
		eComponentType order = _Component->GetOrder();


		if (order != eComponentType::Script)
		{
			mComponents[(UINT)order] = _Component;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(dynamic_cast<CScript*>(_Component));
			_Component->SetOwner(this);
		}
	}

	void CGameObj::SetPos(Vector3 _Value)
	{
		if (nullptr != GetComponent<CTransform>())
		{
			if (eProjectionType::Orthographic == renderer::mainCamera->GetProjectionType())
			{
				switch (mType)
				{
				case dru::enums::eLayerType::Camera:
					break;
				case dru::enums::eLayerType::Grid:
					break;
				case dru::enums::eLayerType::BackGround:
					_Value.z = 5.f;
					break;
				case dru::enums::eLayerType::Monster:
					_Value.z = 3.1f;
					break;
				case dru::enums::eLayerType::MonsterGun:
					//_Value.z = 3.09f;
					break;
				case dru::enums::eLayerType::Player:
					_Value.z = 3.f;
					break;
				case dru::enums::eLayerType::Bullet:
					_Value.z = 2.81f;
					break;
				case dru::enums::eLayerType::AfterImage:
					_Value.z = 3.01f;
					break;
				case dru::enums::eLayerType::Platforms:
					_Value.z = 4.9f;
					break;
				case dru::enums::eLayerType::Ray:
					_Value.z = 4.f;
					break;
				case dru::enums::eLayerType::Particle:
					_Value.z = 2.8f;
					break;
				case dru::enums::eLayerType::FX:
					_Value.z = 3.01f;
					break;
				case dru::enums::eLayerType::UI:
					_Value.z = 0.1f;
					break;
				case dru::enums::eLayerType::End:
					break;
				default:
					break;
				}
			}
			GetComponent<CTransform>()->SetPosition(_Value);
		}
	}

	void CGameObj::SetScale(Vector3 _Value)
	{
		if (nullptr != GetComponent<CTransform>())
		{
			GetComponent<CTransform>()->SetScale(_Value);
		}
		if (nullptr != GetComponent<CSpriteRenderer>())
		{
			GetComponent<CSpriteRenderer>()->ChangeSize();
		}
		if (nullptr != GetComponent<CMeshRenderer>())
		{
			GetComponent<CMeshRenderer>()->ChangeSize();
		}
	}

	void CGameObj::SetRotation(Vector3 _Value)
	{
		if (nullptr != GetComponent<CTransform>())
		{
			GetComponent<CTransform>()->SetRotation(_Value);
		}
	}

	Vector3 CGameObj::GetPos()
	{
		return GetComponent<CTransform>()->GetPosition();
	}

	Vector3 CGameObj::GetScale()
	{
		return GetComponent<CTransform>()->GetScale();
	}

	Vector3 CGameObj::GetRotation()
	{
		return GetComponent<CTransform>()->GetRotation();
	}

	void CGameObj::SetMaterial(std::shared_ptr<CMaterial> _Material)
	{
		if (nullptr != GetComponent<CSpriteRenderer>())
		{
			GetComponent<CSpriteRenderer>()->SetMaterial(_Material);
		}
	}

	void CGameObj::SetMesh(std::shared_ptr<CMesh> _Mesh)
	{
		if (nullptr != GetComponent<CSpriteRenderer>())
		{
			GetComponent<CSpriteRenderer>()->SetMesh(_Mesh);
		}
	}

	void CGameObj::Flip()
	{
		CBaseRenderer* baseRenderer = GetComponent<CBaseRenderer>();
		if (baseRenderer)
		{
			std::shared_ptr<CMaterial> mtrl = baseRenderer->GetMaterial();
			if (mtrl)
			{

#define INVERSE -1
#define NORMAL 1


				int isInverse = mbIsLeft ? INVERSE : NORMAL;

				mtrl->SetData(eGPUParam::Int_1, &isInverse);
			}
		}

	}
	bool CGameObj::MoveToTarget_Smooth_bool(CGameObj* _target, float _speed, bool _zOn, eDir _dir)
	{

		if (!_target)
			return false;

		Vector3 TargetPos;
		Vector3 ObjPos;
		Vector3 result;

		if (_zOn)
		{
			TargetPos = _target->GetPos();
			ObjPos = GetPos();
			result = TargetPos;
		}
		else
		{
			TargetPos = Vector3(_target->GetPos().x, _target->GetPos().y, 0.f);
			ObjPos = Vector3(GetPos().x, GetPos().y, 0.f);
			result = Vector3(TargetPos.x, TargetPos.y, GetPos().z);
		}


		float Distance = 0.f;
		float Speed = 0.f;

		Distance = (TargetPos - ObjPos).Length();

		Vector3 Dir = (TargetPos - ObjPos);
		Dir.Normalize();

		switch (_dir)
		{
		case dru::enums::eDir::UP:
		case dru::enums::eDir::DOWN:
			Dir.x = 0;
			break;
		case dru::enums::eDir::LEFT:
		case dru::enums::eDir::RIGHT:
			Dir.y = 0;
			break;
		default:
			break;
		}

		Speed = Distance / _speed;

		if (Distance < 0.01f)
		{
			Speed = 1.f;
		}

		float Step = Speed * CTimeMgr::DeltaTimeConstant();

		if (Step < Distance)
		{

			ObjPos += Dir * Step;
			this->SetPos(ObjPos);

			return false;
		}

		this->SetPos(result);
		return true;

	}

	Vector3 CGameObj::MoveToTarget_Smooth_vector3(CGameObj* _target, float _speed, bool _zOn, eDir _dir)
	{
		if (!_target)
			return Vector3::Zero;

		Vector3 TargetPos = Vector3(_target->GetPos().x, _target->GetPos().y, 0.f);
		Vector3 ObjPos = Vector3(GetPos().x, GetPos().y, 0.f);
		Vector3 result = Vector3(TargetPos.x, TargetPos.y, GetPos().z);

		float Distance = 0.f;
		float Speed = 0.f;

		Distance = (TargetPos - ObjPos).Length();

		Vector3 Dir = (TargetPos - ObjPos);
		Dir.Normalize();

		switch (_dir)
		{
		case dru::enums::eDir::UP:
		case dru::enums::eDir::DOWN:
			Dir.x = 0;
			Distance = fabs(TargetPos.y - ObjPos.y);
			result.x = GetPos().x;
			break;
		case dru::enums::eDir::LEFT:
		case dru::enums::eDir::RIGHT:
			Distance = fabs(ObjPos.x - TargetPos.x);
			Dir.y = 0;
			result.y = GetPos().y;
			break;
		default:
			break;
		}

		Speed = Distance / _speed;

		if (Distance < 0.001f)
		{
			Speed = 1.f;
		}

		float Step = Speed * CTimeMgr::DeltaTimeConstant();

		if (Step < Distance)
		{

			ObjPos += Dir * Step;
			this->SetPos(ObjPos);

			return ObjPos;
		}
		
		this->SetPos(result);
		return result;
	}
}