#include "Management.h"
#include<conio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;
Management::Management()
{
	readFile("./images/Route.txt");

	::loadimage(&m_bk, "./images/bk.png", Window::width(), Window::height());
	::settextstyle(16,0,"黑体");
	//主界面按钮初始化
	menu_btns.emplace_back(new PushButton("查看航线"));
	menu_btns.emplace_back(new PushButton("添加航线"));
	menu_btns.emplace_back(new PushButton("删除航线"));
	menu_btns.emplace_back(new PushButton("修改航线"));
	menu_btns.emplace_back(new PushButton("查找航线"));
	menu_btns.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < menu_btns.size(); i++) {
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width()- menu_btns[i]->width())/2;
		int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		menu_btns[i]->move(bx,by);
	}
	//初始化查看航线的表格
	m_showTable.reset (new Table);
	m_showTable->setRowCount(16);
	m_showTable->setHeader(m_header);
	updateShowTable();
	
	//让表格居中
	m_showTable->move((Window::width() - m_showTable->width())/2, 100);

	//添加航线
	m_addBtn.reset(new PushButton("添加",670,260,80,40));
	m_addEdit.reset(new LineEdit(150,260,500,40));
	m_addEdit->setTitle("请输入航线信息");
	m_addEdit->setHitText("请按照格式\n 航线编号 出发地 目的地 公里数 时长 \n输入信息");

	//删除航线
	m_delBtn.reset(new PushButton("删除", 670, 260, 80, 40));
	m_delEdit.reset(new LineEdit(150, 260, 500, 40));
	m_delEdit->setTitle("请输入所需删除的航线编号");
	m_delEdit->setHitText("请输入所需删除的航线编号");
	m_delTable.reset(new Table);
	m_delTable->setHeader(m_header);
	m_delTable->move(m_delEdit->x(), m_delEdit->y()+120);
	m_delTable->setRowCount(1);

	//修改航线
	m_modifyEdit.reset(new LineEdit(150, 260, 500, 40));
	m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, 200);
	for (int i = 0; i < 5; i++) {
		m_rotEdits.emplace_back(new LineEdit);
		m_rotEdits[i]->setFixedSize(100, 40);
		m_rotEdits[i]->move(100 + i * 150, m_modifyEdit->y() +200);
	}
	m_modifyIt = vec_rot.end();
}

void Management::run()
{
	//获取菜单的返回值
	int op =Menu;
	Window::beginDraw();
	while (true)
	{
	Window::clear();
		drawBackground();
		
		if (Window::hasMsg()) {
			switch (Window::getMsg().message) {
			case WM_KEYDOWN: //按键按下
				//按ESC退出操作，返回主界面
				if (Window::getMsg().vkcode == VK_ESCAPE) {
					op = Menu;
				}
				break;
			defalt:				//鼠标操作
				eventLoop();
				break;  
			}
		}

		
		switch (op)
		{
		case Menu:
			op = menu();
			break;
		case Management::Display:
			display();
			break;
		case Management::Insert:
			add();
			break;
		case Management::Remove:
			erase();
			break;
		case Management::Modify:
			modify();
			break;
		case Management::Search:
			search();
			break;
		default:
			saveFile("./images/test.txt");
			exit(666);
			break;
		}

		Window::flushDraw();
		Window::getMsg().message = 0;
	}
	Window::endDraw();
}

int Management::menu()
{
	for (int i = 0; i < menu_btns.size(); i++) {
		menu_btns[i]->show();
		menu_btns[i]->event();
		if (menu_btns[i]->isClicked()) {
			return i;
		}
	}
	return Menu;
}

void Management::display()
{
	m_showTable->show();
}

void Management::add()
{
	const char* title = "请输入航线信息<航线信息 起飞地 降落地 公里数 飞行时长";
	settextstyle(25, 0, "黑体");
	outtextxy((Window::width()-textwidth(title))/2, 150, title);
	m_addBtn->show();
	m_addEdit->show();
	auto str = m_addEdit->text();
	if (m_addBtn->isClicked() &&!str.empty()) {

		vec_rot.push_back(Route::fromString(m_addEdit->text()));

		std::replace(str.begin(),str.end(),' ','\t');
		m_showTable->insertData(str);
		m_addEdit->clear();
	}
}

void Management::erase()
{
	const char* title = "请输入所需删除的航线编号";
	settextstyle(25, 0, "黑体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

	m_delBtn->show();
	m_delEdit->show();
	m_delTable->show();
	auto& str = m_delEdit->text();
	if (m_delEdit->textChanged()) {
		auto it = std::find_if(vec_rot.begin(), vec_rot.end(), [=](const Route& rot)
			{
				return rot.routeCode == str;
			});
		if (it == vec_rot.end()) {
			outtextxy(m_delEdit->x(),m_delEdit->y()+50,std::string("未找到航班号为"+str+"的航线信息").data());
		}
		else {
			m_delTable->insertData(it->formatInfo());
		}

	}

	if (m_delBtn->isClicked()) {
		auto it = std::remove_if(vec_rot.begin(), vec_rot.end(), [=](const Route& rot)
			{
				return rot.routeCode == str;
			});
		if (it != vec_rot.end()) {
			m_delEdit->clear();
			m_delTable->clear();
		}
		vec_rot.erase(it, vec_rot.end());
		
		updateShowTable();
		
	}
}

void Management::modify()
{
	const char* title = "请输入所需修改的航线编号";
	settextstyle(25, 0, "黑体");
	outtextxy((Window::width() - textwidth(title)) / 2, 150, title);
	m_modifyEdit->show();

	if (isFind) {
		for (auto& e : m_rotEdits) {
			e->show();
		}
	}
	for (auto& e: m_rotEdits) {
		e->show();
	}

	if (isFind && m_modifyIt != vec_rot.end()) {
		for (int i = 0; i < m_rotEdits.size(); i++) {
			if (m_rotEdits[i]->textChanged()) {
				switch (i)
				{
				case 0:
					m_modifyIt->routeCode = m_rotEdits[i]->text();
					break;
				case 1:
					m_modifyIt->departure = m_rotEdits[i]->text();
					break;
				case2:
					m_modifyIt->destination = m_rotEdits[i]->text();
					break;
				case3:
					m_modifyIt->distance =atoi( m_rotEdits[i]->text().data());
					break;
				case4:
					m_modifyIt->flightDuration = atoi(m_rotEdits[i]->text().data());
					break;
				default:
					break;
				}
				updateShowTable();
			}
		}
	}

	if (m_modifyEdit->textChanged()) {
		auto& str = m_modifyEdit->text();
		std::stringstream ss(str);
		std::string number;
		ss >> number;
		
		auto it = std::find_if(vec_rot.begin(), vec_rot.end(), [=](const Route& rot)
			{
				return (rot.routeCode == number);
			});
		if (it == vec_rot.end()) {
			m_modifyIt = vec_rot.end();
			isFind = false;
		}
		else {
			m_rotEdits[0]->setText(it->routeCode);
			m_rotEdits[1]->setText(it->departure);
			m_rotEdits[2]->setText(it->destination);
			m_rotEdits[3]->setText(std::to_string(it->distance));
			m_rotEdits[4]->setText(std::to_string(it->flightDuration));
			isFind = true;
			m_modifyIt = it;
		}
	}
}

void Management::search()
{
	outtextxy(0, 0, "search");
	cout << "search" << endl;
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
	m_showTable->event();

	m_addBtn->event();
	m_addEdit->event();

	m_delBtn->event();
	m_delEdit->event();
	m_delTable->event();
	m_modifyEdit->event();
	for (auto& e : m_rotEdits) {
		e->event();
	}
}

void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);
	if (!read.is_open()) {
		return ;
	}
	//读取表头
	char buf[1024] = { 0 };
	read.getline(buf,1024);
	m_header = buf;
	//读取数据
	while (!read.eof()) {
		char data[1024] = { 0 };
		read.getline(data, 1024);
		//跳过空行
		if (strlen(data)==0) {
			break;
		}//格式化读取
		Route rot;
		stringstream ss(data);//stringstream可以将字符串按照流的方式进行操作
		ss >> rot.routeCode >> rot.departure >> rot.destination >> rot.distance >> rot.flightDuration;
		vec_rot.push_back(rot);
		//cout << rot.routeCode << rot.departure << rot.destination << rot.distance << rot.flightDuration << endl;
	}
	read.close();
}

void Management::saveFile(const std::string& fileName)
{
	fstream write(fileName, ios::out | ios::trunc);
	if (!write.is_open()) {
		cerr << fileName << "file open failed" << endl;
		return;
	}
	//写表头
	m_header+="\n";
	write.write(m_header.c_str(),m_header.size( ));
	
	//写数据
	for (auto& val : vec_rot) {
		std::string info = val.formatInfo();
		write.write(info.c_str(),info.size());
	}
	write.close();
}

void Management::updateShowTable()
{
	m_showTable->clear();
	for (auto& val : vec_rot) {
		m_showTable->insertData(val.formatInfo());
	}
}


