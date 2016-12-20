
// ImageComparisonDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


class CImageComparisonDlgAutoProxy;


// CImageComparisonDlg 对话框
class CImageComparisonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageComparisonDlg);
	friend class CImageComparisonDlgAutoProxy;

// 构造
public:
	CImageComparisonDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CImageComparisonDlg();

// 对话框数据
	enum { IDD = IDD_IMAGECOMPARISON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CImageComparisonDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	IplImage* TheImage;
	afx_msg void OnFileOpen();
	void ShowImage(IplImage* img, UINT ID);
	void ResizeImage(IplImage* img);
	afx_msg void OnCanny();
	CString SmallThreshold;
	CString BigThreshold;
	CString Filter;
	CString m_file_path;
	afx_msg void OnCorners();
	afx_msg void OnReset();
	afx_msg void OnGray();
	afx_msg void OnThreshold();
	CListCtrl m_list_results;
	afx_msg void OnListResults(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void setContrastBrightness(double percentB, double percentC, Mat& img, Mat& result);
	CSliderCtrl m_light;
	CSliderCtrl m_contrast;
	int m_edit_light;
	int m_edit_contrast;
	Mat img,img1;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMedianFiltering();
	afx_msg void OnElaboration();
	afx_msg bool ThiningDIBSkeleton(unsigned char* lpDIBBits, int lWidth, int lHeight);
	afx_msg void sharpen(const Mat &img, Mat &result);
	afx_msg void OnSharpen();
	afx_msg void SharpenKernel(const Mat &image, Mat &result);
	afx_msg void OnPhash();
	string pHashValue(Mat &src);
	int HanmingDistance(string &str1, string &str2);
	afx_msg void OnFileSaveAs();
	afx_msg void OnEqialization();
	afx_msg void OnMatching();
	afx_msg void OnGrayvalue();
	afx_msg void OnTest();
	afx_msg void OnAverage();
	int m_lines;
	int m_linee;
	int m_columns;
	int m_columne;
	afx_msg void OnGrayContrast();
};
