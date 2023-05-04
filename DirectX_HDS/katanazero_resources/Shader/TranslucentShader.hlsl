
cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

struct VertexInputType
{
    // 버텍스셰이더에 입력될 정보
	// 시맨틱 : 인풋 구조체의 변수들이 어떤 자료와 연결될 지 알려주는 것
    
    //           각각의 변수가 어떤 역할인지
    float4 Pos : POSITION;
    // UV좌표계 : 3차원 공간에 폴리곤에 텍스쳐를 입히기 위한 기준이 되는 2차원 좌표계입니다. 
    // UV좌표는 최소 0 최대 1의 좌표를 가지고 1을 넘어가거나 0 미만이 될 경우 텍스쳐가 반복되어 출력된다. 
    // 최대값은 조정가능. 원하는 값으로 조정이 가능하다고함. 
    float4 UV : TEXCOORD;
};

struct PixelInputType
{
    // 픽셀셰이더에 입력 될 정보
    // 레스터라이저에게 보내는 정보 
    // w 값으로 나눈 후 뷰포트 곱하고 픽셀을 건져낼 때 사용할 포지션 정보를 보낸 거야
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

PixelInputType Texture_VS(VertexInputType _Value)
{
    PixelInputType PixelInputValue = (PixelInputType) 0;
	
    _Value.Pos.w = 1.0f;
    // 월드매트릭스 곱 : mul 함수를 사용하여 가능
    PixelInputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutPutValue.Pos = _Value.Pos;
    PixelInputValue.UV = _Value.UV;
	
	// 다음단계에서 사용할 정보들.
    // _Value.Pos *= 월드뷰프로젝션;

    return PixelInputValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

// 텍스쳐를 사용하려면 
Texture2D TranslucentTex : register(t1);

// 샘플러
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(PixelInputType _Value) : SV_Target0
{
    // 스위즐링 표현법
    // float4
    // float4.xy == float2
    // float4.xyz == float3 
    float4 Color = TranslucentTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    Color.a = 0.3f;
    return Color;
}
// clip <-- 한번확인해볼것 


// 0번째 타겟에 출력하라는 의미가 된다. 
//float4 Texture_PS(Output _Value) : SV_Target0
//{
//    return OutColor;
//}

// 아래 과정을 생략하여 위 코드처럼 작성이 가능하다. 
//struct OutColor
//{
//    // 깔아놓은 도화지중 0번째 도화지에 출력해라.
//    float4 Color : SV_Target0;
//};

//OutColor Texture_PS(Output _Value)
//{
//    OutColor ReturnColor = (OutColor) 0;
//    ReturnColor.Color = _Value.Color;
//    return ReturnColor;
//}
