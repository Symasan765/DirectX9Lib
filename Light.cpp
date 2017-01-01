/*=========================================================//
//		�T�v	:	���C�g�������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//=========================================================*/
#include "Light.h"
#include "GameManager.h"


cLight::cLight(){

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
	aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�����̐F

	aLight[0].Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//���ˌ��̐F

	// ���C�g0�̊����̐ݒ�
	aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g0�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.0f, -1.0f, 0.8f);
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