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
class Texture2D;
class cCamera;
class cLight;
class xFileClass;
class cImage3D;
class cModel3D;
class cBillboard;
class cXWing;
class cTieManage;

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
	cGameTrans* pTrans;
	//�^�C�g��
	//�Q�[���X�^�[�g
		//�Q�[���N���A
		//�Q�[���I�[�o�[
	//�N���A���
	
};

class cCurtain : public cGameTrans{
public:
	cCurtain();
	~cCurtain();
	cGameTrans* update(cGameTrans*);
	void draw();
private:
	int transCnt;
	bool transFlag;
	Texture2D* pTex;
	Texture2D* pPush;
	Texture2D* pDesc;
};

//�^�C�g����ʂ̏���
class Title : public cGameTrans{
public:
	Title();
	virtual ~Title();
	cGameTrans* update(cGameTrans*);
private:
	void draw();
	Texture2D* pTex;
	Texture2D* pKuro1;
	Texture2D* pKuro2;
	cCamera* pCamera;	//!<�@@brief �J��������p�|�C���^
	cLight* pLight;		//!<�@@brief ���C�g����p�|�C���^
	cImage3D* image;
	cImage3D* pLogo;
	cModel3D* pDate;
	cModel3D* pSky;
	cBillboard* pTitle;
	cBillboard* pDeathStar;
	cBillboard* pPush;
	bool titleFlag;
};

class MainGame : public cGameTrans{
public:
	MainGame();
	~MainGame();
	cGameTrans* update(cGameTrans*);
	void draw();
	void GroundDraw();
private:
	enum Trans{
		Set = 0,
		Move,
		Game
	};
	D3DXVECTOR3 cameraMove;
	Trans trans;
	cCamera* pCamera;	//!<�@@brief �J��������p�|�C���^
	cLight* pLight;		//!<�@@brief ���C�g����p�|�C���^
	cXWing* pPlayer;		//�v���C���[�@�̃|�C���^
	cTieManage* pEnemy;
	Texture2D* pHp;
	Texture2D* pLoad;
	Texture2D* pTutolial;
	cImage3D* pBack;
	Texture2D* pKuro1;
	Texture2D* pKuro2;
	int transCnt;			//�J�ڂ̎��Ԍv���p
};


class clear : public cGameTrans{
public:
	clear();
	~clear();
	cGameTrans* update(cGameTrans*);
	void draw();
private:
	Texture2D* pTex;
	Texture2D* pPush;
};


#endif