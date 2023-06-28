#pragma once
#include "BaseActor.h"

enum class BloodType
{
	NONE,
	FIRST,
	SECOND,
	THIRD,
};

// Ό³Έν :
class BloodEffect : public BaseActor
{
public:
	// constrcuter destructer
	BloodEffect();
	~BloodEffect();

	// delete Function
	BloodEffect(const BloodEffect& _Other) = delete;
	BloodEffect(BloodEffect&& _Other) noexcept = delete;
	BloodEffect& operator=(const BloodEffect& _Other) = delete;
	BloodEffect& operator=(BloodEffect&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_Render;
	}

	void SetType(BloodType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
	BloodType m_Type = BloodType::NONE;
};
