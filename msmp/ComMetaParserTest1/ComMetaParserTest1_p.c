
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Jan 14 21:35:01 2002
 */
/* Compiler settings for Q:\Project\Visual Studio\ComMetaParserTest1\ComMetaParserTest1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "ComMetaParserTest1.h"

#define TYPE_FORMAT_STRING_SIZE   973                               
#define PROC_FORMAT_STRING_SIZE   85                                
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyMetaParserTest1_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyMetaParserTest1_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Parse */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x22 ),	/* 34 */
/* 14 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter xmlSource */

/* 16 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x3be ),	/* Type Offset=958 */

	/* Parameter isSuccessful */

/* 22 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 24 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 26 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 28 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 30 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Process */

/* 34 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x4 ),	/* 4 */
/* 42 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 44 */	NdrFcShort( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x22 ),	/* 34 */
/* 48 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter isSuccessful */

/* 50 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 52 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 54 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 56 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 58 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 60 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 62 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 64 */	NdrFcLong( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x5 ),	/* 5 */
/* 70 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0x8 ),	/* 8 */
/* 76 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0x3a6 ),	/* Offset= 934 (938) */
/*  6 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/*  8 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	NdrFcShort( 0x10 ),	/* 16 */
/* 16 */	NdrFcShort( 0x2b ),	/* 43 */
/* 18 */	NdrFcLong( 0x3 ),	/* 3 */
/* 22 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 24 */	NdrFcLong( 0x11 ),	/* 17 */
/* 28 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 30 */	NdrFcLong( 0x2 ),	/* 2 */
/* 34 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 36 */	NdrFcLong( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 42 */	NdrFcLong( 0x5 ),	/* 5 */
/* 46 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 48 */	NdrFcLong( 0xb ),	/* 11 */
/* 52 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 54 */	NdrFcLong( 0xa ),	/* 10 */
/* 58 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 60 */	NdrFcLong( 0x6 ),	/* 6 */
/* 64 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (278) */
/* 66 */	NdrFcLong( 0x7 ),	/* 7 */
/* 70 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 72 */	NdrFcLong( 0x8 ),	/* 8 */
/* 76 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (284) */
/* 78 */	NdrFcLong( 0xd ),	/* 13 */
/* 82 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (308) */
/* 84 */	NdrFcLong( 0x9 ),	/* 9 */
/* 88 */	NdrFcShort( 0xee ),	/* Offset= 238 (326) */
/* 90 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 94 */	NdrFcShort( 0xfa ),	/* Offset= 250 (344) */
/* 96 */	NdrFcLong( 0x24 ),	/* 36 */
/* 100 */	NdrFcShort( 0x304 ),	/* Offset= 772 (872) */
/* 102 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 106 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (872) */
/* 108 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 112 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (876) */
/* 114 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 118 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (880) */
/* 120 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 124 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (884) */
/* 126 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 130 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (888) */
/* 132 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 136 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (892) */
/* 138 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 142 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (880) */
/* 144 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 148 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (884) */
/* 150 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 154 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (896) */
/* 156 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 160 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (892) */
/* 162 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 166 */	NdrFcShort( 0x2de ),	/* Offset= 734 (900) */
/* 168 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 172 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (904) */
/* 174 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 178 */	NdrFcShort( 0x2da ),	/* Offset= 730 (908) */
/* 180 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 184 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (912) */
/* 186 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 190 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (916) */
/* 192 */	NdrFcLong( 0x10 ),	/* 16 */
/* 196 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 198 */	NdrFcLong( 0x12 ),	/* 18 */
/* 202 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 204 */	NdrFcLong( 0x13 ),	/* 19 */
/* 208 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 210 */	NdrFcLong( 0x16 ),	/* 22 */
/* 214 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 216 */	NdrFcLong( 0x17 ),	/* 23 */
/* 220 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 222 */	NdrFcLong( 0xe ),	/* 14 */
/* 226 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (924) */
/* 228 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 232 */	NdrFcShort( 0x2be ),	/* Offset= 702 (934) */
/* 234 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 238 */	NdrFcShort( 0x27e ),	/* Offset= 638 (876) */
/* 240 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 244 */	NdrFcShort( 0x27c ),	/* Offset= 636 (880) */
/* 246 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 250 */	NdrFcShort( 0x27a ),	/* Offset= 634 (884) */
/* 252 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 256 */	NdrFcShort( 0x274 ),	/* Offset= 628 (884) */
/* 258 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 262 */	NdrFcShort( 0x26e ),	/* Offset= 622 (884) */
/* 264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 268 */	NdrFcShort( 0x0 ),	/* Offset= 0 (268) */
/* 270 */	NdrFcLong( 0x1 ),	/* 1 */
/* 274 */	NdrFcShort( 0x0 ),	/* Offset= 0 (274) */
/* 276 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (275) */
/* 278 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 282 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 284 */	
			0x12, 0x0,	/* FC_UP */
/* 286 */	NdrFcShort( 0xc ),	/* Offset= 12 (298) */
/* 288 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 290 */	NdrFcShort( 0x2 ),	/* 2 */
/* 292 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 294 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 296 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 298 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 300 */	NdrFcShort( 0x8 ),	/* 8 */
/* 302 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (288) */
/* 304 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 306 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 308 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 310 */	NdrFcLong( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 318 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 320 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 322 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 324 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 326 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 328 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 334 */	NdrFcShort( 0x0 ),	/* 0 */
/* 336 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 338 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 340 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 342 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 344 */	
			0x12, 0x0,	/* FC_UP */
/* 346 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (854) */
/* 348 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 350 */	NdrFcShort( 0x18 ),	/* 24 */
/* 352 */	NdrFcShort( 0xa ),	/* 10 */
/* 354 */	NdrFcLong( 0x8 ),	/* 8 */
/* 358 */	NdrFcShort( 0x58 ),	/* Offset= 88 (446) */
/* 360 */	NdrFcLong( 0xd ),	/* 13 */
/* 364 */	NdrFcShort( 0x78 ),	/* Offset= 120 (484) */
/* 366 */	NdrFcLong( 0x9 ),	/* 9 */
/* 370 */	NdrFcShort( 0x94 ),	/* Offset= 148 (518) */
/* 372 */	NdrFcLong( 0xc ),	/* 12 */
/* 376 */	NdrFcShort( 0xbc ),	/* Offset= 188 (564) */
/* 378 */	NdrFcLong( 0x24 ),	/* 36 */
/* 382 */	NdrFcShort( 0x114 ),	/* Offset= 276 (658) */
/* 384 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 388 */	NdrFcShort( 0x130 ),	/* Offset= 304 (692) */
/* 390 */	NdrFcLong( 0x10 ),	/* 16 */
/* 394 */	NdrFcShort( 0x148 ),	/* Offset= 328 (722) */
/* 396 */	NdrFcLong( 0x2 ),	/* 2 */
/* 400 */	NdrFcShort( 0x160 ),	/* Offset= 352 (752) */
/* 402 */	NdrFcLong( 0x3 ),	/* 3 */
/* 406 */	NdrFcShort( 0x178 ),	/* Offset= 376 (782) */
/* 408 */	NdrFcLong( 0x14 ),	/* 20 */
/* 412 */	NdrFcShort( 0x190 ),	/* Offset= 400 (812) */
/* 414 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (413) */
/* 416 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 418 */	NdrFcShort( 0x4 ),	/* 4 */
/* 420 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 424 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 426 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 428 */	NdrFcShort( 0x4 ),	/* 4 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 432 */	NdrFcShort( 0x1 ),	/* 1 */
/* 434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 438 */	0x12, 0x0,	/* FC_UP */
/* 440 */	NdrFcShort( 0xffffff72 ),	/* Offset= -142 (298) */
/* 442 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 444 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 446 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 448 */	NdrFcShort( 0x8 ),	/* 8 */
/* 450 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 452 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 454 */	NdrFcShort( 0x4 ),	/* 4 */
/* 456 */	NdrFcShort( 0x4 ),	/* 4 */
/* 458 */	0x11, 0x0,	/* FC_RP */
/* 460 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (416) */
/* 462 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 464 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 466 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 470 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 478 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 480 */	NdrFcShort( 0xffffff54 ),	/* Offset= -172 (308) */
/* 482 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 484 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 486 */	NdrFcShort( 0x8 ),	/* 8 */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0x6 ),	/* Offset= 6 (496) */
/* 492 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 494 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 496 */	
			0x11, 0x0,	/* FC_RP */
/* 498 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (466) */
/* 500 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 512 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 514 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (326) */
/* 516 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 518 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 520 */	NdrFcShort( 0x8 ),	/* 8 */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x6 ),	/* Offset= 6 (530) */
/* 526 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 528 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 530 */	
			0x11, 0x0,	/* FC_RP */
/* 532 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (500) */
/* 534 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 536 */	NdrFcShort( 0x4 ),	/* 4 */
/* 538 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 544 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 546 */	NdrFcShort( 0x4 ),	/* 4 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcShort( 0x1 ),	/* 1 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	0x12, 0x0,	/* FC_UP */
/* 558 */	NdrFcShort( 0x17c ),	/* Offset= 380 (938) */
/* 560 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 562 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 564 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 566 */	NdrFcShort( 0x8 ),	/* 8 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	NdrFcShort( 0x6 ),	/* Offset= 6 (576) */
/* 572 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 574 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 576 */	
			0x11, 0x0,	/* FC_RP */
/* 578 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (534) */
/* 580 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 582 */	NdrFcLong( 0x2f ),	/* 47 */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 592 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 594 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 596 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 598 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 600 */	NdrFcShort( 0x1 ),	/* 1 */
/* 602 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 604 */	NdrFcShort( 0x4 ),	/* 4 */
/* 606 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 608 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 610 */	NdrFcShort( 0x10 ),	/* 16 */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0xa ),	/* Offset= 10 (624) */
/* 616 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 618 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 620 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (580) */
/* 622 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 624 */	
			0x12, 0x0,	/* FC_UP */
/* 626 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (598) */
/* 628 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 630 */	NdrFcShort( 0x4 ),	/* 4 */
/* 632 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 638 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 640 */	NdrFcShort( 0x4 ),	/* 4 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0x1 ),	/* 1 */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	0x12, 0x0,	/* FC_UP */
/* 652 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (608) */
/* 654 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 656 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 658 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 660 */	NdrFcShort( 0x8 ),	/* 8 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	NdrFcShort( 0x6 ),	/* Offset= 6 (670) */
/* 666 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 668 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 670 */	
			0x11, 0x0,	/* FC_RP */
/* 672 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (628) */
/* 674 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 676 */	NdrFcShort( 0x8 ),	/* 8 */
/* 678 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 680 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 682 */	NdrFcShort( 0x10 ),	/* 16 */
/* 684 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 686 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 688 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (674) */
			0x5b,		/* FC_END */
/* 692 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 694 */	NdrFcShort( 0x18 ),	/* 24 */
/* 696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 698 */	NdrFcShort( 0xa ),	/* Offset= 10 (708) */
/* 700 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 702 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 704 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (680) */
/* 706 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 708 */	
			0x11, 0x0,	/* FC_RP */
/* 710 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (466) */
/* 712 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 714 */	NdrFcShort( 0x1 ),	/* 1 */
/* 716 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 720 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 722 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 724 */	NdrFcShort( 0x8 ),	/* 8 */
/* 726 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 728 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 730 */	NdrFcShort( 0x4 ),	/* 4 */
/* 732 */	NdrFcShort( 0x4 ),	/* 4 */
/* 734 */	0x12, 0x0,	/* FC_UP */
/* 736 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (712) */
/* 738 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 740 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 742 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 744 */	NdrFcShort( 0x2 ),	/* 2 */
/* 746 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 752 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 756 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 758 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 760 */	NdrFcShort( 0x4 ),	/* 4 */
/* 762 */	NdrFcShort( 0x4 ),	/* 4 */
/* 764 */	0x12, 0x0,	/* FC_UP */
/* 766 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (742) */
/* 768 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 770 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 772 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 774 */	NdrFcShort( 0x4 ),	/* 4 */
/* 776 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 782 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 786 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 788 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 790 */	NdrFcShort( 0x4 ),	/* 4 */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	0x12, 0x0,	/* FC_UP */
/* 796 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (772) */
/* 798 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 800 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 802 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 806 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 812 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 816 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 818 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	NdrFcShort( 0x4 ),	/* 4 */
/* 824 */	0x12, 0x0,	/* FC_UP */
/* 826 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (802) */
/* 828 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 830 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 832 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 838 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 840 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 844 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 846 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 848 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 850 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (832) */
/* 852 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 854 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x28 ),	/* 40 */
/* 858 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (840) */
/* 860 */	NdrFcShort( 0x0 ),	/* Offset= 0 (860) */
/* 862 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 864 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 866 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 868 */	NdrFcShort( 0xfffffdf8 ),	/* Offset= -520 (348) */
/* 870 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 872 */	
			0x12, 0x0,	/* FC_UP */
/* 874 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (608) */
/* 876 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 878 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 880 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 882 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 884 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 886 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 888 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 890 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 892 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 894 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 896 */	
			0x12, 0x0,	/* FC_UP */
/* 898 */	NdrFcShort( 0xfffffd94 ),	/* Offset= -620 (278) */
/* 900 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 902 */	NdrFcShort( 0xfffffd96 ),	/* Offset= -618 (284) */
/* 904 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 906 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (308) */
/* 908 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 910 */	NdrFcShort( 0xfffffdb8 ),	/* Offset= -584 (326) */
/* 912 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 914 */	NdrFcShort( 0xfffffdc6 ),	/* Offset= -570 (344) */
/* 916 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 918 */	NdrFcShort( 0x2 ),	/* Offset= 2 (920) */
/* 920 */	
			0x12, 0x0,	/* FC_UP */
/* 922 */	NdrFcShort( 0x10 ),	/* Offset= 16 (938) */
/* 924 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 926 */	NdrFcShort( 0x10 ),	/* 16 */
/* 928 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 930 */	0x2,		/* FC_CHAR */
			0x8,		/* FC_LONG */
/* 932 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 934 */	
			0x12, 0x0,	/* FC_UP */
/* 936 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (924) */
/* 938 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 940 */	NdrFcShort( 0x20 ),	/* 32 */
/* 942 */	NdrFcShort( 0x0 ),	/* 0 */
/* 944 */	NdrFcShort( 0x0 ),	/* Offset= 0 (944) */
/* 946 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 948 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 950 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 952 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 954 */	NdrFcShort( 0xfffffc4c ),	/* Offset= -948 (6) */
/* 956 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 958 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 962 */	NdrFcShort( 0x10 ),	/* 16 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0xfffffc3c ),	/* Offset= -964 (2) */
/* 968 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 970 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMyMetaParserTest1, ver. 0.0,
   GUID={0x1A58C0B2,0x2D6F,0x4CAE,{0x90,0x20,0x44,0x56,0xA4,0x36,0x56,0xAF}} */

#pragma code_seg(".orpc")
static const unsigned short IMyMetaParserTest1_FormatStringOffsetTable[] =
    {
    0,
    34,
    62
    };

static const MIDL_STUBLESS_PROXY_INFO IMyMetaParserTest1_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMyMetaParserTest1_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyMetaParserTest1_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMyMetaParserTest1_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IMyMetaParserTest1ProxyVtbl = 
{
    &IMyMetaParserTest1_ProxyInfo,
    &IID_IMyMetaParserTest1,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMyMetaParserTest1::Parse */ ,
    (void *) (INT_PTR) -1 /* IMyMetaParserTest1::Process */ ,
    (void *) (INT_PTR) -1 /* IMyMetaParserTest1::Init */
};

const CInterfaceStubVtbl _IMyMetaParserTest1StubVtbl =
{
    &IID_IMyMetaParserTest1,
    &IMyMetaParserTest1_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x600015b, /* MIDL Version 6.0.347 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _ComMetaParserTest1_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMyMetaParserTest1ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ComMetaParserTest1_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMyMetaParserTest1StubVtbl,
    0
};

PCInterfaceName const _ComMetaParserTest1_InterfaceNamesList[] = 
{
    "IMyMetaParserTest1",
    0
};


#define _ComMetaParserTest1_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ComMetaParserTest1, pIID, n)

int __stdcall _ComMetaParserTest1_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ComMetaParserTest1_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ComMetaParserTest1_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ComMetaParserTest1_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ComMetaParserTest1_StubVtblList,
    (const PCInterfaceName * ) & _ComMetaParserTest1_InterfaceNamesList,
    0, // no delegation
    & _ComMetaParserTest1_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Jan 14 21:35:01 2002
 */
/* Compiler settings for Q:\Project\Visual Studio\ComMetaParserTest1\ComMetaParserTest1.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "ComMetaParserTest1.h"

#define TYPE_FORMAT_STRING_SIZE   953                               
#define PROC_FORMAT_STRING_SIZE   115                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyMetaParserTest1_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyMetaParserTest1_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Parse */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x22 ),	/* 34 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x20 ),	/* 32 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter xmlSource */

/* 26 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 28 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x3aa ),	/* Type Offset=938 */

	/* Parameter isSuccessful */

/* 32 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 34 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 36 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 38 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 40 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 42 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Process */

/* 44 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 46 */	NdrFcLong( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x22 ),	/* 34 */
/* 58 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 60 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter isSuccessful */

/* 70 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 72 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 74 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 76 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 78 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 80 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 82 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 84 */	NdrFcLong( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x5 ),	/* 5 */
/* 90 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x8 ),	/* 8 */
/* 96 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 98 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0x392 ),	/* Offset= 914 (918) */
/*  6 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/*  8 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 12 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 14 */	NdrFcShort( 0x2 ),	/* Offset= 2 (16) */
/* 16 */	NdrFcShort( 0x10 ),	/* 16 */
/* 18 */	NdrFcShort( 0x2b ),	/* 43 */
/* 20 */	NdrFcLong( 0x3 ),	/* 3 */
/* 24 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 26 */	NdrFcLong( 0x11 ),	/* 17 */
/* 30 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 32 */	NdrFcLong( 0x2 ),	/* 2 */
/* 36 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 38 */	NdrFcLong( 0x4 ),	/* 4 */
/* 42 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 44 */	NdrFcLong( 0x5 ),	/* 5 */
/* 48 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 50 */	NdrFcLong( 0xb ),	/* 11 */
/* 54 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 56 */	NdrFcLong( 0xa ),	/* 10 */
/* 60 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 62 */	NdrFcLong( 0x6 ),	/* 6 */
/* 66 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (280) */
/* 68 */	NdrFcLong( 0x7 ),	/* 7 */
/* 72 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 74 */	NdrFcLong( 0x8 ),	/* 8 */
/* 78 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (286) */
/* 80 */	NdrFcLong( 0xd ),	/* 13 */
/* 84 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (312) */
/* 86 */	NdrFcLong( 0x9 ),	/* 9 */
/* 90 */	NdrFcShort( 0xf0 ),	/* Offset= 240 (330) */
/* 92 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 96 */	NdrFcShort( 0xfc ),	/* Offset= 252 (348) */
/* 98 */	NdrFcLong( 0x24 ),	/* 36 */
/* 102 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (852) */
/* 104 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 108 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (852) */
/* 110 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 114 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (856) */
/* 116 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 120 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (860) */
/* 122 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 126 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (864) */
/* 128 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 132 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (868) */
/* 134 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 138 */	NdrFcShort( 0x2de ),	/* Offset= 734 (872) */
/* 140 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 144 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (860) */
/* 146 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 150 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (864) */
/* 152 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 156 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (876) */
/* 158 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 162 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (872) */
/* 164 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 168 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (880) */
/* 170 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 174 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (884) */
/* 176 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 180 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (888) */
/* 182 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 186 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (892) */
/* 188 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 192 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (896) */
/* 194 */	NdrFcLong( 0x10 ),	/* 16 */
/* 198 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 200 */	NdrFcLong( 0x12 ),	/* 18 */
/* 204 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 206 */	NdrFcLong( 0x13 ),	/* 19 */
/* 210 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 212 */	NdrFcLong( 0x16 ),	/* 22 */
/* 216 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 218 */	NdrFcLong( 0x17 ),	/* 23 */
/* 222 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 224 */	NdrFcLong( 0xe ),	/* 14 */
/* 228 */	NdrFcShort( 0x2a4 ),	/* Offset= 676 (904) */
/* 230 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 234 */	NdrFcShort( 0x2a8 ),	/* Offset= 680 (914) */
/* 236 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 240 */	NdrFcShort( 0x268 ),	/* Offset= 616 (856) */
/* 242 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 246 */	NdrFcShort( 0x266 ),	/* Offset= 614 (860) */
/* 248 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 252 */	NdrFcShort( 0x264 ),	/* Offset= 612 (864) */
/* 254 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 258 */	NdrFcShort( 0x25e ),	/* Offset= 606 (864) */
/* 260 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 264 */	NdrFcShort( 0x258 ),	/* Offset= 600 (864) */
/* 266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x0 ),	/* Offset= 0 (270) */
/* 272 */	NdrFcLong( 0x1 ),	/* 1 */
/* 276 */	NdrFcShort( 0x0 ),	/* Offset= 0 (276) */
/* 278 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (277) */
/* 280 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 284 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 286 */	
			0x12, 0x0,	/* FC_UP */
/* 288 */	NdrFcShort( 0xe ),	/* Offset= 14 (302) */
/* 290 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 292 */	NdrFcShort( 0x2 ),	/* 2 */
/* 294 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 296 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 298 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 300 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 302 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 306 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (290) */
/* 308 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 310 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 312 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 322 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 324 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 326 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 328 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 330 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 332 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 340 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 342 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 344 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 346 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 348 */	
			0x12, 0x0,	/* FC_UP */
/* 350 */	NdrFcShort( 0x1e4 ),	/* Offset= 484 (834) */
/* 352 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 354 */	NdrFcShort( 0x20 ),	/* 32 */
/* 356 */	NdrFcShort( 0xa ),	/* 10 */
/* 358 */	NdrFcLong( 0x8 ),	/* 8 */
/* 362 */	NdrFcShort( 0x50 ),	/* Offset= 80 (442) */
/* 364 */	NdrFcLong( 0xd ),	/* 13 */
/* 368 */	NdrFcShort( 0x70 ),	/* Offset= 112 (480) */
/* 370 */	NdrFcLong( 0x9 ),	/* 9 */
/* 374 */	NdrFcShort( 0x90 ),	/* Offset= 144 (518) */
/* 376 */	NdrFcLong( 0xc ),	/* 12 */
/* 380 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (556) */
/* 382 */	NdrFcLong( 0x24 ),	/* 36 */
/* 386 */	NdrFcShort( 0x102 ),	/* Offset= 258 (644) */
/* 388 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 392 */	NdrFcShort( 0x11e ),	/* Offset= 286 (678) */
/* 394 */	NdrFcLong( 0x10 ),	/* 16 */
/* 398 */	NdrFcShort( 0x138 ),	/* Offset= 312 (710) */
/* 400 */	NdrFcLong( 0x2 ),	/* 2 */
/* 404 */	NdrFcShort( 0x14e ),	/* Offset= 334 (738) */
/* 406 */	NdrFcLong( 0x3 ),	/* 3 */
/* 410 */	NdrFcShort( 0x164 ),	/* Offset= 356 (766) */
/* 412 */	NdrFcLong( 0x14 ),	/* 20 */
/* 416 */	NdrFcShort( 0x17a ),	/* Offset= 378 (794) */
/* 418 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (417) */
/* 420 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 424 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 428 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 430 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 434 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 436 */	
			0x12, 0x0,	/* FC_UP */
/* 438 */	NdrFcShort( 0xffffff78 ),	/* Offset= -136 (302) */
/* 440 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 442 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 444 */	NdrFcShort( 0x10 ),	/* 16 */
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	NdrFcShort( 0x6 ),	/* Offset= 6 (454) */
/* 450 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 452 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 454 */	
			0x11, 0x0,	/* FC_RP */
/* 456 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (420) */
/* 458 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 462 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 468 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 472 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 474 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 476 */	NdrFcShort( 0xffffff5c ),	/* Offset= -164 (312) */
/* 478 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 480 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 482 */	NdrFcShort( 0x10 ),	/* 16 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x6 ),	/* Offset= 6 (492) */
/* 488 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 490 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 492 */	
			0x11, 0x0,	/* FC_RP */
/* 494 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (458) */
/* 496 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 500 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 506 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 510 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 512 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 514 */	NdrFcShort( 0xffffff48 ),	/* Offset= -184 (330) */
/* 516 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 518 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 520 */	NdrFcShort( 0x10 ),	/* 16 */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x6 ),	/* Offset= 6 (530) */
/* 526 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 528 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 530 */	
			0x11, 0x0,	/* FC_RP */
/* 532 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (496) */
/* 534 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 544 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 548 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 550 */	
			0x12, 0x0,	/* FC_UP */
/* 552 */	NdrFcShort( 0x16e ),	/* Offset= 366 (918) */
/* 554 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 556 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 558 */	NdrFcShort( 0x10 ),	/* 16 */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0x6 ),	/* Offset= 6 (568) */
/* 564 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 566 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 568 */	
			0x11, 0x0,	/* FC_RP */
/* 570 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (534) */
/* 572 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 574 */	NdrFcLong( 0x2f ),	/* 47 */
/* 578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 584 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 586 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 588 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 590 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 592 */	NdrFcShort( 0x1 ),	/* 1 */
/* 594 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 596 */	NdrFcShort( 0x4 ),	/* 4 */
/* 598 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 600 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 602 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 604 */	NdrFcShort( 0x18 ),	/* 24 */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	NdrFcShort( 0xa ),	/* Offset= 10 (618) */
/* 610 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 612 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 614 */	NdrFcShort( 0xffffffd6 ),	/* Offset= -42 (572) */
/* 616 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 618 */	
			0x12, 0x0,	/* FC_UP */
/* 620 */	NdrFcShort( 0xffffffe2 ),	/* Offset= -30 (590) */
/* 622 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 632 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 636 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 638 */	
			0x12, 0x0,	/* FC_UP */
/* 640 */	NdrFcShort( 0xffffffda ),	/* Offset= -38 (602) */
/* 642 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 644 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 646 */	NdrFcShort( 0x10 ),	/* 16 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x6 ),	/* Offset= 6 (656) */
/* 652 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 654 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 656 */	
			0x11, 0x0,	/* FC_RP */
/* 658 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (622) */
/* 660 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 662 */	NdrFcShort( 0x8 ),	/* 8 */
/* 664 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 666 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 668 */	NdrFcShort( 0x10 ),	/* 16 */
/* 670 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 672 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 674 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (660) */
			0x5b,		/* FC_END */
/* 678 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 680 */	NdrFcShort( 0x20 ),	/* 32 */
/* 682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 684 */	NdrFcShort( 0xa ),	/* Offset= 10 (694) */
/* 686 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 688 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 690 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffe7 ),	/* Offset= -25 (666) */
			0x5b,		/* FC_END */
/* 694 */	
			0x11, 0x0,	/* FC_RP */
/* 696 */	NdrFcShort( 0xffffff12 ),	/* Offset= -238 (458) */
/* 698 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 700 */	NdrFcShort( 0x1 ),	/* 1 */
/* 702 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 708 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 710 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 712 */	NdrFcShort( 0x10 ),	/* 16 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0x6 ),	/* Offset= 6 (722) */
/* 718 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 720 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 722 */	
			0x12, 0x0,	/* FC_UP */
/* 724 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (698) */
/* 726 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 728 */	NdrFcShort( 0x2 ),	/* 2 */
/* 730 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 736 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 738 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 740 */	NdrFcShort( 0x10 ),	/* 16 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x6 ),	/* Offset= 6 (750) */
/* 746 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 748 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 750 */	
			0x12, 0x0,	/* FC_UP */
/* 752 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (726) */
/* 754 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 756 */	NdrFcShort( 0x4 ),	/* 4 */
/* 758 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 764 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 766 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 768 */	NdrFcShort( 0x10 ),	/* 16 */
/* 770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x6 ),	/* Offset= 6 (778) */
/* 774 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 776 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 778 */	
			0x12, 0x0,	/* FC_UP */
/* 780 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (754) */
/* 782 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 786 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 790 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 792 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 794 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x10 ),	/* 16 */
/* 798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 800 */	NdrFcShort( 0x6 ),	/* Offset= 6 (806) */
/* 802 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 804 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 806 */	
			0x12, 0x0,	/* FC_UP */
/* 808 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (782) */
/* 810 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 814 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 816 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 818 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 820 */	NdrFcShort( 0x8 ),	/* 8 */
/* 822 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 824 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 826 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 828 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 830 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (810) */
/* 832 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 834 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 836 */	NdrFcShort( 0x38 ),	/* 56 */
/* 838 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (818) */
/* 840 */	NdrFcShort( 0x0 ),	/* Offset= 0 (840) */
/* 842 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 844 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 846 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 848 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffe0f ),	/* Offset= -497 (352) */
			0x5b,		/* FC_END */
/* 852 */	
			0x12, 0x0,	/* FC_UP */
/* 854 */	NdrFcShort( 0xffffff04 ),	/* Offset= -252 (602) */
/* 856 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 858 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 860 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 862 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 864 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 866 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 868 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 870 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 872 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 874 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 876 */	
			0x12, 0x0,	/* FC_UP */
/* 878 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (280) */
/* 880 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 882 */	NdrFcShort( 0xfffffdac ),	/* Offset= -596 (286) */
/* 884 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 886 */	NdrFcShort( 0xfffffdc2 ),	/* Offset= -574 (312) */
/* 888 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 890 */	NdrFcShort( 0xfffffdd0 ),	/* Offset= -560 (330) */
/* 892 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 894 */	NdrFcShort( 0xfffffdde ),	/* Offset= -546 (348) */
/* 896 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 898 */	NdrFcShort( 0x2 ),	/* Offset= 2 (900) */
/* 900 */	
			0x12, 0x0,	/* FC_UP */
/* 902 */	NdrFcShort( 0x10 ),	/* Offset= 16 (918) */
/* 904 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 906 */	NdrFcShort( 0x10 ),	/* 16 */
/* 908 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 910 */	0x2,		/* FC_CHAR */
			0x8,		/* FC_LONG */
/* 912 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 914 */	
			0x12, 0x0,	/* FC_UP */
/* 916 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (904) */
/* 918 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 920 */	NdrFcShort( 0x20 ),	/* 32 */
/* 922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 924 */	NdrFcShort( 0x0 ),	/* Offset= 0 (924) */
/* 926 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 928 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 930 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 932 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 934 */	NdrFcShort( 0xfffffc60 ),	/* Offset= -928 (6) */
/* 936 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 938 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 942 */	NdrFcShort( 0x18 ),	/* 24 */
/* 944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 946 */	NdrFcShort( 0xfffffc50 ),	/* Offset= -944 (2) */
/* 948 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 950 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMyMetaParserTest1, ver. 0.0,
   GUID={0x1A58C0B2,0x2D6F,0x4CAE,{0x90,0x20,0x44,0x56,0xA4,0x36,0x56,0xAF}} */

#pragma code_seg(".orpc")
static const unsigned short IMyMetaParserTest1_FormatStringOffsetTable[] =
    {
    0,
    44,
    82
    };

static const MIDL_STUBLESS_PROXY_INFO IMyMetaParserTest1_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMyMetaParserTest1_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyMetaParserTest1_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMyMetaParserTest1_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IMyMetaParserTest1ProxyVtbl = 
{
    &IMyMetaParserTest1_ProxyInfo,
    &IID_IMyMetaParserTest1,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMyMetaParserTest1::Parse */ ,
    (void *) (INT_PTR) -1 /* IMyMetaParserTest1::Process */ ,
    (void *) (INT_PTR) -1 /* IMyMetaParserTest1::Init */
};

const CInterfaceStubVtbl _IMyMetaParserTest1StubVtbl =
{
    &IID_IMyMetaParserTest1,
    &IMyMetaParserTest1_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x600015b, /* MIDL Version 6.0.347 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _ComMetaParserTest1_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMyMetaParserTest1ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ComMetaParserTest1_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMyMetaParserTest1StubVtbl,
    0
};

PCInterfaceName const _ComMetaParserTest1_InterfaceNamesList[] = 
{
    "IMyMetaParserTest1",
    0
};


#define _ComMetaParserTest1_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ComMetaParserTest1, pIID, n)

int __stdcall _ComMetaParserTest1_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ComMetaParserTest1_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ComMetaParserTest1_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ComMetaParserTest1_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ComMetaParserTest1_StubVtblList,
    (const PCInterfaceName * ) & _ComMetaParserTest1_InterfaceNamesList,
    0, // no delegation
    & _ComMetaParserTest1_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

