#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
//creates a DTSTART out of the given date (also works for DTEND)
string getDTSTART( string input ){
	string newstring = "";
	//assuming nobody will be using this after year 9999
	newstring+=input.substr(0,4);
	newstring+=input.substr(5,2);
	newstring+=input.substr(8,2);
	newstring += 'T';
	newstring+=input.substr(11,2);
	newstring+=input.substr(14,2);
	newstring += "00";
	//newstring += 'Z';
	return newstring;
}

//creates a DTSTAMP out of the current time
string getDTSTAMP ( tm* input ){
	string newstring = "";
	newstring += to_string( input->tm_year + 1900 );
	if(input->tm_mon + 1 < 10){
		newstring += '0';
	}
	newstring += to_string( input->tm_mon + 1 );
	if(input->tm_mday < 10){
		newstring += '0';
	}
	newstring += to_string( input->tm_mday );
	newstring += 'T';
	if(input->tm_hour < 10){
		newstring += '0';
	}
	newstring += to_string(input->tm_hour);
	if(input->tm_min < 10){
		newstring += '0';
	}
	newstring += to_string(input->tm_min);
	if(input->tm_sec < 10){
		newstring += '0';
	}
	newstring += to_string(input->tm_sec);
	//newstring += 'Z';
	return newstring;
}

//removes spaces from a string
string removespaces ( string input ){
	string newstring = "";
	for (int i=0;i<input.size()-1;i++){
		if(input[i] != ' '){
			newstring += input[i];
		} 
	}
	return newstring;
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
		<<"please enter the filename below (no spaces)"<<endl;
		
	cin>>filename;
	
	filename.append(".ics");
	
	ofstream file(filename.c_str());
	
	file<<"BEGIN:VCALENDAR\r\n"
		<<"VERSION:2.0\r\n"
		<<"PRODID:Thomassawesomeicalcreator\r\n";
		
	while (!klaar){
		rawtime = time(0);
		localtm = localtime(&rawtime);
		
		file<<"BEGIN:VEVENT\r\n";
		//get local time
		string time = asctime(localtm);
		
		time = removespaces(time);
		
		file<<"UID:"<<time<<"@thomassawesomeicalcreator.com\r\n"
			<<"DTSTAMP:"<<getDTSTAMP(localtm)<<"\r\n";
		
		string begindate, enddate;
		//get the begindate
		cout<<"When will the event begin? (yyyy-mm-dd:hh-mm)"<<endl;
		cin>>begindate;
		file<<"DTSTART:"<<getDTSTART(begindate)<<"\r\n";
		
		//get the end date
		cout<<"When will the event end? (yyyy-mm-dd:hh-mm)"<<endl;
		cin>>enddate;
		file<<"DTEND:"<<getDTSTART(enddate)<<"\r\n";
		
		//get the name of the event
		cout<<"What is the name of the event?"<<endl;
		string eventname;
		cin.ignore();
		getline(cin, eventname);
		file<<"SUMMARY:"<<eventname<<"\r\n";
		
		//get the location of the event
		cout<<"What is the location of the event? " 
			<<"(leave blank for no location (press enter twice))"<<endl;
		string eventlocation;
		cin.ignore();
		getline(cin, eventlocation);
		if( eventlocation != ""){ 
			file<<"LOCATION:"<<eventlocation<<"\r\n";
		}
		else
			cout<<"No location."<<endl;
		
		//get the description for the event
		cout<<"What is the description of the event? " 
			<<"(leave blank for no location (press enter twice))"<<endl;
		string eventdescription;
		cin.ignore();
		getline(cin, eventdescription);
		if( eventdescription != ""){ 
			file<<"DESCRIPTION:"<<eventdescription<<"\r\n";
		}
		else
			cout<<"No description."<<endl;
		
		file<<"END:VEVENT\r\n";
		
		cout<<"Add another event? (y/n)"<<endl;
		char answer;
		cin>>answer;
		if( answer != 'y' )
			klaar = true;
	}
	
	file<<"END:VCALENDAR";	
	
	return 0;
}
