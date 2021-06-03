
// SysProg-3.MultiThreadView.h: CSysProg3MultiThreadView 클래스의 인터페이스
//

#pragma once


class CSysProg3MultiThreadView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSysProg3MultiThreadView() noexcept;
	DECLARE_DYNCREATE(CSysProg3MultiThreadView)

// 특성입니다.
public:
	CSysProg3MultiThreadDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSysProg3MultiThreadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SysProg-3.MultiThreadView.cpp의 디버그 버전
inline CSysProg3MultiThreadDoc* CSysProg3MultiThreadView::GetDocument() const
   { return reinterpret_cast<CSysProg3MultiThreadDoc*>(m_pDocument); }
#endif

