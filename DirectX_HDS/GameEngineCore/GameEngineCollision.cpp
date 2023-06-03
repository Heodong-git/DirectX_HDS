#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineRenderUnit GameEngineCollision::DebugUnit;

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}


void GameEngineCollision::Start()
{
	SetDebugCamera(GetLevel()->GetCamera(0).get());
}

std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
	// ���� �浹ü�� ������Ʈ�� false ���, �浹�� �������� �ʴ´�. 
	if (false == this->IsUpdate())
	{
		return nullptr;
	}

	// ���� this �� Ÿ���� MAX ��� ( ���ڿ� ���� �־����� �ʾҴٸ� ) 
	// �ø����� ������ �ִ� �ڽ��� Ÿ������ �浹���� 
	if (_ThisColType == ColType::MAX)
	{
		_ThisColType = Type;
	}

	// ������ �����ϰ� �ִ� �浹ü ����Ʈ�� �޾ƿ´�.
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	// �ݺ�Ž��
	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		// ���� �浹ü�� ������Ʈ�� false ��� continue
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		// ����, ����� �ø���Ÿ���� MAX �� ��� ( ���� �������� �ʾҴٸ� ) 
		// �ø����� ������ �ִ� Ÿ������ �浹����
		if (_OtherColtype == ColType::MAX)
		{
			_OtherColtype = _OtherCol->Type;
		}

		// ������Ʈ ���̶�� Ʈ�������� �޾ƿͼ� �浹����, �浹�ߴٸ� �浹�� �ݸ��� ��ȯ 
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			return _OtherCol;
		}
	}

	// �浹���� �ʾҴٸ� nullptr ��ȯ
	return nullptr;
}

void GameEngineCollision::SetOrder(int _Order)
{
	std::shared_ptr<GameEngineCollision> ConThis = DynamicThis<GameEngineCollision>();

	// ������ ���� ����Ǿ� �ִ� �׷쿡�� ���� �����Ѵ�.
	// �������� ������, �������� �浹ü�� ����Ǿ� ���� ���, ã���� ���� Ž���ϰ� �Ǿ� �ӵ��� ������ �� �ִ�. 
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[GetOrder()];
	Group.remove(ConThis);

	// �������� �����ϰ�
	GameEngineObjectBase::SetOrder(_Order);

	// ���ο� �׷쿡 ���� �߰��Ѵ�.
	GetLevel()->PushCollision(ConThis);
}

void GameEngineCollision::Update(float _Delta)
{
	if (false == IsDebug())
	{
		return;
	}

	switch (Type)
	{
	case ColType::SPHERE2D:
		GameEngineDebug::DrawSphere(DebugCamera, GetTransform());
		break;
	case ColType::AABBBOX2D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::OBBBOX2D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::SPHERE3D:
		GameEngineDebug::DrawSphere(DebugCamera, GetTransform());
		break;
	case ColType::AABBBOX3D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::OBBBOX3D:
		GameEngineDebug::DrawBox(DebugCamera, GetTransform());
		break;
	case ColType::MAX:
		break;
	default:
		break;
	}
}

bool GameEngineCollision::CollisionAll(int _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType, ColType _OtherColtype)
{
	// ���� �浹ü�� ������Ʈ�� false ���, �浹�� �������� �ʴ´�. 
	if (false == this->IsUpdate())
	{
		return false;
	}

	// �����ʱ�ȭ
	_Col.clear();

	// �浹�� ������ ����Ʈ�� �޾ƿ´�.
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	if (0 == Group.size())
	{
		return false;
	}

	// ���ڿ� Ÿ���� ���������� �ʾҴٸ� �ø��� �ڽ��� Ÿ������ �浹����
	if (_ThisColType == ColType::MAX)
	{
		_ThisColType = Type;
	}

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}
		
		// �������� 
		if (_OtherColtype == ColType::MAX)
		{
			_OtherColtype = _OtherCol->Type;
		}

		// �浹�ߴٸ� ���Ϳ� �浹ü�� �߰��Ѵ�. 
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			_Col.push_back(_OtherCol);
		}
	}

	// �浹���θ� ��ȯ�Ѵ�. true ��� ���ڷ� �־��� ���Ϳ� �浹ü�� ����Ǿ� ���� ��, Ȱ���� �� �ִ�. 
	return _Col.size() != 0;

}