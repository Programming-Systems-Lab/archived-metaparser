
ComMetaParserTest1ps.dll: dlldata.obj ComMetaParserTest1_p.obj ComMetaParserTest1_i.obj
	link /dll /out:ComMetaParserTest1ps.dll /def:ComMetaParserTest1ps.def /entry:DllMain dlldata.obj ComMetaParserTest1_p.obj ComMetaParserTest1_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ComMetaParserTest1ps.dll
	@del ComMetaParserTest1ps.lib
	@del ComMetaParserTest1ps.exp
	@del dlldata.obj
	@del ComMetaParserTest1_p.obj
	@del ComMetaParserTest1_i.obj
