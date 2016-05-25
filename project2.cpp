// project2.cpp : main project file.
// adam pluth
// cs 101
// project2

#include "stdafx.h"
#include <iostream>
#include <vector>
//using namespace System;
bool soloply;
int total;
int pick;
int sticks,picks;
bool playagain;
int pickStix(){
	std::cout<<"How many sticks are there on the table initially (10-100)? ";
	std::cin>>total;
	if(total<10||total>100){std::cout<<"sorry not a valid selction try agian\n";total=pickStix();}
	else{return total;}
}	
int stixPick(){
	std::cout<<"How many sticks can be picked up per round (2-20)? ";
	std::cin>>pick;
	if(pick<2||pick>20){std::cout<<"sorry not a valid selction try agian\n";pick=stixPick();}
	return pick;
}
bool playerMenu(){
	int onePlyr;
	bool oneplyr;
	std::cout<<"Option:\n Play againsta friend (1)\n Play against the computer(2)\nWhich option do you take (1-2)? ";
	std::cin>>onePlyr;
	if (onePlyr==2){oneplyr=true;}
	else if(onePlyr==1){oneplyr=false;}
	else{std::cout<<"sorry selection not valid try again\n";oneplyr=playerMenu();}
	return oneplyr;
}
bool again(){//tested funtion works don't modify
	int pix;
	bool choice;
	std::cout<<"Would you like to play again? (yes=1 no=0) ";
	std::cin>>pix;
	if(pix==1){choice=false;}
	else if(pix==0){choice=true;}
	else {std::cout<<"sorry not a valid selction try agian\n";choice=(again());}
	return choice;//tested funtion works don't modify
}
void printBrain(std::vector<std::vector<int>> brain) {
	std::cout << "number of sticks:" << brain.size() - 1 << "\nbest picks:\n";
	for (int i = 0; i <= brain.size(); i++) {
		std::cout << i + 1 << ": ";
		for (int j = 0; j <= brain[i].size(); j++) {
			std::cout << brain[i][j] << ",";
		}
		std::cout << "\n";
	}
	std::cout << "end of brain\n";
}

int p1Turn(int s,int p){
	int grab;
	std::cout<<"Player 1: How many sticks would you like to take (1-"<<p<<")? ";
	std::cin>>grab;
	std::cout<<"\n";
	if(grab>s||grab>p||grab<1){

		std::cout<<"sorry not a valid move\n";
		if(s==1){std::cout<<"there is 1 stick on the board.\n";}
		else{std::cout<<"there are "<<s<<" sticks on the board.\n";}
		s=p1Turn(s,p);
	}
	else {s-=grab;}
	return s;
}
int p2Turn(int s,int p){
	int grab;
	std::cout<<"Player 2: How many sticks would you like to take (1-"<<p<<")? ";
	std::cin>>grab;
	if(grab>s||grab>p||grab<1){
		std::cout<<"sorry not a valid move\n";
		if(s==1){std::cout<<"there is 1 stick on the board.\n";}
		else{std::cout<<"there are "<<s<<" sticks on the board.\n";}
		s=p2Turn(s,p);
	}
	else {s-=grab;}
	return s;
}
int aiTurn(int s,int p,std::vector<std::vector<int>> brain,bool prin){
	int aiPick = 1;
	if(prin){
//			std::cout<<"sticks"<<s<<"\n";
	//		std::cout<<"choices"<<brain[s-1].size()<<"\n";
		//printBrain(brain);

		}
		//if (brain[s-1].size() < 1) { int aiPick = std::rand() % s; }//maybe
	if(prin){std::cout<<"Ai picks: "<<aiPick<<"\n";}
		if (s<=p){
			aiPick=s-1;
			if(aiPick<1){aiPick=1;}
			s-=aiPick;
			if(prin){
			std::cout<<"sticks after smart pick: "<<s;
			std::cout<<"\nAi picks: "<<aiPick<<"\n";
			return s;

			}
		}
	
	
		else {
			s -= aiPick = std::rand() % p;//-1or 2 lines down	
			if (prin) {
				std::cout << "sticks after standard pick: " << s;
				std::cout << "\nAi picks: " << aiPick << "\n";
				//std::cout<<"Ai picks: "<<aiPick<<"\n";
			}
		}
	
	return s;
}
std::vector<std::vector<int>> trainAi(int s, int p) {
	std::vector<std::vector<int>>brain;
	for (int i = 0; i < sticks; i++) {
		std::vector<int>brainRow;
		for (int j = 0; j < picks; j++) { brainRow.push_back(j + 1); }
		brain.push_back(brainRow);
	}
	int ss = s;
	int New;
	for(int k=0;k!=60;k++){
	/*number of training games*/
	s = ss;
	//std::cout<<"\ngame no. : "<<k<<"\n";
	while (s >= 1) {
		std::vector<int> memory;
		bool pr = false;
		int sss = s;
		s = aiTurn(s, p, brain, pr);
		if (s < 1) { continue; }
		New = sss - s;
		memory.push_back(New);
		for (int i = 0; i != memory.size(); i++) { brain[s - 1].push_back(memory[i]); }
	}
}
	printBrain(brain);
	return brain;
}
void playGame(int s,int p,bool ai,std::vector<std::vector<int>> brain){
	if(ai){
		std::vector<int> memory;
		int ss=s;
		int New;
		while(s>=1){
			if(s==1){std::cout<<"there is 1 stick on the board.\n";}
			else{std::cout<<"there are "<<s<<" sticks on the board.\n";}
			s=p1Turn(s,p);
			if (s<1){std::cout<<"you lose\n";break;}
			if(s==1){std::cout<<"there is 1 stick on the board.\n";}
			else{std::cout<<"there are "<<s<<" sticks on the board.\n";}
			int sss=s;
			bool pr=true;
			s=aiTurn(s,p,brain,pr);
			if (s<1){std::cout<<"AI loses\n";break;}
			New=sss-s;
			memory.push_back(New);
			std::cout<<"\n memoryadded";
			//for(int i=0;i!=memory.size();i++){brain[s-1].push_back(memory[i]);}
			std::cout<<"\n";
		}	
	}
	else{
		while(s>=1){
			if(s==1){std::cout<<"there is 1 stick on the board.\n";}
			else{std::cout<<"there are "<<s<<" sticks on the board.\n";}
			s=p1Turn(s,p);
			if (s<1){std::cout<<"Player 1 loses\n";break;}
			if(s==1){std::cout<<"there is 1 stick on the board.\n";}
			else{std::cout<<"there are "<<s<<" sticks on the board.\n";}
			s=p2Turn(s,p);
			if (s<1){std::cout<<"Player 2 loses\n";}
		}
	}
}
int main(){
	std::cout<<"Welcome to the game of sticks\n";	
	sticks=pickStix();
	picks=stixPick();
	soloply=playerMenu();	
	
	std::cout<<"sticks: "<<sticks<<"\npicks: "<<picks<<"\nhumans: "<<!soloply<<"\n";
	std::getchar();
	//playing the game
	std::cout<<"training Ai , please wait...\n..\n.";

	
	std::vector<std::vector<int>>brain;
//	brain=trainAi(sticks,picks);
//	printBrain(brain);
	std::cout<<"\n\n\n....training completed...\n..\n.\n";

	while(!playagain){playGame(sticks,picks,soloply,brain);playagain=again();}

	return 0;
}
