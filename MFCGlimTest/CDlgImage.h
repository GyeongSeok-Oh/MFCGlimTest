#pragma once
#include "afxdialogex.h"
#include <iostream>
using namespace std;

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CWnd* m_pParent;
	CImage m_Image;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void initImage(int nWidth, int nHeight, int nBpp);
	afx_msg void OnBnClickedCancel();
	void DrawCircle(CDC* cd, int x, int y, int radius);
	void DrawCross(CDC* cd, int x, int y, int radius);

};
