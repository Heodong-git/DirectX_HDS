#pragma once
#include "BaseActor.h"


// Ό³Έν :
class NormalDoor : public BaseActor
{
public:
	// constrcuter destructer
	NormalDoor();
	~NormalDoor();

	// delete Function
	NormalDoor(const NormalDoor& _Other) = delete;
	NormalDoor(NormalDoor&& _Other) noexcept = delete;
	NormalDoor& operator=(const NormalDoor& _Other) = delete;
	NormalDoor& operator=(NormalDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;

};
