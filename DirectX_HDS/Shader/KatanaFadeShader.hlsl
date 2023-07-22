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

OutPut KatanaFade_VS(Input _Value)
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


float DiamondMask(float2 p, float zoom)
{
    float x0 = min(p.x, 1.0 - p.x);
	
    zoom *= 0.5f;
    
	// Upper half of the shape.
    float y0 = 0.5 - x0 - zoom;
	
	// Lower half of the shape.
    float y1 = 1.0 - y0;
	
	// Shade area inside shape.
    if (p.y > y0 && p.y < y1)
    {
        return 1.0f;
    }
    else
    {
        return 0.0f;
    }
}


void mainImage(out float4 fragColor, in float2 fragCoord)
{
    // Normalized pixel coordinates (from 0 to 1)
    float2 uv = float2(fragCoord.x * ScreenSize.x, -fragCoord.y * ScreenSize.y) / ScreenSize.y;
    // Time varying pixel color
    
    float4 col;
    if(Time.z != 0)
    {
        float3 tmp = 0.5 + 0.5 * cos(Time.x + uv.xyx + float3(0, 2, 4));
        col = float4(tmp, 1);

    }
    else
    {
        col = float4(1, 1, 1, 1);
    }
                 
    
    float2 uv2 = frac(20.0f * uv);
    float t = frac(0.8 * Time.x);
    float zoom = lerp(2.0, -2.0, t) + lerp(1.0f, -1.0f, uv.x);
    if (DiamondMask(uv2, zoom) < 0.5f)
    {
        col *= 0.0f;
    }

    // Output to screen
    fragColor = col;

}

float4 KatanaFade_PS(OutPut _Value) : SV_Target0
{
    float4 uv = _Value.UV;
 
    float4 Color;
 
    mainImage(Color, _Value.UV.xy);
    float4 PlusColor = DiffuseTex.Sample(WRAP, uv.xy);
    
    Color += PlusColor;
    Color.xyz -= 1;
    
    Color = saturate(Color);
    //Color.a = 1.0f;
    return Color;
}
