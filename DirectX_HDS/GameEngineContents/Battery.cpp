#include "PrecompileHeader.h"
#include "Battery.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BaseLevel.h"
#include "MySpriteRenderer.h"


Battery* Battery::MainBattery = nullptr;

Battery::Battery()
{
	MainBattery = this;
}

Battery::~Battery()
{
}

void Battery::Start()
{
	if (nullptr == GameEngineSprite::Find("battery_state"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("battery");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("battery_state").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	
	//{
	//	if (nullptr == GameEngineTexture::Find("Battery_00.png"))
	//	{
	//		GameEngineDirectory NewDir;
	//		// 원하는 폴더를 가진 디렉터리로 이동
	//		NewDir.MoveParentToDirectory("katanazero_resources");
	//		// 그 폴더로 이동
	//		NewDir.Move("katanazero_resources");
	//		NewDir.Move("Texture");
	//		NewDir.Move("ClubLevel");
	//		NewDir.Move("Battery");

	//		// 파일 전체로드 
	//		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
	//		for (size_t i = 0; i < File.size(); i++)
	//		{
	//			GameEngineTexture::Load(File[i].GetFullPath());
	//		}
	//	}
	//}

	m_MainRender = CreateComponent<GameEngineUIRenderer>();
	m_MainRender->CreateAnimation({ .AnimationName = "battery_state", .SpriteName = "battery_state", .Start = 0, .End = 9 ,
									  .FrameInter = 1.0f , .Loop = true , .ScaleToTexture = true });
	m_MainRender->ChangeAnimation("battery_state");
	m_MainRender->SetScaleRatio(2.0f);
	m_MainRender->SetAnimPauseOff();
	m_MainRender->GetTransform()->SetLocalPosition({ -550 , 330 });	
}

void Battery::Update(float _DeltaTime)
{
	if (BaseLevel::LevelState::WAIT == GetReturnCastLevel()->GetCurState())
	{
		return;
	}

	GameEngineLevel* Level = GetLevel();

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

void Battery::Render(float _DeltaTime)
{
}
