Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState sample : register(s0);

struct PS_Input
{
    float4 inputPosition : SV_Position;
    float2 inputTexCoord : TEXCOORD;
    int size : SIZE;
};

float4 main(PS_Input input) : SV_Target
{
    float4 color;
    
    if (input.size == 0)
    {
        color = texture0.Sample(sample, input.inputTexCoord);
    }
    else if (input.size == 1)
    {
        color = texture1.Sample(sample, input.inputTexCoord);
    }
    
    return color;
}