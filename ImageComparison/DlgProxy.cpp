
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageComparison.h"
#include "DlgProxy.h"
#include "ImageComparisonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageComparisonDlgAutoProxy

IMPLEMENT_DYNCREATE(CImageComparisonDlgAutoProxy, CCmdTarget)

CImageComparisonDlgAutoProxy::CImageComparisonDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CImageComparisonDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CImageComparisonDlg)))
		{
			m_pDialog = reinterpret_cast<CImageComparisonDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CImageComparisonDlgAutoProxy::~CImageComparisonDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CImageComparisonDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CImageComparisonDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImageComparisonDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IImageComparison ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {5D2CAD12-44D1-4B35-A140-18671B6AA0D8}
static const IID IID_IImageComparison =
{ 0x5D2CAD12, 0x44D1, 0x4B35, { 0xA1, 0x40, 0x18, 0x67, 0x1B, 0x6A, 0xA0, 0xD8 } };

BEGIN_INTERFACE_MAP(CImageComparisonDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CImageComparisonDlgAutoProxy, IID_IImageComparison, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {8B6CCAD6-AA1E-430F-8394-94DB52B83850}
IMPLEMENT_OLECREATE2(CImageComparisonDlgAutoProxy, "ImageComparison.Application", 0x8b6ccad6, 0xaa1e, 0x430f, 0x83, 0x94, 0x94, 0xdb, 0x52, 0xb8, 0x38, 0x50)


// CImageComparisonDlgAutoProxy ��Ϣ�������
