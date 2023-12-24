// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "MFCGlimTest.h"
#include "afxdialogex.h"
#include "CDlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CDlgImage::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int nWidth = 700;
	int nHeight = 540;
	int nBpp = 8;

	MoveWindow(0, 0, nWidth, nHeight);
	initImage(nWidth, nHeight, nBpp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	
	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
	DrawCircle(&dc);
	DrawCross(&dc);
}

void CDlgImage::initImage(int nWidth, int nHeight, int nBpp) {

	m_Image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	/*for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) { 
			fm[j * nPitch + i] = 255;
		}
	}*/

	memset(fm, COLOR_BLACK, nWidth * nHeight);
}


void CDlgImage::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CDlgImage::DrawCircle(CDC* cd)
{
	// 원 그리는 색 설정
	/*int penWidth = 5;
	CPen yellowPen(PS_SOLID, penWidth, RGB(255, 255, 0));
	CPen* oldPen = cd->SelectObject(&yellowPen);

	cd->Ellipse(x - radius, y - radius, x + radius, y + radius);
	cd->SelectObject(oldPen);*/

	int size = m_BorderLine.GetSize();
	CRect rect;

	for (int i = 0; i < size; i++) {
		CPoint point = m_BorderLine.GetAt(i);
		rect.SetRect(point, point);
		rect.InflateRect(1, 1);

		cd->FillRect(rect, &CBrush(COLOR_YELLOW));
	}

}

void CDlgImage::DrawCross(CDC* cd)
{
	/*int crossSize = radius / 5;
	if (crossSize < 5) {
		crossSize = 5;
	}
	
	// 수직 선 그리기
	cd->MoveTo(x, y - crossSize); // 시작선
	cd->LineTo(x, y + crossSize + 1); // 라인을 그리는것

	// 수평 선 그리기
	cd->MoveTo(x - crossSize, y);
	cd->LineTo(x + crossSize + 1, y);
	*/

	CRect rect;

	for(int i = 0; i < 1; i++) {
		rect.SetRect(m_Center, m_Center);
		rect.InflateRect(2, 2);
		cd->FillRect(rect, &CBrush(COLOR_BLACK));
	}

	
}