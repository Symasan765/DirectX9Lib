#include "GameTrans.h"
#include "GameManager.h"

/*�`��X�^�[�g*/
void cGameTrans::DrawBegine(){
	GetD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(17, 98, 154), 1.0f, 0);

	GetD3DDevice->BeginScene();		//�`��J�n
}


/*�`��I��*/
void cGameTrans::DrawEnd(){
	GetD3DDevice->EndScene();						//�`��I��
	GetD3DDevice->Present(NULL, NULL, NULL, NULL);
}