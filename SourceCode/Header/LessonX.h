/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;			// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������

    int             m_fGoldBornMinX;
	int	            m_fGoldBornMaxX;
	int	            m_fGoldBornMinY;
	int	            m_fGoldBornMaxY;
	int             m_iGoldCount;

	vector<CSprite*>golds;		            //�����飬ԭ��ͬ���������е�rockFishs����

	int				m_iGoldCoinCount;

	vector<CSprite*>goldCoins;				//�����ң�ԭ��ͬ��

	int             m_iDogCount;

	vector<CSprite*>Dogs;

	float			m_fHookRotation;		//����ͬ����ļн�
    int				m_iHookRotToLeft;		//���Ӱڶ��ķ���1 �� ��0 ��
    CSprite*		goldHook;			    //���Ӷ�Ӧ�ľ���

    int		        m_iHookState;	        //0 ��ʾ������ת��1��ʾ�ͷ����������Ӳ���ת,2��ʾ��������
    float			m_fHookSpeed;		    //�����ͷŵ��ٶ�
    CAnimateSprite*	goldMan;		        //�󹤶�Ӧ��Sprite

    float			m_fHookStartPosX;		//�洢���ӵĳ�ʼλ��
    float			m_fHookStartPosY;
    CSprite*		m_gotGold;		        //�洢ץ���Ľ��

public:
	CGameMain();                            //���캯��
	~CGameMain();                           //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();

	void			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );

	void			OnSpriteColSprite( const char *szSrcName, const char *szTarName );

	CSprite*		FindGoldSpriteByName(const char* szName);

	void			OnSpriteColWorldLimit( const char *szName, const int iColSide );

	CSprite*		FindSpriteByName(const char* szName);
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
