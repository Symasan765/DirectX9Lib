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
#include "Image3D.h"
#include "BillBoard.h"
class cCamera;
class cLight;
class cFighter;
class cFlame;

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
private:
	void draw();
	cCamera* pCamera;	//!<�@@brief �J��������p�|�C���^
	cLight* pLight;		//!<�@@brief ���C�g����p�|�C���^
	cFlame* pTex;
	cImage3D* imaage;
};


#endif