#ifndef INC_BILLBOARD_H
#define INC_BILLBOARD_H
#include "Image3D.h"



//�r���{�[�h����舵���N���X
class cBillboard : public cImage3D{
public:
	cBillboard(Texture3D*);
	virtual ~cBillboard();
	virtual void Draw(D3DXMATRIX*);
private:
};

#endif