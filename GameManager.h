/*=========================================================//
//		�T�v	:	�Q�[���S�̂��Ǘ�����N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//			�Q�[���}�l�[�W���[�N���X���L�q����
//=========================================================*/
#ifndef INC_GAME_MANAGER_H
#define INC_GAME_MANAGER_H
#include <Windows.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

/*=======================�悭�g���̂͂�������============================*/
#define GetGameManager cGameManager::GetInstance()							//�N���X�̎��̂��擾����
#define GetD3DDevice cGameManager::GetInstance()->GetD3dDevice()		//pD3DDevice���擾����
#define GetWindHandle cGameManager::GetInstance()->GethWnd()				//�E�B���h�E�n���h�����擾����
#define GetHINSTANCE cGameManager::GetInstance()->GetHInstance()		//HInstance���擾����
/*=================================================================*/

class cFrameRateCtrl;	//�t���[������N���X
class cGameTrans;		//��ԑJ�ڃN���X
class DebugFont;			//�f�o�b�O�����N���X

class cGameManager{
public:
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	static cGameManager* GetInstance();							//�C���X�^���X�������C���X�^���X�Q�b�g

	LPDIRECT3DDEVICE9& GetD3dDevice();
	HWND& GethWnd();
	HINSTANCE& GetHInstance();
	//�V���O���g���ݒ�
	cGameManager(const cGameManager&) = delete;					//�R�s�[�R���X�g���N�^�� delete �w��
	cGameManager& operator=(const cGameManager&) = delete;	//�R�s�[������Z�q�� delete �w��
	cGameManager(cGameManager&&) = delete;						//���[�u�R���X�g���N�^�� delete �w��
	cGameManager& operator=(cGameManager&&) = delete;			//���[�u������Z�q�� delete �w��
private:
	cGameManager(){};
	void cGameManager::Init(HINSTANCE arghInstance, int argnCmdShow);	//DX������
	~cGameManager();																//DX���
	static void Create(HINSTANCE arghInstance, int argnCmdShow);			//�쐬
	static  void Destroy();														//���
	HRESULT InitD3D(HWND);

	/*==================�Ǘ��������̂���===================*/
	static cGameManager* pGameManager;		//�z���̗͂��Ȃ�������̎���
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;
	HWND hWnd;
	HINSTANCE hInstance;
	int nCmdShow;
	bool SystemError;							//���������ɃG���[���o�����ێ�

	cFrameRateCtrl* pFrameRate;				//�t���[������
	cGameTrans* GameLoop;						//�ŏ�ʑJ��
};

//�t���[�����[�g����
class cFrameRateCtrl{
public:
	cFrameRateCtrl();
	bool FrameStart();
private:
	float fpsDispCnt;		//��FPS�\���p�J�E���^�[
	const float frameTime;	//1�t���[���̎���
	int fpsCnt;
	DWORD oldTime;			//1�t���[���O�̌v������
	DWORD nowTime;			//���t���[���v������
	DWORD frameCnt;			//�t���[�����[�g�J�E���g
};

#endif