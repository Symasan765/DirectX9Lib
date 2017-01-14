/**
* @file Camera.cpp
* @brief �J�����N���X�̏������L�q
* @author ���{�Y�V��
* @date 2017/01/01
*/

#include "Camera.h"
#include "System.h"
#include <math.h>

/**
* @def PI
* @brief �~����
*/
#define PI (3.14159)

/**
*	@brief �R���X�g���N�^�B���W�A�����_�A�������ݒ肷��
*	@param cameraPos �J�����̍��W
*	@param look �����_���W
*	@param up ������x�N�g��
*/
cCamera::cCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 look, D3DXVECTOR3 up){
	//�e�평����
	Translation(cameraPos);
	LookPt = look;
	UpVect = up;

	AngleOfView = MAXIMUM_MAGNIFICATION / 2.0f;		//��p���ϒl�ɐݒ�
	ViewScopeMax = 10000;
	ViewScopeMin = 5;
}

/**
*	@brief �v���W�F�N�V�����ϊ����s���`�悷��
*	@param device D3D9�f�o�C�X�|�C���^
*/
void cCamera::Projection(const LPDIRECT3DDEVICE9 device){
	//���W�v�Z
	D3DXVECTOR3 Pos(0.0f,0.0f,0.0f);
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxTrans);		//���W�ʒu���Z�o

	D3DXMatrixIdentity(&mtxDate.mtxWorld);
	D3DXMatrixLookAtLH(&mtxDate.mtxWorld, &Pos, &LookPt, &UpVect);
	device->SetTransform(D3DTS_VIEW, &mtxDate.mtxWorld);

	D3DXMATRIX mxPrj;

	//�J�����̍\�}�ϊ�
	D3DXMatrixPerspectiveFovLH(&mxPrj, D3DXToRadian(AngleOfView), (float)WINDOW_SCREEN_X / (float)WINDOW_SCREEN_Y, ViewScopeMin, ViewScopeMax);
	device->SetTransform(D3DTS_PROJECTION, &mxPrj);


	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //=================================================
	device->SetRenderState(D3DRS_LIGHTING, false);		//������===============================
}

/**
*	@brief �s��N���X���I�[�o�[���C�h�B�Y�[�������ɑ���
*	@param rate �g�嗦
*/
void cCamera::Scaling(const float rate){
	AngleOfView -= (rate / 10);
	if (AngleOfView > MAXIMUM_MAGNIFICATION)
		AngleOfView = MAXIMUM_MAGNIFICATION;
	if (AngleOfView < MINIMUM_MAGNIFICATION)
		AngleOfView = MINIMUM_MAGNIFICATION;
}

/**
*	@brief �����_��ݒ肷��֐�
*	@param look �����_���W
*/
void cCamera::SetLookPos(D3DXVECTOR3 look){
	LookPt = look;
}

/**
*	@brief ��]�����B��x�N�g���̉�]���܂ށBFPS���_����
*	@param rotX X������]��(�f�O���[)
*	@param rotY Y������]��(�f�O���[)
*	@param rotZ Z������]��(�f�O���[)
*/
void cCamera::Rotation(const float rotX, const float rotY, const float rotZ){
	//�s�����]���������ƁA��x�N�g������]������
	cMatrix::Rotation(rotX, rotY, rotZ);
	//�������]
	D3DXVec3TransformCoord(&UpVect, &UpVect, &mtxDate.mtxRot);
	//�����_��]�B�����_�����_�Ɉړ����������ƂŌ��̈ʒu�ɖ߂�
	//LookPt -= Pos;
	D3DXVec3TransformCoord(&LookPt, &LookPt, &mtxDate.mtxRot);
	//LookPt += Pos;
}

/**
*	@brief ���_���S�ɉ�]����B�Ō�ɍ��W��n���΂������N�_�ɉ�]����(TPS����)
*	@param rotX ��]��(�f�O���[)
*	@param rotY ��]��(�f�O���[)
*	@param rotZ ��]��(�f�O���[)
*	@param Pt ��]�̋N�_�ɂȂ���W(�Ȃ��ɂ���Ό��Ă���ʒu�𒆐S�ɉ��)
*/
void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ){
	
	cMatrix::Rotation(rotX, rotY, rotZ);	//��]
	UpVect = { 0, 1, 0 };
	D3DXVec3TransformCoord(&UpVect, &UpVect, &mtxDate.mtxRot);
	//���ꂼ��ɉ����ĔC�Ӊ�]
	if (rotX)
		RotationAxisX(LookPt, rotX);
	if (rotY)
		RotationAxisY(LookPt, rotY);
	if (rotZ)
		RotationAxisZ(LookPt, rotZ);
}


void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ, D3DXVECTOR3 Pt){
	cMatrix::Rotation(rotX, rotY, rotZ);	//��]

	//���ꂼ��ɉ����ĔC�Ӊ�]
	if (rotX)
		RotationAxisX(Pt, rotX);
	if (rotY)
		RotationAxisY(Pt, rotY);
	if (rotZ)
		RotationAxisZ(Pt, rotZ);
}

/**
*	@brief �����_��Ԃ�
*	@return �����_���W
*/
D3DXVECTOR3 cCamera::GetLookPos()const{
	return LookPt;
}

/**
*	@brief �������Ԃ�
*	@return �����_���W
*/
D3DXVECTOR3 cCamera::GetUpVect()const{
	return UpVect;
}

/**
*	@brief �J�������W��Ԃ�
*	@return �J�������W
*/
D3DXVECTOR3 cCamera::GetCameraPos()const{
	D3DXVECTOR3 Pos(0,0,0);
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxTrans);
	return Pos;
}

/**
*	@brief �C�ӎ���]�ړ�
*	@param tag ��]���S
*	@param dgr ��]�p
*/
void cCamera::RotationAxisX(const D3DXVECTOR3& tag, const float dgr){
	//�C�ӎ��쐬
	D3DXVECTOR3 rot(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&rot, &rot, &mtxDate.mtxRot);

	//�����_�����_�ɃJ�������ړ�
	Translation({ -tag.x, -tag.y, -tag.z });
	D3DXMATRIX rotMt;
	D3DXMatrixRotationAxis(&rotMt, &rot, D3DXToRadian(dgr));
	mtxDate.mtxTrans *= rotMt;
	Translation({ tag.x, tag.y, tag.z });
}

/**
*	@brief �C�ӎ���]�ړ�
*	@param tag ��]���S
*	@param dgr ��]�p
*/
void cCamera::RotationAxisY(const D3DXVECTOR3& tag, const float dgr){
	//�C�ӎ��쐬
	D3DXVECTOR3 rot(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformCoord(&rot, &rot, &mtxDate.mtxRot);

	//�����_�����_�ɃJ�������ړ�
	Translation({ -tag.x, -tag.y, -tag.z });
	D3DXMATRIX rotMt;
	D3DXMatrixRotationAxis(&rotMt, &rot, D3DXToRadian(dgr));
	mtxDate.mtxTrans *= rotMt;
	Translation({ tag.x, tag.y, tag.z });
}

/**
*	@brief �C�ӎ���]�ړ�
*	@param tag ��]���S
*	@param dgr ��]�p
*/
void cCamera::RotationAxisZ(const D3DXVECTOR3& tag, const float dgr){
	//�C�ӎ��쐬
	D3DXVECTOR3 rot(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformCoord(&rot, &rot, &mtxDate.mtxRot);

	//�����_�����_�ɃJ�������ړ�
	Translation({ -tag.x, -tag.y, -tag.z });
	D3DXMATRIX rotMt;
	D3DXMatrixRotationAxis(&rotMt, &rot, D3DXToRadian(dgr));
	mtxDate.mtxTrans *= rotMt;
	Translation({ tag.x, tag.y, tag.z });
}


D3DXMATRIX* cCamera::GetWorldMatrix(){
	return &mtxDate.mtxWorld;
}