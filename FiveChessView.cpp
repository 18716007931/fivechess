// FiveChessView.cpp : implementation of the CFiveChessView class
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDoc.h"
#include "FiveChessView.h"
#include "stdio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* ���� */
ChessBoard board;
CRect start(675, 100, 740, 118);
CRect takeback(675, 150, 740, 168);
CRect restart(675, 200, 740, 218);
int my_color;	/* �Լ����ӵ���ɫ */

/////////////////////////////////////////////////////////////////////////////
// CFiveChessView

IMPLEMENT_DYNCREATE(CFiveChessView, CView)

BEGIN_MESSAGE_MAP(CFiveChessView, CView)
	//{{AFX_MSG_MAP(CFiveChessView)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_GAME_START, OnGameStart)
	ON_WM_KEYUP()
	ON_COMMAND(ID_GAME_RESTART, OnGameRestart)
	ON_COMMAND(ID_GAME_TAKEBACK, OnGameTakeback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiveChessView construction/destruction

CFiveChessView::CFiveChessView()
{
	// TODO: add construction code here
	/* ��ͼ��Ӱ��С */
	VIEW_WIDTH = 800;
	VIEW_HEIGHT = 652;
	
	/* �����˵����ӵ���ɫ */
	my_color = 1;	/* Ĭ����ѡ��ɫ */
	board.SetPlayer(my_color);
	BEGIN = false;
	box_shown = false;	/* ��û���������� */
}

CFiveChessView::~CFiveChessView()
{
}

BOOL CFiveChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	/* ���ô������� */

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFiveChessView drawing

/* ���ô��ڱ��� */
void CFiveChessView::setBackGround(CDC* pDC)
{
	/* ��ˢ�����ñ�Ӱ��ɫ */
	CBrush bru;
	bru.CreateSolidBrush(RGB(85, 123, 205));	/* ������ɫ */
	CRect rect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);	/* Ҫˢ�ľ��� */
	pDC->FillRect(rect, &bru);					/* ������ɫ */
}

/* ��������ͼ�ֿ� */
void CFiveChessView::split(CDC* pDC)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));	/* �ʵ����� */
	pDC->SelectObject(&pen);					/* ʹ����֧�� */
	pDC->MoveTo(620, 0);	/* ����ͼ���ߵ�����ƶ�����(650, 0) */
	pDC->LineTo(620, 650);	/* �ڵ�ǰ��, ��һ����ָ������� */
}

/* �ػ� */
void CFiveChessView::OnDraw(CDC* pDC)
{
	CFiveChessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	setBackGround(pDC);	/* ���ñ�����ɫΪ��ɳ�� */
	split(pDC);			/* ����ֿ� */

	board.DrawBoard(pDC);	/* ������ */
	board.DrawChesses(pDC);	/* �������ϵ����� */
	if (board.GetWinner() == BLACK && !box_shown)	/* ��Ӯ, ��û�������� */
	{
		SetStart(false);	/* ��һ�ֻ�û��ʼ */
		MessageBox("	����ʤ��!	", "GameOver!", MB_OK);
		ReFleshBoard(board);		/* ȫ��ˢ�� */
		board.InitMap();	/* ���³�ʼ������ */
		box_shown = true;	/* �ѵ��� */
	}
	else if (board.GetWinner() == WHITE && !box_shown)	/* ��Ӯ */
	{
		SetStart(false);	/* ��һ�ֻ�û��ʼ */
		MessageBox("	����ʤ��!	", "GameOver!", MB_OK);
		ReFleshBoard(board);		/* ȫ��ˢ�� */
		board.InitMap();	/* ���³�ʼ������ */
	}

	DrawButton(pDC, start);
	DrawButton(pDC, takeback);
	DrawButton(pDC, restart);

	pDC->DrawText("start", start, DT_CENTER | DT_BOTTOM);
	pDC->DrawText("takeback", takeback, DT_CENTER | DT_BOTTOM);
	pDC->DrawText("restart", restart, DT_CENTER | DT_BOTTOM);

	// TODO: add draw code for native data here
}

void CFiveChessView::DrawButton(CDC *pDC, const CRect &rect)		/* ��Ťť */
{
	/* ��ˢ�����ñ�Ӱ��ɫ */
	CBrush bru;
	CPen pen;

	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));	/* �ʵ����� */
	pDC->SelectObject(&pen);					/* ʹ����֧�� */
	bru.CreateSolidBrush(RGB(255, 255, 255));	/* ������ɫ */
	pDC->FillRect(rect, &bru);					/* ������ɫ */

	pDC->MoveTo(rect.left, rect.top);	/* ����ͼ���ߵ�����ƶ�����(650, 110) */
	pDC->LineTo(rect.left, rect.bottom);	/* �ڵ�ǰ��, ��һ����ָ������� */
	pDC->MoveTo(rect.left, rect.bottom);	/* ����ͼ���ߵ�����ƶ�����(650, 110) */
	pDC->LineTo(rect.right, rect.bottom);	/* �ڵ�ǰ��, ��һ����ָ������� */
	pDC->MoveTo(rect.right, rect.bottom);	/* ����ͼ���ߵ�����ƶ�����(650, 110) */
	pDC->LineTo(rect.right, rect.top);	/* �ڵ�ǰ��, ��һ����ָ������� */
	pDC->MoveTo(rect.right, rect.top);	/* ����ͼ���ߵ�����ƶ�����(650, 110) */
	pDC->LineTo(rect.left, rect.top);	/* �ڵ�ǰ��, ��һ����ָ������� */
}

/////////////////////////////////////////////////////////////////////////////
// CFiveChessView diagnostics

#ifdef _DEBUG
void CFiveChessView::AssertValid() const
{
	CView::AssertValid();
}

void CFiveChessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFiveChessDoc* CFiveChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFiveChessDoc)));
	return (CFiveChessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFiveChessView message handlers

BOOL CFiveChessView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::DestroyWindow();
}

void CFiveChessView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int x, y, me, enemy;
	CPoint dest;
	CRect rect;

	if (!IsBegin())	/* ��û����ʼ */
	{
		return;
	}

	me = board.GetFolkColor();
	enemy = board.GetCompColor();

	/* ��굥���ĵ�Ϊ point ��, ���Ӿ�ȷ��λ�� */
	dest = board.GetChessLocation(point);

	/* ����һ����, ���������, �Ҷ�Ӧ��������������, 
	 * ��ΪЩ�����϶�Ӧ�������ϵ�λ�úϷ� 
	 */
	if (board.IsLegal(dest))
	{
		/* ��������ָ�����������һ���� */
		board.AddChess(dest, me);
		/* ������ָ��������λ����������ӱ�� */
		board.SetChessFlg(dest, me);

		/* ˢ������λ��, �Ա�������ʾ���û� */
		x = dest.x;
		y = dest.y;
		/* ˢ�µľ��� */
		rect = CRect(x - GRID_SIZE / 2, y - GRID_SIZE / 2, 
			x - GRID_SIZE / 2 + GRID_SIZE, y - GRID_SIZE / 2 + GRID_SIZE);
		/* ˢ�� */
		InvalidateRect(rect, true);

		/* �ж���Ӯ(�������һ��) */
		board.JudgementOutcome(dest, me);

		Sleep(200);	/* ������0.2���, �ֵ������� */
		x = (dest.x - DEFAULT_X) / GRID_SIZE;
		y = (dest.y - DEFAULT_Y) / GRID_SIZE;
		board.ComputerStep(x, y);	/* ����x, y��ֵ(��������λ��) */
		dest = board.FlgToLocation(x, y);	/* �����϶�Ӧ������ */
		/* ��������ָ�����������һ���� */
		board.AddChess(dest, enemy);
		/* ������ָ��������λ����������ӱ�� */
		board.SetChessFlg(dest, enemy);

		/* ˢ������λ��, �Ա�������ʾ���û� */
		x = dest.x;
		y = dest.y;
		/* ˢ�µľ��� */
		rect = CRect(x - GRID_SIZE / 2, y - GRID_SIZE / 2, 
			x - GRID_SIZE / 2 + GRID_SIZE, y - GRID_SIZE / 2 + GRID_SIZE);
		/* ˢ�� */
		InvalidateRect(rect, true);

		/* �ж���Ӯ(�������һ��) */
		board.JudgementOutcome(dest, enemy);
	}

	CView::OnLButtonUp(nFlags, point);
}

void CFiveChessView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	/* ���¿�ʼ */
	if (point.x >= restart.left && point.x <= restart.right &&
		point.y >= restart.top && point.y <= restart.bottom && 
		IsBegin())
	{
		ReFleshBoard(board);
		board.InitMap();
	}

	/* ��ʼ */
	if (point.x >= start.left && point.x <= start.right &&
		point.y >= start.top && point.y <= start.bottom && 
		!IsBegin())
	{
		SetStart(true);
		ReFleshBoard(board);
		board.InitMap();
	}

	/* ���� */
	if (point.x >= takeback.left && point.x <= takeback.right &&
		point.y >= takeback.top && point.y <= takeback.bottom && 
		board.GetChessesNum() >= 2)
	{
		Sleep(200);
		CRect rect_a, rect_b;
		board.SubChess(rect_a, rect_b);	/* ����������, ���Ƴ���� */

		/* ˢ�� */
		InvalidateRect(rect_a, true);
		InvalidateRect(rect_b, true);
	}

	CView::OnLButtonDown(nFlags, point);
}

bool CFiveChessView::IsBegin()	/* �ж���Ϸ�Ƿ�ʼ�� */
{
	return BEGIN;
}

void CFiveChessView::SetStart(const bool &start)	/* ��ʼ��Ϸ */
{
	BEGIN = start;
}

/* ˢ������ */
void CFiveChessView::ReFleshBoard(ChessBoard &board)
{
	int i, len;
	CRect rect;
	Chess chess;

	len = board.GetChessesNum();
	for (i = 0; i < len; ++i)
	{
		chess = board.GetChess(i);
		rect = chess.ReFleshChess();
		InvalidateRect(rect, true);
	}
}


void CFiveChessView::OnGameStart() 
{
	if (!IsBegin())
	{
		SetStart(true);
		ReFleshBoard(board);
		board.InitMap();
	}
}

void CFiveChessView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nChar == VK_F2 && !IsBegin())	/* ��Ϸ��ʼ */
	{
		OnGameStart();
	}
	else if (nChar == VK_F3 && IsBegin())	/* ��Ϸ���¿�ʼ */
	{
		ReFleshBoard(board);
		board.InitMap();
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CFiveChessView::OnGameRestart() 
{
	// TODO: Add your command handler code here
	if (IsBegin())	/* ��Ϸ�Ѿ���ʼ, ���¿�ʼ */
	{
		ReFleshBoard(board);
		board.InitMap();
	}
}

void CFiveChessView::OnGameTakeback() 
{
	// TODO: Add your command handler code here
	/* ���� */
	if (board.GetChessesNum() >= 2)
	{
		Sleep(200);
		CRect rect_a, rect_b;
		board.SubChess(rect_a, rect_b);	/* ����������, ���Ƴ���� */

		/* ˢ�� */
		InvalidateRect(rect_a, true);
		InvalidateRect(rect_b, true);
	}
}
