// hessBoard.cpp: implementation of the ChessBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FiveChess.h"
#include "hessBoard.h"
#include "hess.h"
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* ����λ�úʹ�С */
ChessBoard::ChessBoard()
{
	/* �������� */
	x = DEFAULT_X;
	y = DEFAULT_Y;

	/* ���̴�С */
	width = 576;
	height = 576;

	/* �����С */
	size = GRID_SIZE;

	/* ������������Ϊ�� */
	chs_len = 0;

	/* ��ʼ������������״̬(�Ƿ�������) */
	InitMap();

	winner = NO_PLAYER;	/* ������ʤ��, Ĭ��Ϊ��ɫ2(�Ǻڷǰ�) */
}

ChessBoard::~ChessBoard()
{

}

/* ������ָ�����������һ���� */
void ChessBoard::AddChess(const CPoint &point, const int &color)
{
	Chess chess(point.x, point.y, color);

	chs[chs_len++] = chess;
}

/* ������������ */
void ChessBoard::DrawChesses(CDC *pDC)
{
	int i;

	/* �𽥻����������� */
	for (i = 0; i < chs_len; ++i)
	{
		chs[i].DrawChess(pDC);
	}	
}

/* �������� */
void ChessBoard::DrawBoard(CDC *pDC)
{
	int i, row, col;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(155, 155, 155));
	pDC->SelectObject(&pen);

	row = height / size;
	col = width / size;
	
	for (i = 0; i <= row; ++i)
	{
		pDC->MoveTo(x, y + i * size);
		pDC->LineTo(x + width, y + i * size);
	}

	for (i = 0; i <= col; ++i)
	{
		pDC->MoveTo(x + i * size, y);
		pDC->LineTo(x + i * size, y + height);
	}
}

/* ��ȡλ�� */
int ChessBoard::GetX()
{
	return x;
}

int ChessBoard::GetY()
{
	return y;
}

/* ��ȡ��� */
int ChessBoard::GetWidth()
{
	return width;
}

/* ��ȡ�߶� */
int ChessBoard::GetHeight()
{
	return height;
}

/* ��ʼ����ͼ */
void ChessBoard::InitMap()
{
	int i, j;

	chs_len = 0;/* �����ϵ��������¹��� */
	winner = NO_PLAYER;	/* ������ʤ�� */
	for (i = 0; i <= MAX_LEN; ++i)
	{
		for (j = 0; j <= MAX_LEN; ++j)
		{
			MAP[i][j] = NO_PLAYER;	/* δȷ����ɫ */
		}
	}
}

/* �������������ɫ */
void ChessBoard::SetPlayer(const int &my_color)
{
	me = my_color;
	if (me == BLACK)
	{
		enemy = WHITE;
	}
	else
	{
		enemy = BLACK;
	}
}

/* �ж���û������ */
bool ChessBoard::HasChess(const int &x, const int &y)
{
	/* 1 ��ʾ������, 2��ʾ������, 0������  */
	return MAP[x][y] != 0;
}

/* �������ӱ��, MAP[i][j] = color */
void ChessBoard::SetChessFlg(const CPoint &point, const int &color)
{
	int i, j;

	/* �������ӱ�ǵ����� */
	i = (point.x - DEFAULT_X) / GRID_SIZE + 1;
	j = (point.y - DEFAULT_Y) / GRID_SIZE + 1;

	/* MAP[i][j] = color; *///�±��1 ~ MAX_LEN
	MAP[i - 1][j - 1] = color;
}

/* �����, ��(color)��(x, y)������ �ж���Ӯ 
 * src:		����ĵ�
 * (x, y):	�жϵķ���(˫����:�ۼӻ��ۼ�)
 * chess_color:	�������ɫ
 */
int ChessBoard::CheckWin(const CPoint src, 
			const int x, const int y, 
			const int chess_color)
{
	int i, j, color, count;

	/* (i, j): ��ͼ����� */
	i = (src.x - DEFAULT_X) / GRID_SIZE;
	j = (src.y - DEFAULT_Y) / GRID_SIZE;
	color = chess_color;
	count = 0;

	/* ����û�г�����Χ, ��������ɫ����µ�������ɫһ�� */
	while (i >= 0 && i < MAX_LEN &&
			j >= 0 && j < MAX_LEN &&
			MAP[i][j] == color)
	{
		++count;	/* �ҵ�����ͬһ��ɫ������ */
		/* ����һ������(����) */
		i += x;	
		j += y;
	}

	i = (src.x - DEFAULT_X) / GRID_SIZE;
	j = (src.y - DEFAULT_Y) / GRID_SIZE;
	color = chess_color;

	/* ����û�г�����Χ, ��������ɫ����µ�������ɫһ�� */
	while (i >= 0 && i < MAX_LEN &&
			j >= 0 && j < MAX_LEN &&
			MAP[i][j] == color)
	{
		++count;	/* �ҵ�����ͬһ��ɫ������ */
		/* ����һ������(����) */
		i -= x;	
		j -= y;
	}

	return --count;	/* Դ���ظ��ۼ� */
}

/* ������ʤ�� */
void ChessBoard::SetWinner(const int &count, const int &color)
{
	if (count == WON)
	{
		winner = color;	/* ʤ���ߵ���ɫ */
	}
}
/* ��ȡ��ʤ�� */
int ChessBoard::GetWinner()
{
	return winner;
}

/* ��������λ����point��, ��ȡ�����׼ȷλ�� */
CPoint ChessBoard::GetChessLocation(const CPoint &point)
{
	int wid, hei, x, y;
	CPoint dest;	/* ����ȷ��Ҫ�����λ�� */

	/* ������ȷ�������������, ��С��Ⱥ͸߶� */
	wid = point.x - DEFAULT_X;
	hei = point.y - DEFAULT_Y;

	/* ����ĵ� */
	x = DEFAULT_X + wid / GRID_SIZE * GRID_SIZE;
	y = DEFAULT_Y + hei / GRID_SIZE * GRID_SIZE;
	CPoint tmp(x, y);
	/* �������� */
	CPoint right(x + GRID_SIZE, y);	/* tmp ���ұߵĵ� */
	CPoint ri_down(x + GRID_SIZE, y + GRID_SIZE);	/* tmp �����µĵ� */
	CPoint down(x, y + GRID_SIZE);	/* tmp �����·��ĵ� */

	/* ��굥���ĵ� */
	x = point.x;
	y = point.y;
	/* ��ȷ��(tmp, right, ri_down, down ����һ��) */
	if (x >= right.x - GRID_SIZE / 2 && 
		x <= right.x + GRID_SIZE / 2 && 
		y >= right.y - GRID_SIZE / 2 && 
		y <= right.y + GRID_SIZE / 2)
	{
		dest = right;
	}
	else if (x >= ri_down.x - GRID_SIZE / 2 && 
		x <= ri_down.x + GRID_SIZE / 2 && 
		y >= ri_down.y - GRID_SIZE / 2 && 
		y <= ri_down.y + GRID_SIZE / 2)
	{
		dest = ri_down;
	}
	else if (x >= down.x - GRID_SIZE / 2 && 
		x <= down.x + GRID_SIZE / 2 && 
		y >= down.y - GRID_SIZE / 2 && 
		y <= down.y + GRID_SIZE / 2)
	{
		dest = down;
	}
	else
	{
		dest = tmp;
	}

	return dest;
}

/* ��ȡָ���±������ */
Chess ChessBoard::GetChess(const int &index)
{
	return chs[index];
}

/* �ж�λ���Ƿ�Ϸ� */
bool ChessBoard::IsLegal(const CPoint &point)
{
	int i, j;

	/* ���������Ӧ�ĵ�ͼ��� */
	i = (point.x - DEFAULT_X) / GRID_SIZE;
	j = (point.y - DEFAULT_Y) / GRID_SIZE;

	/* ����Ϸ�, ���������������� */
	if (point.x >= DEFAULT_X && 
		point.x <= DEFAULT_X + GetWidth() && 
		point.y >= DEFAULT_Y && 
		point.y <= DEFAULT_Y + GetHeight() && 
		!HasChess(i, j))
	{
		return true;
	}

	return false;
}

/* ������ point ��, �ж�ʤ��(�ж������߷���) */
void ChessBoard::JudgementOutcome(const CPoint &point, const int &color)
{
	/* �ж���Ӯ(�������һ��) */
	if (WON == CheckWin(point, 1, 0, color))	/* �᷽�� */
	{
		SetWinner(WON, color);	/* ����ʤ���� */
	}
	else if (WON == CheckWin(point, 0, 1, color))	/* ������ */
	{
		SetWinner(WON, color);	/* ����ʤ���� */
	}
	else if (WON == CheckWin(point, 1, 1, color))	/* ��б�߷��� "\" */
	{
		SetWinner(WON, color);	/* ����ʤ���� */
	}
	else if (WON == CheckWin(point, -1, 1, color))	/* ��б�߷��� "/" */
	{
		SetWinner(WON, color);	/* ����ʤ���� */
	}
}

/* �жϵ�ͼ���, ���ڼ�������������λ�� */
void ChessBoard::JudgeMap()
{
	int i, j, a, now = 0, last = 0, left, up, right, down;
	
	for (i = 0; i < MAX_LEN; ++i)
	{
		for (j = 0; j < MAX_LEN; ++j)
		{
			for (a = 0; a < 4; ++a)
			{
				Com[i][j][a] = 0;
				Pla[i][j][a] = 0;
			}
		}
	}
	
	for (i = 0; i < MAX_LEN; ++i)
	{
		for (j = 0; j < MAX_LEN; ++j)
		{
			if (MAP[i][j] == 0)
			{
				/* left */
				now = 0;
				last = 0;
				left = j - 1;
				for (; left >= 0; --left)
				{
					if (MAP[i][left] == me)
					{
						now = me;
						if (left != j - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][0];
						last = me;
					}
					else if (MAP[i][left] == enemy)
					{
						now = enemy;
						if (left != j - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][0];
						last = enemy;
					}
					else
					{
						break;
					}
				}
				
				/* right */
				now = 0;
				last = 0;
				right = j + 1;
				for (; right < MAX_LEN; ++right)
				{
					if (MAP[i][right] == me)
					{
						now = me;
						if (right != j + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][0];
						last = me;
					}
					else if (MAP[i][right] == enemy)
					{
						now = enemy;
						if (right != j + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][0];
						last = enemy;
					}
					else
					{
						break;
					}
				}
				
				/* up */
				up = i - 1;
				now = 0;
				last = 0;
				for (; up >= 0; --up)
				{
					if (MAP[up][j] == me)
					{
						now = me;
						if (up != i - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][1];
						last = me;
					}
					else if (MAP[up][j] == enemy)
					{
						now = enemy;
						if (up != i - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][1];
						last = enemy;
					}
					else
					{
						break;
					}
				}
				
				down = i + 1;
				now = 0;
				last = 0;
				for (; down < MAX_LEN; ++down)
				{
					if (MAP[down][j] == me)
					{
						now = me;
						if (down != i + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][1];
						last = me;
					}
					else if (MAP[down][j] == enemy)
					{
						now = enemy;
						if (down != i + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][1];
						last = enemy;
					}
					else
					{
						break;
					}
				}
				
				/* down */
				right = j + 1;
				up = i - 1;
				now = 0;
				last = 0;
				while (right < MAX_LEN && up >= 0)
				{
					if (MAP[up][right] == me)
					{
						now = me;
						if (right != j + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][2];
						last = me;
					}
					else if (MAP[up][right] == enemy)
					{
						now = enemy;
						if (right != j + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][2];
						last = enemy;
					}
					else
					{
						break;
					}
					
					++right;
					--up;
				}
				
				left = j - 1;
				down = i + 1;
				now = 0;
				last = 0;
				while (left >= 0 && down < MAX_LEN)
				{
					if (MAP[down][left] == me)
					{
						now = me;
						if (left != j - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][2];
						last = me;
					}
					else if (MAP[down][left] == enemy)
					{
						now = enemy;
						if (left != j - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][2];
						last = enemy;
					}
					else
					{
						break;
					}
					--left;
					++down;
				}
				
				left = j - 1;
				up = i - 1;
				now = 0;
				last = 0;
				while (left >= 0 && up >= 0)
				{
					if (MAP[up][left] == me)
					{
						now = me;
						if (left != j - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][3];
						last = me;
					}
					else if (MAP[up][left] == enemy)
					{
						now = enemy;
						if (left != j - 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][3];
						last = enemy;
					}
					else
					{
						break;
					}
					--left;
					--up;
				}
				
				right = j + 1;
				down = i + 1;
				now = 0;
				last = 0;
				while (right < MAX_LEN && down < MAX_LEN)
				{
					if (MAP[down][right] == me)
					{
						now = me;
						if (right != j + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Com[i][j][3];
						last = me;
					}
					else if (MAP[down][right] == enemy)
					{
						now = enemy;
						if (right != j + 1)
						{
							if (now != last)
							{
								break;
							}
						}
						
						++Pla[i][j][3];
						last = enemy;
					}
					else
					{
						break;
					}
					++right;
					++down;
				}
			}
		}
	}
}

/* ����point, ���ص��������λ�� */
void ChessBoard::ComputerStep(int &x, int &y)
{
	int i, j, temp, max = 0;
	
	x = y = MAX_LEN / 2 + 1;
	JudgeMap();
	for (i = 0; i < MAX_LEN; ++i)
	{
		for (j = 0; j < MAX_LEN; ++j)
		{
			temp = Com[i][j][0] + Com[i][j][1] + Com[i][j][2] + Com[i][j][3];
			if (temp > max)
			{
				x = i;
				y = j;
				max = temp;
			}
			temp = Pla[i][j][0] + Pla[i][j][1] + Pla[i][j][2] + Pla[i][j][3];
			if (temp > max)
			{
				x = i;
				y = j;
				max = temp;
			}
			
			temp = Com[i][j][0];
			
			if (temp > max)
			{	
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j; 
				MAP[x][y] = me;
				return;
			}
			
			temp = Com[i][j][1];
			if (temp > max)
			{	
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j; 
				MAP[x][y] = me;
				return;
			}
			
			temp = Com[i][j][2];
			if (temp > max)
			{
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j; 
				MAP[x][y] = me;
				return;
			}
			
			temp = Com[i][j][3];
			if (temp > max)
			{
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j;
				MAP[x][y] = me;
				return;
			}
			
			temp = Pla[i][j][0];
			if (temp > max)
			{
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j;
				MAP[x][y] = me;
				return;
			}
			
			temp = Pla[i][j][1];
			if (temp > max)
			{
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j; 
				MAP[x][y] = me;
				return;
			}
			
			temp = Pla[i][j][2];
			if (temp > max)
			{
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp == 4)
			{
				x = i;
				y = j; 
				MAP[x][y] = me;
				return;
			}
			
			temp = Pla[i][j][3];
			if (temp > max)
			{
				max = temp;
				x = i;
				y = j;
			}
			
			if (temp ==4)
			{
				x = i;
				y = j; 
				MAP[x][y] = me;
				return;
			}
		}
	}

	for (i = 0; i < MAX_LEN; ++i) {
		for (j = 0; j < MAX_LEN; ++j)
		{
			temp = Com[i][j][0];
			if (temp == 3)
			{
				if (j - 1 >= 0 && j + 4 < MAX_LEN && 
					MAP[i][j-1] == 0 && 
					MAP[i][j+1] == me && 
					MAP[i][j+2] == me && 
					MAP[i][j+3] == me && 
					MAP[i][j+4]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
				else if (j + 1 < MAX_LEN && j - 4 >= 0 && 
					MAP[i][j+1] == 0 && 
					MAP[i][j-1] == me && 
					MAP[i][j-2] == me && 
					MAP[i][j-3] == me && 
					MAP[i][j-4]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
				else if (j + 2 < MAX_LEN && j - 3 >= 0 && 
					MAP[i][j-1] == me && 
					MAP[i][j-2] == me && 
					MAP[i][j-3] == 0 && 
					MAP[i][j+1] == me && 
					MAP[i][j+2]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
				else if (j + 3 < MAX_LEN && j - 2 >= 0 && 
					MAP[i][j+1] == me && 
					MAP[i][j+2] == me && 
					MAP[i][j+3] == 0 && 
					MAP[i][j-1] == me && 
					MAP[i][j-2]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
			}
			
			temp = Com[i][j][1];
			if (temp == 3)
			{
				if (i - 1 >= 0 && i + 4 < MAX_LEN && 
					MAP[i-1][j] == 0 && 
					MAP[i+1][j] == me && 
					MAP[i+2][j] == me && 
					MAP[i+3][j] == me && 
					MAP[i+4][j]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
				else if (i + 1 < MAX_LEN && i - 4 >= 0 && 
					MAP[i+1][j] == 0 && 
					MAP[i-1][j] == me && 
					MAP[i-2][j] == me && 
					MAP[i-3][j] == me && 
					MAP[i-4][j]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
				else if (i + 2 < MAX_LEN && i - 3 >= 0 && 
					MAP[i-1][j] == me && 
					MAP[i-2][j] == me && 
					MAP[i-3][j] == 0 && 
					MAP[i+1][j] == me && 
					MAP[i+2][j]==0)
				{
					x = i;
					y = j; 
					MAP[x][y] = me;
					return;
				}
				else if (i + 3 < MAX_LEN && i - 2 >= 0 && 
					MAP[i+1][j] == me && 
					MAP[i+2][j] == me && 
					MAP[i+3][j] == 0 && 
					MAP[i-1][j] == me && 
					MAP[i-2][j]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
			}
			
			temp = Com[i][j][2];
			if (temp == 3)
			{
				if (i + 4 < MAX_LEN && i - 1 >= 0 && 
					j + 1 < MAX_LEN && j - 4 >= 0 && 
					MAP[i-1][j+1] == 0 && 
					MAP[i+1][j-1] == me && 
					MAP[i+2][j-2] == me && 
					MAP[i+3][j-3] == me && 
					MAP[i+4][j-4] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i - 4 >= 0 && i + 1 < MAX_LEN && 
					j + 4 < MAX_LEN && j - 1 >= 0 && 
					MAP[i+1][j-1] == 0 && 
					MAP[i-1][j+1] == me && 
					MAP[i-2][j+2] == me && 
					MAP[i-3][j+3] == me && 
					MAP[i-4][j+4]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				} else if (i + 2 < MAX_LEN && i - 3 >= 0 && 
					j + 3 < MAX_LEN && j - 2 >= 0 && 
					MAP[i+2][j-2] == 0 && 
					MAP[i+1][j-1] == me && 
					MAP[i-1][j+1] == me && 
					MAP[i-2][j+2] == me && 
					MAP[i-3][j+3] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 3 < MAX_LEN && i - 2 >= 0 && 
					j - 3 >= 0 && j + 2 < MAX_LEN && 
					MAP[i+3][j-3] == 0 && 
					MAP[i+2][j-2] == me && 
					MAP[i+1][j-1] == me && 
					MAP[i-1][j+1] == me && 
					MAP[i-2][j+2]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				
			}
			
			temp=Com[i][j][3];
			if (temp == 3)
			{
				if (i + 4 < MAX_LEN && i - 1 >= 0 && 
					j + 4 < MAX_LEN && j - 1 >= 0 && 
					MAP[i-1][j-1] == 0 && 
					MAP[i+1][j+1] == me && 
					MAP[i+2][j+2] == me && 
					MAP[i+3][j+3] == me && 
					MAP[i+4][j+4]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i - 4 >= 0 && i + 1 < MAX_LEN && 
					j + 1 < MAX_LEN && j - 4 >= 0 && 
					MAP[i+1][j+1] == 0 && 
					MAP[i-1][j-1] == me && 
					MAP[i-2][j-2] == me && 
					MAP[i-3][j-3] == me && 
					MAP[i-4][j-4]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 2 < MAX_LEN && i - 3 >= 0 && 
					j + 2 < MAX_LEN && j - 3 >= 0 && 
					MAP[i+2][j+2] == 0 && 
					MAP[i+1][j+1] == me && 
					MAP[i-1][j-1] == me && 
					MAP[i-2][j-2] == me && 
					MAP[i-3][j-3] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 3 < MAX_LEN && i - 2 >= 0 && 
					j - 2 >= 0 && j + 3 < MAX_LEN && 
					MAP[i+3][j+3] == 0 && 
					MAP[i+2][j+2] == me && 
					MAP[i+1][j+1] == me && 
					MAP[i-1][j-1] == me && 
					MAP[i-2][j-2]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
			}
			
			temp = Pla[i][j][0];
			if (temp == 3)
			{
				if (j - 1 >= 0 && j + 4 < MAX_LEN && 
					MAP[i][j-1] == 0 && 
					MAP[i][j+1] == enemy && 
					MAP[i][j+2] == enemy && 
					MAP[i][j+3] == enemy && 
					MAP[i][j+4]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (j + 1 < MAX_LEN && j - 4 >= 0 && 
					MAP[i][j+1] == 0 && 
					MAP[i][j-1] == enemy && 
					MAP[i][j-2] == enemy && 
					MAP[i][j-3] == enemy && 
					MAP[i][j-4] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (j + 2 < MAX_LEN && j - 3 >= 0 && 
					MAP[i][j-1] == enemy && 
					MAP[i][j-2] == enemy && 
					MAP[i][j-3] == 0 && 
					MAP[i][j+1] == enemy && 
					MAP[i][j+2]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (j + 3 < MAX_LEN && j - 2 >= 0 && 
					MAP[i][j+1] == enemy && 
					MAP[i][j+2] == enemy && 
					MAP[i][j+3] == 0 && 
					MAP[i][j-1] == enemy && 
					MAP[i][j-2]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
			}
			
			temp = Pla[i][j][1];
			if (temp == 3)
			{
				if (i - 1 >= 0 && i + 4 < MAX_LEN && 
					MAP[i-1][j] == 0 && 
					MAP[i+1][j] == enemy && 
					MAP[i+2][j] == enemy && 
					MAP[i+3][j] == enemy && 
					MAP[i+4][j]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 1 < MAX_LEN && i - 4 >= 0 && 
					MAP[i+1][j] == 0 && 
					MAP[i-1][j] == enemy && 
					MAP[i-2][j] == enemy && 
					MAP[i-3][j] == enemy && 
					MAP[i-4][j]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 2 < MAX_LEN && i - 3 >= 0 && 
					MAP[i-1][j] == enemy && 
					MAP[i-2][j] == enemy && 
					MAP[i-3][j] == 0 && 
					MAP[i+1][j] == enemy && 
					MAP[i+2][j] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 3 < MAX_LEN && i - 2 >= 0 && 
					MAP[i+1][j] == enemy && 
					MAP[i+2][j] == enemy && 
					MAP[i+3][j] == 0 && 
					MAP[i-1][j] == enemy && 
					MAP[i-2][j]==0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
			}

			temp = Pla[i][j][2];
			if (temp == 3)
			{
				if (i + 4 < MAX_LEN && i - 1 >= 0 && 
					j + 1 < MAX_LEN && j - 4 >= 0 && 
					MAP[i-1][j+1] == 0 && 
					MAP[i+1][j-1] == enemy && 
					MAP[i+2][j-2] == enemy && 
					MAP[i+3][j-3] == enemy && 
					MAP[i+4][j-4] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i - 4 >= 0 && i + 1 < MAX_LEN && 
					j + 4 < MAX_LEN && j - 1 >= 0 && 
					MAP[i+1][j-1] == 0 && 
					MAP[i-1][j+1] == enemy && 
					MAP[i-2][j+2] == enemy && 
					MAP[i-3][j+3] == enemy && 
					MAP[i-4][j+4] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 2 < MAX_LEN && i - 3 >= 0 && 
					j + 3 < MAX_LEN && j - 2 >= 0 && 
					MAP[i+2][j-2] == 0 && 
					MAP[i+1][j-1] == enemy && 
					MAP[i-1][j+1] == enemy && 
					MAP[i-2][j+2] == enemy && 
					MAP[i-3][j+3] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 3 < MAX_LEN && i - 2 >= 0 && 
					j - 3 >= 0 && j + 2 < MAX_LEN && 
					MAP[i+3][j-3] == 0 && 
					MAP[i+2][j-2] == enemy && 
					MAP[i+1][j-1] == enemy && 
					MAP[i-1][j+1] == enemy && 
					MAP[i-2][j+2] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				
			}
			
			temp = Pla[i][j][3];
			if (temp == 3)
			{
				if (i + 4 < MAX_LEN && i - 1 >= 0 && 
					j + 4 < MAX_LEN && j - 1 >= 0 && 
					MAP[i-1][j-1] == 0 && 
					MAP[i+1][j+1] == enemy && 
					MAP[i+2][j+2] == enemy && 
					MAP[i+3][j+3] == enemy && 
					MAP[i+4][j+4] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i - 4 >= 0 && i + 1 < MAX_LEN && 
					j + 1 < MAX_LEN && j - 4 >= 0 && 
					MAP[i+1][j+1] == 0 && 
					MAP[i-1][j-1] == enemy && 
					MAP[i-2][j-2] == enemy && 
					MAP[i-3][j-3] == enemy && 
					MAP[i-4][j-4] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 2 < MAX_LEN && i - 3 >= 0 && 
					j + 2 < MAX_LEN && j - 3 >= 0 && 
					MAP[i+2][j+2] == 0 && 
					MAP[i+1][j+1] == enemy && 
					MAP[i-1][j-1] == enemy && 
					MAP[i-2][j-2] == enemy && 
					MAP[i-3][j-3] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
				else if (i + 3 < MAX_LEN && i - 2 >= 0 && 
					j - 2 >= 0 && j + 3 < MAX_LEN && 
					MAP[i+3][j+3] == 0 && 
					MAP[i+2][j+2] == enemy && 
					MAP[i+1][j+1] == enemy && 
					MAP[i-1][j-1] == enemy && 
					MAP[i-2][j-2] == 0)
				{
					x = i;
					y = j;
					MAP[x][y] = me;
					return;
				}
			}
			
		}
	} 
	
	MAP[x][y]=me; 
}

/* ����������Ӧ��λ��, ��ȡ����λ�� */
CPoint ChessBoard::FlgToLocation(const int &i, const int &j)
{
	int x, y;
	CPoint dest;

	x = i * GRID_SIZE + DEFAULT_X;
	y = j * GRID_SIZE + DEFAULT_Y;
	dest = CPoint(x, y);

	return dest;
}

/* ��ȡ�˵���ɫ */
int ChessBoard::GetFolkColor()
{
	return me;
}

/* ��ȡ���Ե���ɫ */
int ChessBoard::GetCompColor()
{
	return enemy;
}

/* ���� */
void ChessBoard::TakeBack()
{
}

/* ����һ���� */
void ChessBoard::SubChess(CRect &rect_a, CRect &rect_b)
{
	CRect rect;
	if (chs_len >= 2)
	{
		--chs_len;
		rect = chs[chs_len].ReFleshChess();
		rect_a = rect;	/* ����һ������ */
		RemoveFlg(chs[chs_len]);

		--chs_len;
		rect = chs[chs_len].ReFleshChess();
		rect_b = rect;	/* ������һ������ */
		RemoveFlg(chs[chs_len]);
	}
}

/* ɾ����� */
void ChessBoard::RemoveFlg(Chess chess)
{
	int i, j;

	i = (chess.GetX() - DEFAULT_X) / GRID_SIZE;
	j = (chess.GetY() - DEFAULT_Y) / GRID_SIZE;
	MAP[i][j] = NO_PLAYER;
}

/* ��ȡ������ */
int ChessBoard::GetChessesNum()
{
	return chs_len;
}
