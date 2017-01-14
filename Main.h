/*=========================================================//
//		概要	:	ゲーム処理を記述する
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//				Main.cppはゲームループの中身である。
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
*	MainLoopクラスのコンストラクタはプログラム開始直後に呼ばれ、
*	その後ゲームループとしてupdate関数がループし続けます。 
*	(MainLoopクラス.Update = ゲームループの開始から終了)
*/
class MainLoop : public cGameTrans{
public:
	MainLoop();
	~MainLoop();
	cGameTrans* update(cGameTrans*);
private:
	void draw();
	cGameTrans* pTrans;
	//タイトル
	//ゲームスタート
		//ゲームクリア
		//ゲームオーバー
	//クリア画面
	
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

//タイトル画面の処理
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
	cCamera* pCamera;	//!<　@brief カメラ操作用ポインタ
	cLight* pLight;		//!<　@brief ライト操作用ポインタ
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
	cCamera* pCamera;	//!<　@brief カメラ操作用ポインタ
	cLight* pLight;		//!<　@brief ライト操作用ポインタ
	cXWing* pPlayer;		//プレイヤー機体ポインタ
	cTieManage* pEnemy;
	Texture2D* pHp;
	Texture2D* pLoad;
	Texture2D* pTutolial;
	cImage3D* pBack;
	Texture2D* pKuro1;
	Texture2D* pKuro2;
	int transCnt;			//遷移の時間計測用
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