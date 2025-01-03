#include "LineEdit.h"

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x,y,w,h)
{
	m_text = "按此输入";
}

void LineEdit::show()
{
	//颜色
	setfillcolor(cur_c);
	//框大小
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	//文字颜色
	settextcolor(BLACK);
	settextstyle(23, 0, "黑体");
	//文字居中显示在按钮中间
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;

	::outtextxy(m_x+5, ty, m_text.c_str());
	//点击自己弹出对话框
	if (isClicked()) {
		char buf[128];
		InputBox(buf, 128, m_hitText.data(), m_title.data());
		if (buf[0] != '\0');
			m_text = buf;
	}
}

bool LineEdit::textChanged()
{
	if (m_text.empty())
		return false;
	if (m_prevText == m_text) {
		return false;
	}
	m_prevText = m_text;
	return true;
	
}
