#pragma once
#include "BaseActor.h"
#include <GameEnginePlatform/GameEngineSound.h>


enum class TurretType
{
	NORMAL,
	WALL,
};

enum class TurretState
{
	TRANSFORM,
	NORMAL,
	DEATH,
	RECORDING_PROGRESS,
};

// 설명 :
class Turret : public BaseActor
{
public:
	// constrcuter destructer
	Turret();
	~Turret();

	// delete Function
	Turret(const Turret& _Other) = delete;
	Turret(Turret&& _Other) noexcept = delete;
	Turret& operator=(const Turret& _Other) = delete;
	Turret& operator=(Turret&& _Other) noexcept = delete;

	void SetType(TurretType _Type);
	

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineSoundPlayer m_SoundPlayer;

	void DebugUpdate();
	void LoadAndCreateAnimation();

	void Fire(float4 _Dir, const float _Angle);

	float m_FireTime = 1.5f;

	bool m_ChangeAnim = false;

	TurretType m_Type = TurretType::NORMAL;
	TurretState m_CurState = TurretState::TRANSFORM;

	float4 m_Angle = float4::Zero;

	std::shared_ptr<class GameEngineSpriteRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_TopRender = nullptr;		// 포탑
	std::shared_ptr<class GameEngineSpriteRenderer> m_BodyRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_HolderRender = nullptr;	// 홀더 
	std::shared_ptr<class GameEngineSpriteRenderer> m_DebugRender = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;
};
