#pragma once
#include "GameEngineUpdateObject.h"

// 5월9일자 업데이트로 인해 
// 컴포넌트 리스트를 가지고 있지 않게 되었고
// 리스트를 모두 업데이트하는 구조에서
// 자식이 있다면 자식을 업데이트 해주는 구조로 변경
// 즉, 레벨은 루트 액터만 가지고 있는 형태 


// 설명 :
class GameEngineActor : public GameEngineUpdateObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// 컴포넌트 생성, 생성시 오더입력
	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<class GameEngineComponent> NewComponent = std::make_shared<ComponentType>();

		ComponentInit(NewComponent, _Order);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

	void SetOrder(int _Order) override;

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component, int _Order = 0);
};

