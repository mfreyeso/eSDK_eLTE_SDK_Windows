/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

// CreateGroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eLTE_SDK_Demo.h"
#include "CreateGroupDlg.h"
#include "afxdialogex.h"


// CCreateGroupDlg dialog

IMPLEMENT_DYNAMIC(CCreateGroupDlg, CDialogEx)

CCreateGroupDlg::CCreateGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreateGroupDlg::IDD, pParent)
	, m_pDGNAParamInfo(NULL)
	, m_strDcId(_T(""))
	, m_bDynamic(false)
{

}

CCreateGroupDlg::~CCreateGroupDlg()
{
}

void CCreateGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCreateGroupDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDGROUP, &CCreateGroupDlg::OnBnClickedButtonAddgroup)
	ON_BN_CLICKED(IDC_BUTTON_DELGROUP, &CCreateGroupDlg::OnBnClickedButtonDelgroup)
	ON_BN_CLICKED(IDC_BUTTON_ADDUSER, &CCreateGroupDlg::OnBnClickedButtonAdduser)
	ON_BN_CLICKED(IDC_BUTTON_DELUSER, &CCreateGroupDlg::OnBnClickedButtonDeluser)
	ON_BN_CLICKED(IDOK, &CCreateGroupDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCreateGroupDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCreateGroupDlg message handlers


BOOL CCreateGroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_DCID);
	pEdit->SetReadOnly(TRUE);
	SetDlgItemText(IDC_EDIT_DCID, m_strDcId);
	CEdit* pEditGroupID = (CEdit*)GetDlgItem(IDC_EDIT_GROUPID);
	pEditGroupID->SetCueBanner(L"Auto distribute");
	if (m_bDynamic)
	{		
		SetDlgItemText(IDC_EDIT_PRIORITY, _T("15"));
		SetDlgItemText(IDC_EDIT_MAXPERIOD,_T("60"));
	}
	else
	{
		GetDlgItem(IDC_EDIT_GROUPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ALIAS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRIORITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAXPERIOD)->EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCreateGroupDlg::OnBnClickedButtonAddgroup()
{
	// TODO: Add your control notification handler code here
	CString strGroupID;
	GetDlgItemText(IDC_EDIT_GROUP_ID, strGroupID);
	if (strGroupID.IsEmpty())
		return;

	SetDlgItemText(IDC_EDIT_GROUP_ID, _T(""));

	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_GROUPLIST);

	if (LB_ERR != pList->FindString(-1, strGroupID))
	{
		return;
	}

	pList->AddString(strGroupID);
}


void CCreateGroupDlg::OnBnClickedButtonDelgroup()
{
	// TODO: Add your control notification handler code here
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_GROUPLIST);

	int nMaxItems = pList->GetSelCount();
	LPINT rgIndex = new INT[nMaxItems];
	memset(rgIndex, 0, sizeof(INT)*nMaxItems);
	pList->GetSelItems(nMaxItems, rgIndex);

	for (int i=0; i<nMaxItems; i++)
	{
		pList->DeleteString(rgIndex[i]-i);
	}

	delete []rgIndex;
}


void CCreateGroupDlg::OnBnClickedButtonAdduser()
{
	// TODO: Add your control notification handler code here
	CString strUserID;
	GetDlgItemText(IDC_EDIT_USER_ID, strUserID);
	if (strUserID.IsEmpty())
		return;

	SetDlgItemText(IDC_EDIT_USER_ID, _T(""));

	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_USERLIST);

	if (LB_ERR != pList->FindString(-1, strUserID))
	{
		return;
	}

	pList->AddString(strUserID);
}


void CCreateGroupDlg::OnBnClickedButtonDeluser()
{
	// TODO: Add your control notification handler code here
	CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_USERLIST);

	int nMaxItems = pList->GetSelCount();
	LPINT rgIndex = new INT[nMaxItems];
	memset(rgIndex, 0, sizeof(INT)*nMaxItems);
	pList->GetSelItems(nMaxItems, rgIndex);

	for (int i=0; i<nMaxItems; i++)
	{
		pList->DeleteString(rgIndex[i]-i);
	}

	delete []rgIndex;
}


void CCreateGroupDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString strGroupID,strDcID,strAlias,strPriority,strMaxPeriod;
	GetDlgItemText(IDC_EDIT_GROUPID, strGroupID);
	GetDlgItemText(IDC_EDIT_DCID, strDcID);
	GetDlgItemText(IDC_EDIT_ALIAS, strAlias);
	GetDlgItemText(IDC_EDIT_PRIORITY, strPriority);
	GetDlgItemText(IDC_EDIT_MAXPERIOD, strMaxPeriod);

	//if (strGroupID.IsEmpty())
	//{
	//	MessageBox(_T("GroupID is empty."));
	//	return;
	//}
	//if (strDcID.IsEmpty())
	//{
	//	MessageBox(_T("DcID is empty."));
	//	return;
	//}
	m_pDGNAParamInfo->GroupID = strGroupID;
	m_pDGNAParamInfo->DcID = strDcID;
	m_pDGNAParamInfo->Alias = strAlias;
	m_pDGNAParamInfo->Priority = strPriority;
	m_pDGNAParamInfo->MaxPeriod = strMaxPeriod;

	CListBox* pGroupList = (CListBox*)GetDlgItem(IDC_LIST_GROUPLIST);
	int iMaxCount = pGroupList->GetCount() > 8 ? 8 : pGroupList->GetCount();
	for (int i=0; i<iMaxCount; i++)
	{
		CString strGroup_ID;
		pGroupList->GetText(i, strGroup_ID);
		m_pDGNAParamInfo->GroupList[i] = strGroup_ID;
	}

	CListBox* pUserList = (CListBox*)GetDlgItem(IDC_LIST_USERLIST);
	iMaxCount = pUserList->GetCount() > 200 ? 200 : pUserList->GetCount();
	for (int i=0; i<iMaxCount; i++)
	{
		CString strUser_ID;
		pUserList->GetText(i, strUser_ID);
		m_pDGNAParamInfo->UserList[i] = strUser_ID;
	}

	CDialogEx::OnOK();
}


void CCreateGroupDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CCreateGroupDlg::SetDGNAParamInfo(CString strDcId, DGNAParamInfo* pInfo, bool bDynamic)
{
	m_strDcId = strDcId;
	m_pDGNAParamInfo = pInfo;
	m_bDynamic = bDynamic;
}
