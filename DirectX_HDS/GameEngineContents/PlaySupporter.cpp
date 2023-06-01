#include "PrecompileHeader.h"
#include "PlaySupporter.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BaseLevel.h"
#include "Player.h"
#include "PixelCollider.h"

PlaySupporter* PlaySupporter::MainSupporter = nullptr;
std::shared_ptr<GameEngineUIRenderer> PlaySupporter::g_FailRender = nullptr;
std::shared_ptr<GameEngineUIRenderer> PlaySupporter::g_BlackBoxRender = nullptr;
std::shared_ptr<GameEngineCollision> PlaySupporter::g_MouseCheckCollision = nullptr;
std::shared_ptr<GameEngineUIRenderer> PlaySupporter::g_ClearRender = nullptr;

PlaySupporter::PlaySupporter()
{
	MainSupporter = this;
}

PlaySupporter::~PlaySupporter()
{
}

void PlaySupporter::Start()
{
	// �� ������ ī�޶� ��������
	SaveCameraRange();

	// �ʿ��� ���ҽ� �ε�
	LoadResources();

	// ������Ʈ ����
	ComponentSetting();
}

void PlaySupporter::Update(float _DeltaTime)
{
	// �̰͵� ��� �ʿ����� �𸣰��� 
	if (nullptr != GameEngineCore::GetCurLevel())
	{
		m_MainCamera = GameEngineCore::GetCurLevel()->GetMainCamera();
	}

	// �÷��̾ ����ϸ�, �ؽ�Ʈ�� ���� ������ ��� ���·� �����Ѵ�. 
	if (true == PlayerDeathCheck())
	{
		GetReturnCastLevel()->SetState(BaseLevel::LevelState::WAIT);

		// �������¿���üũ 
		LevelResetCheck();
	}

	// ���� ������ ����� �Ǹ� ī�޶�� �������� ���� 
	if (true == RangeOverCheck(_DeltaTime))
	{
		return;
	}

	CameraMovement(_DeltaTime);
}

void PlaySupporter::Render(float _DeltaTime)
{
}

void PlaySupporter::CameraMovement(float _DeltaTime)
{
	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("�÷��̾ nullptr �Դϴ�.");
		return;
	}

	// ī�޶� ���� ���� ���
	// ī�޶�� �÷��̾��� ��ġ�� �޾ƿͼ� �� �������� �̵� �ϱ����� ����üũ 
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
	float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();

	float4 Dir = PlayerPos - CameraPos;
	Dir.y = 0.0f;
	Dir.Normalize();
	m_MainCamera->GetTransform()->AddLocalPosition(Dir * m_MoveSpeed * _DeltaTime);
}

bool PlaySupporter::RangeOverCheck(float _DeltaTime)
{
	std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();
	BaseLevel* CastLevel = dynamic_cast<BaseLevel*>(CurLevel.get());

	// ���� null �̸� return
	if (nullptr == CastLevel)
	{
		return true;
	}

	// ���� ������ Ÿ�Ե� ������
	LevelType CurLevelType = CastLevel->GetLevelType();

	if (LevelType::NONE == CurLevelType)
	{
		MsgAssert("������ Ÿ���� ���õ��� �ʾҽ��ϴ�.");
		return true;
	}

	// �ȼ��ö��̴��� �浹���� ��������, ������ ���� ����ϴ� �ʰ� ũ��� ����
	std::shared_ptr<GameEngineTexture> CurMap = PixelCollider::PixelCol->GetColMap();

	if (nullptr == CurMap)
	{
		// MsgAssert("���� ���� nullptr �Դϴ�.");
		return true;
	}

	// ���� ũ�⸦ �޾ƿ´�.
	float4 MapSize = CurMap->GetScale();

	// ���� ���� Ÿ�Կ� ���� ī�޶� ������� ���
	switch (CurLevelType)
	{
	case LevelType::CLUBMAP0:
	{
		//// �̺κ��� ���� ���� �ȵ��.. 
		//if (nullptr == m_MainCamera)
		//{
		//	return true;
		//}

		std::map<int, std::vector<float4>>::iterator FindIter = m_MapRanges.find(static_cast<int>(LevelType::CLUBMAP0));
		if (m_MapRanges.end() == FindIter)
		{
			MsgAssert("�� ���� ���� ���Ͱ� ����ֽ��ϴ�.");
		}

		// �װԾƴ϶�� ���� ������ �޾ƿ��� 
		std::vector<float4> Vector = FindIter->second;
		float4 LeftTop = Vector[0];
		float4 RightTop = Vector[1];

		// ī�޶� �̵����� ���� ī�޶��� ��ġ�� ������ ����ٸ� �̵����� �ʵ��� ó��
		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetLocalPosition();
		float4 CameraPos = m_MainCamera->GetTransform()->GetLocalPosition();
		float4 Dir = PlayerPos - CameraPos;
		Dir.Normalize();
		float4 NextPos = CameraPos + Dir * m_MoveSpeed * _DeltaTime;

		// �̵��� ��ġ�� ī�޶��� �̵����ɹ����� ����� �̵����� ����
		if (NextPos.x < LeftTop.x || NextPos.x > RightTop.x)
		{
			return true;
		}

		// �̵��� �����ϴٸ� false ��ȯ, 
		return false;
	}
		break;
	case LevelType::CLUBMAP1:
	{
		// �Ǻ� �� ��ü�� �� ������ ������ �ʿ� ����. 
		return true;
	}
		break;
	case LevelType::CLUBMAP2:
	{
		int a = 0;
	}
		break;
	case LevelType::CLUBMAP3:
		break;
	case LevelType::CLUBMAP4:
		break;
	case LevelType::NONE:
		break;
	default:
		break;
	}

	return true;
}

bool PlaySupporter::PlayerDeathCheck()
{
	if (nullptr == Player::MainPlayer)
	{
		return false;
	}

	if (PlayerState::DEATH == Player::MainPlayer->GetCurState())
	{
		return true;
	}

	return false;
}

void PlaySupporter::LevelResetCheck()
{
	g_BlackBoxRender->On();
	g_FailRender->On();

	if (nullptr == g_MouseCheckCollision)
	{
		MsgAssert("���콺Ŭ�� üũ�� �浹ü�� nullptr�Դϴ�.");
		return;
	}

	// ���� �� �浹ü�� ���콺 Ŭ�� �浹ü�� �����༮�� �浹�ϰ� �Ǹ� ������ ���� ȣ�� 
	g_MouseCheckCollision->GetTransform()->SetLocalPosition(m_MainCamera->GetTransform()->GetLocalPosition());

	std::shared_ptr<GameEngineCollision> CursorCol = g_MouseCheckCollision->Collision(ColOrder::CURSOR, ColType::AABBBOX2D, ColType::AABBBOX2D);

	// ������ ���Դٴ°� �浹�ߴٴ°Ű� 
	// �׷� �浹�� ���͸� ������Ű�� �������� ȣ�� 
	if (nullptr != CursorCol)
	{
		CursorCol->Off();
		g_BlackBoxRender->Off();
		g_FailRender->Off();
		// �����ϰ� 
		GetReturnCastLevel()->LevelReset();
	}
}

void PlaySupporter::ComponentSetting()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	g_BlackBoxRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	g_BlackBoxRender->SetTexture("background_black.png");
	g_BlackBoxRender->GetTransform()->SetLocalScale({ ScreenSize.x / 3.0f , ScreenSize.y / 4.0f });
	g_BlackBoxRender->GetTransform()->SetLocalPosition({ 50.0f , 0.0f });
	g_BlackBoxRender->ColorOptionValue.MulColor.a = 0.4f;
	g_BlackBoxRender->Off();

	g_FailRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	g_FailRender->SetScaleToTexture("restart.png");
	g_FailRender->GetTransform()->SetLocalPosition({ 60.0f , 0.0f });
	g_FailRender->Off();

	g_ClearRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	g_ClearRender->SetTexture("youcandothis.png");
	g_ClearRender->GetTransform()->SetLocalScale(ScreenSize);
	g_ClearRender->Off();

	g_MouseCheckCollision = CreateComponent <GameEngineCollision>(ColOrder::CHECKBOX);
	g_MouseCheckCollision->GetTransform()->SetLocalScale(ScreenSize);
}

// �����غ��� ����Ʈž ����Ʈ���Ҹ� ������ �Ǵ°žƴѰ� ? 
void PlaySupporter::SaveCameraRange()
{
	{
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { -360.0f , 34.0f };
		float4 RightTop = { 307.0f , 34.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP0), Ranges));
	}

	{
		// 1������ �־�α⸸. ������ ����ġ������ ���� X 
		std::vector<float4> Ranges = std::vector<float4>();
		float4 LeftTop = { 0.0f , 0.0f };
		float4 RightTop = { 0.0f, 0.0f };

		Ranges.push_back(LeftTop);
		Ranges.push_back(RightTop);
		m_MapRanges.insert(make_pair(static_cast<int>(LevelType::CLUBMAP1), Ranges));
	}

	{

	}
}

void PlaySupporter::LoadResources()
{
	if (nullptr == g_BlackBoxRender)
	{
		if (nullptr == GameEngineTexture::Find("restart.png"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("katanazero_resources");
			NewDir.Move("katanazero_resources");
			NewDir.Move("Texture");
			NewDir.Move("ClubLevel");
			NewDir.Move("youcandothis");

			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });

			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}
	}
}

void PlaySupporter::Reset()
{
}

