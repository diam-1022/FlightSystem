#pragma once
#include "Window.h"
#include<vector>
#include "PushButton.h"
#include"Route.h"
#include"Table.h"
#include<memory>
#include"LineEdit.h"
class Management
{
	enum Operator {
		Display,
		Insert,
		Remove,
		Modify,
		Search,
		Menu =66
	};
public:
	Management();
	//启动管理类
	void run();
	int menu();

	//显示所有的航线
	void display();
	//添加
	void add();
	//删除
	void erase();
	//修改
	void modify();
	//查找
	void search();
	//绘制背景
	void drawBackground();
	void eventLoop();
	 
	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateShowTable();
private:
	IMAGE m_bk;


	//vector 动态存储
	std::vector< std::unique_ptr <PushButton>> menu_btns;

private://保存航线信息
	std::string m_header;
	std::vector<Route>vec_rot;

private: //查看表格
	std::unique_ptr < Table> m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//添加航线按钮
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<PushButton> m_delBtn;//删除航线按钮
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr <Table> m_delTable;

	//修改航线
	std::unique_ptr<LineEdit> m_modifyEdit;
	std::vector<std::unique_ptr<LineEdit>>m_rotEdits;
	bool isFind = false;
	std::vector<Route>::iterator m_modifyIt;

};
