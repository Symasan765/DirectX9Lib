/*=========================================================//
//		�T�v	:	���C�g�������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
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