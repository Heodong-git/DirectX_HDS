#pragma once
#include "BaseActor.h"

// ���� :
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

	// �÷��̾��� Ư�� ���� �����ͼ� �ش��ϴ� �̹����� �����Ұž�
	

private:
	void TextureChange();
	void Blink();

	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_ShiftRender = nullptr;
	static std::vector<std::shared_ptr<class GameEngineTexture>> m_UseTextures;

	int m_BatteryCount = 9;
};
