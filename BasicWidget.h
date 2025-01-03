#pragma once
#include<easyx.h>
class BasicWidget
{
public:
	BasicWidget(int x, int y, int w, int h);
	virtual ~BasicWidget() {}
	int width();
	int height();
	void setFixedSize(int w, int h);

	int x(); 
	int y();
	void move(int x, int y);

	bool isin();//判断鼠标是否在当前按钮上
	bool isClicked();//判断鼠标是否点击了按钮
	//虚函数实现接口与实现的分离，即允许在运行时决定调用哪个函数实现
	virtual void show() = 0;
	virtual void event();
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);


protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	COLORREF cur_c = RGB(232, 232, 236);//当前颜色
	COLORREF normal_c = RGB(232, 232, 236);
	COLORREF hover_c = BLUE;//移动到btn上所改变的颜色
};

