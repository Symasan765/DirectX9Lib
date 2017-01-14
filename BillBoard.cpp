/**
* @file BillBoard.cpp
* @brief �r���{�[�h�̎�舵�����s��
* @author ���{�Y�V��
* @date 2017/1/4
*/
#include "BillBoard.h"
#include "Input.h"
#include "GameManager.h"
cBillboard::cBillboard(Texture3D* texture) : cImage3D(texture){

}


void cBillboard::Draw(D3DXVECTOR3 Pos,D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct){
	D3DXVECTOR3 move;
	move = Pos - LookVct;
	move *= -1;
	//�J�����̋t�s����쐬����
	D3DXMatrixIdentity(&mtxDate.mtxRot);
	D3DXMatrixLookAtLH(&mtxDate.mtxRot, &D3DXVECTOR3{ 0, 0, 0 }, &move, &UpVct);
	mtxDate.mtxRot._41 = 0;
	mtxDate.mtxRot._42 = 0;
	mtxDate.mtxRot._43 = 0;

	D3DXMatrixInverse(&mtxDate.mtxRot, NULL, &mtxDate.mtxRot);
	
	
	mtxDate.mtxRot *= mtxDate.mtxScale * mtxDate.mtxTrans;

	pTex->Draw(&mtxDate.mtxRot);
}


void cBillboard::SetTexNull(){
	pTex = nullptr;
}