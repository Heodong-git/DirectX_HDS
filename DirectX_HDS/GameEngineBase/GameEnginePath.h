#pragma once
// c++�� ����Ǵ� ������ ����Ҽ� �ִ� ��� ���ڿ� ���� ó������� ����
#include <filesystem>

// ���� : ��ο� ���õ� ����� ��ǥ�ϴ� Ŭ����
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

	// ���ϸ��ȯ
	std::string GetFileName() const;
	// ��ι�ȯ 
	std::string GetPathToString() const;

	// �������͸��� �̵�
	void MoveParent();

	// ���ڽ��� Ư�� ��γ� Ư�� ������ �ִ°����� �̵�
	void MoveParentToChildPath(const std::string_view& _String);

	// �� 
	bool IsExists();
	bool IsExistsToPlusString(const std::string_view& _String);

	// ���͸� üũ
	bool IsRoot();
	bool Move(const std::string_view& _Path);

	// ��� ����
	void SetPath(const std::string_view& _Path);


protected:

private:
	// �������ؼ� ������ �ʰ� �Ǿ����ϴ�.
	// std::string Path;
	std::filesystem::path Path;

};

