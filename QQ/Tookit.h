#pragma once
class CTookit
{
public:
	CTookit(void);
	~CTookit(void);
	static char * ZhuanHuan(CString soure);//��Cstring ת���� char * 
	static void CopyCStringTToChar( char* pchDest, const CString& strSrc, int nDestLen );
	static void rand_id(char  * pDim);//������ˮ�ʺţ�
	static char * Zhongwen(CString cstr_name);
};

