#include "PrecompileHeader.h"
#include "BloodEffect.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


BloodEffect::BloodEffect()
{
}

BloodEffect::~BloodEffect()
{
}

void BloodEffect::SetType(BloodType _Type)
{
	if (BloodType::NONE == _Type)
	{
		MsgAssert("���� ����Ʈ�� ���ð��� �������� ���� �ƴմϴ�.");
		return;
	}
	
	m_CurType = _Type;
	// Ÿ���� �븻�� �����ߴٸ� 
	if (BloodType::NORMAL == m_CurType)
	{
		int RandomValue = GameEngineRandom::MainRandom.RandomInt(0, 7);
		switch (RandomValue)
		{
		case 0:
			m_Render->SetScaleToTexture("normal_blood_00.png");
			m_Render->GetTransform()->AddLocalPosition(float4::Down * 50.0f);
			break;
		case 1:
			m_Render->SetScaleToTexture("normal_blood_01.png");
			m_Render->GetTransform()->AddLocalPosition(float4::Down * 50.0f);
			break;
		case 2:
			m_Render->SetScaleToTexture("normal_blood_03.png");
			break;
		case 3:
			m_Render->SetScaleToTexture("normal_blood_04.png");
			break;
		case 4:
			m_Render->SetScaleToTexture("normal_blood_05.png");
			break;
		case 5:
			m_Render->SetScaleToTexture("normal_blood_06.png");
			m_Render->GetTransform()->AddLocalPosition(float4::Down * 25.0f);
			break;
		case 6:
			m_Render->SetScaleToTexture("normal_blood_07.png");
			break;
		case 7:
			m_Render->SetScaleToTexture("normal_blood_08.png");
			break;
		}
	}
}

void BloodEffect::Start()
{
	// �����������, �ִϸ��̼� �������� �־�ΰ�, ����Ʈ�����Ҷ� 
	// � �ִϸ��̼��� �����ٰ��� set 
	m_Render = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BLOOD_EFFECT);

	if (nullptr == GameEngineSprite::Find("normal_blood"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("ClubLevel");
		Dir.Move("effect");
		Dir.Move("blood_effect");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("blood_effect1").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("blood_effect2").GetFullPath());
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("blood_effect3").GetFullPath());

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("normal_blood").GetFullPath());

		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}

	Set_Recording_StartFrame();
}

void BloodEffect::Update(float _DeltaTime)
{
	if (BloodType::NONE == m_CurType)
	{
		MsgAssert("���� ����Ʈ�� Ÿ���� �������� �ʾҽ��ϴ�.");
		return;
	}
	m_RecordingFrame = !m_RecordingFrame;

	if (BaseLevel::LevelState::RECORDING_PROGRESS == GetReturnCastLevel()->GetCurState())
	{
		if (EffectState::RECORDING_PROGRESS != m_CurState)
		{
			ChangeState(EffectState::RECORDING_PROGRESS);
			return;
		}
	}

	if (EffectState::RECORDING_PROGRESS == m_CurState)
	{
		// ���� ��Ŭ�� �Է½� �ٷ� death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Reverse(m_Render.get());

		// ����� �Լ� ȣ�� �� , ���� ��������� 0 �̶�� ���� death 
		if (0 == Infos.size())
		{
			this->Death();
		}

		return;
	}

	if (BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD == GetReturnCastLevel()->GetCurState())
	{
		if (EffectState::RECORDING_PROGRESS_FORWARD != m_CurState)
		{
			m_Render->Off();
			SetMaxIndex();
			ChangeState(EffectState::RECORDING_PROGRESS_FORWARD);
			return;
		}
	}

	if (EffectState::RECORDING_PROGRESS_FORWARD == m_CurState)
	{
		// ���� ��Ŭ�� �Է½� �ٷ� death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		// �������϶� ����Ǿ��ִ� �����Ӱ��� --
		if (0 < m_Recording_StartFrame)
		{
			--m_Recording_StartFrame;
		}

		if (0 == m_Recording_StartFrame)
		{
			m_Render->On();
			return;
		}

		return;
	}

	if (nullptr != m_Render)
	{
		if (BloodType::NORMAL == m_CurType && EffectState::DEATH != m_CurState)
		{
			ChangeState(EffectState::DEATH);
			m_IsRecording = false;
			//this->Death();
			return;
		}
	}

	// ���� ������Ʈ��, ��ȭ�������� �ƴ϶��, ��ȭ ������ �����Ѵ�. 
	if (EffectState::RECORDING_PROGRESS != m_CurState)
	{
		if (true == m_RecordingFrame)
		{
			InfoSetting(m_Render.get());
		}
	}
}

void BloodEffect::Render(float _DeltaTime)
{
}
