#include "PrecompileHeader.h"
#include "CTestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "CPlayer.h"
#include "CBoss_HeadHunter.h"
#include "CMouse.h"
#include "CBackGround.h"
#include "CTitleUIManager.h"

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
	// �ش� �������� ����� ���ҽ��� �ε��Ѵ�. 
	// �ش� ������ ����Ǹ� �ε��� ���ҽ��� ��� �����Ѵ� 
	// ������ �ε� �� ��� ������ �̸����δ� ������ �� ����.
	{
		// ���丮 Ŭ��������
		GameEngineDirectory NewDir;
		// ���ϴ� ������ ���� ���͸��� �̵�
		NewDir.MoveParentToDirectory("katanazero_resources");
		// �� ������ �̵�
		NewDir.Move("katanazero_resources");

		// ���� ��ü�ε� 
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// �� ���������� �ݵ�� �����Ҷ� ����Ÿ���� �������ش�. 
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	// ī�޶� ��� ��ġ���� �ٶ� ������
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });
	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();

	std::shared_ptr<CPlayer> NewPlayer = CreateActor<CPlayer>("Player");
	SetPlayer(NewPlayer);
	std::shared_ptr<CBoss_HeadHunter> NewBoss = CreateActor<CBoss_HeadHunter>();
	SetBoss(NewBoss);
	NewBoss->GetTransform()->SetLocalPosition({ 100, 100 , });
	std::shared_ptr<CMouse> NewMouse = CreateActor<CMouse>("Mouse");
	SetMouse(NewMouse);
	std::shared_ptr<CTitleUIManager> TitleManager = CreateActor<CTitleUIManager>("TitleUIManager");
	TitleManager->CreateRender();
}

void CTestLevel::Update(float _DeltaTime)
{
	std::shared_ptr<CMouse> Mouse = GetMouse();
	if (nullptr != Mouse)
	{
		m_CurMouseLocalPos = Mouse->GetTransform()->GetLocalPosition();
	}
 
	CKatanaZero_Level::Update(_DeltaTime);
}

