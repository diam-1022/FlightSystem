#include"Management.h"
#include"Window.h"
#include"Table.h"
#include<iostream>

int main666() {
	auto res = Table::split("R001\tShanghai\tBeijing\t1800\t2");
	for (auto& val : res) {
		std::cout << val << " ";
	}
	return  0;
}

int main() {
	Window w(960,640,EX_SHOWCONSOLE);
	w.setWindowTitle("航线航班管理系统");
	Management m;
	m.run();
	return w.exec();
}