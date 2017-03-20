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

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Color		: COLOR0;
	float3 N			: TEXCOORD0;
	float3 X		: TEXCOORD1;
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

	// �g�U���{����
	float tmp = vColor.w;
	float amb = -vLightDir.w;	// �����̋���
	float3 L = -vLightDir; // ���[�J�����W�n�ł̃��C�g�x�N�g��
		Out.Color = vColor * max(amb, dot(Normal, -vLightDir));

	// ���ʔ��˗p�̃x�N�g��
	Out.N = Normal.xyz;
	Out.X = Pos.xyz;

	Out.Color.w = tmp;
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{
	float3 L = -vLightDir.xyz;				// ���C�g�x�N�g��
	float3 N = normalize(In.N);				// �@���x�N�g��
	float3 V = normalize(vEyePos - In.X);	// �����x�N�g��
	float3 H = normalize(L + V);			// �n�[�t�x�N�g��

	// �v�Z�Ɏg�����ꂼ��̊p�x
	float NV = dot(N, V);
	float NH = dot(N, H);
	float VH = dot(V, H);
	float NL = dot(N, L);
	float LH = dot(L, H);

	// Beckmann ���z�֐�
	const float m = 0.3f;// �r��
	float NH2 = NH*NH;
	float D = exp(-(1 - NH2) / (NH2*m*m)) / (4 * m*m*NH2*NH2);

	// �􉽌�����
	float G = min(1, min(2 * NH*NV / VH, 2 * NH*NL / VH));

	// �t���l��
	float n = 6.5f;//						 ���˂�����̗ʓI�Ȋ���
	float g = sqrt(n*n + LH*LH - 1);
	float gpc = g + LH;
	float gnc = g - LH;
	float cgpc = LH*gpc - 1;
	float cgnc = LH*gnc + 1;
	float F = 0.5f*gnc*gnc*(1 + cgpc*cgpc / (cgnc*cgnc)) / (gpc*gpc);	//���̐擪�̒萔�Ŕ��˂̑傫���ς��

	// �����̐F
	float4 ks = { 2.0f*0.45f, 2.0f*0.45f, 2.0f*0.45f, 1.0f };		//�����ŐF�ς��

		return In.Color						// �g�U���{����
		+ ks * max(0, F*D*G / NV);	// ���ʔ��ˌ�
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}