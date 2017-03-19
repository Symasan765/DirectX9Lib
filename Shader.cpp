#include "XfileDX9.h"
#include "GameManager.h"
#include "Debug.h"

Shader::Shader(){
	//�V�F�[�_�t�@�C���̓ǂݍ���
	HRESULT hr;
	D3DXVECTOR4 offset;

	m_pEffect = NULL;
	m_hTechnique = NULL;
	m_hmWVP = NULL;
	m_hmWIT = NULL;
	m_hvLightDir = NULL;
	m_hvEyePos = NULL;

	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER pErr = NULL;
	if (FAILED(hr = D3DXCreateEffectFromFile(
		GetD3DDevice, "hlsl.fx", NULL, NULL,
		0, NULL, &m_pEffect, &pErr)))
	{
		// �V�F�[�_�̓ǂݍ��݂̎��s
		MessageBox(NULL, (LPCTSTR)pErr->GetBufferPointer()
			, "ERROR", MB_OK);
	}
	else{
		m_hTechnique = m_pEffect->GetTechniqueByName("TShader");				//�e�N�j�b�N�̓ǂݍ���
		m_hmWVP = m_pEffect->GetParameterByName(NULL, "mWVP");				//mWVP�ւ̃n���h�����擾
		m_hmWIT = m_pEffect->GetParameterByName(NULL, "mWIT");				//mWIT�ւ̃n���h�����擾
		m_hvLightDir = m_pEffect->GetParameterByName(NULL, "vLightDir");	//vLightDir�ւ̃n���h���擾
		m_hvCol = m_pEffect->GetParameterByName(NULL, "vColor");				//vColor�ւ̃n���h���擾
		m_hvEyePos = m_pEffect->GetParameterByName(NULL, "vEyePos");
	}
	if (pErr)
		pErr->Release();

	LoadFile("MODEL/F15.x");
}

Shader::~Shader(){
	m_pEffect->Release();
}

void Shader::Draw(D3DXMATRIX* wtx, D3DXMATRIX* iew, D3DXMATRIX* mroj){
	D3DXVECTOR3 cameraPos(0, 20, -20);
	D3DXVECTOR3 cameraLook(0, 0, 0);
	D3DXVECTOR3 cameraUp(0, 1, 0);

	D3DXMATRIX m_mView;
	D3DXMatrixLookAtLH(&m_mView, &cameraPos, &cameraLook, &cameraUp);
	m_mView = *iew;

	D3DXMATRIX m_mProj;
	D3DXMatrixPerspectiveFovLH(&m_mProj, D3DXToRadian(45), (float)640 / (float)480, 1, 10000);
	//m_mProj = *mroj;


	D3DXMATRIX m, mT, mR;
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	D3DXVECTOR4 v, light_pos;

	// �s��̐ݒ�
	GetD3DDevice->SetTransform(D3DTS_WORLD, &mWorld);

	//xFileClass::Draw(&mWorld);

	if (m_pEffect != NULL)
	{
		//-------------------------------------------------
		// �V�F�[�_�̐ݒ�
		//-------------------------------------------------
		m_pEffect->SetTechnique(m_hTechnique);
		m_pEffect->Begin(NULL, 0);
		
		GetD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);

		//-------------------------------------------------
		// ��s���f���̕`��
		//-------------------------------------------------
		GetD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		GetD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

		D3DXMatrixIdentity(&mWorld);
		D3DXMatrixTranslation(&m, 1.0f, 0.0f, 0.0f);
		D3DXMatrixRotationY(&mR, D3DXToRadian(180));
		D3DXMatrixTranslation(&mT, 1.0f, 1.2f, 0.0f);
		mWorld = m * mR * mT;

		// ���[�J��-�ˉe�ϊ��s��
		D3DXMatrixInverse(&m, NULL, &mWorld);
		D3DXMatrixTranspose(&m, &m);
		m_pEffect->SetMatrix(m_hmWIT, &m);
		// ���[�J��-�ˉe�ϊ��s��
		m = mWorld * m_mView * m_mProj;
		m_pEffect->SetMatrix(m_hmWVP, &m);

		// ���C�g�̕���
		light_pos = D3DXVECTOR4(-0.577f, -0.577f, -0.577f, 0);
		D3DXMatrixInverse(&m, NULL, &mWorld);
		D3DXVec4Transform(&v, &light_pos, &m);
		D3DXVec3Normalize((D3DXVECTOR3 *)&v, (D3DXVECTOR3 *)&v);
		v.w = -0.3f;
		m_pEffect->SetVector(m_hvLightDir, &v);

		//���_��n��
		m = mWorld * m_mView;
		D3DXMatrixInverse(&m, NULL, &m);
		v = D3DXVECTOR4(0, 0, 0, 1);
		D3DXVec4Transform(&v, &v, &m);
		m_pEffect->SetVector(m_hvEyePos, &v);

		pD3DXMat = (D3DXMATERIAL*)pd3dxBuffer->GetBufferPointer();
		HRESULT hr = 0;
		for (int i = 0; i<numMatModel; i++) {
			v.x = pD3DXMat[i].MatD3D.Diffuse.r / 1.3f;
			v.y = pD3DXMat[i].MatD3D.Diffuse.g / 1.3f;
			v.z = pD3DXMat[i].MatD3D.Diffuse.b / 1.3f;
			v.w = pD3DXMat[i].MatD3D.Diffuse.a;
			hr = m_pEffect->SetVector(m_hvCol, &v);
			m_pEffect->BeginPass(0);
			pd3dxMesh->DrawSubset(i);  // �`��
			m_pEffect->EndPass();
		}
		
		m_pEffect->End();
	}
}