#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}


void GameEngineCollision::Start()
{
}

std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
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

bool GameEngineCollision::CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col)
{
	// �����ʱ�ȭ
	_Col.clear();

	// �浹�� ������ ����Ʈ�� �޾ƿ´�.
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		if (false == _OtherCol->IsUpdate())
		{
			continue;
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