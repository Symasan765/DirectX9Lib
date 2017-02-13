/**
* @file GameTrans.cpp
* @brief ó‘Ô‘JˆÚ‚Ì‹K’èƒNƒ‰ƒX
* @author ¼–{—Y”V‰î
* @date 2016/12/21
*/
#include "GameTrans.h"
#include "GameManager.h"

/*•`‰æƒXƒ^[ƒg*/
void cGameTrans::DrawBegine(){
	GetD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(17, 98, 154), 1.0f, 0);
	//GetD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(25, 0, 120), 1.0f, 0);

	GetD3DDevice->BeginScene();		//•`‰æŠJŽn
}


/*•`‰æI—¹*/
void cGameTrans::DrawEnd(){
	GetD3DDevice->EndScene();						//•`‰æI—¹
	GetD3DDevice->Present(NULL, NULL, NULL, NULL);
}