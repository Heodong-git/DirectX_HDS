#include "PrecompileHeader.h"
#include "SlashLaser_Effect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

SlashLaser_Effect::SlashLaser_Effect()
{
}

SlashLaser_Effect::~SlashLaser_Effect()
{
}

void SlashLaser_Effect::Start()
{
	if (nullptr == GameEngineTexture::Find("slash_laser.png"))
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("Effect");
		NewDir.Move("slash_laser");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	ComponentSetting();
}

void SlashLaser_Effect::Update(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
}

void SlashLaser_Effect::Render(float _DeltaTime)
{
}

void SlashLaser_Effect::MoveUpdate(float _DeltaTime)
{
	if (2.0f <= GetLiveTime())
	{
		this->Death();
	}

	float4 Dir = m_MovePos - GetTransform()->GetLocalPosition();
	float Angle = atan2f(Dir.y, Dir.x) * GameEngineMath::RadToDeg;
	m_MainRender->GetTransform()->SetLocalRotation({ 0 , 0 , Angle });
	float4 MoveDir = float4::AngleToDirection2DToDeg(m_MainRender->GetTransform()->GetLocalRotation().z);
	m_MainRender->GetTransform()->AddLocalPosition(MoveDir * m_MoveSpeed * _DeltaTime);
}

void SlashLaser_Effect::ComponentSetting()
{
	m_MainRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAYER_EFFECT);
	m_MainRender->SetTexture("slash_laser.png");
	m_MainRender->GetTransform()->SetLocalScale(float4{ 750.0f , 6.0f });
	m_MainRender->ColorOptionValue.MulColor.a = 0.8f;
}
