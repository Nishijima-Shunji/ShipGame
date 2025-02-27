#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;

    // ���[���h�A�r���[�A�v���W�F�N�V�����s����|�����킹�č��W�ϊ����s��
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    // ================================
    // �g�̍������v�Z
    // ================================
    float waveFrequency = 0.1;  // �g�̎��g���i�g�̖��x�𒲐��j
    float waveSpeed = 1.0;      // �g�̐i�s���x
    float waveAmplitude = 1.5;  // �g�̐U���i�����𒲐��j
    float time = Timer; // C++ ����n����� 'Timer' �ɕύXfloat time = Time;         // �O���[�o���^�C�}�[�i�O������n���j

    // �g�̎�: sin�֐����g���Ĕg��\��
    float waveHeight = waveAmplitude * sin(input.pos.x * waveFrequency + time * waveSpeed);
    waveHeight += waveAmplitude * cos(input.pos.z * waveFrequency * 0.8 + time * waveSpeed * 1.2); // �����̔g������

    // ���͒��_��Y���W�ɔg�̍��������Z
    input.pos.y += waveHeight;

    // �ϊ���̒��_���W��ݒ�
    output.pos = mul(input.pos, wvp);

    // ================================
    // �@���̍Čv�Z�i�g�̌X���𔽉f�j
    // ================================
    float dx = waveAmplitude * waveFrequency * cos(input.pos.x * waveFrequency + time * waveSpeed);
    float dz = -waveAmplitude * waveFrequency * sin(input.pos.z * waveFrequency * 0.8 + time * waveSpeed * 1.2);
    float3 waveNormal = normalize(float3(-dx, 1.0, -dz));

    // �@���x�N�g�������[���h��Ԃɕϊ����Đ��K��
    float4 normal = float4(waveNormal, 0.0);
    float4 worldNormal = mul(normal, World); // ���[���h��Ԃɕϊ�
    worldNormal = normalize(worldNormal);

    // ================================
    // ���C�e�B���O�v�Z
    // ================================
    // ���������Ɩ@���x�N�g���̓��ς��v�Z���Ċg�U�������߂�
    float d = -dot(Light.Direction.xyz, worldNormal.xyz);
    d = saturate(d); // ���ς�0�`1�ɃN�����v

    // �g�U���ƃA���r�G���g����K�p
    output.col.xyz = input.col.xyz * d * Light.Diffuse.xyz; // �g�U��
    output.col.xyz += input.col.xyz * Light.Ambient.xyz;    // �A���r�G���g��
    output.col.xyz += Material.Emission.xyz;               // �G�~�b�V���������Z
    output.col.a = input.col.a * Material.Diffuse.a;        // �A���t�@�l��K�p

    // ================================
    // �e�N�X�`�����W�͂��̂܂܎g�p
    // ================================
    output.tex = input.tex;

    return output;
}
