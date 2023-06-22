#pragma once
#include "BaseActor.h"


// 설명 : 스테이지 클리어 후 충돌시 다음 이벤트 호출용
class ColEventObj : public BaseActor
{
public:
	// constrcuter destructer
	ColEventObj();
	~ColEventObj();

	// delete Function
	ColEventObj(const ColEventObj& _Other) = delete;
	ColEventObj(ColEventObj&& _Other) noexcept = delete;
	ColEventObj& operator=(const ColEventObj& _Other) = delete;
	ColEventObj& operator=(ColEventObj&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
	
private:
	void DebugUpdate();
	void CollisionUpdate(float _DeltaTime);
	void ComponentSetting();

	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
};
