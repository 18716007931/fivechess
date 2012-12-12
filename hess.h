// hess.h: interface for the Chess class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_HESS_H__512E1886_862A_49F1_AD35_452B96BC6343__INCLUDED_)
#define AFX_HESS_H__512E1886_862A_49F1_AD35_452B96BC6343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SIZE 20

class Chess  
{
public:
	Chess();
	Chess(int x, int y, int color);
	Chess(int a, int b, int wid, int hei, int color);
	virtual ~Chess();

public:
	void DrawChess(CDC *pDC);	/* ������ */
	void SetColor(int col);		/* ����������ɫ */
	void SetLocation(int x, int y);	/* ��������λ�� */
	int GetX();	/* ��ȡX���� */
	int GetY();	/* ��ȡY���� */
	int GetSize();	/* ��ȡ���Ӵ�С */
	bool IsInChessBoard(int x, int y);	/* �ж������Ƿ��������� */
	int GetColor();	/* ��ȡ��ɫ */
	CRect ReFleshChess();	/* ˢ������, �Ա�������ʾ */

private:
	int x, y, width, height, size, color;
	bool is_in_chess_board;	/* �ж��Ƿ��������� */
};

#endif // !defined(AFX_HESS_H__512E1886_862A_49F1_AD35_452B96BC6343__INCLUDED_)
