#ifndef INC_BILLBOARD_H
#define INC_BILLBOARD_H
#include "Image3D.h"



//ビルボードを取り扱うクラス
class cBillboard : public cImage3D{
public:
	cBillboard(Texture3D*);
	virtual ~cBillboard();
	virtual void Draw(D3DXVECTOR3 Pos,D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct);
};

#endif