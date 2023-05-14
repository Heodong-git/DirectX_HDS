#include "PrecompileHeader.h"
#include "Platform.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Platform* Platform::MainPlatform = nullptr;

Platform::Platform()
{
	MainPlatform = this;
}

Platform::~Platform()
{
}

void Platform::Start()
{
	GameEngineDirectory NewDir;
	// 원하는 폴더를 가진 디렉터리로 이동
	NewDir.MoveParentToDirectory("katanazero_resources");
	// 그 폴더로 이동
	NewDir.Move("katanazero_resources");
	NewDir.Move("Texture");
	NewDir.Move("ClubLevel");
	NewDir.Move("Debug");

	// 파일 전체로드 
	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}
	
	if (false == GameEngineInput::IsKey("Platform_DebugSwitch"))
	{
		DebugSwitch();
	}

	m_Render = CreateComponent<GameEngineSpriteRenderer>();
	m_Render->SetPipeLine("2DBlinkTexture");
	m_Render->SetAtlasConstantBuffer();
	m_Render->GetShaderResHelper().SetTexture("BlinkTex", "debugbox_green.png");

}

void Platform::Update(float _DeltaTime)
{
	// 테스트 
	/*if(m_Render->GetTransform()->Collision({ Player::MainPlayer->GetRender()->GetTransform() , ColType::OBBBOX3D, ColType::OBBBOX3D }))
	{
		Player::MainPlayer->GetRender()->GetTransform()->AddLocalPosition({ 0 , 1 });
	}*/

	DebugUpdate();
}

void Platform::Render(float _DeltaTime)
{
	int a = 0;
}

void Platform::DebugUpdate()
{
	if (true == IsDebug())
	{
		int a = 0;
	}

	else if (false == IsDebug())
	{
		
	}
}
