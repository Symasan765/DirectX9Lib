/**
* @file Particle.h
* @brief �p�[�e�B�N���N���X�W��
* @author ���{�Y�V��
* @date 2017/1/3
*/
#ifndef INC_PARTICLE_H
#define INC_PARTICLE_H

#include "BillBoard.h"

float frand(unsigned v);

/**
*	@brief�@���q����̃f�[�^
*	[��]�Œ���̃��\�b�h�������Ă��܂��B
*/
class cParticle : public cBillboard{
public:
	cParticle(Texture3D*);
	cParticle() :cBillboard(nullptr){};
	void SetParticle(const D3DXVECTOR3,const D3DXVECTOR3,const int);
	void Draw(D3DXMATRIX*,bool = true);
	void SetColor(D3DCOLOR DIF);
	//virtual void Update();
	D3DXVECTOR3 moveVct;	//!<�@@brief �ړ�����
	int life;		//!<�@@brief ��������
	bool flag;		//!<�@@brief �����t���O
	D3DCOLOR diffuse;	//�J���[
};

class cFlame{
public:
	cFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move, Texture3D* bTex, const int num, const float SetR, const float SetHei,const int life,const float setSize);
	~cFlame();
	void Draw(D3DXVECTOR3 Pos, D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct);
	void SetPos(D3DXVECTOR3);
	void SetMoveVect(D3DXVECTOR3);
	void Update();
private:
	cParticle* pParticle;	//!<�@@brief ���q�Q���i�[
	Texture3D* pParticleTex;	//!<�@@brief �e�N�X�`���|�C���^
	D3DXVECTOR3 orginPos;		//!<�@@brief ������
	D3DXVECTOR3 moveVector;	//!<�@@brief �ړ�����
	float radius;			//!<�@@brief ���a
	float height;			//!<�@@brief ����
	float size;			//!<�@@brief �T�C�Y
	int maxLife;			//!<�@@brief �ő吶������
	int createNum;		//!<�@@brief �t���[���Ԃ̔�����
	int particleNo;		//!<�@@brief ���p�[�e�B�N����
};



#endif