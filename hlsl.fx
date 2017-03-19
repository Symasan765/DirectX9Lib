// -------------------------------------------------------------
// �g�U��
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------

float4x4 mWVP;
float4x4 mWIT;

float4 vLightDir;							// ���C�g�̕���
float4 vColor;

// ���̋���
float4 I_a = { 0.3f, 0.3f, 0.3f, 0.0f };    // ambient
float4 I_d = { 0.7f, 0.7f, 0.7f, 0.0f };    // diffuse

											// ���˗�
float4 k_a = { 1.0f, 1.0f, 1.0f, 1.0f };    // ambient
float4 k_d = { 0.5f, 0.5f, 0.5f, 1.0f };    // diffuse

											// -------------------------------------------------------------
											// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
											// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Color		: COLOR0;
};
// -------------------------------------------------------------
// �V�[���̕`��
// -------------------------------------------------------------
VS_OUTPUT VS(
	float4 Pos    : POSITION,          // ���[�J���ʒu���W
	float4 Normal : NORMAL            // �@���x�N�g��
) {
	VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^

										 // ���W�ϊ�
	Out.Pos = mul(Pos, mWVP);

	// ���_�F
	float4 L = -vLightDir; // ���[�J�����W�n�ł̃��C�g�x�N�g��
		float amb = L.w;

	float tmp = vColor.w;
		Out.Color = vColor * max(amb, dot(Normal, L));
		Out.Color.w = tmp;
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	return In.Color;
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
