
RuleEngine1ps.dll: dlldata.obj RuleEngine1_p.obj RuleEngine1_i.obj
	link /dll /out:RuleEngine1ps.dll /def:RuleEngine1ps.def /entry:DllMain dlldata.obj RuleEngine1_p.obj RuleEngine1_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del RuleEngine1ps.dll
	@del RuleEngine1ps.lib
	@del RuleEngine1ps.exp
	@del dlldata.obj
	@del RuleEngine1_p.obj
	@del RuleEngine1_i.obj
