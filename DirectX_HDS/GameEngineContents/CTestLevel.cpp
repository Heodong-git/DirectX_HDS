#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CMouse.h"
#include "CBackGround.h"
#include "CTitleManager.h"
#include "CPlayManager.h"

// test
#include <GameEngineCore/GameEngineVideo.h>


CTestLevel::CTestLevel()
{
}

CTestLevel::~CTestLevel()
{
}

void CTestLevel::Start()
{
	CKatanaZero_Level::Start();

	// �ش� �������� ����� ���ҽ��� �ε��Ѵ�. 
	// �ش� ������ ����Ǹ� �ε��� ���ҽ��� ��� �����Ѵ� 
	// ������ �ε� �� ��� ������ �̸����δ� ������ �� ����.
	{
		//// ���丮 Ŭ��������
		//GameEngineDirectory NewDir;
		//// ���ϴ� ������ ���� ���͸��� �̵�
		//NewDir.MoveParentToDirectory("katanazero_resources");
		//// �� ������ �̵�
		//NewDir.Move("katanazero_resources");
		//NewDir.Move("Texture");
		//NewDir.Move("TestLevel");

		//// ���� ��ü�ε� 
		//std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		//for (size_t i = 0; i < File.size(); i++)
		//{
		//	GameEngineTexture::Load(File[i].GetFullPath());
		//}
	}

	// ���ҽ�, ���ͷε� 
	ResourcesLoad();
	ActorLoad();

	/*{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("katanazero_resources");
		NewDir.Move("katanazero_resources");
		NewDir.Move("TestMovie");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".avi", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineVideo::Load(File[i].GetFullPath());
		}
	}*/
}

void CTestLevel::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
}

void CTestLevel::ResourcesLoad()
{
}

void CTestLevel::ActorLoad()
{
	m_PlayManager = CreateActor<CPlayManager>("PlayManager");
	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	std::shared_ptr<CMouse> NewMouse = CreateActor<CMouse>("Mouse");
	SetMouse(NewMouse);
}


void CTestLevel::LevelChangeStart()
{
}

void CTestLevel::LevelChangeEnd()
{
	
}

