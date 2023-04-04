#pragma once
#include "GameEngineUpdateObject.h"

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

	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateComponent()
	{
		std::shared_ptr<class GameEngienComponent> NewComponent = std::make_shared<ComponentType>();

		ComponentInit(NewComponent);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	// virtual 로 선언함으로써 자식클래스들은 이 함수들을 구현해도 되고, 안해도 된다.
	// 구현한다면 본인의 함수로, 구현하지 않는다면 부모클래스의 함수로 동작한다. 
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}

private:
	class GameEngineLevel* Level = nullptr;

	//// 이걸 컴포넌트 구조라고 합니다.
	std::list<std::shared_ptr<class GameEngineComponent>> ComponentList;
	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component);
};

