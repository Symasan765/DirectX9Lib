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
float3 vEyePos;		//�J�����̈ʒu

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
	float3 N			: TEXCOORD0;
	float3 Eye		: TEXCOORD1;
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
	float tmp = vColor.w;
	float amb = -vLightDir.w;
	float3 L = -vLightDir;
		Out.Color = vColor * max(amb, dot(Normal, -vLightDir));

	Out.N = Normal.xyz;
	Out.Eye = vEyePos - Pos.xyz;

	Out.Color.w = tmp;
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	float3 L = -vLightDir.xyz;
	float3 H = normalize(L + normalize(In.Eye));
	float3 N = normalize(In.N);


	float4 color = In.Color + pow(max(0, dot(N, H)), 100);
	return color;
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
