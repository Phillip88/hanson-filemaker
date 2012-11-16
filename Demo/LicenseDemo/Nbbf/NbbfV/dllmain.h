// dllmain.h : Declaration of module class.

class CNbbfVModule : public CAtlDllModuleT< CNbbfVModule >
{
public :
	DECLARE_LIBID(LIBID_NbbfVLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_NBBFV, "{9BA59474-5D82-4004-9559-F5993FE2A2F0}")
};

extern class CNbbfVModule _AtlModule;
