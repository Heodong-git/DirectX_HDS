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

	// 충돌을 진행할 타겟그룹, 충돌시킬타입을 넣어주고 충돌진행
	template<typename EnumType>
	std::shared_ptr<GameEngineCollision> Collision(EnumType _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
	{
		return Collision(static_cast<int>(_TargetGroup), _ThisColType, _OtherColtype);
	}

	// 충돌을 진행할 타겟그룹, 충돌시킬타입을 넣어주고 충돌진행
	std::shared_ptr<GameEngineCollision> Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype);


	template<typename EnumType>
	bool CollisionAll(EnumType _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col)
	{
		return CollisionAll(static_cast<int>(_TargetGroup), _ThisColType, _OtherColtype, _Col);
	}

	// 충돌된 모든 콜리전을 벡터에 담아서 반환, 반환된 벡터에 저장되어 있는 콜리전을 활용할 수 있다. 
	bool CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col);

	void SetOrder(int _Order) override;

protected:
	void Start() override;
private:

};

// 1. 액터생성, 생성시 오더지정
// 2. 컬리전 생성 , 생성시 오더지정
// 3. 원하는 시점에서 충돌확인 후 원하는 함수 호출 