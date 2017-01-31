/*=========================================================//
//		�T�v	:	���C�g�������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//=========================================================*/
#include "Light.h"
#include "GameManager.h"
#include "System.h"
#include "Debug.h"
#include <d3dx9.h>


cLight::cLight(){
	time = MORNINNG;
	//R = 255, G = 255, B = 255;
	R = 184, G = 141, B = 194;
	//R = 255, G = 42, B = 0;
	//R = 25, G = 0, B = 120;
	FpsCnt = 0;
	vect = { 0, -0.8f, -0.4f };
}

cLight::~cLight(){

}

void cLight::InitLight(){
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&aLight[0], sizeof(D3DLIGHT9));

	// ���C�g0�̃^�C�v�̐ݒ�
	aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g0�̊g�U���̐ݒ�
	aLight[0].Diffuse = D3DXCOLOR(R / 255.0f, G / 255.0f, B / 255.0f, 1.0f);		//�����̐F

	aLight[0].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//���ˌ��̐F

	// ���C�g0�̊����̐ݒ�
	aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g0�̕����̐ݒ�
	//vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
	vecDir = vect;
	//D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);
	vecDir *= 200.0f;
	aLight[0].Direction = vecDir;

	// ���C�g0�������_�����O�p�C�v���C���ɐݒ�
	GetD3DDevice->SetLight(0, &aLight[0]);

	// ���C�g0���g�p�g�p��Ԃ�
	GetD3DDevice->LightEnable(0, TRUE);

	// ���C�e�B���O���[�h��ON
	GetD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/**
*	@brief ���C�g�̐F�� �� �镗�ɕύX���Ă���
*/
void cLight::DayNightUpdate(const float Second){
	GetConsole->SetPos(0, 1);
	const float frame = (Second * (float)FRAME_RATE) / 10;

	switch (time)
	{
	case MORNINNG:
		printf("��");
		if (NoonChange(frame * 4.0f))
			time = NOON;
		break;
	case NOON:
		printf("��");
		if (EveningChange(frame * 1.0f))
			time = EVENING;
		break;
	case EVENING:
		printf("�[");
		if (NightChange(frame * 4.0f))
			time = NIGHT;
		break;
	case NIGHT:
		printf("��");
		if (MorningChange(frame * 1.0f))
			time = MORNINNG;
		break;
	default:
		break;
	}
}

/**
*	@brief ����Ԃ��璋��Ԃւ̕ύX
*	@param �ϐ��� ������
*/
bool cLight::NoonChange(const float Second){
	const float tB = NOON_B, tG = NOON_G, tR = NOON_R;
	float BlueMove = (MORNINNG_B - tB) / Second;
	float GreenMove = (MORNINNG_G - tG) / Second;
	float RedMove = (MORNINNG_R - tR) / Second;

	if (B < tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B >= tB)
		return true;
	return false;
}

/**
*	@brief ����Ԃ���[����Ԃւ̕ύX
*	@param �ϐ��� ������
*/
bool cLight::EveningChange(const float Second){
	const float tB = EVENING_B, tG = EVENING_G, tR = EVENING_R;
	float BlueMove = (NOON_B - tB) / Second;
	float GreenMove = (NOON_G - tG) / Second;
	float RedMove = (NOON_R - tR) / Second;

	if (B > tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B <= tB)
		return true;
	return false;
}

/**
*	@brief �[����Ԃ�����Ԃւ̕ύX
*	@param �ϐ��� ������
*/
bool cLight::NightChange(const float Second){
	const float tB = NIGHT_B, tG = NIGHT_G, tR = NIGHT_R;
	float BlueMove = (EVENING_B - tB) / Second;
	float GreenMove = (EVENING_G - tG) / Second;
	float RedMove = (EVENING_R - tR) / Second;

	if (B < tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B >= tB)
		return true;
	return false;
}

/**
*	@brief ���Ԃ��璩��Ԃւ̕ύX
*	@param �ϐ��� ������
*/
bool cLight::MorningChange(const float Second){
	const float tB = MORNINNG_B, tG = MORNINNG_G, tR = MORNINNG_R;
	float BlueMove = (NIGHT_B - tB) / Second;
	float GreenMove = (NIGHT_G - tG) / Second;
	float RedMove = (NIGHT_R - tR) / Second;

	if (B < tB){
		B -= BlueMove;
		G -= GreenMove;
		R -= RedMove;
	}
	else{
		B = tB;
		G = tG;
		R = tR;
	}

	if (B >= tB)
		return true;
	return false;
}

D3DCOLOR cLight::GetLightColor(){
	return D3DCOLOR_XRGB((int)R, (int)G, (int)B);
}