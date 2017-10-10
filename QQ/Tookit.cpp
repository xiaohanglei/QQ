#include "stdafx.h"
#include "Tookit.h"


CTookit::CTookit(void)
{
}


CTookit::~CTookit(void)
{
}
char * CTookit::ZhuanHuan(CString soure)  //将Cstring 转换成 char * 
{
	//***********************************************************************
	const size_t strsize=(soure.GetLength()+1)*2; // 宽字符的长度;   //*
	char * p_strname= new char[strsize]; //分配空间;                     *
	size_t sz=0;                                                       //*
	wcstombs_s(&sz,p_strname,strsize,soure,_TRUNCATE);	           //*
	return p_strname;
	//*********************************************                      *
}


void CTookit:: CopyCStringTToChar( char* pchDest, const CString& strSrc, int nDestLen )
{
	if ( pchDest == NULL )
	{
		return;
	}

#ifdef _UNICODE // 使用宽字节
	{
		WCHAR* pWStrSRc = const_cast<CString&>(strSrc).GetBuffer(0);
		int nTmplen = WideCharToMultiByte( CP_ACP, 0, pWStrSRc, -1, NULL, 0, NULL, NULL );
		char* pTemp = new char[nTmplen+1];
		memset( pTemp, 0, nTmplen+1 );
		WideCharToMultiByte( CP_ACP, 0, pWStrSRc, -1, pTemp, nTmplen+1, NULL, NULL );

		int nLen = strlen(pTemp);
		if( nLen + 1 > nDestLen )				
		{													
			strncpy( pchDest, pTemp, nDestLen-1 );		
			pchDest[nDestLen-1] = 0;					    
		}													
		else												    
		{													
			strcpy( pchDest, pTemp );							
		}

		delete []pTemp;
	}
#else // 使用窄字节
	{
		int nSrcLen = strSrc.GetLength();

		if( nSrcLen + 1 > nDestLen )				
		{													
			strncpy( pchDest, strSrc, nDestLen-1 );		
			pchDest[nDestLen-1] = 0;					    
		}													
		else												    
		{													
			strcpy( pchDest, strSrc );							
		}
	}
#endif
}


void CTookit::rand_id(char  * pDim)//产生流水帐号！
{
	//生成当前日期
	time_t tt = time(NULL);
	tm * p_time = localtime(&tt);
	char a_time[15] = {'0'};//
	strftime(a_time,sizeof(a_time),"%Y%m%d%H%M%S",p_time);
	strcat(pDim,a_time);

	//生成 5  位随机数
	srand(time(0));
	int n_rand = rand() % 100000;
	char rand_buf[6] ;
	sprintf(rand_buf,"%05d",n_rand);//转化为字符串

	//生成编号
	strcat(pDim,rand_buf);
}

char * CTookit::Zhongwen(CString cstr_name)
{
	int nLength = cstr_name.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP,0,cstr_name,nLength,NULL,0,NULL,NULL);
	char* path1 = new char[ nBytes + 1];
	memset(path1,0,nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, cstr_name, nLength, path1, nBytes, NULL, NULL); 
	path1[nBytes] = 0; 
	return path1;
}