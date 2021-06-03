
// SysProg-3.MultiThreadView.cpp: CSysProg3MultiThreadView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SysProg-3.MultiThread.h"
#endif

#include "SysProg-3.MultiThreadDoc.h"
#include "SysProg-3.MultiThreadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSysProg3MultiThreadView

IMPLEMENT_DYNCREATE(CSysProg3MultiThreadView, CView)

BEGIN_MESSAGE_MAP(CSysProg3MultiThreadView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSysProg3MultiThreadView 생성/소멸

CSysProg3MultiThreadView::CSysProg3MultiThreadView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSysProg3MultiThreadView::~CSysProg3MultiThreadView()
{
}

BOOL CSysProg3MultiThreadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSysProg3MultiThreadView 그리기
int nBlue;
void CSysProg3MultiThreadView::OnDraw(CDC* pDC)
{
	CSysProg3MultiThreadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.	
}




// CSysProg3MultiThreadView 인쇄

BOOL CSysProg3MultiThreadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSysProg3MultiThreadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSysProg3MultiThreadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSysProg3MultiThreadView 진단

#ifdef _DEBUG
void CSysProg3MultiThreadView::AssertValid() const
{
	CView::AssertValid();
}

void CSysProg3MultiThreadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSysProg3MultiThreadDoc* CSysProg3MultiThreadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSysProg3MultiThreadDoc)));
	return (CSysProg3MultiThreadDoc*)m_pDocument;
}
#endif //_DEBUG


// CSysProg3MultiThreadView 메시지 처리기
CSysProg3MultiThreadView* g_pView;
DWORD WINAPI ThreadDraw(LPVOID p)
{
	CDC* pDC = g_pView->GetDC();
	RECT rc = *(LPRECT)p;
	while (1)
	{
		nBlue += 5;
		if (nBlue > 255) nBlue = 0;

		CBrush brBlue(RGB(rand()%256, rand() % 256, nBlue));
		CBrush* oldBr = pDC->SelectObject(&brBlue);
		pDC->Rectangle(rc.left,rc.top,rc.right,rc.bottom);
		pDC->SelectObject(oldBr);
	}

	g_pView->ReleaseDC(pDC);
	return 0;
}

void CSysProg3MultiThreadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	g_pView = this;
	DWORD dwID;

	static RECT arRect[] = {
		{100,100,200,200},
		{300,100,400,200},
		{100,300,200,400},
		{300,300,400,400}
	};
	
	for (int i = 0; i < 4; i++)
	{
		CloseHandle(
			CreateThread(
				NULL,
				0,
				ThreadDraw,
				&arRect[i],
				0,
				&dwID
			));
	}
	CView::OnLButtonDown(nFlags, point);
}
