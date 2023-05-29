#include "PrecompileHeader.h"
#include "ClubDoor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

ClubDoor::ClubDoor()
{
}

ClubDoor::~ClubDoor()
{
}

void ClubDoor::Start()
{
}

void ClubDoor::Update(float _DeltaTime)
{
}

void ClubDoor::Render(float _DeltaTime)
{
}

void ClubDoor::DebugUpdate()
{
}

void ClubDoor::ComponentSetting()
{
}

void ClubDoor::LoadAndCreateAnimation()
{
}

// -------------------------------------------- State ----------------------------------------------------

void ClubDoor::UpdateState(float _DeltaTime)
{
	// 현재 상태의 update 호출 
	switch (m_CurState)
	{
	case ClubDoorState::CLOSE:
		CloseUpdate(_DeltaTime);
		break;
	case ClubDoorState::OPEN:
		OpenUpdate(_DeltaTime);
		break;
	}
}

// state 변경, 변경될 상태의 start, 이전 상태의 end 수행
void ClubDoor::ChangeState(ClubDoorState _State)
{
	m_NextState = _State;
	m_PrevState = m_CurState;
	m_CurState = m_NextState;

	switch (m_NextState)
	{
	case ClubDoorState::CLOSE:
		CloseStart();
		break;
	case ClubDoorState::OPEN:
		OpenStart();
		break;
	}

	// 이전 state의 end 
	switch (m_PrevState)
	{
	case ClubDoorState::CLOSE:
		CloseEnd();
		break;
	case ClubDoorState::OPEN:
		OpenEnd();
		break;
	}
}

void ClubDoor::CloseStart()
{
}

void ClubDoor::CloseUpdate(float _DeltaTime)
{
}

void ClubDoor::CloseEnd()
{
}

void ClubDoor::OpenStart()
{
}

void ClubDoor::OpenUpdate(float _DeltaTime)
{
}

void ClubDoor::OpenEnd()
{
}
