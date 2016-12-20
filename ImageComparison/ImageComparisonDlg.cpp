
// ImageComparisonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageComparison.h"
#include "ImageComparisonDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#define MAX_CORNERS 100
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageComparisonDlg 对话框


IMPLEMENT_DYNAMIC(CImageComparisonDlg, CDialogEx);

CImageComparisonDlg::CImageComparisonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageComparisonDlg::IDD, pParent)
	, TheImage(NULL)
	, SmallThreshold(_T(""))
	, BigThreshold(_T(""))
	, Filter(_T(""))
	, m_file_path(_T(""))
	, m_edit_light(0)
	, m_edit_contrast(0)
	, m_lines(0)
	, m_linee(0)
	, m_columns(0)
	, m_columne(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CImageComparisonDlg::~CImageComparisonDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CImageComparisonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SMALL_THRESHOLD, SmallThreshold);
	DDX_Text(pDX, IDC_BIG_THRESHOLD, BigThreshold);
	DDX_Text(pDX, IDC_FILTER, Filter);
	DDX_Text(pDX, IDC_FILE_PATH, m_file_path);
	DDX_Control(pDX, IDC_LIST_RESULTS, m_list_results);
	DDX_Control(pDX, IDC_SLIDER_LIGHT, m_light);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_contrast);
	DDX_Text(pDX, IDC_EDIT_LIGHT, m_edit_light);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_edit_contrast);
	DDV_MinMaxInt(pDX, m_edit_light, 0, 100);
	DDV_MinMaxInt(pDX, m_edit_contrast, 0, 100);
	DDX_Text(pDX, IDC_LINE_S, m_lines);
	DDX_Text(pDX, IDC_LINE_E, m_linee);
	DDX_Text(pDX, IDC_COLUMN_S, m_columns);
	DDX_Text(pDX, IDC_COLUMN_E, m_columne);
}

BEGIN_MESSAGE_MAP(CImageComparisonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_File_Open, &CImageComparisonDlg::OnFileOpen)
	ON_BN_CLICKED(IDC_CANNY, &CImageComparisonDlg::OnCanny)
	ON_BN_CLICKED(IDC_CORNERS, &CImageComparisonDlg::OnCorners)
	ON_BN_CLICKED(IDC_RESET, &CImageComparisonDlg::OnReset)
	ON_BN_CLICKED(IDC_GRAY, &CImageComparisonDlg::OnGray)
	ON_BN_CLICKED(IDC_THRESHOLD, &CImageComparisonDlg::OnThreshold)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RESULTS, &CImageComparisonDlg::OnListResults)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_MEDIAN_FILTERING, &CImageComparisonDlg::OnMedianFiltering)
	ON_BN_CLICKED(IDC_ELABORATION, &CImageComparisonDlg::OnElaboration)
	ON_BN_CLICKED(IDC_SHARPEN, &CImageComparisonDlg::OnSharpen)
	ON_BN_CLICKED(IDC_PHASH, &CImageComparisonDlg::OnPhash)
	ON_BN_CLICKED(IDC_FILE_SAVE_AS, &CImageComparisonDlg::OnFileSaveAs)
	ON_BN_CLICKED(IDC_EQIALIZATION, &CImageComparisonDlg::OnEqialization)
	ON_BN_CLICKED(IDC_MATCHING, &CImageComparisonDlg::OnMatching)
	ON_BN_CLICKED(IDC_GRAYVALUE, &CImageComparisonDlg::OnGrayvalue)
	ON_BN_CLICKED(IDC_TEST, &CImageComparisonDlg::OnTest)
	ON_BN_CLICKED(IDC_Average, &CImageComparisonDlg::OnAverage)
	ON_BN_CLICKED(IDC_GRAY_CONTRAST, &CImageComparisonDlg::OnGrayContrast)
END_MESSAGE_MAP()


// CImageComparisonDlg 消息处理程序

BOOL CImageComparisonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码
	CvSize ImgSize;
	ImgSize.height = IMAGE_HEIGHT;
	ImgSize.width = IMAGE_WIDTH;
	TheImage = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);

	m_light.SetRange(0, 100);//设置滑动范围
	m_light.SetTicFreq(1);//每10个单位画一刻度
	m_light.SetPageSize(1);
	m_light.SetPos(50);

	m_contrast.SetRange(0, 100);//设置滑动范围
	m_contrast.SetTicFreq(1);//每10个单位画一刻度
	m_contrast.SetPageSize(1);
	m_contrast.SetPos(50);

	m_edit_contrast = 50;
	m_edit_light = 50;//取得当前位置值	
	UpdateData(FALSE); //刷新edit控件

	m_list_results.DeleteAllItems();
	m_list_results.InsertColumn(0,_T( "时间"));
	m_list_results.InsertColumn(1,_T( "故障"));
	m_list_results.SetColumnWidth(0, 150);
	m_list_results.SetColumnWidth(1, 350);
	m_list_results.SetRedraw(FALSE);

	m_list_results.SetRedraw(TRUE);//显示

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageComparisonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageComparisonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();                // 重绘对话框
                   
		CDialogEx::UpdateWindow();                // 更新windows窗口，如果无这步调用，图片显示还会出现问题
		ShowImage(TheImage, IDC_PIC);    // 重绘图片函数
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImageComparisonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CImageComparisonDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CImageComparisonDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CImageComparisonDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CImageComparisonDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CImageComparisonDlg::OnFileOpen()                      //图像文件打开与载入
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog *dlg = new CFileDialog(
		TRUE, _T("*.bmp; *.JPG"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.JPG)|*.bmp; *.JPG| All Files (*.*) |*.*||"), NULL
		);                                        // 选项图片的约定
	dlg->m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	CString mPath, mFileName;

	if (dlg->DoModal() != IDOK)                    // 判断是否获得图片
		return;

	mPath = dlg->GetPathName();            // 获取图片路径
	mFileName = dlg->m_ofn.lpstrFileTitle;


	int len = WideCharToMultiByte(CP_ACP, 0, mPath, -1, NULL, 0, NULL, NULL);
	char *pfilePath = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, mPath, -1, pfilePath, len, NULL, NULL);
	
	
	IplImage* ipl = cvLoadImage(pfilePath);    // 读取图片、缓存到一个局部变量 ipl 中

	if (!ipl)                                    // 判断是否成功载入图片
		return;
	if (TheImage)                                // 对上一幅显示的图片数据清零
		cvZero(TheImage);

	ResizeImage(ipl);    // 对读入的图片进行缩放，使其宽或高最大值者刚好等于 256，再复制到 TheImage 中
	ShowImage(TheImage, IDC_PIC);            // 调用显示图片函数    
	cvReleaseImage(&ipl);                        // 释放 ipl 占用的内存
	delete dlg;
	
	img = imread(pfilePath, IMREAD_COLOR);

	m_file_path.Empty();
	m_file_path += mPath;
	UpdateData(FALSE);
	delete[] pfilePath;
}

void CImageComparisonDlg::OnFileSaveAs()
{
	CFileDialog *dlg = new CFileDialog(
		FALSE, _T("*.bmp; *.JPG"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("保存为(*.bmp;*.JPG)|*.bmp;*.JPG|所有文件(*.*)|*.*||"), NULL
		); 
	CString strPath("");

	if (dlg->DoModal() == IDOK)
	{
		strPath = dlg->GetPathName();
		const size_t strsize = (strPath.GetLength() + 1) * 2;
		char *pfilePath = new char[strsize];
		size_t sz = 0;
		wcstombs_s(&sz, pfilePath, strsize, strPath, _TRUNCATE);
		cvSaveImage(pfilePath, TheImage);
	}
	delete dlg;
}

void CImageComparisonDlg::ResizeImage(IplImage* img)
{
	// 读取图片的宽和高
	int w = img->width;
	int h = img->height;

	// 找出宽和高中的较大值者
	int max = (w > h) ? w : h;

	// 计算将图片缩放到TheImage区域所需的比例因子
	float scale = (float)((float)max / 256.0f);

	// 缩放后图片的宽和高
	int nw = (int)(w / scale);
	int nh = (int)(h / scale);

	// 为了将缩放后的图片存入 TheImage 的正中部位，需计算图片在 TheImage 左上角的期望坐标值
	int tlx = (nw > nh) ? 0 : (int)(256 - nw) / 2;
	int tly = (nw > nh) ? (int)(256 - nh) / 2 : 0;

	// 设置 TheImage 的 ROI 区域，用来存入图片 img
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// 对图片 img 进行缩放，并存入到 TheImage 中
	cvResize(img, TheImage);

	// 重置 TheImage 的 ROI 准备读入下一幅图片
	cvResetImageROI(TheImage);
}

void CImageComparisonDlg::ShowImage(IplImage* img, UINT ID)    // ID 是Picture Control控件的ID号
{
	CDC* pDC = GetDlgItem(ID)->GetDC();        // 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();                // 获取 HDC(设备句柄) 来进行绘图操作

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;            // 求出图片控件的宽和高
	int rh = rect.bottom - rect.top;
	int iw = img->width;                        // 读取图片的宽和高
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                    // 使图片的显示位置正好在控件的正中
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);                            // 复制图片
	cimg.DrawToHDC(hDC, &rect);                // 将图片绘制到显示控件的指定区域内

	ReleaseDC(pDC);
}


void CImageComparisonDlg::OnCanny()                     //边缘检测
{
	// TODO:  在此添加控件通知处理程序代码
	IplImage *gray = 0, *edge = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	edge = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);

	GetDlgItem(IDC_SMALL_THRESHOLD)->GetWindowText(SmallThreshold);
	GetDlgItem(IDC_BIG_THRESHOLD)->GetWindowText(BigThreshold);
	GetDlgItem(IDC_FILTER)->GetWindowText(Filter);

	int m_small_threshold = _ttoi(SmallThreshold);
	int m_big_threshold = _ttoi(BigThreshold);
	int m_filter = _ttoi(Filter);

	cvCanny(gray, edge, 80, 160, 3);
	cvCvtColor(edge, TheImage, CV_GRAY2BGR);
	ShowImage(TheImage, IDC_PIC);            // 调用显示图片函数

	cvReleaseImage(&gray);
	cvReleaseImage(&edge);
}


void CImageComparisonDlg::OnCorners()                     //角点检测
{
	// TODO:  在此添加控件通知处理程序代码
	int cornersCount = MAX_CORNERS;//得到的角点数目
	CvPoint2D32f corners[MAX_CORNERS];//输出角点集合
	IplImage *gray = 0, *corners1 = 0, *corners2 = 0;
	int i;
	CvScalar color = CV_RGB(255, 0, 0);

	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);

	//create empty images os same size as the copied images
	//两幅临时32位浮点图像，cvGoodFeaturesToTrack会用到
	corners1 = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	corners2 = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);

	cvGoodFeaturesToTrack(gray, corners1,
		corners2, corners,
		&cornersCount, 0.05,
		30,//角点的最小距离是30
		0,//整个图像
		3, 0, 0.4);
	//默认值
	//	printf("num corners found: %d/n", cornersCount);

	//开始画出每个点
	if (cornersCount > 0)
	{
		for (i = 0; i < cornersCount; i++)
		{
			cvCircle(TheImage, cvPoint((int)(corners[i].x), (int)(corners[i].y)),
				2, color, 2, CV_AA, 0);
		}
	}

	ShowImage(TheImage, IDC_PIC);

	cvReleaseImage(&gray);
	cvReleaseImage(&corners1);
	cvReleaseImage(&corners2);
}


void CImageComparisonDlg::OnReset()               //重置图像
{
	// TODO:  在此添加控件通知处理程序代码
	CRect Rect;
	(this->GetDlgItem(IDC_PIC))->GetClientRect(&Rect);
	GetDC()->FillSolidRect(&Rect, RGB(240, 240, 240));
	 
	int len = WideCharToMultiByte(CP_ACP, 0, m_file_path, -1, NULL, 0, NULL, NULL);
	 char *pfilePath = new char[len + 1];
	 WideCharToMultiByte(CP_ACP, 0,m_file_path , -1, pfilePath, len, NULL, NULL);

	IplImage* ipl = cvLoadImage(pfilePath);
	if (!ipl)                                    // 判断是否成功载入图片
		return;
	if (TheImage)                                // 对上一幅显示的图片数据清零
		cvZero(TheImage);
	ResizeImage(ipl);    
	ShowImage(TheImage, IDC_PIC);    
	m_contrast.SetPos(50);
	m_light.SetPos(50);
	m_edit_contrast = 50;
	m_edit_light = 50;
	cvReleaseImage(&ipl);
	delete[] pfilePath;
}


void CImageComparisonDlg::OnGray()                //灰度化
{
	// TODO:  在此添加控件通知处理程序代码
	IplImage *gray = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	cvCvtColor(gray, TheImage, CV_GRAY2BGR);

	ShowImage(TheImage, IDC_PIC);         
	cvReleaseImage(&gray);
}


void CImageComparisonDlg::OnThreshold()                //二值化
{
	// TODO:  在此添加控件通知处理程序代码
	IplImage *Threshold = 0, *gray = 0;

	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	Threshold = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);

	cvCvtColor(TheImage, gray, CV_BGR2GRAY);

	cvThreshold(gray, Threshold, 128, 256, CV_THRESH_BINARY);

	cvCvtColor(Threshold, TheImage, CV_GRAY2BGR);

	ShowImage(TheImage, IDC_PIC);
	cvReleaseImage(&Threshold);
	cvReleaseImage(&gray);
}


void CImageComparisonDlg::setContrastBrightness(double percentB, double percentC, Mat& img, Mat& result)
{
	const double pi = 3.1415926535898;

	//百分比转为调整系数，0~100  转为 -range~range，最大为[-1,1]
	const double Crange = 0.7;  //range越小，对比度调节的精度越高
	double C = (percentC - 50)* Crange / 50; //取值范围:[-range,range]
	const double Brange = 0.5;
	double B = (percentB - 50)* Brange / 50;

	double k = tan((45 + 44 * C) / 180 * pi);
	int channel = 0;
	int MAXGRAYVALUE = 0;
	int orgtype = img.type();
	switch (orgtype)
	{
	case CV_8UC1:
		channel = 1;
		MAXGRAYVALUE = 255;
		break;
	case CV_8UC3:
		channel = 3;
		MAXGRAYVALUE = 255;
		break;
	case CV_16UC1:
		channel = 1;
		MAXGRAYVALUE = 65535;
		break;
	default:
		MAXGRAYVALUE = 65535; break;
	}
	double threshold = MAXGRAYVALUE / 2;
	vector<Mat> mv(channel);
	Mat imgcyp;
	img.convertTo(imgcyp, CV_32F);
	split(imgcyp, mv);
	for (int i = 0; i < channel; i++)
	{
		mv[i] = (mv[i] - threshold * (1 - B)) * k + threshold * (1 + B);
	}
	merge(mv, result);

	result.convertTo(result, orgtype);
}

void CImageComparisonDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
	m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

	pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
	m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	
	UpdateData(FALSE); //刷新edit控件

	//刷新显示
	setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);

	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img=IplImage(img1);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImageComparisonDlg::OnMedianFiltering()        //去除椒盐噪声
{
	// TODO:  在此添加控件通知处理程序代码
	cv::Mat img = cv::cvarrToMat(TheImage);
	medianBlur(img, img1, 3);
	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img1);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}

bool CImageComparisonDlg::ThiningDIBSkeleton(unsigned char* lpDIBBits, int lWidth, int lHeight)
{
	//循环变量  
	long i;
	long j;
	long lLength;

	unsigned char deletemark[256] = {      // 这个即为前人据8领域总结的是否可以被删除的256种情况  
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
		1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0
	};//索引表  

	unsigned char p0, p1, p2, p3, p4, p5, p6, p7;
	unsigned char *pmid, *pmidtemp;    // pmid 用来指向二值图像  pmidtemp用来指向存放是否为边缘  
	unsigned char sum;
	bool bStart = true;
	lLength = lWidth * lHeight;
	unsigned char *pTemp = new uchar[sizeof(unsigned char)* lWidth * lHeight]();  //动态创建数组 并且初始化  

	//    P0 P1 P2  
	//    P7    P3  
	//    P6 P5 P4  

	while (bStart)
	{
		bStart = false;

		//首先求边缘点  
		pmid = (unsigned char *)lpDIBBits + lWidth + 1;
		memset(pTemp, 0, lLength);
		pmidtemp = (unsigned char *)pTemp + lWidth + 1; //  如果是边缘点 则将其设为1  
		for (i = 1; i < lHeight - 1; i++)
		{
			for (j = 1; j < lWidth - 1; j++)
			{
				if (*pmid == 0)                   //是0 不是我们需要考虑的点  
				{
					pmid++;
					pmidtemp++;
					continue;
				}
				p3 = *(pmid + 1);
				p2 = *(pmid + 1 - lWidth);
				p1 = *(pmid - lWidth);
				p0 = *(pmid - lWidth - 1);
				p7 = *(pmid - 1);
				p6 = *(pmid + lWidth - 1);
				p5 = *(pmid + lWidth);
				p4 = *(pmid + lWidth + 1);
				sum = p0 & p1 & p2 & p3 & p4 & p5 & p6 & p7;
				if (sum == 0)
				{
					*pmidtemp = 1;       // 这样周围8个都是1的时候  pmidtemp==1 表明是边缘                           
				}

				pmid++;
				pmidtemp++;
			}
			pmid++;
			pmid++;
			pmidtemp++;
			pmidtemp++;
		}

		//现在开始删除  
		pmid = (unsigned char *)lpDIBBits + lWidth + 1;
		pmidtemp = (unsigned char *)pTemp + lWidth + 1;

		for (i = 1; i < lHeight - 1; i++)   // 不考虑图像第一行 第一列 最后一行 最后一列  
		{
			for (j = 1; j < lWidth - 1; j++)
			{
				if (*pmidtemp == 0)     //1表明是边缘 0--周围8个都是1 即为中间点暂不予考虑  
				{
					pmid++;
					pmidtemp++;
					continue;
				}

				p3 = *(pmid + 1);
				p2 = *(pmid + 1 - lWidth);
				p1 = *(pmid - lWidth);
				p0 = *(pmid - lWidth - 1);
				p7 = *(pmid - 1);
				p6 = *(pmid + lWidth - 1);
				p5 = *(pmid + lWidth);
				p4 = *(pmid + lWidth + 1);

				p1 *= 2;
				p2 *= 4;
				p3 *= 8;
				p4 *= 16;
				p5 *= 32;
				p6 *= 64;
				p7 *= 128;

				sum = p0 | p1 | p2 | p3 | p4 | p5 | p6 | p7;
				//  sum = p0 + p1 + p2 + p3 + p4 + p5 + p6 + p7;  
				if (deletemark[sum] == 1)
				{
					*pmid = 0;
					bStart = true;      //  表明本次扫描进行了细化  
				}
				pmid++;
				pmidtemp++;
			}

			pmid++;
			pmid++;
			pmidtemp++;
			pmidtemp++;
		}
	}
	delete[]pTemp;
	return true;
}


void CImageComparisonDlg::OnElaboration()
{
	// TODO:  在此添加控件通知处理程序代码
	IplImage *src = 0,*gray = 0;

	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	src = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	cvThreshold(gray,src , 128, 256, CV_THRESH_BINARY);

	unsigned char* imagedata;

	imagedata = new uchar[sizeof(char)*src->width*src->height]();
	int x, y;
	for (y = 0; y < src->height; y++)
	{
	unsigned char* ptr = (unsigned char*)(src->imageData + y*src->widthStep);
	for (x = 0; x<src->width; x++)
	{
	imagedata[y*src->width + x] = ptr[x] > 0 ? 1 : 0;
	}
	}
	ThiningDIBSkeleton(imagedata, src->width, src->height);

	for (y = 0; y < src->height; y++)
	{
	unsigned char* ptr = (unsigned char*)(src->imageData + y*src->widthStep);
	for (x = 0; x<src->width; x++)
	{
	ptr[x] = imagedata[y*src->width + x]>0 ? 255 : 0;
	}

	}
	delete[]imagedata;
	

	cvCvtColor(src, TheImage, CV_GRAY2BGR);

	ShowImage(TheImage, IDC_PIC);
	cvReleaseImage(&src);
}

void CImageComparisonDlg::sharpen(const Mat &image, Mat &result)
{

	result.create(image.size(), image.type());
	for (int j = 1; j < image.rows - 1; j++)
	{
		const uchar* previous = image.ptr<const uchar>(j - 1);
		const uchar* current = image.ptr<const uchar>(j);
		const uchar* next = image.ptr<const uchar>(j + 1);

		uchar * output = result.ptr<uchar>(j);
		for (int i = 1; i < (image.cols - 1); i++)
		{
			output[i * 3] = saturate_cast<uchar>(5 * current[i * 3] - current[(i - 1) * 3] - current[(i + 1) * 3] - previous[i * 3] - next[i * 3]);
			output[i * 3 + 1] = saturate_cast<uchar>(5 * current[i * 3 + 1] - current[(i - 1) * 3 + 1] - current[(i + 1) * 3 + 1] - previous[i * 3 + 1] - next[i * 3 + 1]);
			output[i * 3 + 2] = saturate_cast<uchar>(5 * current[i * 3 + 2] - current[(i - 1) * 3 + 2] - current[(i + 1) * 3 + 2] - previous[i * 3 + 2] - next[i * 3 + 2]);
		}
	}
	result.row(0).setTo(Scalar(0, 0, 0));
	result.row(result.rows - 1).setTo(Scalar(0, 0, 0));
	result.col(0).setTo(Scalar(0, 0, 0));
	result.col(result.cols - 1).setTo(Scalar(0, 0, 0));
}



void CImageComparisonDlg::OnSharpen()
{
	// TODO:  在此添加控件通知处理程序代码
	cv::Mat img = cv::cvarrToMat(TheImage);

	Mat kernela(3, 3, CV_32F, Scalar(0));

	// assigns kernel values 

	kernela.at<float>(1, 1) = 5.0;
	kernela.at<float>(0, 1) = -1.0;
	kernela.at<float>(2, 1) = -1.0;
	kernela.at<float>(1, 0) = -1.0;
	kernela.at<float>(1, 2) = -1.0;

//	sharpen(img, img1);
	SharpenKernel(img, img1);

	//filter2D(img, img1, img.depth(), kernela);
	
	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img1);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}

void CImageComparisonDlg::SharpenKernel(const Mat &image, Mat &result)
{
	Mat kernel(3, 3, CV_32F, Scalar(0));
	kernel.at<float>(1, 1) = 5;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;
	filter2D(image, result, image.depth(), kernel);
	result.row(0).setTo(Scalar(0, 0, 0));
	result.row(result.rows - 1).setTo(Scalar(0, 0, 0));
	result.col(0).setTo(Scalar(0, 0, 0));
	result.col(result.cols - 1).setTo(Scalar(0, 0, 0));
}


void CImageComparisonDlg::OnPhash()
{
	// TODO:  在此添加控件通知处理程序代码
	cv::Mat img3 = cv::cvarrToMat(TheImage);
	string hash_1 = pHashValue(img3);

	cv::Mat img_standard_m = imread("F:\\show image\\img-05.JPG");
	string hash_2 = pHashValue(img_standard_m);

	int Hamming = HanmingDistance(hash_1, hash_2);

	if (Hamming > 10) { 
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("有变化"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("无变化"));
		m_list_results.SetRedraw(TRUE);//显示
	}
}

string CImageComparisonDlg::pHashValue(Mat &src)
{
	Mat imgg, dst;
	string rst(64, '\0');
	double dIdex[64];
	double mean = 0.0;
	int k = 0;
	if (src.channels() == 3)
	{
		cvtColor(src, src, CV_BGR2GRAY);
		imgg = Mat_<double>(src);
	}
	else
	{
		imgg = Mat_<double>(src);
	}

	/* 第一步，缩放尺寸*/
	resize(imgg, imgg, Size(8, 8));

	/* 第二步，离散余弦变换，DCT系数求取*/
	dct(imgg, dst);

	/* 第三步，求取DCT系数均值（左上角8*8区块的DCT系数）*/
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j)
		{
			dIdex[k] = dst.at<double>(i, j);
			mean += dst.at<double>(i, j) / 64;
			++k;
		}
	}

	/* 第四步，计算哈希值。*/
	for (int i = 0; i<64; ++i)
	{
		if (dIdex[i] >= mean)
		{
			rst[i] = '1';
		}
		else
		{
			rst[i] = '0';
		}
	}
	return rst;
}

int CImageComparisonDlg::HanmingDistance(string &str1, string &str2)
{
	if ((str1.size() != 64) || (str2.size() != 64))
		return -1;
	int difference = 0;
	for (int i = 0; i<64; i++)
	{
		if (str1[i] != str2[i])
			difference++;
	}
	return difference;
}



void CImageComparisonDlg::OnEqialization()
{
	IplImage *gray = 0;
	gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	cvEqualizeHist(gray, ipl_img);
	cvCvtColor(ipl_img, TheImage, CV_GRAY2BGR);
	ShowImage(TheImage, IDC_PIC);
	cvReleaseImage(&gray);
}


void CImageComparisonDlg::OnMatching()
{
	cv::Mat  area_standard, area_test;
	area_standard = imread("F:\\show image\\img-05.JPG");
	area_test = cv::cvarrToMat(TheImage);

	m_lines = GetDlgItemInt(IDC_LINE_S);
	m_linee = GetDlgItemInt(IDC_LINE_E);
	m_columns = GetDlgItemInt(IDC_COLUMN_S);
	m_columne = GetDlgItemInt(IDC_COLUMN_E);

	cv::Mat area_test_1 = area_test(Range(m_lines, m_linee), Range(m_columns, m_columne));//水瓶嘴(90,130)(45,80)   盒子（30，150）（80，170）
	cv::Mat area_standard_1 = area_standard(Range(m_lines, m_linee), Range(m_columns, m_columne));
	cv::rectangle(area_test, Rect(m_columns,m_lines , m_columne-m_columns, m_linee - m_lines), Scalar(0, 255, 0), 2, 1, 0);
	cv::rectangle(area_standard, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 2, 1, 0);

	string hash_1 = pHashValue(area_test_1);
	string hash_2 = pHashValue(area_standard_1);

	int Hamming = HanmingDistance(hash_1, hash_2);

	if (Hamming > 10) {
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("有变化"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("无变化"));
		m_list_results.SetRedraw(TRUE);//显示
	}
	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(area_test);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}


void CImageComparisonDlg::OnGrayvalue()
{
	cv::Mat   src = imread("F:\\show image\\img-06.JPG", 1);
	Scalar     mean;
	Scalar     stddev;

	cv::meanStdDev(src, mean, stddev);
	uchar       mean_pxl = mean.val[0];
	uchar       stddev_pxl = stddev.val[0];

	while(1){
		cv::Mat img_adj = cv::cvarrToMat(TheImage);
		cv::meanStdDev(img_adj, mean, stddev);
		uchar       mean_pxl_adj = mean.val[0];	
		if (abs(mean_pxl_adj - mean_pxl) < 2) break;
		else {
			CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
			m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	

			if (mean_pxl_adj - mean_pxl<0)
			{
				m_edit_light++;
				m_light.SetPos(m_edit_light);
			}
			else{ m_edit_light--; 
			m_light.SetPos(m_edit_light);
			}
			UpdateData(FALSE); //刷新edit控件
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);
			IplImage *ipl_img = NULL;
			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}
	while (1){
		cv::Mat img_adj = cv::cvarrToMat(TheImage);
		cv::meanStdDev(img_adj, mean, stddev);
		uchar       stddev_pxl_adj = stddev.val[0];
		if (abs(stddev_pxl_adj - stddev_pxl) < 2) break;
		else {
			CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
			m_edit_contrast = pSlidCtrl->GetPos();//取得当前位置值 

			pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
			m_edit_light = pSlidCtrl->GetPos();//取得当前位置值	

			if (stddev_pxl_adj - stddev_pxl < 0)
			{
				m_edit_contrast++;
				m_contrast.SetPos(m_edit_contrast);
			}
			else{
				m_edit_contrast--;
				m_contrast.SetPos(m_edit_contrast);
			}
			UpdateData(FALSE); //刷新edit控件
			setContrastBrightness(m_edit_light, m_edit_contrast, img, img1);
			IplImage *ipl_img = NULL;
			ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
			*ipl_img = IplImage(img1);
			ResizeImage(ipl_img);
		}
	}
	ShowImage(TheImage, IDC_PIC);
}


void CImageComparisonDlg::OnListResults(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码	
	*pResult = 0;
}



void CImageComparisonDlg::OnAverage()       //去除高斯白噪声
{
	cv::Mat img = cv::cvarrToMat(TheImage);
	blur(img, img1, Size(3, 3), Point(-1, -1));
	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(img1);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}

void CImageComparisonDlg::OnTest()
{
	IplImage *gray = 0, *edge = 0;
	cvCornerMinEigenVal(TheImage, edge, 1, 3);

	cvCvtColor(edge, TheImage, CV_GRAY2BGR);
	ShowImage(TheImage, IDC_PIC);            // 调用显示图片函数

	cvReleaseImage(&gray);
	cvReleaseImage(&edge);
}


void CImageComparisonDlg::OnGrayContrast()
{
	cv::Mat  area_standard, area_test;
	area_standard = imread("F:\\show image\\img-06.JPG");
	area_test = cv::cvarrToMat(TheImage);

	m_lines = GetDlgItemInt(IDC_LINE_S);
	m_linee = GetDlgItemInt(IDC_LINE_E);
	m_columns = GetDlgItemInt(IDC_COLUMN_S);
	m_columne = GetDlgItemInt(IDC_COLUMN_E);

	cv::Mat area_test_1 = area_test(Range(m_lines, m_linee), Range(m_columns, m_columne));//灯（115，140）（80，140）
	cv::Mat area_standard_1 = area_standard(Range(m_lines, m_linee), Range(m_columns, m_columne));
	cv::rectangle(area_test, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);//(左顶点列，左顶点行，长，宽，颜色，粗细，坐标点小数点后位数)
	cv::rectangle(area_standard, Rect(m_columns, m_lines, m_columne - m_columns, m_linee - m_lines), Scalar(0, 255, 0), 1, 1, 0);

	Scalar     mean;
	Scalar     stddev;

	cv::meanStdDev(area_test_1, mean, stddev);
	uchar       mean_pxl_test = mean.val[0];
	uchar       stddev_pxl_test = stddev.val[0];

	cv::meanStdDev(area_standard_1, mean, stddev);
	uchar       mean_pxl_standard = mean.val[0];
	uchar       stddev_pxl_standard = stddev.val[0];

	if (abs(mean_pxl_test-mean_pxl_standard) > 3) {
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("有变化"));
		m_list_results.SetRedraw(TRUE);
	}
	else{
		int nIndex;
		CTime m_time;
		m_time = CTime::GetCurrentTime();
		CString p;
		p = m_time.Format("%Y-%m-%d %H:%M:%S");
		nIndex = m_list_results.InsertItem(0, p);
		m_list_results.SetItemText(nIndex, 1, _T("无变化"));
		m_list_results.SetRedraw(TRUE);//显示
	}
	IplImage *ipl_img = NULL;
	ipl_img = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	*ipl_img = IplImage(area_test);
	ResizeImage(ipl_img);
	ShowImage(TheImage, IDC_PIC);
}
