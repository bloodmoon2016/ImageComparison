
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CImageComparisonDlg;


// CImageComparisonDlgAutoProxy ����Ŀ��

class CImageComparisonDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CImageComparisonDlgAutoProxy)

	CImageComparisonDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CImageComparisonDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CImageComparisonDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CImageComparisonDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

