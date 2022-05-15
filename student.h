#ifndef STUDENT_H
#define STUDENT_H

class InvalidInputException{
	char m_type_of_exception;
public:
	InvalidInputException(char type_of_exception){
		m_type_of_exception = type_of_exception;
	}
	char get_exception() const{
		return m_type_of_exception;
	}
};

struct Student{
	std::string name;
	unsigned long long roll_number;
	unsigned int total_marks;
	char semester_result;
};

void reset_inputStream(void);
void sort_record(nstd::LinkedList<Student>& studentRecord);
void read_from_file(nstd::LinkedList<Student>& studentRecord);
void write_to_file(nstd::LinkedList<Student>& studentRecord);
bool student_record_is_present(const nstd::LinkedList<Student>& studentRecord,unsigned long long& roll_number,unsigned int& index);
void input_student_details(nstd::LinkedList<Student>& studentRecord);
void display_details(const Student& student);
void view_single_student_details(const nstd::LinkedList<Student>& studentRecord);
void view_all_student_details(const nstd::LinkedList<Student>& studentRecord);
void modify_student_details(nstd::LinkedList<Student>& studentRecord);
void delete_record(nstd::LinkedList<Student>& studentRecord);

#endif