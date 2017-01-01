/*=========================================================//
//		�T�v	:	���͏������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//=========================================================*/
#include "Input.h"
#include "GameManager.h"
#define DIRECTINPUT_VERSION 0x0800

//���̃t�@�C������B�؂�
namespace{
	const int NUM_KEY_MAX = 256;
	LPDIRECTINPUT8			pDInput = NULL;						// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8	pDIDevKeyboard = NULL;				// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
	LPDIRECTINPUTDEVICE8	pDIDevMouse = NULL;					// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�}�E�X)
	BYTE						keyState[NUM_KEY_MAX];				// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE						keyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE						keyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE						keyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	int							keyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
	DIMOUSESTATE2			mouseState;							// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	DIMOUSESTATE2			mouseStateTrigger;					// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	POINT						MousePoint;							// �}�E�X�̌��ݍ��W
}
using namespace Input;

cKeyboard::cKeyboard(){
	HRESULT hr;
	if (!pDInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(GetHINSTANCE, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&pDInput, NULL);
	}
	InitKeyboard(GetHINSTANCE,GetWindHandle);
}

HRESULT cKeyboard::InitKeyboard(HINSTANCE hInst, HWND hWnd){
	HRESULT hr = 0;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = pDInput->CreateDevice(GUID_SysKeyboard, &pDIDevKeyboard, NULL);
	if (FAILED(hr) || pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	pDIDevKeyboard->Acquire();

	return S_OK;
}

HRESULT cKeyboard::UpdateKeyboard(void){
	HRESULT hr;
	BYTE keyStateOld[256];

	// �O��̃f�[�^��ۑ�
	memcpy(keyStateOld, keyState, NUM_KEY_MAX);

	// �f�o�C�X����f�[�^���擾
	hr = pDIDevKeyboard->GetDeviceState(sizeof(keyState), keyState);
	if (SUCCEEDED(hr))
	{
		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			// �g���K�[�ƃ����[�X���擾
			keyStateTrigger[cnt] = (keyState[cnt] ^ keyStateOld[cnt]) & keyState[cnt];
			keyStateRelease[cnt] = (keyState[cnt] ^ keyStateOld[cnt]) & keyStateOld[cnt];

			// �L�[��������Ă���Ȃ烊�s�[�g�̔��菈��
			if (keyState[cnt])
			{
				if (keyStateRepeatCnt[cnt] < 20)
				{
					keyStateRepeatCnt[cnt]++;
					// �u������́v�������́u�{�^���������Ă���20�t���[���o�߁v
					// �����ꍇ�A���s�[�g�p�z��̃f�[�^��L���ɂ���
					// ��L�����ȊO�̓��s�[�g�p�z��̃f�[�^�𖳌��ɂ���
					if (keyStateRepeatCnt[cnt] == 1 || keyStateRepeatCnt[cnt] >= 20) {
						keyStateRepeat[cnt] = 0x80;
					}
					else {
						keyStateRepeat[cnt] = 0;
					}
				}
			}
			else
			{
				keyStateRepeatCnt[cnt] = 0;
				keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		hr = pDIDevKeyboard->Acquire();
	}

	return hr;
}

void cKeyboard::UninitKeyboard(void){
	if (pDIDevKeyboard)
	{
		pDIDevKeyboard->Unacquire();

		pDIDevKeyboard->Release();
		pDIDevKeyboard = nullptr;
	}
}

cKeyboard::~cKeyboard(){
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	if (pDInput){
		pDInput->Release();
		pDInput = nullptr;
	}
}

bool cKeyboard::Press(int key){
	return ((keyState[key] & 0x80) != 0);
}

bool cKeyboard::Trigger(int key){
	return ((keyStateTrigger[key] & 0x80) != 0);
}