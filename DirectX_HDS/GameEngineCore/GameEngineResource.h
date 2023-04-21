#pragma once
#include <string>
#include <string_view>
#include <map>
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineNameObject.h>
#include "GameEngineDevice.h"

template<typename ResourcesType>
class GameEngineResource : public GameEngineNameObject
{
public:
	friend class GameEngineCore;

	// constrcuter destructer
	GameEngineResource() {}
	virtual ~GameEngineResource() = 0 {}

	// delete Function
	GameEngineResource(const GameEngineResource& _Other) = delete;
	GameEngineResource(GameEngineResource&& _Other) noexcept = delete;
	GameEngineResource& operator=(const GameEngineResource& _Other) = delete;
	GameEngineResource& operator=(GameEngineResource&& _Other) noexcept = delete;

	std::string_view GetPath()
	{
		return Path.c_str();
	}

	std::string_view GetName()
	{
		return Name.c_str();
	}

	std::string GetNameToString()
	{
		return Name;
	}

	void SetPath(const std::string_view& _Value)
	{
		Path = _Value;
	}

	void SetName(const std::string_view& _Value)
	{
		Name = _Value;
	}

	static std::shared_ptr<ResourcesType> Find(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() == NamedResources.find(UpperName.c_str()))
		{
			return nullptr;
		}

		return NamedResources[UpperName];
	}

	virtual void Setting() {}

protected:
	// 언네임드리소스 생성
	static std::shared_ptr<ResourcesType> CreateUnNamed()
	{
		// 리소스 생성후 단순하게 리스트에 push_back 후 생성한 리소스를 shared ptr로 반환 
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		UnNamedRes.push_back(NewRes);
		return NewRes;
	}

	// 인자로 들어온 문자열의 이름으로 리소스를 만든다. 
	static std::shared_ptr<ResourcesType> Create(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() != NamedResources.find(UpperName))
		{
			MsgAssert("이미 존재하는 이름의 리소스를 또 만들려고 했습니다.");
			return nullptr;
		}

		// 중복체크 후 shardptr 로 리소스 생성
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();

		// 리소스 이름세팅
		NewRes->SetName(UpperName);
		// std::pair<key, value>
		// NamedResources.insert(std::make_pair(UpperName, NewRes));
		// 조금이라도 최적화가 필요하다면 아래처럼 사용할 수 도 있음
		NamedResources.insert(std::map<std::string, std::shared_ptr<ResourcesType>>::value_type(UpperName, NewRes));
		return NewRes;
	}

	static void ResourcesClear()
	{
		NamedResources.clear();
		UnNamedRes.clear();
	}

private:
	std::string Path;
	std::string Name;

	static std::map<std::string, std::shared_ptr<ResourcesType>> NamedResources;
	static std::list<std::shared_ptr<ResourcesType>> UnNamedRes;

};

// template 클래스의 경우 
// 원래라면 static 으로 선언한 변수들을 cpp에 구현해주어야 하지만 템플릿클래스로 구현하였을 경우 헤더의 하단에 아래처럼 구현이 가능하다.
template<typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResource<ResourcesType>::NamedResources;

template<typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResource<ResourcesType>::UnNamedRes;
