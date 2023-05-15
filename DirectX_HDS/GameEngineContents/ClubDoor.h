#pragma once
#include "BaseActor.h"

// Ό³Έν :
class ClubDoor : public BaseActor
{
public:
	// constrcuter destructer
	ClubDoor();
	~ClubDoor();

	// delete Function
	ClubDoor(const ClubDoor& _Other) = delete;
	ClubDoor(ClubDoor&& _Other) noexcept = delete;
	ClubDoor& operator=(const ClubDoor& _Other) = delete;
	ClubDoor& operator=(ClubDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};
