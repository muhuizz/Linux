#include "window.h"

using namespace std;
Window::Window()
{
	initscr();
}
Window::~Window()
{
	delwin(header);
	delwin(output);
	delwin(input);
	delwin(friend_list);
	endwin();
}

void Window::fresh_window(WINDOW* win)
{
	wrefresh(win);
}

WINDOW* Window::create_newwin(int y, int x, int starty, int startx, char ch)
{
	WINDOW* win = newwin(y, x, starty, startx);
	box(win, ch, ch);
	return win;
}

void Window::send_msg_to_window(WINDOW* win, int starty, int startx, const std::string& msg)
{
	mvwaddstr(win, starty, startx, msg.c_str());
	fresh_window(win);
}

void Window::recv_msg_from_window(WINDOW* win, std::string& msg, size_t sz)
{
	char buf[1024];
	memset(buf, 0, sizeof(buf));

	wgetnstr(win, buf, sizeof(buf));
	msg = buf;
}

void Window::clear_lines(WINDOW* win, int begin, int line)
{
	while(line-- > 0)
	{
		wmove(win, begin++, 0);
		wclrtoeol(win);
	}
}

void Window::draw_header_windows()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = 0;
	int _x = 0;
	header = create_newwin(_h, _w, _y, _x, '*');
	fresh_window(header);
}
void Window::draw_output_windows()
{
	int _h = LINES*3/5;
	int _w = COLS*3/4;
	int _y = LINES/5;
	int _x = 0;
	output = create_newwin(_h, _w, _y, _x, 0);
	fresh_window(output);
}
void Window::draw_input_windows()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = LINES*4/5;
	int _x = 0;
	input = create_newwin(_h, _w, _y, _x, '~');
	fresh_window(input);
}
void Window::draw_friend_list_windows()
{
	int _h = LINES*3/5;
	int _w = COLS/4;
	int _y = LINES*1/5;
	int _x = COLS*3/4;
	friend_list = create_newwin(_h, _w, _y, _x, 0);
	fresh_window(friend_list);
}

#ifdef _DEBUG_
void *header_fun(void* arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*) arg;
	pwin->draw_header_windows();
	return NULL;
}
void* output_fun(void* arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*) arg;
	pwin->draw_output_windows();
	return NULL;
}

void* input_fun(void* arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*) arg;
	pwin->draw_input_windows();
	return NULL;
}

void* friend_list_fun(void* arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*) arg;
	pwin->draw_friend_list_windows();
	return NULL;
}

int main()
{
	Window win;
	pthread_t header_pthread;
	pthread_t output_pthread;
	pthread_t input_pthread;
	pthread_t friend_list_pthread;
	
	pthread_create(&header_pthread, NULL, header_fun, &win);
	pthread_create(&output_pthread, NULL, output_fun, &win);
	pthread_create(&input_pthread, NULL, input_fun, &win);
	pthread_create(&friend_list_pthread, NULL, friend_list_fun, &win);

	while(1);
	return 0;
}

#endif //_DEBUG_

