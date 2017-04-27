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
	void display_msg(WINDOW* win, int starty, int startx, const std::string msg);
	void clear_lines(WINDOW* win, int begin, int line);
	~Window();
protected:
	WINDOW* create_newwin(int y, int x, int starty, int startx);
public:
	WINDOW* header;
	WINDOW* output;
	WINDOW* input;
	WINDOW* friend_list;
};


#endif// __WINDOW_H__
