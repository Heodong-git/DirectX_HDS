#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"


void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{

	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBuffer)
	{
		ConstantBuffer.insert(Setter);
	}


}