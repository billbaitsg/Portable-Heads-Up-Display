/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller
	
	Module:	VFD Commands header
	
	Desc.:	This file contains the global variables and 
			function prototypes for the VFD Commands module.
**********************************************************/

#ifndef VFD_H
#define VFD_H

	/* Function prototypes */
	void cursor_home(void);
	void cursor_up(unsigned char lines);
	void cursor_down(unsigned char lines);
	void cursor_right(unsigned char cols);
	void cursor_left(unsigned char cols);
	void cursor_position(unsigned char row, unsigned char col);
	void save_cursor(void);
	void restore_cursor(void);
	void request_cursor(void);
	void auto_linefeed_on(void);
	void auto_linefeed_off(void);
	void reverse_video_on(void);
	void reverse_video_off(void);
	void blinking_on(void);
	void blinking_off(void);
	void reset(void);
	void single_single(void);
	void double_double(void);
	void dpmm(unsigned char a, unsigned char b, unsigned char c,
		unsigned char d, unsigned char e, unsigned char f,
		unsigned char g, unsigned char h);
	void brightness(unsigned char level);
	void self_test(void);
	void rcvd_data_test(void);
	void rcvd_data_test_exit(void);
	void cancel(void);
	
#endif