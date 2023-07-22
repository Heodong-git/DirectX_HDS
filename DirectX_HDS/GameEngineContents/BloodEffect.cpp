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
		MsgAssert("블러드 이펙트의 세팅값이 정상적인 값이 아닙니다.");
		return;
	}
	
	m_CurType = _Type;
	// 타입을 노말로 세팅했다면 
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
	// 렌더러만들고, 애니메이션 세개만들어서 넣어두고, 이펙트생성할때 
	// 어떤 애니메이션을 보여줄건지 set 
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
		MsgAssert("블러드 이펙트의 타입을 지정하지 않았습니다.");
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
		// 만약 좌클릭 입력시 바로 death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		Reverse(m_Render.get());

		// 역재생 함수 호출 후 , 나의 인포사이즈가 0 이라면 나를 death 
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
		// 만약 좌클릭 입력시 바로 death 
		if (true == GameEngineInput::IsDown("EngineMouseLeft"))
		{
			this->Death();
			return;
		}

		// 정방향일때 저장되어있는 프레임값을 --
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

	// 나의 스테이트가, 녹화진행중이 아니라면, 녹화 정보를 저장한다. 
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
