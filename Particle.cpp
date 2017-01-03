#include "Particle.h"

/**
*	@brief ���q�̏�����������
*	@param tex �e�N�X�`���|�C���^
*/
cParticle::cParticle(Texture3D* tex) : cBillboard(tex){
	moveVct = { 0, 0, 0 };
	life = 0;
	flag = false;
}

/**
*	@brief �p�[�e�B�N���̊e�ݒ���s��
*	@param pos ���q�����ʒu
*	@param vct �ړ�����
*	@param setLife ��������(�t���[��)
*/
void cParticle::SetParticle(const D3DXVECTOR3 pos, const D3DXVECTOR3 vct, const int setLife){
	SetTrans(pos);	//���W�Z�b�g
	SetScaling(1.0f);
	moveVct = vct;	//�ړ�����
	life = setLife;	//��������
	flag = true;		//�������Ă邼�I
}

/**
*	@brief �`����s���֐�
*	@param InvMtx �J�����t�s��
*/
void cParticle::Draw(D3DXMATRIX* InvMtx,bool SetFlag){
	mtxDate.mtxWorld = *InvMtx * mtxDate.mtxScale * mtxDate.mtxRot * mtxDate.mtxTrans;	//�ʒu
	pTex->SetColor(diffuse);
	pTex->Draw(&mtxDate.mtxWorld,SetFlag);
}

void cParticle::SetColor(D3DCOLOR DIF){
	diffuse = DIF;
}

/**
*	@brief �p�[�e�B�N���X�V����
*	@param �ϐ��� ������
*/
//void cParticle::Update(){
//	if (life > 0){
//		--life;
//		Translation(moveVct);	//�ړ�
//	}
//	else{
//		flag = false;
//	}
//}