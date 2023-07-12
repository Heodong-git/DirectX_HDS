#pragma once
#include "BaseActor.h"

// 보류 

// 설명 :
class Player_Trail : public BaseActor
{
public:
	// constrcuter destructer
	Player_Trail();
	~Player_Trail();

	// delete Function
	Player_Trail(const Player_Trail& _Other) = delete;
	Player_Trail(Player_Trail&& _Other) noexcept = delete;
	Player_Trail& operator=(const Player_Trail& _Other) = delete;
	Player_Trail& operator=(Player_Trail&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};
