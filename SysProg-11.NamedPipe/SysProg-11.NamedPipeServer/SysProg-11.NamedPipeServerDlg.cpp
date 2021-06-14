
// SysProg-11.NamedPipeServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SysProg-11.NamedPipeServer.h"
#include "SysProg-11.NamedPipeServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSysProg11NamedPipeServerDlg 대화 상자



CSysProg11NamedPipeServerDlg::CSysProg11NamedPipeServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSPROG11NAMEDPIPESERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSysProg11NamedPipeServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSysProg11NamedPipeServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT, &CSysProg11NamedPipeServerDlg::OnEnChangeEdit)
	ON_BN_CLICKED(IDC_BUTTON_START, &CSysProg11NamedPipeServerDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CSysProg11NamedPipeServerDlg 메시지 처리기

BOOL CSysProg11NamedPipeServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSysProg11NamedPipeServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSysProg11NamedPipeServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSysProg11NamedPipeServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSysProg11NamedPipeServerDlg::OnEnChangeEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
DWORD WINAPI ListenThread(LPVOID p)
{
	CSysProg11NamedPipeServerDlg* pWnd = (CSysProg11NamedPipeServerDlg*)p;
	while (true)
	{
		HANDLE hPipe = CreateNamedPipe(
			_T("\\\\.\\pipe\\mypipe"),
			PIPE_ACCESS_OUTBOUND, // 내보내는
			PIPE_TYPE_BYTE,
			PIPE_UNLIMITED_INSTANCES, //255
			4096,
			0,
			0,
			NULL);
		pWnd->SetDlgItemText(IDC_EDIT, _T("파이프 생성"));
		BOOL bConnect = ConnectNamedPipe(hPipe, NULL);
		if (bConnect == FALSE && GetLastError() == ERROR_PIPE_CONNECTED)
		{
			bConnect = TRUE;
		}
		if (bConnect)
		{
			pWnd->SetDlgItemText(IDC_EDIT, _T("접속 대기"));
			DWORD dwWritten;
			TCHAR* strMessage = _T("야무지게 긴 문자열 병원에가서 진료를 받아요");
			WriteFile(
				hPipe,
				strMessage,
				lstrlen(strMessage) + 1 * sizeof(TCHAR),
				&dwWritten,
				NULL);
			//연결해제
			FlushFileBuffers(hPipe);
			DisconnectNamedPipe(hPipe);
		}
	}

	// 3. 정보 주고 받기(1회성)
	pWnd->SetDlgItemText(IDC_EDIT, _T("정보 주고 받기(1회성)"));
	// 4. 뒷처리
	pWnd->SetDlgItemText(IDC_EDIT, _T("뒷처리"));
	return 0;
}

void CSysProg11NamedPipeServerDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CloseHandle(CreateThread(
		NULL,
		0,
		ListenThread,
		this,
		0,
		0
	));
}
