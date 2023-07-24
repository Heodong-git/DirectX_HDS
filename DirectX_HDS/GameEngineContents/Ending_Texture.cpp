#include "PrecompileHeader.h"
#include "Ending_Texture.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "Timer.h"
#include "Inven.h"
#include "Battery.h"
#include "Hud.h"

Ending_Texture::Ending_Texture()
{
}

Ending_Texture::~Ending_Texture()
{
}

void Ending_Texture::Start()
{
	GameEngineDirectory NewDir;
	// 원하는 폴더를 가진 디렉터리로 이동
	NewDir.MoveParentToDirectory("katanazero_resources");
	// 그 폴더로 이동
	NewDir.Move("katanazero_resources");
	NewDir.Move("texture");
	NewDir.Move("clublevel");
	NewDir.Move("endingtexture");

	GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("endtex").GetFullPath());

	m_MainRender = CreateComponent<GameEngineUIRenderer>();
	m_MainRender->GetTransform()->SetLocalPosition(float4{ 0.0f , 0.0f , -100.0f });
	m_MainRender->GetTransform()->SetLocalScale(float4{ 1280.0f, 720.0f });
	m_MainRender->SetTexture("end_tex.png");
	m_MainRender->ColorOptionValue.MulColor.a = 0.0f;
}

void Ending_Texture::Update(float _DeltaTime)
{
	// 여기서 유아이들 가져와서 알파값 - 

	if (1.0f > m_MainRender->ColorOptionValue.MulColor.a)
	{
		if (m_MainRender->ColorOptionValue.MulColor.a <= 0.1f && nullptr != Timer::MainTimer)
		{
			Timer::MainTimer->RenderOff();
			Hud::MainHud->RenderOff();
			Battery::MainBattery->RenderOff();
			Inven::MainInven->RenderOff();

			// 이때 사운드하나 재생
			
		}
		
		
		m_MainRender->ColorOptionValue.MulColor.a += _DeltaTime / 4.0f;
	}
}
