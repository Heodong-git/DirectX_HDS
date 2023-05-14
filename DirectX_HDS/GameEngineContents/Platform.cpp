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
	// ���ϴ� ������ ���� ���͸��� �̵�
	NewDir.MoveParentToDirectory("katanazero_resources");
	// �� ������ �̵�
	NewDir.Move("katanazero_resources");
	NewDir.Move("Texture");
	NewDir.Move("ClubLevel");
	NewDir.Move("Debug");

	// ���� ��ü�ε� 
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
	// �׽�Ʈ 
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
