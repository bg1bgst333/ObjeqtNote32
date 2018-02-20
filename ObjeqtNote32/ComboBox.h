// ��d�C���N���[�h�h�~
#ifndef __COMBO_BOX_H__
#define __COMBO_BOX_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl

// �R���{�{�b�N�X�R���g���[���N���XCComboBox
class CComboBox : public CCustomControl{

	// public�����o
	public:

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CComboBox();	// �R���X�g���N�^CComboBox
		virtual ~CComboBox();	// �f�X�g���N�^~CComboBox
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		void AddString(LPCTSTR lpctszStr);	// �R���{�{�b�N�X�ɕ������ǉ�����֐�AddString.
		void SetCurSel(int iIndex);	// �R���{�{�b�N�X�̎w��̃C���f�b�N�X�v�f��I��SetCurSel.
		int GetCurSel();	// �R���{�{�b�N�X�őI������Ă���v�f�̃C���f�b�N�X��Ԃ�GetCurSel.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.

};

#endif