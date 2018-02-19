// ��d�C���N���[�h�h�~
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <string>	// std::string
// �Ǝ��̃w�b�_
#include "MenuWindow.h"	// CMenuWindow
#include "MultiView.h"	// CMultiView
#include "Edit.h"	// CEdit
#include "TextFile.h"	// CTextFile
#include "resource.h"	// ���\�[�X.

// �}�N���̒�`
// UNICODE�؂�ւ�
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// ���C���E�B���h�E�N���XCMainWindow
class CMainWindow : public CMenuWindow{

	// public�����o
	public:

		// public�����o�ϐ�
		CMultiView *m_pMultiView;	// CMultiView�I�u�W�F�N�g�|�C���^m_pMultiView.
		CTextFile *m_pTextFile;	// CTextFile�I�u�W�F�N�g�|�C���^m_pTextFile.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CMainWindow();	// �R���X�g���N�^CMainWindow()
		virtual ~CMainWindow();	// �f�X�g���N�^~CMainWindow()
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��o�[�W����.)
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��, �w�i�u���V�w��o�[�W����.)
		// �����o�֐��o�[�W����.
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		void InitTextFile();	// �e�L�X�g�t�@�C���̏�����.
		void InitMultiView();	// �}���`�r���[�̏�����.
		void ShowTextFile();	// �e�L�X�g�t�@�C���̕\��.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnTimer(UINT_PTR nIDEvent);	// �^�C�}�[�C�x���g������������.
		virtual void OnPaint();	// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
		virtual int OnClose();	// �E�B���h�E�������.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "�J��"��I�����ꂽ���̃n���h��.
		virtual int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "���O��t���ĕۑ�"��I�����ꂽ���̃n���h��.

};

#endif