#include <iostream>
#include "derived_facilities.h"

namespace pseudo_hash  {
    char floor[]={'A','B','C'};//a one on one representation for floors using the alphabet
};

int junior_formula(int iterator)  {
    return 3*((iterator%9)/3)+iterator%3; //returns the id that the junior student be placed upon entry
}

Person::Person(std::string name) : exhaustion(0) {
    this->name.assign(name);
}

std::string& Person::get_name()  {
    return name;
}

int Person::get_exhaustion()  {
    return exhaustion;
}

void Person::increase_exhaustion(int n)  {
    exhaustion=exhaustion+n;
}


Teacher::Teacher(Classroom* classroom,std::string name) : Person(name), inside_classroom(false), classroom(classroom) {
    std::cout << "A Teacher has been created, " << this->name <<" of classroom "<< pseudo_hash::floor[classroom->get_id()/6] << classroom->get_id()%6<< std::endl;
    classroom->register_teacher(this);
}

bool Teacher::is_in_classroom() {
    return inside_classroom;
}

void Teacher::teach(int hours)  {
    int exhaustion_rate=School::get_teacher_exhaustion_rate();
    increase_exhaustion(hours*exhaustion_rate);
}

void Teacher::place()  {
    inside_classroom=true;
}



void Student::enters_classroom()  {
    inside_classroom=true;
}

int Student::get_classroom_id()  {
    return classroom->get_id();
}


Junior::Junior(Classroom* classroom,std::string name): Student(classroom,name) {
    std::cout << "A Junior student has been created, "<< this->name <<" of classroom "<< pseudo_hash::floor[classroom->get_id()/6] << classroom->get_id()%6<< std::endl;
}

void Junior::attend(int hours)  {
    int exhaustion_rate=School::get_junior_exhaustion_rate();
    increase_exhaustion(hours*exhaustion_rate);
}

void Junior::print()  {
    std::cout << "Junior "<< name << "("<< exhaustion <<")";
}


Senior::Senior(Classroom* classroom,std::string name): Student(classroom,name) {
    std::cout << "A Senior student has been created, "<< this->name <<" of classroom "<< pseudo_hash::floor[classroom->get_id()/6] << classroom->get_id()%6<< std::endl;
}

void Senior::attend(int hours)  {
    int exhaustion_rate=School::get_senior_exhaustion_rate();
    increase_exhaustion(hours*exhaustion_rate); 
}

void Senior::print()  {
    std::cout << "Senior "<< name << "("<< exhaustion <<")";
}



void Space::enter(Student* student)  {
    students.at(0)=student;
}


Yard::Yard()  {
    std::cout << "The yard has beem created \n";
    students.push_back(NULL);
}

void Yard::enter(Student* student)  {
    student->print();
    std::cout << " enters yard\n";
    Space::enter(student);
}

Student* Yard::exit()  {
    students.at(0)->print();
    std::cout << " exits yard->";
    return students.at(0);
}


Stairs::Stairs()  {
    std::cout << "The stairs has been created \n";
    students.push_back(NULL);
}

void Stairs::enter(Student* student)  {
    student->print();
    std::cout <<" enters stairs\n";
    Space::enter(student);
}

Student* Stairs::exit()  {
    students.at(0)->print();
    std::cout << " exits stairs->";
    return students.at(0);
}

int Stairs::floor_distribution()  {
    return students.at(0)->get_classroom_id()/6;
}


Corridor::Corridor()  {
    std::cout << "A corridor has beem created \n";
    students.push_back(NULL);
}

void Corridor::enter(Student* student)  {
    student->print();
    std::cout << " enters corridor\n";
    Space::enter(student);
}

Student* Corridor::exit()  {
    students.at(0)->print();
    std::cout <<" exits corridor->";
    return students.at(0);
}


Classroom::Classroom(int id) : id(id)  {
    std::cout << "A classroom has beem created "<< id<< '\n';
}

void Classroom::register_teacher(Teacher* teacher)  {
    this->teacher=teacher;
}

int Classroom::get_id()  {
    return id;
}

void Classroom::enter(Student* student)  {
    std::cout <<student->get_name() << " enters classroom\n";
    students.push_back(student);
}

void Classroom::print()  {
    std::cout << "\tClassroom " << id%6 << ":\n";
    for (int i=0;i<students.size();i++)  {
        std::cout << "\t->";
        students.at(i)->print();
        std::cout << std::endl;
    }
    if (teacher->is_in_classroom())  { 
        std::cout << "\t->Teacher " << teacher->get_name() <<"(" <<teacher->get_exhaustion()<< ")"<< std::endl;
    }
    std::cout << std::endl;
}

void Classroom::operate(int hours)  {
    for (int i=0;i<students.size();i++)  {
        students.at(i)->attend(hours);
    }
    teacher->teach(hours);
}

Floor::Floor(int floor_number)  {
    this->floor_number=floor_number;
    for (int i=0;i<6;i++)  {
        classrooms.push_back(Classroom(6*floor_number+i));
    }
}

Classroom* Floor::get_classroom(int index)  {
    return &classrooms.at(index);
}

void Floor::operate(int hours)  {
    for (int i=0;i<6;i++)  {
        classrooms.at(i).operate(hours);
    }
}
void Floor::enter(Student* student)  {
    student->print();
    std::cout << " enters floor "<< pseudo_hash::floor[floor_number] << "->";
    corridor.enter(student);
    classrooms[student->get_classroom_id()%6].enter(corridor.exit());
}

void Floor::print()  {
    std::cout << " Floor " << pseudo_hash::floor[floor_number] << " consists of:\n" ;
    for (int i=0;i<6;i++)  {
        classrooms.at(i).print();
    }
    std::cout << '\n';
}


School::School(int Lj,int Ls,int Lt) : juniors_iterator(0), seniors_iterator(0) {
    Junior_exhaustion_rate=Lj;
    Senior_exhaustion_rate=Ls;
    Teacher_exhaustion_rate=Lt;
    for (int i=0;i<3;i++)  {
        floors.push_back(Floor(i));
    }
}

School::~School()  {
    for (int i=0;i<students.size();i++)  {
        delete students.at(i);
    }
    for (int i=0;i<teachers.size();i++)  {
        delete teachers.at(i);
    }
}

void School::print()  {
    std::cout << "School building consists of: \n";
    for (int i=0;i<3;i++)  {
        floors.at(i).print();
    }
}

void School::begins()  {
    for (int i=0;i<students.size();i++)  {
        students.at(i)->print();
        std::cout << " enters school building->";
        yard.enter(students.at(i));
        stairs.enter(yard.exit());
        floors.at(stairs.floor_distribution()).enter(stairs.exit());
        std::cout << "\n";
    }
    for (int i=0;i<teachers.size();i++)  {
        teachers.at(i)->place();
    }
}

void School::operate(int hours)  {
    for (int i=0;i<3;i++)  {
        floors.at(i).operate(hours);
    }
}

void School::register_junior(std::string name)  {
    Student* junior_pointer=new Junior(floors.at((juniors_iterator%9)/3).get_classroom(juniors_iterator%3),name);
    students.push_back(junior_pointer);
    juniors_iterator++;
}

void School::register_senior(std::string name)  {
    Student* senior_pointer=new Senior(floors.at((seniors_iterator%9)/3).get_classroom(seniors_iterator%3+3),name);
    students.push_back(senior_pointer);
    seniors_iterator++;
}

void School::register_teacher(std::string name)  {
    teachers.push_back(new Teacher(floors.at(teachers.size()/6).get_classroom(teachers.size()%6),name));
}

int School::get_junior_exhaustion_rate()  {
    return Junior_exhaustion_rate;
}

int School::get_teacher_exhaustion_rate()  {
    return Teacher_exhaustion_rate;
}

int School::get_senior_exhaustion_rate()  {
    return Senior_exhaustion_rate;
}

