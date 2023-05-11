#include "PrecompileHeader.h"
#include "BaseLevel.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineCamera.h>


BaseLevel::BaseLevel()
{
}

BaseLevel::~BaseLevel()
{
}

void BaseLevel::Start()
{
	CameraSetting();
}

void BaseLevel::Update(float _DeltaTime)
{
	// ���� Ŀ���� nullptr �� �ƴ϶�� 
	// �޾ƿͼ� ������������ ����
	std::shared_ptr<Cursor> Cursor = GetCursor();
	if (nullptr != Cursor)
	{
		m_CurMouseLocalPos = Cursor->GetTransform()->GetLocalPosition();
	}

	// GameEngineLevel �� update �� virtual �� �������شٸ� ����
	GameEngineLevel::Update(_DeltaTime);

}

void BaseLevel::LevelChangeStart()
{
	
}

void BaseLevel::CameraSetting()
{
	// ī�޶���
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000 });
}
