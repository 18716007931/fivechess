// hess.cpp: implementation of the Chess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FiveChess.h"
#include "hessBoard.h"
#include "hess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEFAULT_X 22
#define DEFAULT_Y 12

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Chess::Chess()
{
	x = DEFAULT_X;
	y = DEFAULT_Y;
	is_in_chess_board = false;	/* ���Ӳ��������� */
	color = BLACK;	/* Ĭ�Ϻ�ɫ */
	width = height = size = SIZE;
}

Chess::Chess(int a, int b, int col)
{
	/* λ�� */
	x = a;
	y = b;
	is_in_chess_board = false;	/* ���Ӳ��������� */
	color = col;	/* 0 �����ɫ, 1�����ɫ */
	width = height = size = SIZE;	/* ��С */
}

/* λ�úʹ�С */
Chess::Chess(int a, int b, int wid, int hei, int col)
{
	x = a;
	y = b;
	is_in_chess_board = false;	/* ���Ӳ��������� */
	color = col;
	width = height = size = SIZE;
}

/* ����������ɫ */
void Chess::SetColor(int col)
{
	color = col;
}

/* ����λ�� */
void Chess::SetLocation(int a, int b)
{
	x = a;
	y = b;
}

/* ��ȡλ�� */
int Chess::GetX()
{
	return x;
}

int Chess::GetY()
{
	return y;
}

/* ������ */
void Chess::DrawChess(CDC *pDC)
{
	CBrush *brush;
	COLORREF color;
	CPen pen;
	int a, b;

	a = x - SIZE / 2;
	b = y - SIZE / 2;

	/* ѡ����ɫ */
	if (this->color == WHITE)	/* ��ɫ */
	{
		color = RGB(255, 255, 255);
		pen.CreatePen(PS_SOLID, 1, color);
	}
	else	/* ��ɫ */
	{
		color = RGB(0, 0, 0);
		pen.CreatePen(PS_SOLID, 1, color);
	}

	brush = new CBrush(color);	/* �ʵ����� */
	pDC->SelectObject(brush);			/* ʹ����֧�� */
	pDC->SelectObject(&pen);
	pDC->Ellipse(a, b, a + size, b + size);	/* ��Բ */
	brush->DeleteObject();
	pen.DeleteObject();
}

Chess::~Chess()
{

}

/* ��ȡ���Ӵ�С */
int Chess::GetSize()
{
	return size;
}

/* �ж������Ƿ��������� */
bool Chess::IsInChessBoard(int x, int y)
{
	return is_in_chess_board;
}

int Chess::GetColor()	/* ��ȡ��ɫ */
{
	return color;
}

CRect Chess::ReFleshChess()	/* ˢ������, �Ա�������ʾ */
{
	CRect rect;

	/* ˢ�µľ��� */
	rect = CRect(x - GRID_SIZE / 2, y - GRID_SIZE / 2, 
		x - GRID_SIZE / 2 + GRID_SIZE, y - GRID_SIZE / 2 + GRID_SIZE);

	return rect;	/* ���� */
}