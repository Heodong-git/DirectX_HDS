#include "PrecompileHeader.h"
#include "Battery.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BaseLevel.h"
#include "MySpriteRenderer.h"
#include "Player.h"


Battery* Battery::MainBattery = nullptr;

// ���ʿ���°Ű�����?������ 
std::vector<std::shared_ptr<class GameEngineTexture>> Battery::m_UseTextures = std::vector<std::shared_ptr<class GameEngineTexture>>();

Battery::Battery()
{
	MainBattery = this;
}

Battery::~Battery()
{
}

void Battery::Start()
{
	/*if (nullptr == GameEngineSprite::Find("battery_state"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("battery");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("battery_state").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}*/

	{
		if (nullptr == GameEngineTexture::Find("Battery_00.png"))
		{
			GameEngineDirectory NewDir;
			// ���ϴ� ������ ���� ���͸��� �̵�
			NewDir.MoveParentToDirectory("katanazero_resources");
			// �� ������ �̵�
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("Battery");
			NewDir.Move("Battery_State");

			// ���� ��ü�ε� 
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
			for (size_t i = 0; i < File.size(); i++)
			{
				std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(File[i].GetFullPath());
				m_UseTextures.push_back(Tex);
			}
		}
	}

	size_t Check = m_UseTextures.size();
	if (0 == Check)
	{
		// ���� ������ ����� 0�̶�� �̹����� ����� �߰����� ���� ���̴�.
		MsgAssert("���� ���͸��� �̹����� ����� �߰����� �ʾҽ��ϴ�.");
		return;
	}

	m_MainRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	m_MainRender->SetScaleToTexture("battery_09.png");
	m_MainRender->GetTransform()->SetLocalScale({ 160.0f , 40.0f });
	m_MainRender->GetTransform()->SetLocalPosition({ -560 , 337 });	

	m_ShiftRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	m_ShiftRender->SetTexture("keyboard_shift_0.png");
	m_ShiftRender->GetTransform()->SetLocalScale({ 60.0f , 25.0f });
	m_ShiftRender->GetTransform()->SetLocalPosition({ -440.0f , 335.0f });
}

void Battery::Update(float _DeltaTime)
{
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	// �ؽ��ĺ���
	TextureChange();

	// ��¦��¦
	Blink();
}

void Battery::Render(float _DeltaTime)
{
}

void Battery::TextureChange()
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("�÷��̾ nullptr �Դϴ�.");
		return;
	}

	float TimeCheck = Player::MainPlayer->GetSlowLimitTime();

	// Ű���� ����Ʈ �ؽ���
	// ���� �𿩳����ִٸ� ������ �ִ°�.. �ε� ���⼭�����ϰԾȵǳ� ?
	if (false == Player::MainPlayer->IsSlowSkill())
	{
		m_ShiftRender->SetTexture("keyboard_shift_0.png");
	}

	else if (true == Player::MainPlayer->IsSlowSkill())
	{
		m_ShiftRender->SetTexture("keyboard_shift_1.png");
	}

	
	// ���͸��ؽ���
	if (9.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_09.png");
		return;
	}

	else if (9.0f > TimeCheck && 8.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_08.png");
		return;
	}

	else if (8.0f > TimeCheck && 7.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_07.png");
		return;
	}

	else if (7.0f > TimeCheck && 6.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_06.png");
		return;
	}

	else if (6.0f > TimeCheck && 5.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_05.png");
		return;
	}

	else if (5.0f > TimeCheck && 4.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_04.png");
		return;
	}

	else if (4.0f > TimeCheck && 3.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_03.png");
		return;
	}

	else if (3.0f > TimeCheck && 2.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_02.png");
		return;
	}

	else if (2.0f > TimeCheck && 1.0f <= TimeCheck)
	{
		m_MainRender->SetTexture("Battery_01.png");
		return;
	}

	else if (1.0f > TimeCheck)
	{
		m_MainRender->SetTexture("Battery_00.png");
		return;
	}
	//// 9�� �̸��� ���
	//else if (8.0f >= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_08.png");
	//	return;
	//}

	//// 8�� �̸��� ��� 
	//else if (7.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_07.png");
	//	return;
	//}

	//else if (7.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_06.png");
	//	return;
	//}
	//else if (6.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_05.png");
	//	return;
	//}
	//else if (5.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_04.png");
	//	return;
	//}
	//else if (4.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_03.png");
	//	return;
	//}
	//else if (3.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_02.png");
	//	return;
	//}

	//else if (2.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_01.png");
	//	return;
	//}

	//else if (1.0f <= TimeCheck)
	//{
	//	m_MainRender->SetTexture("Battery_00.png");
	//	return;
	//}

}

void Battery::Blink()
{
	int Random = GameEngineRandom::MainRandom.RandomInt(1, 40);
	if (Random == 1)
	{
		m_MainRender->Off();
	}
	else
	{
		m_MainRender->On();
	}
}
