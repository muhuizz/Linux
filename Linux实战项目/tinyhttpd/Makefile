.PHONY:all
all:httpd cgi

httpd:httpd.o main.o
	gcc -o $@ $^ -lpthread
%.o:%.c
	gcc -c $<
	
.PHONY:cgi
cgi:
	cd cgi-bin; make; cd -

.PHONT:output
output:all
	mkdir output
	cp httpd output/
	cp -rf log output/
	cp -rf conf	output/
	cp -rf wwwRoot	output/
	mkdir -p output/wwwRoot/cgi
	cp /home/muhui/code/httpd/cgi-bin/cgi_math	output/wwwRoot/cgi/
	cp http_ctl.sh output/http_ctl

.PHONY:clean
clean:
	rm -rf httpd *.o output
	cd /home/muhui/code/httpd/cgi-bin;make clean; cd -
