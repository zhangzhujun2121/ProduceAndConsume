
// ProduceAndConsumeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ProduceAndConsume.h"
#include "ProduceAndConsumeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include"manage.h"
vector<process*>manage::vec;
int manage::N = 3;
Semaphore manage::empty(N);
Semaphore manage::full(0);
Semaphore manage::mutex(1);

int n = 1;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProduceAndConsumeDlg 对话框



CProduceAndConsumeDlg::CProduceAndConsumeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRODUCEANDCONSUME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProduceAndConsumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ed);
	DDX_Control(pDX, IDC_EDIT2, ed1);
	DDX_Control(pDX, IDC_EDIT3, ed2);
	DDX_Control(pDX, IDC_EDIT5, ed3);
}

BEGIN_MESSAGE_MAP(CProduceAndConsumeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProduceAndConsumeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProduceAndConsumeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CProduceAndConsumeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CProduceAndConsumeDlg::OnBnClickedButton4)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProduceAndConsumeDlg 消息处理程序

BOOL CProduceAndConsumeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	string str;
	str = to_string(manage::N);
	GetDlgItem(IDC_EDIT4)->SetWindowTextA(str.c_str());
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProduceAndConsumeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProduceAndConsumeDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProduceAndConsumeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

static int num1 = 0;
static int num2 = 0;

void CProduceAndConsumeDlg::OnBnClickedButton1()
{
	// TODO: 
	manage::creatProcess(producer,n++);
	num1++;

}


void CProduceAndConsumeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	manage::creatProcess(consumer, n++);
	num2++;
}


void CProduceAndConsumeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Cstr;
	ed.GetWindowTextA(Cstr);
	string str= manage::update();
	Cstr += str.c_str();
	Cstr += "----------------------------------------------------------";
	Cstr += "----------------------------------------------------------";
	Cstr += "\r\n";
	ed.SetWindowTextA(Cstr);
	ed.LineScroll(ed.GetLineCount());
	
	if (num1 > num2)
	{
		ed1.SetWindowTextA(to_string(num1-num2).c_str());
		ed2.SetWindowTextA("0");
		if (num1-num2 > manage::N)
		{
			ed3.SetWindowTextA(to_string(num1-num2 - manage::N).c_str());
		}
		else
		{
			ed3.SetWindowTextA("0");
		}
	}
	else
	{
		ed2.SetWindowTextA(to_string(num2 - num1).c_str());
		ed1.SetWindowTextA("0");
		ed3.SetWindowTextA("0");
	}
}


void CProduceAndConsumeDlg::OnBnClickedButton4()
{
	CString str;
	GetDlgItem(IDC_BUTTON4)->GetWindowTextA(str);
	if (str == "自动执行")
	{
		GetDlgItem(IDC_BUTTON4)->SetWindowTextA("暂停");
		SetTimer(1, 1000, NULL);
	}
	else
	{
		GetDlgItem(IDC_BUTTON4)->SetWindowTextA("自动执行");
		KillTimer(1);
	}
		
	// TODO: 在此添加控件通知处理程序代码
}

void CProduceAndConsumeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent==1)
	{
		OnBnClickedButton3();
	}
	CDialogEx::OnTimer(nIDEvent);
}
