
// SysProg-7.BackEventView.cpp: CSysProg7BackEventView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SysProg-7.BackEvent.h"
#endif

#include "SysProg-7.BackEventDoc.h"
#include "SysProg-7.BackEventView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysProg7BackEventView

IMPLEMENT_DYNCREATE(CSysProg7BackEventView, CView)

BEGIN_MESSAGE_MAP(CSysProg7BackEventView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CSysProg7BackEventView 생성/소멸
HANDLE hEvent30;
HANDLE hEventClac;
CSysProg7BackEventView::CSysProg7BackEventView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	hEvent30 = CreateEvent(NULL, FALSE, FALSE, NULL); //자동 리셋 이벤트
	hEventClac = CreateEvent(NULL, TRUE, FALSE, NULL); //수동 리셋 이벤트
}

CSysProg7BackEventView::~CSysProg7BackEventView()
{
	CloseHandle(hEvent30);
	CloseHandle(hEventClac);
}

BOOL CSysProg7BackEventView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSysProg7BackEventView 그리기

void CSysProg7BackEventView::OnDraw(CDC* /*pDC*/)
{
	CSysProg7BackEventDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSysProg7BackEventView 인쇄

BOOL CSysProg7BackEventView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSysProg7BackEventView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSysProg7BackEventView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSysProg7BackEventView 진단

#ifdef _DEBUG
void CSysProg7BackEventView::AssertValid() const
{
	CView::AssertValid();
}

void CSysProg7BackEventView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSysProg7BackEventDoc* CSysProg7BackEventView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSysProg7BackEventDoc)));
	return (CSysProg7BackEventDoc*)m_pDocument;
}
#endif //_DEBUG


// CSysProg7BackEventView 메시지 처리기
int buf[100];

DWORD WINAPI ThreadFunc(LPVOID p) {
	for (int i = 0; i < 100; i++)
	{
		Sleep(30);
		buf[i] = i;
		if (i == 10)
			SetEvent(hEvent30);
	}	
	return 0;
}


DWORD WINAPI ThreadClac(LPVOID p) {
	CSysProg7BackEventView* pView = (CSysProg7BackEventView*)p;
	CDC* pDC = pView->GetDC();
	for (int i = 0; i < 10; i++)
	{
		pDC->TextOut(500, 100, _T("계산중 Beats!!"));
		GdiFlush();
		Sleep(300);
		pDC->TextOut(500, 100, _T("기다려 Beats!!"));
		GdiFlush();
		Sleep(300);
	}
	pDC->TextOut(500, 100, _T("계산완료 Beats!!"));
	SetEvent(hEventClac);
	pView->ReleaseDC(pDC);
	return 0;
}
DWORD WINAPI ThreadSave(LPVOID p) {
	WaitForSingleObject(hEventClac, INFINITE);
	CSysProg7BackEventView* pView = (CSysProg7BackEventView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 200, _T("저장 Beats!!"));
	pView->ReleaseDC(pDC);
	
	return 0;
}
DWORD WINAPI ThreadSend(LPVOID p) {
	WaitForSingleObject(hEventClac, INFINITE);
	CSysProg7BackEventView* pView = (CSysProg7BackEventView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 300, _T("전송 Beats!!"));
	pView->ReleaseDC(pDC);
	return 0;
}
DWORD WINAPI ThreadPrint(LPVOID p) {
	WaitForSingleObject(hEventClac, INFINITE);
	CSysProg7BackEventView* pView = (CSysProg7BackEventView*)p;
	CDC* pDC = pView->GetDC();
	pDC->TextOut(500, 400, _T("인쇄 Beats!!"));
	pView->ReleaseDC(pDC);
	return 0;
}

void CSysProg7BackEventView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DWORD dwID;

	HANDLE hTh = CreateThread(
		NULL,
		0,
		ThreadFunc,
		this,
		0,
		&dwID
	);

	//WaitForSingleObject(hTh, INFINITE);
	WaitForSingleObject(hEvent30, INFINITE);

	CDC* pDC = GetDC();
	CString str;
	for (int i = 0; i < 30; i++)
	{
		str.Format(_T("%d 라인은 %d 입니다"), i, buf[i]);
		pDC->TextOut(10, i * 20, str);
	}
	CView::OnLButtonDown(nFlags, point);
}


void CSysProg7BackEventView::OnRButtonDown(UINT nFlags, CPoint point)
{
	ResetEvent(hEventClac);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DWORD dwID;
	HANDLE hTh = CreateThread(
		NULL,
		0,
		ThreadClac,
		this,
		0,
		&dwID
	);
	
	CloseHandle(CreateThread(
		NULL,
		0,
		ThreadSave,
		this,
		0,
		&dwID
	));
	CloseHandle(CreateThread(
		NULL,
		0,
		ThreadSend,
		this,
		0,
		&dwID
	));
	CloseHandle(CreateThread(
		NULL,
		0,
		ThreadPrint,
		this,
		0,
		&dwID
	));
	CView::OnRButtonDown(nFlags, point);
}
