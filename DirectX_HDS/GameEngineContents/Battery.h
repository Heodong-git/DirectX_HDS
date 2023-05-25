#pragma once
#include "BaseActor.h"

// 설명 :
class Battery : public BaseActor
{
public:
	static Battery* MainBattery;

public:
	// constrcuter destructer
	Battery();
	~Battery();

	// delete Function
	Battery(const Battery& _Other) = delete;
	Battery(Battery&& _Other) noexcept = delete;
	Battery& operator=(const Battery& _Other) = delete;
	Battery& operator=(Battery&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	// 플레이어의 특정 값을 가져와서 해당하는 이미지로 변경할거야
	

private:
	void TextureChange();
	void Blink();

	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_ShiftRender = nullptr;
	static std::vector<std::shared_ptr<class GameEngineTexture>> m_UseTextures;

	int m_BatteryCount = 9;
};
