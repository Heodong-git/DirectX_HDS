#pragma once
// c++이 실행되는 곳에서 사용할수 있는 모든 문자열 관련 처리방식을 지원
#include <filesystem>

// 설명 : 경로에 관련된 기능을 대표하는 클래스
class GameEnginePath
{
	friend class GameEngineFile;
	friend class GameEngineDirectory;

public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	// 파일명반환
	std::string GetFileName() const;
	// 경로반환 
	std::string GetPathToString() const;

	// 상위디렉터리로 이동
	void MoveParent();

	// 내자식중 특정 경로나 특정 파일이 있는곳까지 이동
	void MoveParentToChildPath(const std::string_view& _String);

	// 음 
	bool IsExists();
	bool IsExistsToPlusString(const std::string_view& _String);

	// 디렉터리 체크
	bool IsRoot();
	bool Move(const std::string_view& _Path);

	// 경로 세팅
	void SetPath(const std::string_view& _Path);


protected:

private:
	// 고생고생해서 만들지 않게 되었습니다.
	// std::string Path;
	std::filesystem::path Path;

};

