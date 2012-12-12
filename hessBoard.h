// hessBoard.h: interface for the ChessBoard class.
//
//////////////////////////////////////////////////////////////////////
#include "hess.h"

#if !defined(AFX_HESSBOARD_H__3FF45F9A_50FD_41E4_8D8E_CA8981F3D258__INCLUDED_)
#define AFX_HESSBOARD_H__3FF45F9A_50FD_41E4_8D8E_CA8981F3D258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define DEFAULT_X 22	/* ����Ĭ�ϵĺ����� */
#define DEFAULT_Y 12	/* ����Ĭ�ϵ������� */
#define GRID_SIZE 24	/* �����С */
#define MAX_LEN 25	/* ���������󳤶�: MAX_LEN * MAX_LEN�ξ��� */
#define MAX_CHESSES MAX_LEN * MAX_LEN	/* ��������� */
#define NO_PLAYER 0	/* û����� */
#define BLACK 1	/* ���� */
#define WHITE 2	/* ���� */
#define WON 5	/* ʤ�� */

/* ���� */
class ChessBoard  
{
public:
	ChessBoard();
	virtual ~ChessBoard();
public:
	/* ������ */
	void DrawBoard(CDC *pDC);
	/* �����������̵����� */
	void DrawChesses(CDC *pDC);
	/* ��������ָ�����������ָ����ɫ������ */
	void AddChess(const CPoint &point, const int &color);
	/* ��(color)����(x, y), �ж���Ӯ */
	int CheckWin(const CPoint src, const int x, const int y, const int color);

	/* ��ȡλ�úʹ�С */
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	/* ��ʼ����ͼ */
	void InitMap();
	/* �������������ɫ */
	void SetPlayer(const int &my_color);
	/* �ж���û������ */
	bool HasChess(const int &i, const int &j);
	/* �������ӱ��, MAP[i][j] = color */
	void SetChessFlg(const CPoint &point, const int &color);
	/* ������ʤ�� */
	void SetWinner(const int &count, const int &color);
	/* ��ȡ��ʤ�� */
	int GetWinner();
	/* ��ȡ�����λ�� */
	CPoint GetChessLocation(const CPoint &point);
	/* ��ȡָ���±������ */
	Chess GetChess(const int &index);
	/* �ж�λ���Ƿ�Ϸ� */
	bool IsLegal(const CPoint &point);
	/* ������ point ��, �ж�ʤ��(�ж������߷���) */
	void JudgementOutcome(const CPoint &point, const int &color);
	/* �жϵ�ͼ���, ���ڼ�������������λ�� */
	void JudgeMap();
	/* ����point, ���ص��������λ�� */
	void ComputerStep(int &x, int &y);
	/* ����������Ӧ��λ��, ��ȡ����λ�� */
	CPoint FlgToLocation(const int &i, const int &j);
	/* ��ȡ�˵���ɫ */
	int GetFolkColor();
	/* ��ȡ���Ե���ɫ */
	int ChessBoard::GetCompColor();
	/* ���� */
	void TakeBack();
	/* ����һ���� */
	void SubChess(CRect &rect_a, CRect &rect_b);
	/* ɾ����� */
	void RemoveFlg(Chess chess);
	/* ��ȡ������ */
	int GetChessesNum();

private:
	Chess chs[MAX_CHESSES];	/* �����ϵ����� */
	int chs_len;	/* ������ */

	/* ��ͼ */
	int MAP[MAX_LEN][MAX_LEN];
	short Com[MAX_LEN][MAX_LEN][4];
	short Pla[MAX_LEN][MAX_LEN][4];

	int winner;	/* ��ʤ�� */
	int me, enemy;	/* �Һ͵з� */

private:
	int x, y, width, height, size;
};

#endif // !defined(AFX_HESSBOARD_H__3FF45F9A_50FD_41E4_8D8E_CA8981F3D258__INCLUDED_)
