#include <iostream>
#include <limits>
#include <fstream>
#include "linkedlist.h"
#include "student.h"

void reset_inputStream(void){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

void sort_record(nstd::LinkedList<Student>& studentRecord){
    for(int i=0;i<studentRecord.size()-1;i++){
        int minIndex=i;
        for(int j=i+1;j<studentRecord.size();j++){
            if(studentRecord.at(j).roll_number<studentRecord.at(minIndex).roll_number)
                minIndex=j;
        }
        studentRecord.swap(i,minIndex);
    }
}

void read_from_file(nstd::LinkedList<Student>& studentRecord){
	Student student;
	std::ifstream inFile("studentRecord.txt");

	if(!inFile){
		inFile.open("studentRecord.txt",std::ios::app);
	}

	inFile.seekg(0, std::ios::beg);

	if(inFile.is_open()){
		while(getline(inFile,student.name)){
			if(student.name=="")
				break;
			inFile>>student.roll_number;
			inFile>>student.total_marks;
			inFile>>student.semester_result;
			inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			studentRecord.append(student);
		}
	}
	else{
		std::cout<<"ERROR: unable to open file"<<std::endl;
	}

	inFile.close();
}

void write_to_file(nstd::LinkedList<Student>& studentRecord){
	std::ofstream oFile("studentRecord.txt");
	
	if(studentRecord.size()!=0)
		sort_record(studentRecord);
	if(oFile.is_open()){
		for(int i =0;i<studentRecord.size();i++){
			oFile<<studentRecord.at(i).name<<std::endl;
			oFile<<studentRecord.at(i).roll_number<<std::endl;
			oFile<<studentRecord.at(i).total_marks<<std::endl;
			oFile<<studentRecord.at(i).semester_result<<std::endl;
			oFile<<std::endl;
		}
	}
	else{
		std::cout<<"ERROR: unable to access the file"<<std::endl;
	}

	oFile.close();

}

bool student_record_is_present(const nstd::LinkedList<Student>& studentRecord,unsigned long& roll_number,unsigned int& index){
	bool roll_number_present = false;
	Student student;

	std::cout<<" Enter AKTU Roll Number : ";
	if(!(std::cin>>roll_number))
		throw InvalidInputException('I');

	for(index=0;index<studentRecord.size();index++){
		student = studentRecord.at(index);
		if(student.roll_number == roll_number){
			roll_number_present = true;
			break;
		}
	}
	return roll_number_present;
}

void input_student_details(nstd::LinkedList<Student>& studentRecord){
	Student student;
	unsigned int index =0;

	std::cout<<" Enter Name : ";
	getline(std::cin,student.name);
	if(student_record_is_present(studentRecord,student.roll_number,index)){
		std::cout<<" Roll Number "<<student.roll_number<<" is already present"<<std::endl;
		return ;
	}
	std::cout<<" Enter Total Marks Obtained :";
	if(!(std::cin>>student.total_marks))
		throw InvalidInputException('I');
	if(!(student.total_marks>=0&&student.total_marks<=900))
		throw InvalidInputException('R');

	if(student.total_marks >= 300)
		student.semester_result = 'P';
	else
		student.semester_result = 'F';

	studentRecord.append(student);
	sort_record(studentRecord);
	std::cout<<"\n Successfully Added a new record "<<std::endl;
}

void display_details(const Student& student){
		std::cout<<"\n Name : "<<student.name<<std::endl;
		std::cout<<" Roll Number : "<<student.roll_number<<std::endl;
		std::cout<<" Total Marks Obtained : "<<student.total_marks<<std::endl;
		std::cout<<" Semester Result : ";
		if(student.semester_result == 'P')
			std::cout<<"Pass"<<std::endl;
		else
			std::cout<<"Fail"<<std::endl;	
}


void view_single_student_details(const nstd::LinkedList<Student>& studentRecord){
	unsigned int index =0;
	unsigned long roll_number=0;
	if(student_record_is_present(studentRecord,roll_number,index)){
		display_details(studentRecord.at(index));
	}
	else
		std::cout<<" No Record with Roll Number "<<roll_number<<" Found"<<std::endl;		
}

void view_all_student_details(const nstd::LinkedList<Student>& studentRecord){
	for(int index=0;index<studentRecord.size();index++){
		display_details(studentRecord.at(index));
	}
}

void modify_student_details(nstd::LinkedList<Student>& studentRecord){
	unsigned int index =0;
	unsigned long roll_number =0;
	if(student_record_is_present(studentRecord,roll_number,index)){
		Student student;
		student = studentRecord.at(index);
		reset_inputStream();

		std::cout<<" Enter Name : ";
		getline(std::cin,student.name);
		std::cout<<" Enter Total Marks Obtained :";
		if(!(std::cin>>student.total_marks))
			throw InvalidInputException('I');
		if(!(student.total_marks>=0&&student.total_marks<=900))
			throw InvalidInputException('R');

		if(student.total_marks >= 300)
			student.semester_result = 'P';
		else
			student.semester_result = 'F';

		studentRecord.at(index) = student;

		sort_record(studentRecord);
		std::cout<<"\n Record modifed Successfully "<<std::endl;	
	}
	else
		std::cout<<" No Record with Roll Number "<<roll_number<<" Found"<<std::endl;
}

void delete_record(nstd::LinkedList<Student>& studentRecord){
	unsigned int index =0;
	unsigned long roll_number=0;
	if(student_record_is_present(studentRecord,roll_number,index)){
		studentRecord.del(index);
		std::cout<<"\n Record deleted Successfully "<<std::endl;
	}
	else
		std::cout<<" No Record with Roll Number "<<roll_number<<" Found"<<std::endl;
}

void menu(void){
	unsigned int choice;
	Student student;
	nstd::LinkedList<Student> studentRecord;
	read_from_file(studentRecord);

	while(true){
		system("cls");
		std::cout<<" Press \n";
		std::cout<<" 1 to create a new Record\n";
		std::cout<<" 2 to search a Student Record\n";
		std::cout<<" 3 to view all students record\n";
		std::cout<<" 4 to modify a student record\n";		
		std::cout<<" 5 to delete a student record\n";
		std::cout<<" 6 to Exit\n"<<std::endl;
		std::cout<<" Enter your choice : ";

		try{
			if(!(std::cin>>choice))
				throw InvalidInputException('I');
			reset_inputStream();
			system("cls");
			switch(choice){
				case 1: std::cout<<"\n Create New Record \n\n"<<std::endl;
						input_student_details(studentRecord);
						break;

				case 2:	std::cout<<"\n View Single Record \n\n"<<std::endl;
						view_single_student_details(studentRecord);
						break;

				case 3: std::cout<<"\n View All Records \n\n"<<std::endl;
						view_all_student_details(studentRecord);
						break;

				case 4: std::cout<<"\n Modify Record \n\n"<<std::endl;
						modify_student_details(studentRecord);
						break;

				case 5: std::cout<<"\n Delete Record \n\n"<<std::endl;
						delete_record(studentRecord);
						break;

				case 6: write_to_file(studentRecord);
						return ;

				default : std::cout<<" Invalid choice "<<std::endl;
						break;
			}			
		}
		catch(const InvalidInputException& e){
			if(e.get_exception() == 'R')
				std::cout<<" Marks should be in range [0, 900]"<<std::endl;
			else if(e.get_exception() == 'I'){
				std::cout<<" ERROR: value can't be non integer"<<std::endl;
			}
		}
		std::cout<<"\n\n\n\n\n\n\n\n Press any Key to continue ..."<<std::endl;
		if(choice==1||choice==2||choice==4||choice==5||choice==6)			
			reset_inputStream();
		std::cin.get();				
	}	
}

int main(void){
	menu();
	return 0;
}

