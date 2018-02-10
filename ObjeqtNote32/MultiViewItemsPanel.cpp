// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MultiViewItemsPanel.h"	// CMultiViewItemsPanel

// �R���X�g���N�^CMultiViewItemsPanel
CMultiViewItemsPanel::CMultiViewItemsPanel() : CUserControl(){

	// �����o�̏�����.
	m_vecMultiViewItemList.clear();	// m_vecMultiViewItemList.clear�ŃN���A.
	m_nNextId = 0;	// m_nNextId��0�ŏ�����.

}

// �f�X�g���N�^~CMultiViewItemsPanel
CMultiViewItemsPanel::~CMultiViewItemsPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMultiViewItemsPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CMultiViewItemsPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CMultiViewItemsPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CMultiViewItemsPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CMultiViewItemsPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CMultiViewItemsPanel::Destroy(){

	// �}���`�r���[�A�C�e�����X�g�̏I������.
	m_vecMultiViewItemList.clear();	// m_vecMultiViewItemList.clear�ŃN���A.
	m_nNextId = 0;	// m_nNextId��0���Z�b�g.

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �A�C�e���𖖔�����ǉ�����֐�Add.
void CMultiViewItemsPanel::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// �}���`�r���[�A�C�e���̒ǉ�.
	CMultiViewItem *pMultiViewItem = new CMultiViewItem();	// CMultiViewItem�I�u�W�F�N�g�𐶐���, �|�C���^��pMultiViewItem�Ɋi�[.
	pMultiViewItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, m_hWnd, (HMENU)(MULTI_VIEW_ITEM_ID_START + m_nNextId), hInstance);	// pMultiViewItem->Create�ŃA�C�e���쐬.
	m_vecMultiViewItemList.push_back(pMultiViewItem);	// m_vecMultiViewItemList.push_back�Ŗ����ɒǉ�.
	m_nNextId++;	// m_nNextId���C���N�������g.
	
}

// �A�C�e���𖖔�����폜����֐�Remove.
void CMultiViewItemsPanel::Remove(){

	// �}���`�r���[�A�C�e���̍폜.
	CMultiViewItem *pMultiViewItem = m_vecMultiViewItemList[m_vecMultiViewItemList.size() - 1];	// �����v�f���擾.
	delete pMultiViewItem;	// delete��pMultiViewItem�̍폜.
	m_vecMultiViewItemList.pop_back();	// m_vecMultiViewItemList.pop_back�Ń��X�g��1���炷.
	m_nNextId--;

}

// �S�ẴA�C�e�����폜����֐�RemoveAll.
void CMultiViewItemsPanel::RemoveAll(){

	// �A�C�e���̐������J��Ԃ�.
	size_t n = GetSize();	// GetSize�ŃT�C�Y���擾��, n�Ɋi�[.
	for (size_t i = 0; i < n; i++){	// n�̐������J��Ԃ�.
		Remove();	// Remove�Ŗ������폜.
	}

}

// �A�C�e���̐���Ԃ��֐�GetSize.
size_t CMultiViewItemsPanel::GetSize(){

	// �A�C�e���̗v�f����Ԃ�.
	return m_vecMultiViewItemList.size();	// m_vecMultiViewItemList.size�ŗv�f����Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMultiViewItemsPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMultiViewItemsPanel::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�N���X��OnDestroy���Ă�.
	CUserControl::OnDestroy();	// CUserControl::OnDestroy���Ă�.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CMultiViewItemsPanel::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));	// CreatePen�Ő�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0));		// CreateSolidBrush�Ő�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �Ԃ̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �Ԃ̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
	// �y���ƃu���V�̕���
	SelectObject(hDC, hOldBrush);		// �Â��u���V��I��.
	SelectObject(hDC, hOldPen);		// �Â��y����I��.

	// �y���ƃu���V�̔j��.
	DeleteObject(hBrush);	// �u���V�̔j��.
	DeleteObject(hPen);	// �y���̔j��.

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMultiViewItemsPanel::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

}