﻿
// MFCGlimTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCGlimTest.h"
#include "MFCGlimTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCGlimTestDlg 대화 상자



CMFCGlimTestDlg::CMFCGlimTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGLIMTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGlimTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCGlimTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Play, &CMFCGlimTestDlg::OnBnClickedPlay)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCGlimTestDlg 메시지 처리기

BOOL CMFCGlimTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	srand((unsigned int)(time(NULL)));

	m_TotalFont.CreatePointFont(120, _T("Arial"));
	GetDlgItem(IDC_Radius)->SetFont(&m_TotalFont);
	GetDlgItem(IDC_CENTER)->SetFont(&m_TotalFont);
	GetDlgItem(IDC_CENTER_POINT)->SetFont(&m_TotalFont);

	MoveWindow(0, 0, 960, 600);

	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	
	//IDC_Radius.SetFont(&TotalFont, TRUE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCGlimTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCGlimTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCGlimTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCGlimTestDlg::OnBnClickedPlay()
{
	// 자식 객체 윈도우 클라이언트 영역 선언
	//CClientDC dc(m_pDlgImage);
	m_pDlgImage->m_BorderLine.RemoveAll();

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, COLOR_BLACK, nWidth * nHeight);

	//dc.FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));

	// 반지름 값 받아오기
	CString n_RadiusString;
	GetDlgItemText(IDC_RADIUS_RESULT, n_RadiusString);
	int n_Radius = _ttoi(n_RadiusString);
	
	if (n_Radius <= 0 && n_RadiusString != _T("0")) {
		AfxMessageBox(_T("0이상의 숫자만 입력해주세요."));
	}else if (nWidth / 2 < n_Radius || nHeight / 2 < n_Radius) {
		AfxMessageBox(_T("반지름의 길이를 줄여서 입력해주세요."));
	}else {

		int x, y;

		while (true) {
			x = rand() % (nWidth - n_Radius * 2) + n_Radius;
			y = rand() % (nHeight - n_Radius * 2) + n_Radius;

			m_pDlgImage->m_Center.x = x;
			m_pDlgImage->m_Center.y = y;

			if (x - n_Radius >= 0 && x + n_Radius <= nWidth && y - n_Radius >= 0 && y + n_Radius <= nHeight) {
				break;
			}
		}
		
		// 텍스트 변경
		CString text;
		text.Format(_T("( %d , %d )"), x, y);
		GetDlgItem(IDC_CENTER_POINT)->SetWindowText(text);

		// 원그리기
		//m_pDlgImage->DrawCircle(&dc, x, y, n_Radius);

		// 원 테두리 배열에 저장
		SetBorderLine(x, y, n_Radius, nPitch);
		// 십자선 그리기
		//m_pDlgImage->DrawCross(&dc, x, y, n_Radius);
		SetCrossLine(x, y, n_Radius);

		m_pDlgImage->Invalidate();
	}
}

void CMFCGlimTestDlg::SetBorderLine(int x, int y, int n_Radius, int nPitch)
{
	int nBlack = 0;
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	for (int j = y - n_Radius; j <= y + n_Radius; j++) {
		for (int i = x - n_Radius; i <= x + n_Radius; i++) {

			bool bRet = false;

			double dX = i - x;
			double dY = j - y;
			double dDist = dX * dX + dY * dY;
			// 원 테두리 두께 설정
			int nThick = 2;

			if (dDist <= n_Radius * n_Radius && dDist >= (n_Radius - nThick) * (n_Radius - nThick)) {
				bRet = true;
			}
			if (bRet) {
				fm[nPitch * j + i] = nBlack;
				m_pDlgImage->m_BorderLine.Add(CPoint(i, j));
			}
			
		}
	}
}

void CMFCGlimTestDlg::SetCrossLine(int x, int y, int n_Radius)
{
	int nBlack = 0;
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	// 수직선 그리기
	for (int j = y - (n_Radius / 2); j <= y + (n_Radius / 2); j++) {
		fm[nPitch * j + x] = nBlack;
		m_pDlgImage->m_Vertical.Add(CPoint(x, j));
	}

	// 수평선 그리기
	for (int i = x - (n_Radius / 2); i <= x + (n_Radius / 2); i++) {
		fm[nPitch * y + i] = nBlack;
		m_pDlgImage->m_Horizon.Add(CPoint(i, y));
	}
}

void CMFCGlimTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 메모리 릭 제거
	if (m_pDlgImage) delete m_pDlgImage;
}
