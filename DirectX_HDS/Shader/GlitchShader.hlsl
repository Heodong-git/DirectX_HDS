#define shake_power 0.3
   
#define shake_rate  0.45

#define shake_speed  10.0

#define shake_block_size  70.5

#define shake_color_rate 0.01

float random(float seed)
{
    return frac(543.2543 * sin(dot(float2(seed, seed), float2(3525.46, -54.3415))));
}

struct Input
{
    float4 Pos : POSITION;  
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut Glitch_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    // 화면 전체 범위
    return OutPutValue;
}

cbuffer RenderBaseValue : register(b11)
{
    // 상수버퍼는 
    float4 Time;
    float4 ScreenSize;
    float4 Mouse;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAP : register(s0);

float4 Glitch_PS(OutPut _Value) : SV_Target0
{
    float enable_shift = float(
        random(floor(Time.x * shake_speed))
        < shake_rate
    );

    float2 fixed_uv = _Value.UV;
    fixed_uv.x += (
        random(
            (floor(_Value.UV.y * shake_block_size) / shake_block_size)
            + Time.x
        ) - 0.5
    ) * shake_power * enable_shift;

    float4 pixel_color = DiffuseTex.SampleLevel(WRAP, fixed_uv, 0.0);
    pixel_color.r = lerp(
        pixel_color.r,
        DiffuseTex.SampleLevel(WRAP, fixed_uv + float2(shake_color_rate, 0.0), 0.0).r,
        enable_shift
    );
    pixel_color.b = lerp(
        pixel_color.b,
        DiffuseTex.SampleLevel(WRAP, fixed_uv + float2(-shake_color_rate, 0.0), 0.0).b,
        enable_shift
    );
    
    return pixel_color;
}


