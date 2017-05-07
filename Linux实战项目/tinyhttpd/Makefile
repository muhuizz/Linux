.PHONY:all
all:httpd cgi

httpd:httpd.o main.o
	gcc -o $@ $^ -lpthread
%.o:%.c
	gcc -c $<
	
.PHONY:cgi
cgi:
	cd cgi-bin; make; cd -
	cd mysql_cgi; make; cd -

.PHONT:output
output:all
	mkdir output
	cp httpd output/
	cp -rf log output/
	cp -rf conf	output/
	cp -rf wwwRoot	output/
	mkdir -p output/wwwRoot/cgi/sql
	cp /home/muhui/code/httpd/cgi-bin/cgi_math	output/wwwRoot/cgi/
	cp http_ctl.sh output/http_ctl
#	cp -rf /home/muhui/code/httpd/lib/lib output/
	cp /home/muhui/code/httpd/mysql_cgi/cgi_select output/wwwRoot/cgi/sql/
	cp /home/muhui/code/httpd/mysql_cgi/cgi_insert output/wwwRoot/cgi/sql/
	cp /home/muhui/code/httpd/mysql_cgi/cgi_modify output/wwwRoot/cgi/sql/
	cp /home/muhui/code/httpd/mysql_cgi/cgi_delete output/wwwRoot/cgi/sql/

.PHONY:clean
clean:
	rm -rf httpd *.o output
	cd /home/muhui/code/httpd/cgi-bin;make clean; cd -
	cd /home/muhui/code/httpd/mysql_cgi; make clean; cd -
