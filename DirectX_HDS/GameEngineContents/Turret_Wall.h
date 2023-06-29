#pragma once

#include "BaseActor.h"

// Ό³Έν :
class Turret_Wall : public BaseActor
{
public:
	// constrcuter destructer
	Turret_Wall();
	~Turret_Wall();

	// delete Function
	Turret_Wall(const Turret_Wall& _Other) = delete;
	Turret_Wall(Turret_Wall&& _Other) noexcept = delete;
	Turret_Wall& operator=(const Turret_Wall& _Other) = delete;
	Turret_Wall& operator=(Turret_Wall&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer>& GetRender()
	{
		return m_MainRender;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void DebugUpdate();
	void LoadAndCreateAnimation();

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;

};
