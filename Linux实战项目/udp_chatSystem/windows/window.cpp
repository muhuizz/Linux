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



WINDOW* Window::create_newwin(int y, int x, int starty, int startx)
{
	WINDOW* win = newwin(y, x, starty, startx);
	box(win, '*', '*');
	return win;
}

void Window::display_msg(WINDOW* win, int starty, int startx, const std::string msg)
{
	mvwaddstr(win, starty, startx, msg.c_str());
	wrefresh(win);
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
	int line = LINES/5;
	int col = COLS;
	int start_line = 0;
	int start_col = 0;
	header = create_newwin(line, col, start_line, start_col);
	wrefresh(header);
}
void Window::draw_output_windows()
{
	int line = LINES*3/5;
	int col = COLS*3/4;
	int start_line = LINES/5;
	int start_col = 0;
	output = create_newwin(line, col, start_line, start_col);
	wrefresh(output);
}
void Window::draw_input_windows()
{
	int line = LINES/5;
	int col = COLS;
	int start_line = LINES*4/5;
	int start_col = 0;
	input = create_newwin(line, col, start_line, start_col);
	wrefresh(input);
}
void Window::draw_friend_list_windows()
{
	int line = LINES*3/5;
	int col = COLS/4;
	int start_line = LINES*1/5;
	int start_col = COLS*3/4;
	friend_list = create_newwin(line, col, start_line, start_col);
	wrefresh(friend_list);
}

void* header_fun(void *arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*)arg;
	int index = 1;
	while(1)
	{
		pwin->draw_header_windows();
		int nowy = 0;
		int nowx = 0;
		getmaxyx(pwin->header, nowy, nowx);
		string msg = "Welcome to ChatingSystem^-^";
		
		pwin->display_msg(pwin->header, nowy/2-1, index++, msg);
		index%=(COLS-msg.size());
		if(index == 0)
			index = 1;
		usleep(300000);
	}
	return NULL;
}

void* output_fun(void *arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*)arg;
	pwin->draw_output_windows();
	string msg = "abcdefgaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	int index = 1 ;
	while(1)
	{
		int x = 0;
		int y = 0;
		getmaxyx(pwin->output, y, x);
		index %= (y-1);
		if(index == 0)
			index = 1;
		
		pwin->display_msg(pwin->output, index, 1, msg.c_str());
		index++;
		usleep(300000);
		if(index >= (y-1))
		{
			pwin->clear_lines(pwin->output, 1, y-2);
			pwin->draw_output_windows();
			sleep(1);
		}
	}
	return NULL;
}

void* input_fun(void* arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*)arg;
	int index = 0;
	while(1)
	{
		char buf[1024];
		memset(buf, '\0', sizeof(buf));
		pwin->draw_input_windows();
		pwin->display_msg(pwin->input, 1, 1, "Please Input# ");
		keypad(pwin->input, true);
		wgetnstr(pwin->input, buf, sizeof(buf)-1);
	}
	return NULL;
}

void* friend_list_fun(void* arg)
{
	pthread_detach(pthread_self());
	Window* pwin = (Window*)arg;
	pwin->draw_friend_list_windows();
	return NULL;
}

// #ifdef _DEBUG_
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
// #endif //_DEBUG_










 
