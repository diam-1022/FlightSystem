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
	//����������
	void run();
	int menu();

	//��ʾ���еĺ���
	void display();
	//���
	void add();
	//ɾ��
	void erase();
	//�޸�
	void modify();
	//����
	void search();
	//���Ʊ���
	void drawBackground();
	void eventLoop();
	 
	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateShowTable();
private:
	IMAGE m_bk;


	//vector ��̬�洢
	std::vector< std::unique_ptr <PushButton>> menu_btns;

private://���溽����Ϣ
	std::string m_header;
	std::vector<Route>vec_rot;

private: //�鿴���
	std::unique_ptr < Table> m_showTable;
	std::unique_ptr<PushButton> m_addBtn;//��Ӻ��߰�ť
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<PushButton> m_delBtn;//ɾ�����߰�ť
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr <Table> m_delTable;

	//�޸ĺ���
	std::unique_ptr<LineEdit> m_modifyEdit;
	std::vector<std::unique_ptr<LineEdit>>m_rotEdits;
	bool isFind = false;
	std::vector<Route>::iterator m_modifyIt;

};
