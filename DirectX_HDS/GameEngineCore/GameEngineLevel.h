#pragma once
#include "GameEngineUpdateObject.h"
#include <GameEngineBase\GameEngineTimeEvent.h>
#include <string_view>
#include <map>

class GameEngineActor;
class GameEngineCamera;
class GameEngineCollision;
class GameEngineLevel : public GameEngineUpdateObject
{
	friend class GameEngineCollision;
	friend class GameEngineTransform;
	friend class GameEngineCore;
	friend class GameEngineActor;

public:
	GameEngineTimeEvent TimeEvent;

	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


	template<typename ActorType>
	std::shared_ptr<ActorType> CreateActor(const std::string_view& _Name)
	{
		return CreateActor<ActorType>(0, _Name);
	}

	template<typename ActorType >
	std::shared_ptr<ActorType> CreateActor(int _Order = 0, const std::string_view& _Name = "")
	{
		std::shared_ptr<GameEngineActor> NewActor = std::make_shared<ActorType>();

		std::string Name = _Name.data();
	
		// 2번인자로 아무것도 들어오지 않았다면
		if (_Name == "")
		{
			// 생성한 클래스의 이름으로.. 엥 여기서 추가 안한거같은데 
			const type_info& Info = typeid(ActorType);
			Name = Info.name();
			Name.replace(0, 6, "");
		}

		// 생성한 액터 초기화
		ActorInit(NewActor, _Order, this);

		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

	std::shared_ptr<class GameEngineCamera> GetMainCamera()
	{
		return MainCamera;
	}

	std::shared_ptr<GameEngineLevel> GetSharedThis()
	{
		// GameEngineLevel의 shared_ptr type를 반환하는데 
		// 너무길어서 조금더 간단하게 사용하기 위해 작성
		return DynamicThis<GameEngineLevel>();
	}

protected:
	virtual void LevelChangeStart();
	virtual void LevelChangeEnd();
	// 로딩
	virtual void Start() = 0;
	void Update(float _DeltaTime);
	void Render(float _DeltaTime);

private:
	// 메인카메라 , UI카메라 
	std::shared_ptr<GameEngineCamera> MainCamera;
	std::shared_ptr<GameEngineCamera> UICamera;

	std::map<int, std::list<std::shared_ptr<GameEngineActor>>> Actors;

	std::map<int, std::list<std::shared_ptr<GameEngineCollision>>> Collisions;

	void PushCollision(std::shared_ptr<GameEngineCollision> _Collision);

	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level);

	void ActorUpdate(float _DeltaTime);
	void ActorRender(float _DeltaTime);
	void ActorRelease();
};

