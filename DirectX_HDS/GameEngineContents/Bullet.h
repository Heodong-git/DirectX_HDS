#pragma once
#include "BaseActor.h"

enum class BulletType
{
	NORMAL,
	ROT,
};

// 설명 :
class Bullet : public BaseActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	inline void SetMoveDir(const float4& _Dir)
	{
		m_MoveDir = _Dir;
	}

	inline bool IsParring() const
	{
		return m_Parring;
	}

	void SetType(BulletType _Type)
	{
		m_Type = _Type;
	}

	void SetAngle(const float _Angle)
	{
		m_Angle = _Angle;
	}

	// death 함수를 만들고
	void BulletDeath();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineSoundPlayer m_SoundPlayer;

	BulletType m_Type = BulletType::NORMAL;
	
	void CreateReflectEffect();
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	std::shared_ptr<class GameEngineCollision> m_Collision = nullptr;

	void DirCorrection();
	float4 m_MoveDir = {};
	float m_MoveSpeed = 1000.0f;
	float m_LiveTime = 4.0f;
	
	bool m_Parring = false;
	bool m_DirChange = false;
	float m_Angle = 0.0f;

};


// 컨텐츠에 부모클래스를 만든다.
// 