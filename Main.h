/*=========================================================//
//		�T�v	:	�Q�[���������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//				Main.cpp�̓Q�[�����[�v�̒��g�ł���B
//=========================================================*/
#ifndef INC_MAIN_H
#define INC_MAIN_H
#include "GameTrans.h"
#include <d3dx9.h>
class cLight;
class cModel3D;
class cCamera;
class cBillboard;

/**
*	MainLoop�N���X�̃R���X�g���N�^�̓v���O�����J�n����ɌĂ΂�A
*	���̌�Q�[�����[�v�Ƃ���update�֐������[�v�������܂��B 
*	(MainLoop�N���X.Update = �Q�[�����[�v�̊J�n����I��)
*/
class MainLoop : public cGameTrans{
public:
	MainLoop();
	~MainLoop();
	cGameTrans* update(cGameTrans*);
	void draw();
private:
	cLight* pLight;
	cModel3D* pDate;
	cModel3D* pSky;
	cCamera* pCamera;
	cBillboard* pTex;
};


#endif