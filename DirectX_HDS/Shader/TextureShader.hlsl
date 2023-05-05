// 트랜스폼 데이터를 저장할 상수버퍼

// 0~ 16번 슬롯이 있고
// 선언해 놨다고 사용한다는 의미가 아니다.
// 0번슬롯을 사용하겠다고 하는 의미가 된다. 
// constantbuffer (상수버퍼) : 장면의 물체마다 달라지는 상수 데이터를 담기 위한 저장공간
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

struct Input
{
    // 버텍스셰이더에 입력될 정보
	// 시맨틱 : 인풋 구조체의 변수들이 어떤 자료와 연결될 지 알려주는 것
    float4 Pos : POSITION;
    // UV좌표계 : 3차원 공간에 폴리곤에 텍스쳐를 입히기 위한 기준이 되는 2차원 좌표계입니다. 
    // UV좌표는 최소 0 최대 1의 좌표를 가지고 1을 넘어가거나 0 미만이 될 경우 텍스쳐가 반복되어 출력된다. 
    // 최대값은 조정가능. 원하는 값으로 조정이 가능하다고함. 
    float4 UV : TEXCOORD;
};

struct Output
{
    // 픽셀셰이더에 입력 되고 계산되어
    // 레스터라이저에 보내는 정보가 된다. 
    // w 값으로 나눈 후 뷰포트 곱하고 픽셀을 건져낼 때 사용할 포지션 정보
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

// 버텍스셰이더에서 계산되어 반환되는 값이 Output struct
// 이 구조체에 저장된 값을 픽셀셰이더에 넘겨준다. 
Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;
	
    _Value.Pos.w = 1.0f;
    // 월드뷰프로젝션 곱 : mul 함수 사용
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutPutValue.Pos = _Value.Pos;
    OutputValue.UV = _Value.UV;

    return OutputValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

// 텍스쳐를 사용하려면 
Texture2D DiffuseTex : register(t0); 

// 샘플러
// 텍스쳐를 어떻게 불러들이겠냐는 설정, 
SamplerState CLAMPSAMPLER : register(s0);

// 픽셀셰이더에서는 버텍스셰이더에서 반환한 값을 받아서
// 픽셀을 건져낸다. 
float4 Texture_PS(Output _Value) : SV_Target0
{
    // 스위즐링 표현법
    // float4
    // float4.xy == float2
    // float4.xyz == float3 
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
  
    Color.r += 0.1f;
    Color.g += 0.1f;
    Color.b += 0.11f;
    Color.a;
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
