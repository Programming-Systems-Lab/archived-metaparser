
Client2ps.dll: dlldata.obj Client2_p.obj Client2_i.obj
	link /dll /out:Client2ps.dll /def:Client2ps.def /entry:DllMain dlldata.obj Client2_p.obj Client2_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Client2ps.dll
	@del Client2ps.lib
	@del Client2ps.exp
	@del dlldata.obj
	@del Client2_p.obj
	@del Client2_i.obj
