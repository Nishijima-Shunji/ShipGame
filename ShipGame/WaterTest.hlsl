cbuffer HeightMapBuffer : register(b7)
{
    float heightData[1024]; // CPUとサイズ一致させる！
};

struct VS_INPUT {
    float3 position : POSITION;
    uint vertexID : SV_VertexID; // 頂点インデックス
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;

    float height = heightData[input.vertexID];
    float3 pos = input.position;
    pos.y += height;

    output.position = mul(float4(pos, 1.0f), worldViewProj);
    return output;
}
