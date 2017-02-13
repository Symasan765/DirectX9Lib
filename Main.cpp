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
	pTex->SetColor(pLight->GetLightColor());
	return this;	//��ԑJ�ڂ��Ȃ���Ύ�����Ԃ�
}

/*===================================================
//	�`�揈��
//	�`��@�\�������ɏ������݂߂Ύ����ŌĂяo�����
===================================================*/
void MainLoop::draw(){
	/*=================�`�揈��===================*/
	pLight->DayNightUpdate(30);
	pLight->InitLight();
	pCamera->Projection(GetD3DDevice);

	pTex->Draw(pCamera->GetCameraPos(), pCamera->GetLookPos(), pCamera->GetUpVect());
	pDate->Draw(pDate->GetWorldMatrix());
	
	/*===========================================*/
}

/*===================================================
//	����������
//	�Q�[�����Ŏg�p����ϐ��̓w�b�_�[�Œ�`�������ŏ�����
===================================================*/
MainLoop::MainLoop(){
	pDate = new cModel3D;
	pDate->LoadFile("MODEL/F15.x");

	//pSky = new cModel3D;
	//pSky->LoadFile("MODEL/Dome_Y301.x");

	pCamera = new cCamera({ -10, 5, 10 }, { 0, 0, 0 }, { 0, 1, 0 });

	pLight = new cLight;

	pTex = new cBillboard(new Texture3D("IMAGE/Sky.jpg"));
	pTex->SetTexSize(640, 360);
	pTex->SetTrans({ 100, -50, -100 });
}

/*===================================================
//	�������
//	�Q�[�����Ŏg�p�����ϐ��͂��������Еt�����܂��傤�ˁI
===================================================*/
MainLoop::~MainLoop(){
	delete pDate;
	delete pCamera;
	delete pLight;
	delete pTex;
}