// FiveChessView.h : interface of the CFiveChessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIVECHESSVIEW_H__9644732A_8BAF_4A7B_B329_FB5515A1D762__INCLUDED_)
#define AFX_FIVECHESSVIEW_H__9644732A_8BAF_4A7B_B329_FB5515A1D762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "hessBoard.h"

bool box_shown;	/* ��Ϸ����ʱ��������Ϣ���� */

class CFiveChessView : public CView
{
private:
	/* ��ͼ��С */
	int VIEW_WIDTH;
	int VIEW_HEIGHT;
	bool BEGIN;

protected: // create from serialization only
	CFiveChessView();
	DECLARE_DYNCREATE(CFiveChessView)

// Attributes
public:
	CFiveChessDoc* GetDocument();

// Operations
public:
	void setBackGround(CDC* pDC);	/* ���ñ�����ɫ */
	void CFiveChessView::split(CDC* pDC);	/* ��ͼ��������ֿ� */
	void DrawButton(CDC *pDC, const CRect &rect);		/* ��Ťť */
	bool IsBegin();	/* �ж���Ϸ�Ƿ�ʼ�� */
	void SetStart(const bool &start);	/* ��ʼ��Ϸ */
	void ReFleshBoard(ChessBoard &board);	/* ˢ������ */

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiveChessView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFiveChessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFiveChessView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGameStart();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGameRestart();
	afx_msg void OnGameTakeback();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FiveChessView.cpp
inline CFiveChessDoc* CFiveChessView::GetDocument()
   { return (CFiveChessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIVECHESSVIEW_H__9644732A_8BAF_4A7B_B329_FB5515A1D762__INCLUDED_)
