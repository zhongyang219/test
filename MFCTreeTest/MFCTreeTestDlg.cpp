
// MFCTreeTestDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCTreeTest.h"
#include "MFCTreeTestDlg.h"
#include "afxdialogex.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCTreeTestDlg 对话框



CMFCTreeTestDlg::CMFCTreeTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MFCTREETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTreeTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, m_tree_ctrl);
}

BEGIN_MESSAGE_MAP(CMFCTreeTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CMFCTreeTestDlg::OnNMRClickTree1)
END_MESSAGE_MAP()


// CMFCTreeTestDlg 消息处理程序

BOOL CMFCTreeTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

    //初始化树控件
    HTREEITEM hRoot = m_tree_ctrl.InsertItem(_T("根节点"));
    HTREEITEM hChild1 = m_tree_ctrl.InsertItem(_T("子节点1"), hRoot);
    HTREEITEM hChild2 = m_tree_ctrl.InsertItem(_T("子节点2"), hRoot);
    HTREEITEM hChild3 = m_tree_ctrl.InsertItem(_T("子节点3"), hRoot);

    HTREEITEM hRoot1 = m_tree_ctrl.InsertItem(_T("根节点1"));
    HTREEITEM hChild1_1 = m_tree_ctrl.InsertItem(_T("子节点1_1"), hRoot1);
    HTREEITEM hChild1_2 = m_tree_ctrl.InsertItem(_T("子节点1_2"), hRoot1);

    m_tree_ctrl.InsertPath(_T("D:\\Music"), NULL);
    m_tree_ctrl.InsertPath(_T("D:\\Temp"), NULL);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTreeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTreeTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCTreeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTreeTestDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    if(pNMHDR->hwndFrom == m_tree_ctrl.GetSafeHwnd())
    {
        CPoint point(GetMessagePos());
        unsigned int nFlags = 0;
        m_tree_ctrl.ScreenToClient(&point);
        HTREEITEM hItem = m_tree_ctrl.HitTest(point, &nFlags);
        CString path = m_tree_ctrl.GetItemPath(hItem);

        m_tree_ctrl.SetFocus();
        m_tree_ctrl.SelectItem(hItem);
        if ((nFlags& TVHT_ONITEM || nFlags & TVHT_ONITEMRIGHT || nFlags & TVHT_ONITEMINDENT) && (hItem != NULL))
        {
            CMenu MyMenu;
            MyMenu.LoadMenu(IDR_MENU1);//加载菜单资源
            CMenu* popup = MyMenu.GetSubMenu(0);
            GetCursorPos(&point);//获取当前光标的位置，以便使得菜单可以跟随光标这里也可以用m_tree.ClientToScreen(&point);
            popup->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);
        }
    }
    *pResult = 0;
}
