// TreeCtrlEx.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCTreeTest.h"
#include "TreeCtrlEx.h"


// CTreeCtrlEx

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)

CTreeCtrlEx::CTreeCtrlEx()
{

}

CTreeCtrlEx::~CTreeCtrlEx()
{
}

void CTreeCtrlEx::InsertPath(CString path, HTREEITEM hRoot)
{
    HTREEITEM hRootItem = InsertItem(path, hRoot);
    _InsertPath(path, hRootItem);
}

CString CTreeCtrlEx::GetItemPath(HTREEITEM hItem)
{
    CString strPath;
    strPath = GetItemText(hItem);
    while (hItem != NULL)
    {
        hItem = GetNextItem(hItem, TVGN_PARENT);
        CString strParent = GetItemText(hItem);
        if(!strParent.IsEmpty())
            strPath = strParent + _T("\\") + strPath;
    }
    return strPath;
}

void CTreeCtrlEx::_InsertPath(CString path, HTREEITEM hRoot)
{
    CFileFind nFindFile;
    CString str = L"";
    CString nPicFileName = L"";
    BOOL IsExist = FALSE;
    HTREEITEM hSubItem;
    nPicFileName.Format(L"%s\\*.*", path);
    IsExist = nFindFile.FindFile(nPicFileName);
    while (IsExist)
    {
        IsExist = nFindFile.FindNextFile();
        if (nFindFile.IsDots())
            continue;
        nPicFileName = nFindFile.GetFileName();
        //路径
        if (nFindFile.IsDirectory())
        {
            hSubItem = InsertItem(nPicFileName, hRoot);
            _InsertPath(nFindFile.GetFilePath(), hSubItem);
        }
        //else
        //{
        //    //文件
        //    str = nPicFileName.Right(4);
        //    if (!str.CompareNoCase(_T(".jpg")) || !str.CompareNoCase(_T(".tif")))
        //    {
        //        InsertItem(nPicFileName, hRoot);
        //    }
        //}
    }
    nFindFile.Close();
}


BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CTreeCtrlEx::OnNMCustomdraw)
END_MESSAGE_MAP()



// CTreeCtrlEx 消息处理程序




void CTreeCtrlEx::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    static bool this_item_select = false;
    switch (pNMCD->nmcd.dwDrawStage)	//判断状态   
    {
    case CDDS_PREPAINT:
        *pResult = CDRF_NOTIFYITEMDRAW;
        break;
    case CDDS_ITEMPREPAINT:
        this_item_select = false;
        if (IsWindowEnabled())
        {
            //设置选中行的颜色
            if (GetItemState((HTREEITEM)pNMCD->nmcd.dwItemSpec, LVIS_SELECTED) == LVIS_SELECTED)
            {
                this_item_select = true;
                //SetItemState(nmcd.dwItemSpec, 0, LVIS_SELECTED);
                pNMCD->clrText = RGB(0, 34, 82);
                pNMCD->clrTextBk = RGB(161, 200, 255);
            }
            ////设置偶数行的颜色
            //else if (nmcd.dwItemSpec % 2 == 0)
            //{
            //    lplvdr->clrText = CColorConvert::m_gray_color.dark3;
            //    lplvdr->clrTextBk = CColorConvert::m_gray_color.light3;
            //}
            ////设置奇数行的颜色
            else
            {
                pNMCD->clrText = RGB(60, 60, 60);
                pNMCD->clrTextBk = RGB(245, 245, 245);
            }

            //用背景色填充单元格，以去掉每行前面的空白
            //CRect rect = nmcd.rc;
            //CDC* pDC = CDC::FromHandle(nmcd.hdc);		//获取绘图DC
            //pDC->FillSolidRect(rect, lplvdr->clrTextBk);
        }
        else		//当控件被禁用时，显示文本设为灰色
        {
            //lplvdr->clrText = GRAY(140);
            //lplvdr->clrTextBk = GRAY(240);
        }
        *pResult = CDRF_NOTIFYPOSTPAINT;
        break;
    case CDDS_ITEMPOSTPAINT:
        //if (this_item_select)
        //    SetItemState(nmcd.dwItemSpec, 0xFF, LVIS_SELECTED);
        //*pResult = CDRF_DODEFAULT;
        break;
    }

    *pResult = 0;
}
