
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once

class TW_ProgressCtrl {
private:
	int m_pos, m_min, m_max;
	COLORREF m_bk_color, m_fore_color;
	CRect m_rect;

public:
	TW_ProgressCtrl() : m_rect(0, 0, 0, 0)
	{
		m_pos = 0;
		m_min = 0;
		m_max = 0;
		m_bk_color = RGB(0, 80, 160);
		m_fore_color = RGB(0, 160, 255);
	}

	CRect GetRect()
	{
		return m_rect;
	}

	void Update(CWnd * ap_parent) {
		ap_parent->InvalidateRect(m_rect, 0);
	}

	void Update(CWnd * ap_parent, int a_pos) {
		ap_parent->InvalidateRect(m_rect, 0);
		SetPos(a_pos);
	}

	void Create(CWnd * ap_parent, int a_quide_ctrl_id) {
		ap_parent->GetDlgItem(a_quide_ctrl_id)->GetWindowRect(m_rect);
		ap_parent->ScreenToClient(m_rect);
	}

	void Create(CRect a_rect) {
		m_rect = a_rect;
	}

	void SetRange(int a_min, int a_max) {
		if (a_min == a_max) return;
		if (a_max < m_min) {
			m_max = a_min;
			m_min = a_max;
		}
		m_max = a_max;
		m_min = a_min;
	}

	inline void SetPos(int a_pos) {
		m_pos = a_pos;
		if (m_min > a_pos) m_pos = m_min;
		else if (m_max < a_pos) m_pos = m_max;
	}

	int GetPos() {
		return m_pos;
	}

	void SetColor(COLORREF a_bk_color, COLORREF a_fore_color)
	{
		m_bk_color = a_bk_color;
		m_fore_color = a_fore_color;
	}

	void Draw(CDC * ap_dc) {
		int pos = m_pos * m_rect.Width() / (m_max-m_min);
		ap_dc->FillSolidRect(m_rect.left + pos, m_rect.top, m_rect.Width(), m_rect.Height(), m_bk_color);
		ap_dc->FillSolidRect(m_rect.left, m_rect.top, pos, m_rect.Height(), m_fore_color);
	}
};

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	CProgressCtrl m_my_progress;

	CRect m_user_rect;
	TW_ProgressCtrl m_user_progress;
};
