#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"


// 파일은 바이트 덩어리라고 볼 수 있다. 확장자도 딱히 의미가 없음.
enum class SAVEMODE
{
	Text,
	Bin,
};

class GameEngineFile
{
public:
	// constrcuter destructer
	GameEngineFile();
	~GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);

	// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	// GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	// 저장되어 있는 전체경로를 반환
	std::string GetFullPath() 
	{
		return Path.Path.string();
	}

	void SaveBin(const GameEngineSerializer& _Data);
	void SaveText(const std::string_view& _View);

	void LoadBin(GameEngineSerializer& _Data);

protected:

private:
	GameEnginePath Path;
};

