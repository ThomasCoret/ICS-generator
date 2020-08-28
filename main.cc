#include "libs/agendaitem.h"
#include <list>

using namespace std;

char getyn(){
	char answer;
	cin>>answer;
	return answer;
}

//manage the current items in the list
void manageitems(list<agendaitem>* agendaitems){

}

void menu(ofstream* file){
	int itemsadded = 0;
	bool ready = false;
	list<agendaitem> agendaitems;
beginlabel:
	while(true){
		cout<<"you currently have "<<itemsadded<<" events added. \n Do you want to add an event? (y/n)\n";
		//if user is done adding items break from the while loop (we use tolower to also allow user to use a Y instead of y.)
		if( tolower(getyn()) != 'y' ){
			break;
		}
		
		agendaitem newitem;

		//fill the item
		newitem.fillitem();

		//add the item to the list
		itemsadded++;
		agendaitems.emplace_back(newitem);

		//allow user to manage the events
		cout<<"Do you want to manage the events? (delete or change events)\n";
		if( tolower(getyn()) != 'y' ){
			manageitems(&agendaitems);
		}

	}

	cout<<"Are you sure you do not want to add anymore items?(y/n)\n";

	//loop back to menu if user wants to continue
	if(tolower(getyn()) == 'n')
		//I know goto's are kinda a nono but they are just too convenient.
		goto beginlabel;

	//allow user to manage the items before making the final ical file.
	cout<<"Do you want to manage the events?(y/n) (delete or change events)\n";
	if( tolower(getyn()) != 'y' ){
		manageitems(&agendaitems);
	}

	cout<<"Your items will now be turned into an ical file please stand by.\n";
	//iterate over all items and add them to the file
	for(list<agendaitem>::iterator it=agendaitems.begin(); it != agendaitems.end(); it++){
		cout<<"loop\n";
		it->addtofile(file);
	}
	
}

int main ( ){
	
	string filename;
	bool klaar = false;
	time_t rawtime;
	tm* localtm;
	
	cout<<"------------------------------------"<<endl
		<<"  Welcome to my ical file creator."<<endl
		<<"  Created by: Thomas Coret 2019"<<endl
		<<"------------------------------------"<<endl
		<<"please enter the filename below (no spaces and no extension)"<<endl;
	
	

	cin>>filename;
	
	filename.append(".ics");
	
	ofstream file(filename.c_str());
	
	//Standard file start
	file<<"BEGIN:VCALENDAR\r\n"
		<<"VERSION:2.0\r\n"
		<<"PRODID:Thomassawesomeicalcreator\r\n";

	menu(&file);
	
	file<<"END:VCALENDAR";	
	file.close();

	return 0;
}
