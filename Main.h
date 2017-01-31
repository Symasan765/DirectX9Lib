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
class cLight;
class cModel3D;
class cCamera;
class cBillboard;

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
	void draw();
private:
	cLight* pLight;
	cModel3D* pDate;
	cModel3D* pSky;
	cCamera* pCamera;
	cBillboard* pTex;
};


#endif