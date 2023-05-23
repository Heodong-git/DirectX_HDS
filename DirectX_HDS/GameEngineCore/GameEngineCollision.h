#pragma once
#include "GameEngineComponent.h"

// 설명 :
class GameEngineCollision : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	template<typename EnumType>
	std::shared_ptr<GameEngineCollision> Collision(EnumType _TargetGroup, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX)
	{
		return Collision(static_cast<int>(_TargetGroup), _ThisColType, _OtherColtype);
	}

	std::shared_ptr<GameEngineCollision> Collision(int _TargetGroup, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX);

	template<typename EnumType>
	bool CollisionAll(EnumType _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX)
	{
		return CollisionAll(static_cast<int>(_TargetGroup), _Col, _ThisColType, _OtherColtype);
	}

	bool CollisionAll(int _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX);

	void SetOrder(int _Order) override;

protected:
	void Start() override;

private:
	ColType Type = ColType::SPHERE3D;
};

// 1. 액터생성, 생성시 오더지정
// 2. 컬리전 생성 , 생성시 오더 , 컬리전타입 지정
// 3. 원하는 시점에서 충돌확인 후 원하는 함수 호출 