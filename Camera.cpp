/**
* @file Camera.cpp
* @brief �J�����N���X�̏������L�q
* @author ���{�Y�V��
* @date 2017/01/01
*/

#include "Camera.h"
#include "System.h"

/**
*	@brief �R���X�g���N�^�B���W�A�����_�A�������ݒ肷��
*	@param cameraPos �J�����̍��W
*	@param look �����_���W
*	@param up ������x�N�g��
*/
cCamera::cCamera(D3DXVECTOR3 cameraPos, D3DXVECTOR3 look, D3DXVECTOR3 up){
	//�e�평����
	Pos = cameraPos;
	LookPt = look;
	UpVect = up;

	AngleOfView = MAXIMUM_MAGNIFICATION / 2.0f;		//��p���ϒl�ɐݒ�
	ViewScopeMax = 2000;
	ViewScopeMin = 1;
}

/**
*	@brief �f�X�g���N�^�B���̂Ƃ����֐�
*/
cCamera::~cCamera(){};

/**
*	@brief �v���W�F�N�V�����ϊ����s���`�悷��
*	@param device D3D9�f�o�C�X�|�C���^
*/
void cCamera::Projection(const LPDIRECT3DDEVICE9 device){
	//���W�v�Z
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

	//�s�񏉊���
	D3DXMatrixIdentity(&mtxDate.mtxTrans);
	D3DXMatrixIdentity(&mtxDate.mtxRot);
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
	//�����_��]
	D3DXVec3TransformCoord(&LookPt, &LookPt, &mtxDate.mtxRot);
}

/**
*	@brief ���_���S�ɉ�]����B�Ō�ɍ��W��n���΂������N�_�ɉ�]����
*	@param rotX ��]��(�f�O���[)
*	@param rotY ��]��(�f�O���[)
*	@param rotZ ��]��(�f�O���[)
*	@param Pt ��]�̋N�_�ɂȂ���W(�Ȃ��ɂ���Ό��Ă���ʒu�𒆐S�ɉ��)
*/
void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ){
	//�s�����]���������ƁA��x�N�g������]������
	cMatrix::Rotation(rotX, rotY, rotZ);

	//���W�����_�Ɉړ����Čv�Z��A���̈ʒu�ɖ߂�
	Pos.x -= LookPt.x;
	Pos.y -= LookPt.y;
	Pos.z -= LookPt.z;
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxRot);
	Pos.x += LookPt.x;
	Pos.y += LookPt.y;
	Pos.z += LookPt.z;
}


void cCamera::PointRotatMove(const float rotX, const float rotY, const float rotZ,D3DXVECTOR3 Pt){
	//�s�����]���������ƁA��x�N�g������]������
	cMatrix::Rotation(rotX, rotY, rotZ);

	//���W�����_�Ɉړ����Čv�Z��A���̈ʒu�ɖ߂�
	Pos.x -= Pt.x;
	Pos.y -= Pt.y;
	Pos.z -= Pt.z;
	D3DXVec3TransformCoord(&Pos, &Pos, &mtxDate.mtxRot);
	Pos.x += Pt.x;
	Pos.y += Pt.y;
	Pos.z += Pt.z;
}

/**
*	@brief �����_��Ԃ�
*	@return �����_���W
*/
D3DXVECTOR3 cCamera::GetLookPos()const{
	return LookPt;
}