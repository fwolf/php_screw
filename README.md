#PHP Screw - User's Manual ver1.5
Copyright (C) 2007 Kunimasa Noda/PM9.com, Inc.
contact:  http://www.pm9.com,  kuni@pm9.com

1. 只是修改了些代码,让WIN下可以编译

2. WIN 下编译成独立的DLL 需要指定ZLIB

	Makefile 修改如下
	LIBS=kernel32. ...(略) zdll.lib
	LDFLAGS=/nologo  /libpath ...(略)  /libpath:"E:\php\zlib\lib"	

3. ZLIB 下载见:www.zlib.net

4. 如果在PHP编译时候添加依赖库见: http://www.cnblogs.com/liushannet/p/3978866.html

5. php_screw.dll 为PHP5.5.13 线程安全版本 密码未修改
 
