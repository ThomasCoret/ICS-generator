#include "agendaitem.h"

agendaitem::agendaitem( ){
	begindate = "";
	enddate = "";
	title = "";
	description = "";
	location = "";
	//we assume that an event will have a location
	haslocation = true;
	hasdescription = true;
}

void agendaitem::fillitem( ){
	settitle();
	setbegindate();
	setenddate();
	setdescription();
	setlocation();
}

void agendaitem::addtofile( std::ofstream* file ){
	std::cout<<"we sure are adding now!\n";
	time_t rawtime;
	tm* localtm;

	rawtime = time(0);
	localtm = localtime(&rawtime);
	
	*file<<"BEGIN:VEVENT\r\n";
	//get local time
	std::string time = asctime(localtm);
	
	time = removespaces(time);
	
	*file<<"UID:"<<time<<"@thomassawesomeicalcreator.com\r\n"
		<<"DTSTAMP:"<<getDTSTAMP(localtm)<<"\r\n";

	*file<<"DTSTART:"<<begindate<<"\r\n";
	*file<<"DTEND:"<<enddate<<"\r\n";
	*file<<"SUMMARY:"<<title<<"\r\n";
	if( haslocation){ 
		*file<<"LOCATION:"<<location<<"\r\n";
	}
	if( hasdescription){ 
		*file<<"DESCRIPTION:"<<description<<"\r\n";
	}
	*file<<"END:VEVENT\r\n";
}

void agendaitem::setbegindate( ){
begindatelabel:
	std::cout<<"When will the event begin? (yyyymmdd:hhmm)\n";
	std::cin>>begindate;
	if (begindate.size()!=13){
		std::cout<<"date is wrong format.\n";
		goto begindatelabel;
	}
	begindate = getDTSTART(begindate);
}

void agendaitem::setenddate( ){
enddatelabel:
	std::cout<<"When will the event end? (yyyymmdd:hhmm)\n";
	std::cin>>enddate;
	if (enddate.size()!=13){
		std::cout<<"date is wrong format.\n";
		goto enddatelabel;
	}
	enddate = getDTSTART(enddate);
}

void agendaitem::settitle( ){
	std::cout<<"What is the name of the event?\n";
	std::cin.ignore();
	std::getline(std::cin, title);
}

void agendaitem::setdescription( ){
	std::cout<<"What is the description of the event? " 
			<<"(leave blank for no location (press enter twice))\n";
	std::cin.ignore();
	std::getline(std::cin, description);
	if( description == "")
		hasdescription = false;
}

void agendaitem::setlocation( ){
	std::cout<<"What is the location of the event? " 
		<<"(leave blank for no location (press enter twice))\n";
	std::cin.ignore();
	std::getline(std::cin, location);
	if( location == "")
		haslocation = false;
}

std::string agendaitem::removespaces ( std::string input ){
	std::string newstring = "";
	for (int i=0;i<input.size()-1;i++){
		if(input[i] != ' '){
			newstring += input[i];
		} 
	}
	return newstring;
}

std::string  agendaitem::getDTSTART( std::string  input ){
	std::string newstring = "";
	//assuming nobody will be using this after year 9999 (big assumption I know)
	newstring+=input.substr(0,8);
	newstring += 'T';
	newstring+=input.substr(9,4);
	newstring += "00";
	return newstring;
}

std::string  agendaitem::getDTSTAMP ( tm* input ){
	std::string newstring = "";
	newstring += std::to_string( input->tm_year + 1900 );
	if(input->tm_mon + 1 < 10){
		newstring += '0';
	}
	newstring += std::to_string( input->tm_mon + 1 );
	if(input->tm_mday < 10){
		newstring += '0';
	}
	newstring += std::to_string( input->tm_mday );
	newstring += 'T';
	if(input->tm_hour < 10){
		newstring += '0';
	}
	newstring += std::to_string(input->tm_hour);
	if(input->tm_min < 10){
		newstring += '0';
	}
	newstring += std::to_string(input->tm_min);
	if(input->tm_sec < 10){
		newstring += '0';
	}
	newstring += std::to_string(input->tm_sec);
	return newstring;
}