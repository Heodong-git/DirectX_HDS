#include "PrecompileHeader.h"
#include "PixelCollider.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "BaseLevel.h"
#include "Player.h"

PixelCollider* PixelCollider::PixelCol = nullptr;
std::vector<std::shared_ptr<class GameEngineTexture>> PixelCollider::m_ColMaps = std::vector<std::shared_ptr<class GameEngineTexture>>();

GameEnginePixelColor PixelCollider::g_BlackPixel = { static_cast<char>(0), static_cast<char>(0) , static_cast<char>(0) ,
										static_cast<char>(255) };

GameEnginePixelColor PixelCollider::g_WhitePixel = { static_cast<char>(255), static_cast<char>(255) , static_cast<char>(255) ,
									static_cast<char>(255) };

GameEnginePixelColor PixelCollider::g_GreenPixel = { static_cast<char>(0), static_cast<char>(255) , static_cast<char>(0) ,
									static_cast<char>(255) };

GameEnginePixelColor PixelCollider::g_ErrorPixel = { static_cast<char>(255), static_cast<char>(0) , static_cast<char>(255) ,
									static_cast<char>(255) };

PixelCollider::PixelCollider()
{
	PixelCol = this;
}

PixelCollider::~PixelCollider()
{
}

void PixelCollider::Start()
{
	if (0 == m_ColMaps.size())
	{
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("ColMap");

		// ���� ��ü�ε� 
		// ���⼭ ������� ����Ǳ� ������ ������ ������ �ٲ�� �ȵȴ�. 
		// �̷��Ÿ� ���� ������ ���⵵.. 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd" });
		for (size_t i = 0; i < File.size(); i++)
		{
			m_ColMaps.push_back(GameEngineTexture::Load(File[i].GetFullPath()));
		}

		// �������ϰ� ���� ����� 0�̶�� assert
		if (0 == m_ColMaps.size())
		{
			MsgAssert("�浹���� ������� �ʾҽ��ϴ�.");
			return;
		}
	}
}

bool PixelCollider::ColMapSetting()
{
	if (0 == m_ColMaps.size())
	{
		MsgAssert("ColMap�� ���Ϳ� ������� �ʾҽ��ϴ�.");
		return false;
	}

	if (nullptr == Player::MainPlayer)
	{
		MsgAssert("Player �� nullptr �Դϴ�.");
		return false;
	}

	BaseLevel* CurLevel = Player::MainPlayer->GetReturnCastLevel();

	if (nullptr == CurLevel)
	{
		MsgAssert("���� ������ nullptr �Դϴ�.");
		return false;
	}

	LevelType CurMapName = CurLevel->GetLevelType();

	// �ȼ��ݶ��̴����� ���� ������ Ÿ���� �޾ƿ���, �� ����Ÿ�Կ� �´� �浹���� �������ش�. 
	switch (CurMapName)
	{
	case LevelType::CLUBMAP0:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP0)];
		break;
	case LevelType::CLUBMAP1:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP1)];
		break;
	case LevelType::CLUBMAP2:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP2)];
		break;
	case LevelType::CLUBMAP3:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP3)];
		break;
	case LevelType::CLUBMAP4:
		m_CurColMap = m_ColMaps[static_cast<int>(ColMapName::COLMAP4)];
		break;
	}

	if (nullptr == m_CurColMap)
	{
		MsgAssert("�浹���� nullptr �Դϴ�. PixelCollider Ŭ������ Ȯ���ϼ���.");
		return false;
	}
	return true;
}


GameEnginePixelColor PixelCollider::PixelCollision(const float4& _Pos)
{
	// �浹�� ����
	ColMapSetting();

	// üũ�� ��ġ
	float4 CheckPos = _Pos;

	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// 
	if (g_BlackPixel == ColPixel)
	{
		return g_BlackPixel;
	}

	// y ������ �̵��Ѱ� 
	int UpCount = 0;
	if (g_BlackPixel == ColPixel)
	{
		// true ���� �������°���.
		while (true)
		{
			// �� - ����ߵ���
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (g_WhitePixel == ColPixel)
			{
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0 , static_cast<float>(UpCount) });
				break;
			}
		}

		return g_WhitePixel;
	}

	return g_WhitePixel;
}



// ���ڰ� ���� �ʿ� ���� �ϴ�. 
bool PixelCollider::GroundCheck(class GameEngineObject* _Object)
{
	ColMapSetting();

	if (nullptr == _Object)
	{
		MsgAssert("���ڷ� ���� ������Ʈ�� nullptr �Դϴ�.");
		return false;
	}

	// üũ�� ��ġ 
	float4 CheckPos = Player::MainPlayer->GetTransform()->GetLocalPosition();

	float WidthHalf = static_cast<float>(m_CurColMap->GetWidth() / 2);
	float HeightHalf = static_cast<float>(m_CurColMap->GetHeight() / 2);

	int CheckX = static_cast<int>(CheckPos.x + WidthHalf);
	int CheckY = static_cast<int>(HeightHalf - CheckPos.y);

	// �浹���� �÷��̾�� ��ġ�� ��ġ�� ������ �޾ƿ´�. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// y ������ �̵��Ѱ� 
	int UpCount = 0;
	if (g_BlackPixel == ColPixel)
	{
		// true ���� �������°���.
		while (true)
		{
			// �� - ����ߵ���
			--CheckY;
			++UpCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
			if (g_WhitePixel == ColPixel)
			{
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0 , static_cast<float>(UpCount) });
				break;
			}
		}

		return true;
	}

	return false;
}

// �浹 �˻� �Լ�
bool PixelCollider::RightPixelCheck()
{
	// ���� ���� ������ ���� �ִٸ� 
	ColMapSetting();

	float4 CheckPos = {};
	if (false == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Left->GetTransform()->GetWorldPosition();
	}
	
	else if (true == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	}
	
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �˻��� ��ġ�� �ȼ����� �޾ƿ´�.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);
	
	// �浹 �˻�
	if (g_BlackPixel == ColPixel)
	{
		return true; // �浹 �߻�
	}

	return false; // �浹 ����
}

bool PixelCollider::RightWallCheck(float4& _Pos)
{
	// ���� ���� ������ ���� �ִٸ� 
	ColMapSetting();

	float4 CheckPos = _Pos;
	if (false == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Left->GetTransform()->GetWorldPosition();
	}

	else if (true == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	}

	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �˻��� ��ġ�� �ȼ����� �޾ƿ´�.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// �浹 �˻�
	if (g_BlackPixel == ColPixel)
	{
		return true; // �浹 �߻�
	}

	return false; // �浹 ����
}

// �浹 �˻� �Լ� (Left �浹)
bool PixelCollider::LeftPixelCheck()
{
	ColMapSetting();

	float4 CheckPos = {};
	if (false == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Right->GetTransform()->GetWorldPosition();
	}

	else if (true == Player::MainPlayer->GetDir())
	{
		CheckPos = Player::MainPlayer->m_DebugRender_Left->GetTransform()->GetWorldPosition();
	}
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();

	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �˻��� ��ġ�� �ȼ����� �޾ƿ´�.
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// �浹 �˻�
	if (g_BlackPixel == ColPixel)
	{
		return true; // �浹 �߻�
	}

	return false; // �浹 ����
}

bool PixelCollider::TopPixelCheck()
{
	ColMapSetting();

	float4 CheckPos = Player::MainPlayer->m_DebugRender_Top->GetTransform()->GetWorldPosition();
	float4 ColMapSize = m_CurColMap->GetScale();
	float4 ColMapHalpSize = ColMapSize.half();
	
	// �ȼ� ũ�� ���
	float PixelSizeX = ColMapSize.x / m_CurColMap->GetWidth();
	float PixelSizeY = ColMapSize.y / m_CurColMap->GetHeight();

	// �浹 ��ġ ���
	int CheckX = static_cast<int>((CheckPos.x + (ColMapSize.x / 2)) / PixelSizeX);
	int CheckY = static_cast<int>(((ColMapSize.y / 2) - CheckPos.y) / PixelSizeY);

	// ���� ���� �������� ��� ��� �浹�� ����
	if (CheckX < 0 || CheckX >= m_CurColMap->GetWidth() ||
		CheckY < 0 || CheckY >= m_CurColMap->GetHeight())
	{
		return true; // �浹 �߻� (�� ������ ���)
	}

	// �浹���� �÷��̾�� ��ġ�� ��ġ�� ������ �޾ƿ´�. 
	GameEnginePixelColor ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

	// �������Դ��� üũ
	bool Check = false;
	// y ������ �̵��Ѱ� 
	int DownCount = 0;
	
	if (g_BlackPixel == ColPixel)
	{
		// �������� ������ �ݺ�
		while (true)
		{
			// �Ʒ��� �̵�
			++CheckY;
			++DownCount;
			ColPixel = m_CurColMap->GetPixel(CheckX, CheckY);

			if (g_WhitePixel == ColPixel)
			{
				// �������� �ȼ��� �Ʒ� �ȼ��� ����̸� ��������
				Player::MainPlayer->GetTransform()->AddLocalPosition({ 0, -static_cast<float>(DownCount) });
				break;
			}
		}

		return true;
	}

	return false;
}

