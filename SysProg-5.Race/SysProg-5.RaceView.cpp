
// SysProg-5.RaceView.cpp: CSysProg5RaceView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SysProg-5.Race.h"
#endif

#include "SysProg-5.RaceDoc.h"
#include "SysProg-5.RaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysProg5RaceView

IMPLEMENT_DYNCREATE(CSysProg5RaceView, CView)

BEGIN_MESSAGE_MAP(CSysProg5RaceView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSysProg5RaceView 생성/소멸
CRITICAL_SECTION cs;
HANDLE hMutex;
CSysProg5RaceView::CSysProg5RaceView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	InitializeCriticalSection(&cs);
	hMutex = CreateMutex(NULL, FALSE, NULL);
}

CSysProg5RaceView::~CSysProg5RaceView()
{
	DeleteCriticalSection(&cs);
	CloseHandle(hMutex);
}

BOOL CSysProg5RaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSysProg5RaceView 그리기

void CSysProg5RaceView::OnDraw(CDC* /*pDC*/)
{
	CSysProg5RaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSysProg5RaceView 인쇄

BOOL CSysProg5RaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSysProg5RaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSysProg5RaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSysProg5RaceView 진단

#ifdef _DEBUG
void CSysProg5RaceView::AssertValid() const
{
	CView::AssertValid();
}

void CSysProg5RaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSysProg5RaceDoc* CSysProg5RaceView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSysProg5RaceDoc)));
	return (CSysProg5RaceDoc*)m_pDocument;
}
#endif //_DEBUG


// CSysProg5RaceView 메시지 처리기
int x;
BOOL Wait;
DWORD WINAPI ThreadDog(LPVOID p)
{
	
	CSysProg5RaceView* pView = (CSysProg5RaceView*)p;
	CDC* pDC = pView->GetDC();

	for (int i = 0; i < 100; i++)
	{
		//while (Wait == TRUE) { ; }
		//Wait = TRUE; //원자성을 가지지 못했기 때문
		//EnterCriticalSection(&cs);// 누가 먼저 들어갈지는 os 가 결정
		WaitForSingleObject(hMutex, INFINITE);

		///
		x = 100;
		Sleep(1);
		pDC->TextOutW(x, 100, _T("Dog"));
		///

		ReleaseMutex(hMutex);
		//LeaveCriticalSection(&cs);
		//Wait = FALSE;
	}

	pView->ReleaseDC(pDC);
	return 0;
}

DWORD WINAPI ThreadCat(LPVOID p)
{
	CSysProg5RaceView* pView = (CSysProg5RaceView*)p;
	CDC* pDC = pView->GetDC();

	for (int i = 0; i < 100; i++)
	{
		//while (Wait == TRUE) { ; }
		//Wait = TRUE; //원자성을 가지지 못했기 때문
		//EnterCriticalSection(&cs);// 누가 먼저 들어갈지는 os 가 결정
		WaitForSingleObject(hMutex, INFINITE);

		///
		x = 200;
		Sleep(1);
		pDC->TextOutW(x, 200, _T("Cat"));
		///
		ReleaseMutex(hMutex);
		//LeaveCriticalSection(&cs);
		//Wait = FALSE;
	}

	pView->ReleaseDC(pDC);
	return 0;
}

void CSysProg5RaceView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DWORD dwID;
	HANDLE hAnimal[2];
	hAnimal[0] = CreateThread(
		NULL,
		0,
		ThreadDog,
		this,
		0,
		&dwID
	);

	hAnimal[1] = CreateThread(
		NULL,
		0,
		ThreadCat,
		this,
		0,
		&dwID
	);

	//두 스레드가 종료되면 종료 메시지를 출력한다
	DWORD dw = WaitForMultipleObjects(2, hAnimal, FALSE, INFINITE);
	switch (dw)
	{
	case WAIT_FAILED:
		break;
	case WAIT_TIMEOUT:
		break;
	case WAIT_OBJECT_0+0:
		AfxMessageBox(_T("Close the Dog"));
		break;
	case WAIT_OBJECT_0+1:
		AfxMessageBox(_T("Close the Cat"));
		break;
	default:
		break;
	}
	CloseHandle(hAnimal[0]);
	CloseHandle(hAnimal[1]);
	CView::OnLButtonDown(nFlags, point);
}
