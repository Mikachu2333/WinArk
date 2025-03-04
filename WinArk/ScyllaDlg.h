#pragma once
#include "resource.h"
#include "HexEdit.h"
#include "ImportsHandling.h"
#include "ApiReader.h"


class CScyllaDlg 
	:public CDialogImpl<CScyllaDlg>,
	public CWinDataExchange<CScyllaDlg>,
	public CMessageFilter{
public:
	enum {IDD = IDD_SCYLLA};

	// Dialog Data eXchange, attaches/subclasses child controls to wrappers
	// DDX_CONTROL : subclass
	// DDX_CONTROL_HANDLE : attach
	BEGIN_DDX_MAP(CScyllaDlg)
		DDX_CONTROL_HANDLE(IDC_LIST_LOG,m_ListLog)
		DDX_CONTROL(IDC_OEP_ADDRESS,_oepAddress)
		DDX_CONTROL(IDC_IAT_ADDRESS,_iatAddress)
		DDX_CONTROL(IDC_IAT_SIZE,_iatSize)
		DDX_CONTROL(IDC_TREE_IMPORTS,_treeImports)
	END_DDX_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CScyllaDlg(const WinSys::ProcessManager& pm, ProcessInfoEx& px);

	BEGIN_MSG_MAP_EX(CScyllaDlg)
		MSG_WM_SIZE(OnSize)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CONTEXTMENU(OnContextMenu)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER_EX(IDC_BTN_AUTO_SEARCH,OnAutoSearch)
		COMMAND_ID_HANDLER_EX(IDC_BTN_GET_IMPORTS,OnGetImports)
	END_MSG_MAP()


	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void OnSize(UINT nType, CSize size);
	void OnDestroy();
	void OnContextMenu(CWindow wnd, CPoint point);

	void DisplayContextMenuLog(CWindow, CPoint);

	void EnableDialogControls(BOOL value);

	void ProcessHandler();
	void GetImportsHandler();

	void OnAutoSearch(UINT uNotifyCode, int nID, CWindow wndCtl);
	void OnGetImports(UINT uNotifyCode, int nID, CWindow wndCtl);

	bool IsIATOutsidePEImage(DWORD_PTR addressIAT);

protected:
	void SetupStatusBar();
	void UpdateStatusBar();

	enum StatusParts {
		Count = 0,
		Invalid,
		ImageBase,
		Module,
	};

	void IATAutoSearchActionHandler();

	WCHAR _text[512];
	ImportsHandling _importsHandling;
	CMultiSelectTreeViewCtrl _treeImports;
	ApiReader _ApiReader;

	CIcon _hIconError;
	CIcon _hIconWarning;
	CIcon _hIconCheck;

protected:
	void SetDialogIATAddressAndSize(DWORD_PTR addressIAT, DWORD sizeIAT);

private:
	ProcessInfoEx& m_px;
	const WinSys::ProcessManager& m_pm;
	CStatusBarCtrl m_StatusBar;
	
	CListBox m_ListLog;
	CAccelerator m_Accelerators;
	CHexEdit _oepAddress;
	CHexEdit _iatAddress;
	CHexEdit _iatSize;
	CIcon m_Icon;
	DWORD _pid;
};