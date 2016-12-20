
// DlgProxy.cpp : 实现文件
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
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
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
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CImageComparisonDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CImageComparisonDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImageComparisonDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IImageComparison 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {5D2CAD12-44D1-4B35-A140-18671B6AA0D8}
static const IID IID_IImageComparison =
{ 0x5D2CAD12, 0x44D1, 0x4B35, { 0xA1, 0x40, 0x18, 0x67, 0x1B, 0x6A, 0xA0, 0xD8 } };

BEGIN_INTERFACE_MAP(CImageComparisonDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CImageComparisonDlgAutoProxy, IID_IImageComparison, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {8B6CCAD6-AA1E-430F-8394-94DB52B83850}
IMPLEMENT_OLECREATE2(CImageComparisonDlgAutoProxy, "ImageComparison.Application", 0x8b6ccad6, 0xaa1e, 0x430f, 0x83, 0x94, 0x94, 0xdb, 0x52, 0xb8, 0x38, 0x50)


// CImageComparisonDlgAutoProxy 消息处理程序
