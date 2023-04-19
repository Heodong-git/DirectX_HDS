#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"

// 모든 텍스처건 상수버퍼건 
class GameEngineShaderResources
{
public:
	std::string Name;
	class GameEngineShader* ParentShader = nullptr;
	int BindPoint = -1; // b0 t0 같은 몇번째 슬롯에 세팅되어야 하는지에 대한 정보.

public:
	virtual void Setting() = 0;
};

class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;
	const void* CPUData;
	size_t CPUDataSize;

	void Setting() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;
};


// 
class GameEngineShaderResHelper
{
private:
	// 기본적으로 map 과 동일하지만 하나의 차이점 존재 -> 동일한 키값으로 저장이 가능하다. 
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	bool IsConstantBuffer(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

		if (ConstantBuffer.end() == FindIter)
		{
			return false;
		}

		return true;
	}

	template<typename DataType>
	void SetConstantBufferLink(const std::string_view& _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, reinterpret_cast<const void*>(&_Data), sizeof(DataType));
	}

	void SetConstantBufferLink(const std::string_view& _Name, const void* _Data, size_t _Size);

	void Copy(const GameEngineShaderResHelper& _ResHelper);

	void Setting();
};
