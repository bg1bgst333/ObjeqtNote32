// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MultiView.h"	// CMultiView

// �R���X�g���N�^CMultiView
CMultiView::CMultiView() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pMultiViewItemsPanel = NULL;	// m_pMultiViewItemsPanel��NULL�ŏ�����.
	m_iHScrollPos = 0;	// m_iHScrollPos��0�ŏ�����.
	m_iVScrollPos = 0;	// m_iVScrollPos��0�ŏ�����.

}

// �f�X�g���N�^~CMultiView
CMultiView::~CMultiView(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMultiView::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CMultiView::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CMultiView"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CMultiView::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CMultiView"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CMultiView::Destroy(){

	// �}���`�r���[�A�C�e���Y�p�l���̔j��.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanel��NULL�łȂ���.
		m_pMultiViewItemsPanel->Destroy();	// m_pMultiViewItemsPanel->Destroy�Ŕj��.
		delete m_pMultiViewItemsPanel;	// delete��m_pMultiViewItemsPanel�����.
		m_pMultiViewItemsPanel = NULL;	// m_pMultiViewItemsPanel��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �A�C�e���𖖔�����ǉ�����֐�Add.
void CMultiView::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// �A�C�e���Y�p�l���ɒǉ�.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanel��NULL�łȂ����.
		m_pMultiViewItemsPanel->Add(lpctszWindowName, x, y, iWidth, iHeight, hInstance);	// Add�Ŗ����ɒǉ�.
	}

}

// �A�C�e���𖖔�����폜����֐�Remove.
void CMultiView::Remove(){

	// �A�C�e���Y�p�l������폜.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanel��NULL�łȂ����.
		m_pMultiViewItemsPanel->Remove();	// Remove�Ŗ�������폜.
	}

}

// �A�C�e�����擾����֐�Get.
CMultiViewItem * CMultiView::Get(int iIndex){

	// �A�C�e���Y�p�l������擾.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanel��NULL�łȂ����.
		return m_pMultiViewItemsPanel->Get(iIndex);	// 
	}

	// �Ȃ����NULL.
	return NULL;	// NULL��Ԃ�.

}

// �S�ẴA�C�e�����폜����֐�RemoveAll.
void CMultiView::RemoveAll(){

	// �A�C�e���Y�p�l������S�č폜.
	if (m_pMultiViewItemsPanel != NULL){	// m_pMultiViewItemsPanel��NULL�łȂ����.
		m_pMultiViewItemsPanel->RemoveAll();
	}

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMultiView::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �}���`�r���[�A�C�e���Y�p�l���̐���.
	m_pMultiViewItemsPanel = new CMultiViewItemsPanel();	// CMultiViewItemsPanel�̍쐬.

	// �}���`�r���[�A�C�e���Y�p�l���̃E�B���h�E����.
	m_pMultiViewItemsPanel->Create(_T(""), 0, 0, 0, 320 + 300, 240 + 200, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pMultiViewItemsPanel->Create�ŃE�B���h�E����.

	// ����X�V�^�C�}�[���Z�b�g.
	SetTimer(hwnd, 1, 100, NULL);	// SetTimer�ōX�V�^�C�}�[���Z�b�g.(100�~���b==0.1�b)

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMultiView::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�N���X��OnDestroy���Ă�.
	CUserControl::OnDestroy();	// CUserControl::OnDestroy���Ă�.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CMultiView::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));	// CreatePen�Ő�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0x7f));		// CreateSolidBrush�Ő�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
	// �y���ƃu���V�̕���
	SelectObject(hDC, hOldBrush);		// �Â��u���V��I��.
	SelectObject(hDC, hOldPen);		// �Â��y����I��.

	// �y���ƃu���V�̔j��.
	DeleteObject(hBrush);	// �u���V�̔j��.
	DeleteObject(hPen);	// �y���̔j��.

	// �X�N���[���o�[�ݒ�.
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// �y�[�W��
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iWidth;	//�ő�l
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// �y�[�W����
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iHeight;	//�ő�l
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMultiView::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �X�N���[���o�[�ݒ�.
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// �y�[�W��
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iWidth;	//�ő�l
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// �y�[�W����
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pMultiViewItemsPanel->m_iHeight;	//�ő�l
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)

}

// �^�C�}�[�C�x���g������������.
void  CMultiView::OnTimer(UINT_PTR nIDEvent){

	// ����X�V�^�C�}�[�̎�.
	if (nIDEvent == 1){	// 1�̎�.

		// �����̈���쐬���ĉ�ʂ̍X�V.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

		// �^�C�}�[���I��.
		KillTimer(m_hWnd, 1);	// ����X�V�^�C�}�[���I��.

	}

}

// ���������X�N���[���o�[�C�x���g��.
void CMultiView::OnHScroll(UINT nSBCode, UINT nPos){

	// �X�N���[�����擾.
	m_ScrollInfo.fMask = SIF_POS;	// �ʒu�����ύX���[�h(���ꂪ�Ȃ���, �X�N���[���o�[�����̈ʒu�ɖ߂��Ă��܂��̂Œ���!���������O!)
	GetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo);	// �}�X�N��ݒ肵�Ă���GetScrollInfo.(����������!)

	// �X�N���[���o�[����.
	switch (nSBCode) {	// nSBCode���ƂɐU�蕪��.

		// ��ԍ�
		case SB_LEFT:

			// �ʒu���ŏ��l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// ��ԉE
		case SB_RIGHT:

			// �ʒu���ő�l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1��
		case SB_LINELEFT:

			// nPos��0�łȂ���΃f�N�������g.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1��E
		case SB_LINERIGHT:

			// nPos���ő�l-1�łȂ���΃C���N�������g.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1�y�[�W��
		case SB_PAGELEFT:

			// nPage�����炷.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1�y�[�W�E
		case SB_PAGERIGHT:

			// nPage�����₷.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBTRACK:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBPOSITION:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// ����ȊO.
		default:

			break;

	}

	// �X�N���[�����ݒ�.
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);
	// �����o�ɂ��Z�b�g.
	m_iHScrollPos = m_ScrollInfo.nPos;
	// �A�C�e���Y�p�l���̈ړ�.
	MoveWindow(m_pMultiViewItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pMultiViewItemsPanel->m_iWidth, m_pMultiViewItemsPanel->m_iHeight, TRUE);	// MoveWindow�ňړ�.
	// �����̈���쐬���ĉ�ʂ̍X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

}

// ���������X�N���[���o�[�C�x���g��.
void CMultiView::OnVScroll(UINT nSBCode, UINT nPos){

	// �X�N���[�����擾.
	m_ScrollInfo.fMask = SIF_POS;	// �ʒu�����ύX���[�h(���ꂪ�Ȃ���, �X�N���[���o�[�����̈ʒu�ɖ߂��Ă��܂��̂Œ���!���������O!)
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// �}�X�N��ݒ肵�Ă���GetScrollInfo.(����������!)

	// �X�N���[���o�[����.
	switch (nSBCode) {	// nSBCode���ƂɐU�蕪��.

		// ��ԏ�
		case SB_TOP:

			// �ʒu���ŏ��l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// ��ԉ�
		case SB_BOTTOM:

			// �ʒu���ő�l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1�s��
		case SB_LINEUP:

			// nPos��0�łȂ���΃f�N�������g.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1�s��
		case SB_LINEDOWN:

			// nPos���ő�l-1�łȂ���΃C���N�������g.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1�y�[�W��
		case SB_PAGEUP:

			// nPage�����炷.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1�y�[�W��
		case SB_PAGEDOWN:

			// nPage�����₷.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBTRACK:
	
			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBPOSITION:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// ����ȊO.
		default:

			break;

	}

	// �X�N���[�����ݒ�.
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);
	// �����o�ɂ��Z�b�g.
	m_iVScrollPos = m_ScrollInfo.nPos;
	// �A�C�e���Y�p�l���̈ړ�.
	MoveWindow(m_pMultiViewItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pMultiViewItemsPanel->m_iWidth, m_pMultiViewItemsPanel->m_iHeight, TRUE);	// MoveWindow�ňړ�.
	// �����̈���쐬���ĉ�ʂ̍X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

}