#include "Main.h"
#include "Debug.h"
#include "Input.h"
#include "XfileDX9.h"
#include "Camera.h"
#include "Light.h"
#include "BillBoard.h"
#include "GameManager.h"

/*===================================================
//	���C������
//	����	��O�̑J�ڃN���X�̃|�C���^���n�����
//	�ߒl	�J�ڂ���ꍇ�A���Ɉڂ�J�ڐ�A�h���X��n��
===================================================*/
cGameTrans* MainLoop::update(cGameTrans* Parent){
	/*=====================���C��������������============================*/
	if (GetKey->Press(DIK_LEFT)){
		pCamera->PointRotatMove(0.0f, 1.0f, 0.0f);
	}
	else if (GetKey->Press(DIK_RIGHT)){
		pCamera->PointRotatMove(0.0f, -1.0f, 0.0f);
	}
	else if (GetKey->Press(DIK_UP)){
		pCamera->PointRotatMove(1.0f, 0.0f, 0.0f);
	}
	else if (GetKey->Press(DIK_DOWN)){
		pCamera->PointRotatMove(-1.0f, 0.0f, 0.0f);
	}
	
	return this;	//��ԑJ�ڂ��Ȃ���Ύ�����Ԃ�
}

/*===================================================
//	�`�揈��
//	�`��@�\�������ɏ������݂߂Ύ����ŌĂяo�����
===================================================*/
void MainLoop::draw(){
	/*=================�`�揈��===================*/
	pCamera->Projection(GetD3DDevice);
	D3DXMATRIX buf;
	D3DXMatrixIdentity(&buf);
	pShader->Draw(&buf,pCamera->GetWorldMatrix(),pCamera->GetPrjMatrix());
	//pShader->Draw(&buf);
	/*===========================================*/
}

/*===================================================
//	����������
//	�Q�[�����Ŏg�p����ϐ��̓w�b�_�[�Œ�`�������ŏ�����
===================================================*/
MainLoop::MainLoop(){
	pShader = new cMetalReflection();

	pCamera = new cCamera({ 0.0f, 10.0f, -10.0f }, { 0, 0, 0 }, { 0, 1, 0 });
}

/*===================================================
//	�������
//	�Q�[�����Ŏg�p�����ϐ��͂��������Еt�����܂��傤�ˁI
===================================================*/
MainLoop::~MainLoop(){
	
}