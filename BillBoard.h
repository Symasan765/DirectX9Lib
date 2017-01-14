/**
* @file BillBoard.h
* @brief �r���{�[�h�̎�舵�����s��
* @author ���{�Y�V��
* @date 2017/1/4
*/
#ifndef INC_BILLBOARD_H
#define INC_BILLBOARD_H
#include "Image3D.h"



//�r���{�[�h����舵���N���X
class cBillboard : public cImage3D{
public:
	cBillboard(Texture3D*);
	virtual ~cBillboard() = default;
	virtual void Draw(D3DXVECTOR3 Pos,D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct);
	void SetTexNull();
};

#endif