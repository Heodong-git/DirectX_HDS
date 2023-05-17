
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
   
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    // 0.0 0.5
    float2 FramePos;
    // 0.5 0.5 
    float2 FrameScale;
    // float4 AtlasUV;
}


Output Texture_VS(Input _Value)
{
    Output OutputValue = (Output) 0;
	
    _Value.Pos.w = 1.0f;
    // 월드뷰프로젝션 곱 : mul 함수 사용
    OutputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutPutValue.Pos = _Value.Pos;
    OutputValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutputValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;

    return OutputValue;
}
 
cbuffer ColorOption : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}

Texture2D BlinkTex : register(t2);

SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(Output _Value) : SV_Target0
{
    float4 color = BlinkTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    return color;
}
