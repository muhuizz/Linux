Usage：

	1>	./configure
	2>	./build
	3>	cd output; ./http_ctl start
	4>	./http_ctl stop

默认为127.0.0.1本地回环，端口号为8080，可在/conf/httpd.conf手动修改。

说明：
	基于开源Tinyhttpd小型服务器，1.0版本基于多线程实现
功能：
	基于cgi的数据库访问
