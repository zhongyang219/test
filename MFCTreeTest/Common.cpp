#include "stdafx.h"
#include "Common.h"


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

void CCommon::InsertPath(CString path, HTREEITEM hRoot, CTreeCtrl& ctrl)
{
    HTREEITEM hRootItem = ctrl.InsertItem(path, hRoot);
    _InsertPath(path, hRootItem, ctrl);
}

void CCommon::_InsertPath(CString path, HTREEITEM hRoot, CTreeCtrl& ctrl)
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
        //Â·¾¶
        if (nFindFile.IsDirectory())
        {
            hSubItem = ctrl.InsertItem(nPicFileName, hRoot);
            _InsertPath(nFindFile.GetFilePath(), hSubItem, ctrl);
        }
        //else
        //{
        //    //ÎÄ¼þ
        //    str = nPicFileName.Right(4);
        //    if (!str.CompareNoCase(_T(".jpg")) || !str.CompareNoCase(_T(".tif")))
        //    {
        //        ctrl.InsertItem(nPicFileName, hRoot);
        //    }
        //}
    }
    nFindFile.Close();
}
