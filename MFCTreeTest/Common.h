#pragma once
class CCommon
{
public:
    CCommon();
    ~CCommon();
    static void InsertPath(CString path, HTREEITEM hRoot, CTreeCtrl& ctrl);
private:
    static void _InsertPath(CString path, HTREEITEM hRoot, CTreeCtrl& ctrl);
};

