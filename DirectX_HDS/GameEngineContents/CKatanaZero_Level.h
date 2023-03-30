#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 컨텐츠 구성시 레벨에서 사용할 필요한 기능 구현 예정
class CKatanaZero_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	CKatanaZero_Level();
	~CKatanaZero_Level();

	// delete Function
	CKatanaZero_Level(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level(CKatanaZero_Level&& _Other) noexcept = delete;
	CKatanaZero_Level& operator=(const CKatanaZero_Level& _Other) = delete;
	CKatanaZero_Level& operator=(CKatanaZero_Level&& _Other) noexcept = delete;

protected:

private:

};

// 카타나제로는 스테이지별로 진행시간이 정해져 있고.
// 음. 소유한 오브젝트의 정보를 전부 기록하는 기능과 그걸 저장하는 기능, 저장된 정보를 로드하는 기능