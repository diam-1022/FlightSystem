#pragma once
#include"Configure.h"

class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const std::string& title);
	int exec();
	//静态变量获取窗口宽度
	static int width();
	static int height();
	static void clear();
	static void beginDraw(); 
	static void flushDraw();
	static void endDraw();

	//按键操作和鼠标操作
	//判断有没有消息
	inline static bool hasMsg() { return ::peekmessage(&m_msg, EX_MOUSE|EX_KEY); }
	inline static ExMessage& getMsg() { return m_msg; }
private:
	HWND m_handle; //窗口句柄
	inline static ExMessage m_msg; //鼠标和键盘消息获取
};


