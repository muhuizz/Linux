#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <ncurses.h>
#include <string>
#include <string.h>
#include <pthread.h>
class Window
{
public:
	Window();
	void draw_header_windows();
	void draw_output_windows();
	void draw_input_windows();
	void draw_friend_list_windows();

	void fresh_window(WINDOW* win);
	void send_msg_to_window(WINDOW* win, int starty, int startx, const std::string& msg);
	void recv_msg_from_window(WINDOW* win, std::string& msg, size_t sz);
	void clear_lines(WINDOW* win, int begin, int line);
	~Window();
protected:
	WINDOW* create_newwin(int y, int x, int starty, int startx, char ch);
public:
	WINDOW* header;
	WINDOW* output;
	WINDOW* input;
	WINDOW* friend_list;
};


#endif// __WINDOW_H__
