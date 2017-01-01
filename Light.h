/*=========================================================//
//		概要	:	ライト処理を記述する
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//	
//=========================================================*/
#ifndef INC_LIGHT_H
#define INC_LIGHT_H

#include <Windows.h>
#include <d3dx9.h>

class cLight{
public:
	cLight();
	~cLight();
	void InitLight();
private:
	D3DLIGHT9 aLight[2];
};



#endif