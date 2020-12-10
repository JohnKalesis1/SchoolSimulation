#include <iostream>
#include "derived_facilities.h"

namespace pseudo_hash  {
    char floor[]={'A','B','C'};//a one on one representation for floors using the alphabet
};


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


bool Teacher::is_in_classroom() {
    return inside_classroom;
}

void Teacher::teach(int hours)  {
    int exhaustion_rate=School::get_teacher_exhaustion_rate();
    increase_exhaustion(hours*exhaustion_rate);
}

void Teacher::enters_classroom()  {
    inside_classroom=true;
}



void Student::enters_classroom()  {
    inside_classroom=true;
}

int Student::get_classroom_id()  {
    return classroom->get_id();
}



void Junior::attend(int hours)  {
    int exhaustion_rate=School::get_junior_exhaustion_rate();
    increase_exhaustion(hours*exhaustion_rate);
}



void Senior::attend(int hours)  {
    int exhaustion_rate=School::get_senior_exhaustion_rate();
    increase_exhaustion(hours*exhaustion_rate); 
}



Space::Space()  {
    students.push_back(NULL);
}

void Space::enter(Student* student)  {
    students.at(0)=student;
}



void Yard::enter(Student* student)  {
    std::cout <<student->get_name() << " enters yard\n";
    Space::enter(student);
}

Student* Yard::exit()  {
    std::cout <<students.at(0)->get_name() << " exits yard\n";
    
}



void Stairs::enter(Student* student)  {
    std::cout <<student->get_name() << " enters stairs\n";
    Space::enter(student);
}

Student* Stairs::exit()  {
    std::cout <<students.at(0)->get_name() << " exits stairs\n";
}

int Stairs::floor_distribution()  {
    return students.at(0)->get_classroom_id()/6;
}



void Corridor::enter(Student* student)  {
    std::cout <<student->get_name() << " enters corridor\n";
    Space::enter(student);
}

Student* Corridor::exit()  {
    std::cout <<students.at(0)->get_name() << " exits corridor\n";
}



void Classroom::register_teacher(Teacher* teacher)  {
    this->teacher=teacher;
}

int Classroom::get_id()  {
    return id;
}

void Classroom::enter(Student* student)  {
    std::cout <<student->get_name() << " enters classroom\n";
    Space::enter(student);
}

void Classroom::print()  {
    for (int i=0;i<students.size();i++)  {
        std::cout << "\t->Student " << students.at(i)->get_name() << std::endl;
    }
    if (teacher->is_in_classroom())  { 
        std::cout << "\t->Teacher " << teacher->get_name() << std::endl;
    }
    std::cout << std::endl;
}

void Classroom::operate(int hours)  {
    for (int i=0;i<students.size();i++)  {
        students.at(i)->attend(hours);
    }
    teacher->teach(hours);
}

Floor::Floor(int floor_number,int class_capacity)  {
    this->floor_number=floor_number;
    corridor=Corridor();
    for (int i=0;i<6;i++)  {
        classrooms.push_back(Classroom(6*floor_number+i));
    }
}

void Floor::operate(int hours)  {
    for (int i=0;i<6;i++)  {
        classrooms.at(i).operate(hours);
    }
}
void Floor::enter(Student* student)  {
    std::cout << student->get_name() << "enters floor "<< pseudo_hash::floor[floor_number] << '\n';
    corridor.enter(student);
    classrooms[student->get_classroom_id()/6].enter(corridor.exit());
}

void Floor::print()  {
    std::cout << " Floor " << pseudo_hash::floor[floor_number] << " consists of:\n" ;
    for (int i=0;i<6;i++)  {
        classrooms.at(i).print();
    }
    std::cout << '\n';
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

