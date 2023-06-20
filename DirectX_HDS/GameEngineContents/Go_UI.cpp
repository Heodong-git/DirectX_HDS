#include "PrecompileHeader.h"
#include "Go_UI.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BaseLevel.h"

Go_UI::Go_UI()
{
}

Go_UI::~Go_UI()
{
}

void Go_UI::Start()
{
	if (nullptr == GameEngineTexture::Find("go_go.png"))
	{
		GameEngineDirectory NewDir;
		// 원하는 폴더를 가진 디렉터리로 이동
		NewDir.MoveParentToDirectory("katanazero_resources");
		// 그 폴더로 이동
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Go");

		// 파일 전체로드 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	ComponentSetting();
}

void Go_UI::Update(float _DeltaTime)
{
	Move(_DeltaTime);
}

void Go_UI::Render(float _DeltaTime)
{
}

void Go_UI::Move(float _DeltaTime)
{
	if (0.0f >= m_MoveTime)
	{
		m_MoveTime = 1.0f;
		GetTransform()->SetLocalPosition(m_StartPos);
		return;
	}

	float OriginDeltaTime = GameEngineTime::GlobalTime.GetDeltaTime();
	m_MoveTime -= OriginDeltaTime;
	GetTransform()->AddLocalPosition(float4::Right * m_MoveSpeed * OriginDeltaTime);
}

void Go_UI::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	m_SubRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	/*m_MainRender->SetScaleToTexture("go_go.png");
	m_SubRender->SetScaleToTexture("go_arrow.png");*/
	
	m_MainRender->SetTexture("go_go.png");
	m_MainRender->GetTransform()->SetLocalScale({ 78.0f , 40.0f });
	m_SubRender->SetTexture("go_arrow.png");
	m_SubRender->GetTransform()->SetLocalScale({ 62.0f , 38.0f });
	m_MainRender->GetTransform()->SetLocalPosition({ 0.0f, 40.0f , -1.0f });

	GetTransform()->SetLocalPosition(m_StartPos);
}
