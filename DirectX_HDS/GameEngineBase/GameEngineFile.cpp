#include "PrecompileHeader.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::~GameEngineFile() 
{
}


GameEngineFile::GameEngineFile(std::filesystem::path _Path) 
	: Path(_Path)
{

}

// ���̳ʸ��� ����
void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	// c��Ÿ���� ���������, ���������� �غ�
	FILE* FilePtr = nullptr;

	// ��θ� �޾ƿ´�. 
	std::string PathString = Path.GetPathToString();
	
	// ���� ���� ����, write , binary 
	std::string Text = "wb";

	// ����������, ���, ������ ���ڷ� �־��ش�. 
	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	// ���� ���������Ͱ� nullptr �̶�� �Ͷ߸���.
	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	// ������ ���Ͽ� �Է�
	// 1������ : ������
	// 2������ : �������� ũ��
	// 3������ : ����������
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr);

	// ������ �����ٸ� �ݾ��ش�.
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// �ؽ�Ʈ�� ����
void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;
	std::string PathString = Path.GetPathToString();
	std::string Text = "wt";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	//                         500               1
	fwrite(_View.data(), _View.size(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// ���̳ʸ��� ����Ǿ� �ִ� ���Ϸε�
void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetPathToString();
	std::string Text = "rb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	size_t FileSize = std::filesystem::file_size(Path.Path);
	
	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}