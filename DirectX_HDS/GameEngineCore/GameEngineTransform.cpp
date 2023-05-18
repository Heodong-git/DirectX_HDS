#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

std::function<bool(GameEngineTransform*, GameEngineTransform*)> GameEngineTransform::ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

// 콜리전함수 초기화용 클래스
class InitColFunction
{
public:
	InitColFunction()
	{
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::SPHERE3D)] = &GameEngineTransform::SphereToSpehre;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::AABBBOX3D)] = &GameEngineTransform::SphereToAABB;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::OBBBOX3D)] = &GameEngineTransform::SphereToOBB;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::SPHERE3D)] = &GameEngineTransform::AABBToSpehre;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::AABBBOX3D)] = &GameEngineTransform::AABBToAABB;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::OBBBOX3D)] = &GameEngineTransform::AABBToOBB;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::SPHERE3D)] = &GameEngineTransform::OBBToSpehre;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::AABBBOX3D)] = &GameEngineTransform::OBBToAABB;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::OBBBOX3D)] = &GameEngineTransform::OBBToOBB;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::SPHERE2D)] = &GameEngineTransform::Sphere2DToSpehre2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::AABBBOX2D)] = &GameEngineTransform::Sphere2DToAABB2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::OBBBOX2D)] = &GameEngineTransform::Sphere2DToOBB2D;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = &GameEngineTransform::AABB2DToSpehre2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = &GameEngineTransform::AABB2DToAABB2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = &GameEngineTransform::AABB2DToOBB2D;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = &GameEngineTransform::OBB2DToSpehre2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = &GameEngineTransform::OBB2DToAABB2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = &GameEngineTransform::OBB2DToOBB2D;

	}
};

// 이렇게 전역으로 구현해두게 되면 프로그램 실행시 데이터영역에 메모리를 생성하기 때문에
// 해당 클래스의 생성자가 호출되고, 생성자에서 함수들의 초기화를 진행해준다. 
InitColFunction InitFunction;

bool GameEngineTransform::SphereToSpehre(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.SPHERE.Intersects(_Right->ColData.SPHERE);
}

bool GameEngineTransform::SphereToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.SPHERE.Intersects(_Right->ColData.AABB);
}

bool GameEngineTransform::SphereToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.SPHERE.Intersects(_Right->ColData.OBB);
}

bool GameEngineTransform::AABBToSpehre(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.AABB.Intersects(_Right->ColData.SPHERE);
}

bool GameEngineTransform::AABBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.AABB.Intersects(_Right->ColData.AABB);
}

bool GameEngineTransform::AABBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.AABB.Intersects(_Right->ColData.OBB);
}

bool GameEngineTransform::OBBToSpehre(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.OBB.Intersects(_Right->ColData.SPHERE);
}

bool GameEngineTransform::OBBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.OBB.Intersects(_Right->ColData.AABB);
}

bool GameEngineTransform::OBBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	return _Left->ColData.OBB.Intersects(_Right->ColData.OBB);
}



bool GameEngineTransform::Sphere2DToSpehre2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.SPHERE.Intersects(RightData.SPHERE);
}

bool GameEngineTransform::Sphere2DToAABB2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.SPHERE.Intersects(RightData.AABB);
}

bool GameEngineTransform::Sphere2DToOBB2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.SPHERE.Intersects(RightData.OBB);
}

bool GameEngineTransform::AABB2DToSpehre2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.AABB.Intersects(RightData.SPHERE);
}

bool GameEngineTransform::AABB2DToAABB2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.AABB.Intersects(RightData.AABB);
}

bool GameEngineTransform::AABB2DToOBB2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.AABB.Intersects(RightData.OBB);
}

bool GameEngineTransform::OBB2DToSpehre2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.OBB.Intersects(RightData.SPHERE);
}

bool GameEngineTransform::OBB2DToAABB2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.OBB.Intersects(RightData.AABB);
}

bool GameEngineTransform::OBB2DToOBB2D(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	CollisionData LeftData = _Left->ColData;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right->ColData;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.OBB.Intersects(RightData.OBB);
}



GameEngineTransform::GameEngineTransform()
{
	TransformUpdate();
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.ScaleMatrix.Scale(TransData.Scale);

	TransData.Rotation.w = 0.0f;
	TransData.Quaternion = TransData.Rotation.EulerDegToQuaternion();
	TransData.RotationMatrix = TransData.Quaternion.QuaternionToRotationMatrix();
	TransData.PositionMatrix.Pos(TransData.Position);

	TransData.LocalWorldMatrix = TransData.ScaleMatrix * TransData.RotationMatrix * TransData.PositionMatrix;


	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}
	else // 차이
	{
		WorldCalculation();
	}

	WorldDecompose();
	LocalDecompose();
	// ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);

}

void GameEngineTransform::WorldCalculation()
{
	float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
	float4 PScale, PRotation, PPosition;
	ParentWorldMatrix.Decompose(PScale, PRotation, PPosition);


	if (true == AbsoluteScale)
	{
		PScale = float4::One;
	}
	if (true == AbsoluteRotation)
	{
		// 부모의 회전 
		PRotation = float4::Zero;
		PRotation.EulerDegToQuaternion();
	}
	if (true == AbsolutePosition)
	{
		PPosition = float4::Zero;
	}

	float4x4 MatScale, MatRot, MatPos;

	//scale
	MatScale.Scale(PScale);

	//rot
	MatRot = PRotation.QuaternionToRotationMatrix();

	//pos
	MatPos.Pos(PPosition);

	TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
}

void GameEngineTransform::LocalDecompose()
{
	// 로컬변환행렬을 분해하여 스케일, 쿼터니언, 포지션 값으로 분리한다. 
	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	// 추출된 로컬 쿼터니언 값을 이용해서 로컬 회전값을 계산한다. 
	// 쿼터니언을 오일러 각도로 변환한 결과를 저장한다. 
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

}
void GameEngineTransform::WorldDecompose()
{
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

	ColData.OBB.Center = TransData.WorldPosition.DirectFloat3;
	ColData.OBB.Extents = (TransData.WorldScale * 0.5f).DirectFloat3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.DirectFloat4;
	ColData.ScaleABS();
}

// 트랜스폼의 부모세팅 구조 
void GameEngineTransform::SetParent(GameEngineTransform* _Parent, bool _IsParentWorld /*= true*/)
{
	if (IsDebug())
	{
		int a = 0;
	}

	// 인자로 들어온 트랜스폼이 nullptr 이고, Master 가 nullptr 이고
	if (nullptr == _Parent && nullptr == Master)
	{
		// 마스터를 액터로 다이나믹캐스트에 실패했다면 assert 
		if (nullptr == dynamic_cast<GameEngineActor*>(Master))
		{
			MsgAssert("액터만이 루트 리스트에 추가될수 있습니다.");
			return;
		}
	}

	// this 의 부모가 nullptr 이고, 인자의 트랜스폼이 nullptr 이라면 return 
	if (nullptr == Parent && nullptr == _Parent)
	{
		return;
	}

	// 내가 원래 기존의 부모(트랜스폼)이 있다면 
	if (nullptr != Parent)
	{
		// 부모의 child list 에서, this를 제거
		Parent->Child.remove(this);

		// 부모 트랜스폼의 마스터(액터)를 받아온다. 
		GameEngineObject* ParentMaster = Parent->Master;

		// 부모의 마스터가 nullptr 이라면 마스터인 액터가 존재하지 않는다는 의미. 말이 안되기 때문에 assert 
		if (nullptr == ParentMaster)
		{
			MsgAssert("존재할수 없는 상황입니다 Master가 nullptr입니다");
			return;
		}

		// 마스터(기존액터)의 shared ptr 
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		// 부모의마스터의 (액터) 의 자식리스트에서 마스터를 제거
		ParentMaster->Childs.remove(MasterPtr);
		Parent = nullptr;

	}

	Parent = _Parent;

	// 현재 부모가 있는 상태라면 
	if (nullptr != Parent)
	{
		if (true == _IsParentWorld)
		{
			// 역행렬을 받아온다. 
			TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.WorldMatrix.InverseReturn();	
		}

		// 변환행렬을 분해하여 위치,회전,크기값을 저장한다. 
		LocalDecompose();

		TransData.Position = TransData.LocalPosition;
		TransData.Rotation = TransData.LocalRotation;
		TransData.Scale = TransData.LocalScale;

		TransformUpdate();

		// 변환된 상태를 초기화한다고 볼 수 있음
		AbsoluteReset();

		// 마스터의 레벨을 받아온다. 
		GameEngineLevel* Level = Master->GetLevel();

		// 마스터의 shared ptr 을 받아온다. 
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		// 마스터가 nullptr 이 아니라면
		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			// 액터를 저장한 맵의 키값.remove( 함수의 인자로 
			// 다이나믹포인터 캐스트 : shared ptr 용, dynamic cast. 
			Level->Actors[MasterPtr->GetOrder()].remove(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}

		Parent->Child.push_back(this);
		Parent->Master->Childs.push_back(Master->shared_from_this());
	}
	else
	{
		WorldDecompose();

		TransData.Position = TransData.WorldPosition;
		TransData.Rotation = TransData.WorldRotation;
		TransData.Scale = TransData.WorldScale;
		TransformUpdate();
		AbsoluteReset();

		// 레벨에 집어넣어야 한다.

		GameEngineLevel* Level = Master->GetLevel();

		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			Level->Actors[MasterPtr->GetOrder()].push_back(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}
		else
		{
			MsgAssert("액터만이 레벨의 루트 오브젝트로 지정될 수 있습니다.");
		}

	}
}




void GameEngineTransform::CalChild()
{
	for (GameEngineTransform* ChildTrans : Child)
	{
		ChildTrans->WorldCalculation();
		ChildTrans->WorldDecompose();
		ChildTrans->CalChild();
	}
}



float4 GameEngineTransform::GetLocalPosition()
{
	return TransData.LocalPosition;
}

float4 GameEngineTransform::GetLocalScale()
{
	return TransData.LocalScale;
}

float4 GameEngineTransform::GetLocalRotation()
{
	return TransData.LocalRotation;
}

float4 GameEngineTransform::GetLocalQuaternion()
{
	return TransData.LocalQuaternion;
}

float4 GameEngineTransform::GetWorldPosition()
{
	return TransData.WorldPosition;
}

float4 GameEngineTransform::GetWorldScale()
{
	return TransData.WorldScale;
}

float4 GameEngineTransform::GetWorldRotation()
{
	return TransData.WorldRotation;
}

float4 GameEngineTransform::GetWorldQuaternion()
{
	return TransData.WorldQuaternion;
}

void GameEngineTransform::AbsoluteReset()
{
	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}

void GameEngineTransform::SetMaster(GameEngineObject* _Master)
{
	Master = _Master;
}

void GameEngineTransform::AllAccTime(float _DeltaTime)
{
	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->AccLiveTime(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllAccTime(_DeltaTime);
	}
}

void GameEngineTransform::AllUpdate(float _DeltaTime)
{

	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->Update(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllUpdate(_DeltaTime);
	}
}


void GameEngineTransform::AllRender(float _DeltaTime)
{
	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->Render(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllRender(_DeltaTime);
	}
}

void GameEngineTransform::AllRelease()
{
	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->Release();

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllRelease();
	}
}

void GameEngineTransform::ChildRelease()
{
	std::list<GameEngineTransform*>::iterator ReleaseStartIter = Child.begin();
	std::list<GameEngineTransform*>::iterator ReleaseEndIter = Child.end();

	for (; ReleaseStartIter != ReleaseEndIter; )
	{
		GameEngineTransform* Trans = *ReleaseStartIter;

		if (nullptr == Trans->Master)
		{
			MsgAssert("몬가 잘못됨 도라에몽을 부르자.");
		}

		if (false == Trans->Master->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		ReleaseStartIter = Child.erase(ReleaseStartIter);
	}
}


bool GameEngineTransform::Collision(const CollisionParameter& Data)
{
	if (nullptr == Data._OtherTrans)
	{
		MsgAssert("nullptr인 트랜스 폼과는 충돌을 할수가 없습니다.");
	}

	return ArrColFunction[static_cast<int>(Data.ThisType)][static_cast<int>(Data.OtherType)](this, Data._OtherTrans);
}