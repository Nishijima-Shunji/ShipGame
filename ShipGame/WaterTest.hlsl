cbuffer HeightMapBuffer : register(b7)
{
    float heightData[1024]; // CPU�ƃT�C�Y��v������I
};

struct VS_INPUT {
    float3 position : POSITION;
    uint vertexID : SV_VertexID; // ���_�C���f�b�N�X
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
