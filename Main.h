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
#include "Image3D.h"
#include "BillBoard.h"
class cCamera;
class cLight;
class cFighter;
class cFlame;

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
	cCamera* pCamera;	//!<　@brief カメラ操作用ポインタ
	cLight* pLight;		//!<　@brief ライト操作用ポインタ
	cFlame* pTex;
	cImage3D* imaage;
};


#endif