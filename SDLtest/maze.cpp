#include "stdafx.h"
#include "maze.h"


void maze::showroute(){
	if (route.empty()){
		std::cout<<"empty route";
		return;
	}
	std::vector<point>::iterator it;
	for (it=route.begin();it !=route.end();it++){
		std::cout<<"("<<it->i<<","<<it->j<<")";
	}
}
int maze::generate(){
	
	for (int j=0;j<MX;j++){
		cells[0][j].top=0;
	}
	for (int i=0;i<MY;i++){
		cells[i][0].left=0;
	}
	for (int i=0;i<MY;i++){
		for (int j=0;j<MX;j++){
			cells[i][j].right=rand1();
			cells[i][j].down=rand1();
			if (j>=1){
			cells[i][j].left=cells[i][j-1].right;
			}
			if (i>=1){
			cells[i][j].top=cells[i-1][j].down;
			}
		}
	
	}
	for (int j=0;j<MX;j++){
		cells[MY-1][j].down=0;
	}
	for (int i=0;i<MY;i++){
		cells[i][MX-1].right=0;
	}
	return 1;
}
int maze::rand1(){
	return rd()%2;
}
void maze::print() const{
	for (int i=0;i<MY;i++){
		for (int j=0;j<MX;j++){	std::cout<<cells[i][j].top<<cells[i][j].down<<cells[i][j].left<<cells[i][j].right<<" ";	
		}
		std::cout<<std::endl;
	}
}
void maze::draw() const{
	for (int i=0;i<MY;i++){
		for (int j=0;j<MX;j++){
			std::cout<<" "<<cells[i][j].top<<"  ";
		}
		std::cout<<std::endl;
		for (int j=0;j<MX;j++){
			std::cout<<cells[i][j].left<<" "<<cells[i][j].right<<" ";
		}
		std::cout<<std::endl;
		for (int j=0;j<MX;j++){
			std::cout<<" "<<cells[i][j].down<<"  ";
		}
		std::cout<<std::endl;
	}
}

int maze::find(int i,int j){
	route.clear();
	cells[i][j].used=1;
	if ((i==MY-1)&&(j==MX-1)) {
		route.insert(route.begin(),point(i,j));
		cells[i][j].used=0;
		return 1;
		}
	if (cells[i][j].top==1&&cells[i-1][j].used==0){
		if (find(i-1,j)==1) {
			route.insert(route.begin(),point(i,j));
			cells[i][j].used=0;
			return 1;
			}
	}
	if (cells[i][j].down==1&&cells[i+1][j].used==0){
		if (find(i+1,j)==1) {
			route.insert(route.begin(),point(i,j));
			cells[i][j].used=0;
			return 1;
			}
	}
	if (cells[i][j].left==1&&cells[i][j-1].used==0){
		if (find(i,j-1)==1) {
			route.insert(route.begin(),point(i,j));
			cells[i][j].used=0;
			return 1;
			}
	}
	if (cells[i][j].right==1&&cells[i][j+1].used==0){
		if (find(i,j+1)==1) {
			route.insert(route.begin(),point(i,j));
			cells[i][j].used=0;
			return 1;
			}
	}
	cells[i][j].used=0;
	return 0;
}
/*
int main() {
	maze m;
	m.generate();
	m.print();
	m.draw();
	int a, b;
	if (m.find(0, 0)) {
		m.showroute();
		std::cout << "found" << std::endl;
	}
	else std::cout << "not found" << std::endl;

	while (1) {
		std::cin >> a >> b;
		std::cout << a << "," << b << std::endl;
		if (m.find(a, b)) {
			m.showroute();
			std::cout << "found" << std::endl;
		}
		else std::cout << "not found" << std::endl;
	}

}
*/