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

	bool isin();//�ж�����Ƿ��ڵ�ǰ��ť��
	bool isClicked();//�ж�����Ƿ����˰�ť
	//�麯��ʵ�ֽӿ���ʵ�ֵķ��룬������������ʱ���������ĸ�����ʵ��
	virtual void show() = 0;
	virtual void event();
	void setBackgroundColor(COLORREF c);
	void setHoverColor(COLORREF c);


protected:
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	COLORREF cur_c = RGB(232, 232, 236);//��ǰ��ɫ
	COLORREF normal_c = RGB(232, 232, 236);
	COLORREF hover_c = BLUE;//�ƶ���btn�����ı����ɫ
};

