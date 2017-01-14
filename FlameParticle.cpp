/**
* @file FlameParticle.cpp
* @brief ���̃p�[�e�B�N���̏������L�q����
* @author ���{�Y�V��
* @date 2017/1/3
*/
#include "Particle.h"
#include "System.h"
#include <new>	//�����t���z��̃R���X�g���N�^��ݒ肷�邽�߂ɕK�v
#include <time.h>

//float frand(unsigned v) {
//	unsigned res = (v >> 9) | 0x3f800000;
//	return (*(float*)&res) - 1.0f;
//}

float frand(unsigned v) {
	v %= 100;
	return (float)v / 100;
}

cFlame::cFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move, Texture3D* bTex, const int num, const float SetR, const float SetHei, const int life, const float setSize){
	orginPos = pos;
	D3DXVec3Normalize(&moveVector, &move);
	pParticleTex = bTex;
	createNum = num / FRAME_RATE;	//
	radius = SetR;
	height = SetHei;	//
	maxLife = life;	//
	size = setSize;
	srand((unsigned)time(NULL));//��������

	//��񂩂烁�����m�ۂ��s��
	particleNo = createNum * maxLife + 1;
	pParticle = new cParticle[particleNo];	//��U�A�����Ȃ��ŏ�����

	// �z���placement new���g���ď���������
	for (int i = 0; i < particleNo; i++) {
		new(pParticle + i) cParticle(pParticleTex);	//�����R���X�g���N�^�Œu������
	}
}

cFlame::~cFlame(){
	for (int i = 0; i < particleNo; i++)
		(pParticle + i)->SetTexNull();
	delete[] pParticle;
	pParticle = nullptr;
	delete pParticleTex;
	pParticle = nullptr;
}

void cFlame::Draw(D3DXVECTOR3 Pos, D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct){
	//�t�s����쐬����
	D3DXVECTOR3 move;
	move = Pos - LookVct;
	move *= -1;

	D3DXMATRIX Inv;
	D3DXMatrixIdentity(&Inv);
	D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3{ 0, 0, 0 }, &move, &UpVct);
	Inv._41 = 0;
	Inv._42 = 0;
	Inv._43 = 0;

	D3DXMatrixInverse(&Inv, NULL, &Inv);

	pParticle->AlphaBlendStart();
	pParticle->Draw(&Inv, true);

	//�`��J�n
	for (int i = 1; i < particleNo; ++i){
		if ((pParticle + i)->flag){
			(pParticle + i)->Scaling(0.9f);
			//(pParticle + i)->Rotation(0.0f, 0.0f, 1.0f);
			(pParticle + i)->Draw(&Inv, false);
		}
	}

	pParticle->AlphaBlendEnd();
}


void cFlame::SetPos(D3DXVECTOR3 pos){
	orginPos = pos;
}

void cFlame::SetMoveVect(D3DXVECTOR3 move){
	D3DXVec3Normalize(&moveVector, &move);
}

void cFlame::Update(){

	//�܂��͌���������̂̈ړ�����
	for (int i = 0; i < particleNo; ++i){
		//�������Ă��邩�H
		if ((pParticle + i)->flag){
			(pParticle + i)->life--;		//�������ԃ}�C�i�X
			(pParticle + i)->Translation((pParticle + i)->moveVct);	//�ړ�

			//�F�ύX
			if ((pParticle + i)->life < maxLife / 10)
				(pParticle + i)->SetColor(D3DCOLOR_XRGB(0xFF, 0x00, 0x00));
			else if ((pParticle + i)->life < maxLife / 5)
				(pParticle + i)->SetColor(D3DCOLOR_XRGB(0xFF, 0x66, 0x00));
			else if ((pParticle + i)->life < maxLife / 8)
				(pParticle + i)->SetColor(D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));

			if ((pParticle + i)->life <= 0)
				(pParticle + i)->flag = false;		//����
		}
	}

	//�V�K�̐���
	for (int crt = 0; crt < createNum; ++crt){
		bool pFlag;
		pFlag = true;
		for (int i = 0; pFlag; ++i){
			//�󂫂��������I
			if ((pParticle + i)->flag == false){
				D3DXVECTOR3 pos = orginPos;
				D3DXVECTOR3 vec = moveVector;
				int setLife = maxLife - (rand() % (maxLife / 2) + (maxLife / 2));
				/*pos.x += (rand() % ((int)radius * 2)) - radius;
				pos.y += (rand() % ((int)radius * 2)) - radius;
				pos.z += (rand() % ((int)radius * 2)) - radius;*/
				if (radius >= 1.0f){
					pos.x += (float)((rand() % ((int)radius * 2)) - radius);
					pos.y += (float)((rand() % ((int)radius * 2)) - radius);
					pos.z += (float)((rand() % ((int)radius * 2)) - radius);
				}
				pos.x += (frand(rand()));
				pos.y += (frand(rand()));
				pos.z += (frand(rand()));


				float ti = height / setLife;
				vec *= ti;

				(pParticle + i)->SetParticle(pos, vec, setLife);
				(pParticle + i)->SetTexSize(size, size);
				pFlag = false;
			}

		}
	}
}