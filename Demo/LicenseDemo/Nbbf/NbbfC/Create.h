/* -------------------------------------------------------------------------------------------------
This file is part of the Nbbf Copy Protection Library (Nbbf)
 
Nbbf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
Nbbf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser Public License for more details.
 
You should have received a copy of the GNU Lesser Public License
along with Nbbf.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------------------------- */
#pragma once
#include "resource.h"       // main symbols

#include "NbbfC_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CCreate

class ATL_NO_VTABLE CCreate :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCreate, &CLSID_Create>,
	public IDispatchImpl<ICreate, &IID_ICreate, &LIBID_NbbfCLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCreate()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CREATE)


BEGIN_COM_MAP(CCreate)
	COM_INTERFACE_ENTRY(ICreate)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(Create)(LONG lID1, LONG lID2, LONG lCaps, BSTR * pbstrKey);
};

OBJECT_ENTRY_AUTO(__uuidof(Create), CCreate)
