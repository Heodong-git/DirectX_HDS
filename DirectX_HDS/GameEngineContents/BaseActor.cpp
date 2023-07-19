#include "PrecompileHeader.h"
#include "BaseActor.h"
#include "BaseLevel.h"

#include <GameEngineBase/GameEngineRandom.h>

BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

const int BaseActor::CreateRandomValue(const int _MAX)
{
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, _MAX);
	return RandomValue;
}

BaseLevel* BaseActor::GetReturnCastLevel() const
{
	BaseLevel* Level = dynamic_cast<BaseLevel*>(GetLevel());
	
	if (nullptr == Level)
	{
		MsgAssert("Level �� nullptr �Դϴ�.");
		return nullptr;
	}

	return Level;
}

void BaseActor::ForcedReset()
{
	Infos.clear();
	m_Recording_Complete = true;
}

BaseLevel::LevelState BaseActor::GetLevelState()
{
	BaseLevel* CurLevel = GetReturnCastLevel();
	return CurLevel->GetCurState();
}

// ������Լ� 
void BaseActor::Reverse(GameEngineSpriteRenderer* _Renderer)
{
	if (nullptr == _Renderer)
	{
		MsgAssert("�������� nullptr �Դϴ�.");
		return;
	}
	BaseLevel::LevelState CurLevelState = GetLevelState();

	// ���� ������ ����ִٸ� return; 
	if (true == Infos.empty() || BaseLevel::LevelState::PLAY == CurLevelState)
	{
		// ���⼭ bool �� �ϳ��ΰ�, ��ȭ�Ϸ� üũ�� �ϰ�,
		// true�� �ٲ���ٸ� �ܺ� ��ȭ state ���� ���¸� �����Ų��. 
		m_Recording_Complete = true;
		return;
	}

	// ���� ������ ���� �޾ƿ´�. 

	

	switch (CurLevelState)
	{
	case BaseLevel::LevelState::RECORDING_PROGRESS:
	{
		ReverseInfo& Info = *(Infos.rbegin());

		if (true == Info.IsRecording)
		{
			_Renderer->On();
		}

		else if (false == Info.IsRecording)
		{
			Infos.pop_back();
			return;
		}

		this->GetTransform()->SetTransformData(Info.ActorData);
		_Renderer->GetTransform()->SetTransformData(Info.RendererData);
		_Renderer->SetTexture(Info.InfoData.Texture->GetName());
		_Renderer->SetAtlasData(Info.InfoData.CutData);

		// ������ ���� �� ���� 
		Infos.pop_back();
	}
		break;
	case BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD:
	{
		ReverseInfo& Info = *(Infos.begin());

		if (true == Info.IsRecording)
		{
			_Renderer->On();
		}

		else if (false == Info.IsRecording)
		{
			Infos.pop_front();
			return;
		}

		this->GetTransform()->SetTransformData(Info.ActorData);
		_Renderer->GetTransform()->SetTransformData(Info.RendererData);
		_Renderer->SetTexture(Info.InfoData.Texture->GetName());
		_Renderer->SetAtlasData(Info.InfoData.CutData);

		// ������ ���� �� ���� 
		Infos.pop_front();
	}
		break;
	default:
		break;
	}
	
}

// �ڷᱸ�� ���ͷ� �ٲٰ�
// �÷��̾� �����Ӱ������ϰ�
// ����Ʈ ���͵� ����������� �÷��̾� �����Ӱ� �޾ƿ���
// �ε������� �ʿ�

// 
void BaseActor::InfoSetting(GameEngineSpriteRenderer* _Renderer)
{
	SpriteInfo Info;

	GameEngineTextureSetter* Tex = _Renderer->GetShaderResHelper().GetTextureSetter("DiffuseTex");
	Info.Texture = Tex->Res;
	Info.CutData = _Renderer->GetAtlasData();

	Infos.push_back({ _Renderer->GetActor()->GetTransform()->GetTransDataRef(), _Renderer->GetTransform()->GetTransDataRef(), Info , m_IsRecording });
}

void BaseActor::Update(float _DeltaTime)
{
	
}

