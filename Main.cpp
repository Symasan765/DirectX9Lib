#include "Main.h"
#include "GameManager.h"
#include "Camera.h"
#include "Light.h"
#include <ctime>
#include "Input.h"


/*===================================================
//	���C������
//	����	��O�̑J�ڃN���X�̃|�C���^���n�����
//	�ߒl	�J�ڂ���ꍇ�A���Ɉڂ�J�ڐ�A�h���X��n��
===================================================*/
cGameTrans* MainLoop::update(cGameTrans* Parent){
	/*=====================���C��������������============================*/
	if (GetKey->Press(DIK_UP))
		pCamera->Rotation(1.0f, 0.0f, 0.0f);
	if (GetKey->Press(DIK_DOWN))
		pCamera->Rotation(-1.0f, 0.0f, 0.0f);
	if (GetKey->Press(DIK_LEFT))
		pCamera->PointRotatMove(0.0f, 1.0f, 0.0f);
	if (GetKey->Press(DIK_RIGHT))
		pCamera->Rotation(0.0f, -1.0f, 0.0f);

	if (GetKey->Press(DIK_RETURN))
		pTex->Translation({ 0.0f, 0.0f, 1.0f });

	draw();		//�`��͎U�炩�邩��draw�ɏ����Ă�
	return this;	//��ԑJ�ڂ��Ȃ���Ύ�����Ԃ�
}

/*===================================================
//	�`�揈��
//	�`��@�\�������ɏ������݁AUpdate�ŌĂяo����OK
===================================================*/
void MainLoop::draw(){
	DrawBegine();	//���炩����Begine�Ɓc

	/*=================�`�揈��===================*/
	pLight->InitLight();
	pCamera->Projection(GetD3DDevice);
	//����Ȃ�����
	D3DXMATRIX wld;
	D3DXMatrixIdentity(&wld);
	pTex->Draw(&wld);

	
	
	/*===========================================*/

	DrawEnd();		//End�������Ă����Ƃ��̊Ԃɏ����������΍ςނ�I
}

/*===================================================
//	����������
//	�Q�[�����Ŏg�p����ϐ��̓w�b�_�[�Œ�`�������ŏ�����
===================================================*/
MainLoop::MainLoop(){
	srand((unsigned)time(NULL));
	pCamera = new cCamera({ 100.0f, 0.0f, -20.0f }, { 100, 0, 0 }, { 0, 1, 0 });		//�J����
	
	pTex = new cBillboard(new Texture3D("004.jpg"));
	pTex->SetTexSize(10.0f, 10.0f);
	pTex->Translation({ 100.0f, 0.0f, 0.0f });


	pLight = new cLight;
}

/*===================================================
//	�������
//	�Q�[�����Ŏg�p�����ϐ��͂��������Еt�����܂��傤�ˁI
===================================================*/
MainLoop::~MainLoop(){
	delete pCamera;
	pCamera = nullptr;

	delete pLight;
	pLight = nullptr;

	delete pTex;
	pTex = nullptr;
}