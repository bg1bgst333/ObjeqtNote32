// ��d�C���N���[�h�h�~
#ifndef __MULTI_VIEW_ITEMS_PANEL_H__
#define __MULTI_VIEW_ITEMS_PANEL_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <vector>	// std::vector
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "MultiViewItem.h"	// CMultiViewItem

// �}�N����`
#define MULTI_VIEW_ITEM_ID_START (WM_APP + 100)	// �}���`�r���[�A�C�e����ID�̊J�n��WM_APP + 100�Ƃ���.

// �}���`�r���[�A�C�e���Y�p�l��CMultiViewItemsPanel
class CMultiViewItemsPanel : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		std::vector<CMultiViewItem *> m_vecMultiViewItemList;	// �}���`�r���[�A�C�e�����X�gm_vecMultiViewItemList.
		int m_nNextId;	// �}���`�r���[�A�C�e���̎��������o�����\�[�XID m_nNextId.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CMultiViewItemsPanel();	// �R���X�g���N�^CMultiViewItemsPanel
		virtual ~CMultiViewItemsPanel();	// �f�X�g���N�^~CMultiViewItemsPanel
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual void Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance);	// �A�C�e���𖖔�����ǉ�����֐�Add.
		virtual void Remove();	// �A�C�e���𖖔�����폜����֐�Remove.
		virtual CMultiViewItem * Get(int iIndex);	// �A�C�e�����擾����֐�Get.
		virtual void RemoveAll();	// �S�ẴA�C�e�����폜����֐�RemoveAll.
		virtual size_t GetSize();	// �A�C�e���̐���Ԃ��֐�GetSize.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
		virtual void OnPaint();	// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.

};

#endif