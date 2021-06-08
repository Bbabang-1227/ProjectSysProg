
// SysProg-7.BackEventView.h: CSysProg7BackEventView 클래스의 인터페이스
//

#pragma once


class CSysProg7BackEventView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSysProg7BackEventView() noexcept;
	DECLARE_DYNCREATE(CSysProg7BackEventView)

// 특성입니다.
public:
	CSysProg7BackEventDoc* GetDocument() const;

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
	virtual ~CSysProg7BackEventView();
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SysProg-7.BackEventView.cpp의 디버그 버전
inline CSysProg7BackEventDoc* CSysProg7BackEventView::GetDocument() const
   { return reinterpret_cast<CSysProg7BackEventDoc*>(m_pDocument); }
#endif

