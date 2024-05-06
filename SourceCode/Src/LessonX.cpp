/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include <vector>
#include "CommonClass.h"
#include "LessonX.h"
#include <vld.h>
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	_CrtSetBreakAlloc(106);//

    goldHook            = new CSprite("goldhook");		//��������ʵ��
    goldMan             = new CAnimateSprite("goldMan");
	m_iGameState		=	1;
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
	free(goldHook);
	free(goldMan);	
	for (auto it : golds) {
		free(it);
	}
	for (auto it : goldCoins) {
		free(it);
	}
	for (auto it : Dogs) {
		free(it);
	}
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
    m_iGoldCount		=	30;	//���ӳ�ʼ����
	m_iGoldCoinCount	=	5;	//�������
	m_iDogCount         =   3;  //������

	m_fGoldBornMinX		=	CSystem::GetScreenLeft() + 5;		//������߽�
	m_fGoldBornMaxX		=	CSystem::GetScreenRight() - 5;		//�����ұ߽�
	m_fGoldBornMinY		=	CSystem::GetScreenTop() + 20;		//�����ϱ߽�
	m_fGoldBornMaxY		=	CSystem::GetScreenBottom() -5;		//�����±߽�

    m_iHookRotToLeft    =	1;					    //���ӳ�ʼ������Ϊ��
	m_fHookRotation     =	0.f;					//��ʼ���ļн�Ϊ0

	m_iHookState        =	0;		                //��ʼ�����ʹ������ת
    m_fHookSpeed        =	15.f;

    m_fHookStartPosX    =	goldHook->GetSpritePositionX();	//��ȡ���ӵĳ�ʼ��X����
	m_fHookStartPosY    =	goldHook->GetSpritePositionY();//��ȡ���ӵĳ�ʼ��Y����

	int	iLoop	        =	0;	                    //ѭ����������
	int	iSize			=	4,		iPosX			=	0,		iPosY			=	0;//iSize��ʾ����С�ı���
	for( iLoop = 0; iLoop < m_iGoldCount; iLoop++ )	{
		if( iLoop < 15 )		                    //����10��С��飬��СΪ4
		{
			iSize	    =	4;
		}
		else if( iLoop >= 15 && iLoop < 24 )	    //����6���н�飬��СΪ6
		{
			iSize	    =	6;
		}
		else			//����4�����飬��СΪ8
		{
			iSize	    =	8;
		}
		//��ʼ�����Ӿ���ʵ��
		char* tmpName;
		//���ɽ������
		tmpName=CSystem::MakeSpriteName("GoldBlock",iLoop);
		CSprite *tmpSprite = new CSprite(tmpName);
		tmpSprite->CloneSprite("goldTemplate");
		tmpSprite->SetSpriteWidth(iSize);			//���ý��Ŀ��
		tmpSprite->SetSpriteHeight(iSize);			//���ý��ĸ߶�
		//����Ļ�ȡ���ӵ�X�����Y����
		iPosX	        =	CSystem::RandomRange(m_fGoldBornMinX, m_fGoldBornMaxX);
		iPosY	        =	CSystem::RandomRange(m_fGoldBornMinY, m_fGoldBornMaxY);
         //���ý�龫���λ��
		tmpSprite->SetSpritePosition(iPosX, iPosY);
		golds.push_back(tmpSprite);	                //�����ѹ��golds vector�м��й���
	}
	for( iLoop = 0; iLoop < m_iGoldCoinCount; iLoop++ ) {
		//��ʼ����Ҿ���ʵ��
		char* tmpName;
		//���ɽ������
		tmpName=CSystem::MakeSpriteName("GoldCoin", iLoop);
		CSprite* tmpSprite = new CSprite(tmpName);
		tmpSprite->CloneSprite("goldCoin");
		//����Ļ�ȡ��ҵ�X�����Y����
		iPosX = CSystem::RandomRange(m_fGoldBornMinX, m_fGoldBornMaxX);
		iPosY = CSystem::RandomRange(m_fGoldBornMinY, m_fGoldBornMaxY);
		//���ý�Ҿ����λ��
		tmpSprite->SetSpritePosition(iPosX, iPosY);
        //�����ѹ��goldCoin vector�м��й���
		goldCoins.push_back(tmpSprite);
	}
	for( iLoop = 0; iLoop < m_iDogCount; iLoop++ ){
		//��ʼ��������ʵ��
        char* tmpName;
		//���ɹ�����
        tmpName=CSystem::MakeSpriteName("Dog", iLoop);
        CSprite* tmpSprite = new CSprite(tmpName);
		tmpSprite->CloneSprite("dog");
		//����Ļ�ȡ����X�����Y����
		iPosX = CSystem::RandomRange(m_fGoldBornMinX, m_fGoldBornMaxX);
		iPosY = CSystem::RandomRange(m_fGoldBornMinY, m_fGoldBornMaxY);
		//���ù������λ��
		tmpSprite->SetSpritePosition(iPosX, iPosY);
		//���ù����������ƶ�
		tmpSprite->SetSpriteLinearVelocity(-12, 0);
        //�����ѹ��Dogs vector�м��й���
		Dogs.push_back(tmpSprite);
	}
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
	if(m_iHookState ==0){		                    //��m_iHookState==0ʱ���ӲŰڶ�
        const float	fRotateSpeed = 45.f; 			//  ҡ���ٶȣ���λ ��/��
        float fThisRotate =	fRotateSpeed * fDeltaTime;  // ������ת�ĽǶ�
        if( m_iHookRotToLeft ){					    //����ת���������ϱ��
            m_fHookRotation	+= fThisRotate;
            if( m_fHookRotation >= 180.f ){		    //����180����Ϊ����ת����0
                m_fHookRotation		=	180.f;
                m_iHookRotToLeft	=	0;
            }
        }
        else{		//����ת���������ϱ�С
            m_fHookRotation	-= fThisRotate;		    //С��0����Ϊ����ת���� 1
            if( m_fHookRotation <= 0.f ){
                m_fHookRotation		=	0.f;
                m_iHookRotToLeft	=	1;
            }
        }
        goldHook->SetSpriteRotation(m_fHookRotation);//���ù��ӵĵ�ǰ�Ƕ�
	}else if(m_iHookState == 1 || m_iHookState == 2){		            //��������������Ҫ����
		// ���ȣ��ӿ󹤾����ϻ�ȡһ���������ӵ���Ϊ���ӵ���ʼ��(�����ӵ��ڱ༭����༭��)
		float fStartX =	goldMan->GetSpriteLinkPointPosX(1);
		float fStartY = goldMan->GetSpriteLinkPointPosY(1);
		// �����յ��ڹ��Ӿ����ϻ�ȡ(�����ӵ��ڱ༭����༭��)
		float fEndX	= goldHook->GetSpriteLinkPointPosX(1);
		float fEndY	= goldHook->GetSpriteLinkPointPosY(1);
		// ��������֮�仮��.�ߵ���ɫ������ֵ��Ϊ50������ɫ��255��ʾ��͸����2.0f��ʾ�ߵĴ�ϸ��0��ʾ���ڵĲ�
		CSystem::DrawLine(fStartX, fStartY, fEndX, fEndY, 2.f, 0, 50, 50, 50, 255 );
        if(m_iHookState == 2){		//����������
			float	fSpeedX	=	goldHook->GetSpriteLinearVelocityX();	//��ȡ����X������ٶ�
			float	fSpeedY	=	goldHook->GetSpriteLinearVelocityY();	//��ȡ����Y������ٶ�
			//���ٶȽӽ�Ϊ0ʱ�������ж����ѵ����ʼ��
			if( fSpeedX < 0.00001f && fSpeedX > -0.00001f && fSpeedY < 0.00001f && fSpeedY > -0.00001f ){
				m_gotGold->SpriteDismount();	//�������빳�ӵ�ê��
				m_gotGold->DeleteSprite();		//ɾ����ȡ�Ľ��
				m_iHookState = 0;				//�����������趨����״̬Ϊ0,�������ذڶ�
				goldMan->AnimateSpritePlayAnimation("GolderManAnimation2", false);	//���ſ󹤵Ķ�������׼�������ӵĶ���
			}
		}
	}
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}

void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress ){
	if( KEY_DOWN == iKey &&  m_iHookState == 0){		//���¡�������Ϸ״̬Ϊ	��1��
		m_iHookState = 1;		//����Ϸ״̬Ϊ1�������ڿ��ƹ����Ƿ�ڶ�
		// �Ե�ǰ���������һ����ǰ���ٶ�
		goldHook->SetSpriteLinearVelocityPolar(m_fHookSpeed, m_fHookRotation);
		// �����ڽ��ߵĶ���(һ���첲����ѹ�Ķ���)
		goldMan->AnimateSpritePlayAnimation("GolderManAnimation1", 0);	//0 ��ʾ����һ�Σ�����첲����ѹ����һ��
	}
}

void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName ){
    if(strcmp(szSrcName, "goldhook")     == 0 &&
       (strstr(szTarName, "GoldBlock")   !=NULL ||
        strstr(szTarName, "Dog")         !=NULL ||
        strstr(szTarName, "GoldCoin")    !=NULL
        )){
        m_gotGold = FindGoldSpriteByName(szTarName);	//��golds�в����Ƿ���ڶ�Ӧ�Ľ�飬������CSprite*ָ��ָ��ý��
            if(m_gotGold!=NULL){
            //˼����Ϊʲô���ӵ��λ��Ϊ2��
            m_gotGold->SpriteMountToSpriteLinkPoint("GoldHook", 2 );	//�����ê���ڹ�����
            goldHook->SpriteMoveTo(m_fHookStartPosX, m_fHookStartPosY, m_fHookSpeed, 1);	//ʹ�������ʼλ���ƶ���������
            //˼����AnimateSpritePlayAnimation�е�false������������ʲô��
            goldMan->AnimateSpritePlayAnimation("GolderManAnimation3", false );	//���������Ķ���
            m_iHookState = 2;		//��ʾ��������״̬
        }
	}
}


CSprite* CGameMain::FindGoldSpriteByName(const char* szName)
{
    int iLoop;
	for(int iLoop=0;iLoop<golds.size();iLoop++)
		if(strcmp(szName,golds[iLoop]->GetName())==0)
			return golds[iLoop];
    for(int iLoop=0;iLoop<goldCoins.size();iLoop++)
		if(strcmp(szName,goldCoins[iLoop]->GetName())==0)
			return goldCoins[iLoop];
    for(int iLoop=0;iLoop<Dogs.size();iLoop++)
		if(strcmp(szName,Dogs[iLoop]->GetName())==0)
			return Dogs[iLoop];
	return NULL;
}

void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide ){
	CSprite* tmp;
	if(strcmp(szName,"goldhook") == 0){		//�����߽��Ϊ����ʱ
			goldHook->SpriteMoveTo(m_fHookStartPosX, m_fHookStartPosY, m_fHookSpeed, 1);
		goldMan->AnimateSpritePlayAnimation("GolderManAnimation3", false );
		m_iHookState = 2;	//ͬ������Ϊ������ֻ��û����������
	}
	if((tmp = FindSpriteByName(szName))!=NULL){
        if(iColSide == 1){
			tmp->SetSpriteLinearVelocityX(-12.f);
			tmp->SetSpriteFlipX(false);
		}else if(iColSide == 0){
			tmp->SetSpriteLinearVelocityX(12.f);
			tmp->SetSpriteFlipX(true);
		}
    }
}

CSprite* CGameMain::FindSpriteByName(const char* szName)
{
    for(int i=0;i<Dogs.size();i++)			//size()����vector�Ĵ�С
        if(strcmp(szName,Dogs[i]->GetName())==0)	//����vector������szName������ͬ�����Ƶ�Dogs�еľ���
            return Dogs[i];
    return NULL;
}
