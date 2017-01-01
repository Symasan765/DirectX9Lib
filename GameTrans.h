/*=========================================================//
//		概要	:	ゲーム遷移を管理するクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//			ゲーム遷移クラスを記述する
//=========================================================*/
#ifndef INC_GAME_TRANS_H
#define INC_GAME_TRANS_H

//状態遷移クラスの抽象クラス
class cGameTrans{
public:
	cGameTrans(){};
	virtual ~cGameTrans(){};
	virtual cGameTrans* update(cGameTrans*) = 0;
	void DrawBegine();	//描画スタート
	void DrawEnd();		//描画エンド
private:
	virtual void draw() = 0;
};


#endif