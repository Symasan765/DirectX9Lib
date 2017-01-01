/////////////////////////////////////////////////////////////
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)					�@//
//						�쐬���@											  //
//					  �X�V��												  //
/////////////////////////////////////////////////////////////

/*=======================#include========================*/
#include "GameManager.h"
#include "GameTrans.h"
#include "time.h"
#include "Input.h"
cGameManager* cGameManager::pGameManager = nullptr;		//���̃|�C���^��������

/*================================================================================
//									WinMain�֐�													//
================================================================================*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;				//���b�Z�[�W�\����
	cGameManager::Create(hInstance, nCmdShow);	//�C���X�^���X�쐬

	if (!cGameManager::GetInstance()->SystemError)
		return -1;

	/*===============���C�����[�v====================*/
	srand((unsigned)time(NULL));
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0) == 0)		//"WM_QUIT"���b�Z�[�W���擾�����ꍇ0��ԋp
			{
				break;
			}
			//���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&msg);			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
			DispatchMessage(&msg);			//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
		}
		else
		{
			if (cGameManager::GetInstance()->pFrameRate->FrameStart())	//�t���[�����[�g����
			{
				GetKey->UpdateKeyboard();
				GetGameManager->GameLoop->update(GetGameManager->GameLoop);	//�Q�[�����[�v����
			}
		}
	}

	//DirectX�I�������֐�
	cGameManager::GetInstance()->Destroy();
	return (int)msg.wParam;
}