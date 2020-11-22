#include "school_facilities.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace pseudo_hash  {
    std::string matrix[]={"school entrance","yard","stairs","corridor"};
    char floor[]={'A','B','C'};
};

Student** re_adjust_array(Student** old_array,int start_index,int end_index,int size)  {
    Student** array=new Student*[size];
    for (int i=0;i<end_index-start_index;i++)  {
        array[i]=old_array[start_index+i];
    }
    delete[] old_array;
    return array;
}

void Classroom::assign_teacher(std::string name)  {
    this->teacher.assign(name);
}

/*void Classroom::assign_student(Student* student)  {
    students[registered_students_count]=student;
}*/

void Classroom::teacher_enters()  {
    entry_possible=false;
    return ;
}

int Classroom::get_capacity()  {
    return capacity;
}

bool Classroom::teacher_inside()  {
    return !entry_possible;
}

short Classroom::get_id()  {
    return id;
}

Classroom::Classroom(int capacity,short id)  : entry_possible(true), population(0), capacity(capacity)/*, registered_students_count(0)*/, id(id) {
    std::cout << "A classroom has been created" << std::endl;
    students=new Student*[capacity];
}

Classroom::~Classroom()  {
    std::cout << "A classroom has been destroyed" << std::endl;
    delete[] students;
}

void Classroom::print()  {
    for (int i=0;i<population;i++)  {
        std::cout << "\t\t->Student " << students[i]->get_name() << std::endl;
    }
    if (entry_possible==false)  { 
        std::cout << "\t\t->Teacher " << teacher << std::endl;
    }
    std::cout << std::endl;
}

void Classroom::enter(Student* student)  {
    student->set_location_to(4);
    students[population]=student;
    population++;
    std::cout << student->get_name() << " enters classroom\n";
}



Corridor::Corridor(int capacity) : capacity(capacity), population(0)  {
    std::cout << "A corridor has been created" << std::endl;
    students=new Student*[capacity];
}

Corridor::~Corridor()  {
    std::cout << "A corridor has been destroyed" << std::endl;
    delete[] students;
}

int Corridor::get_student_class_id()  {
    return students[population-1]->get_classroom_id();
}

void Corridor::print()  {
    for (int i=0;i<population;i++)  {
        std::cout << "\t\t->Student " << students[i]->get_name() << std::endl;
    }  
    std::cout << std::endl;
}

bool Corridor::space_available()  {
    return population<capacity? true:false;
}

bool Corridor::is_empty()  {
    return population==0? true:false;
}

void Corridor::enter(Student* student)  {
    student->set_location_to(3);
    students[population]=student;
    population++;
    std::cout << student->get_name() << " enters " << pseudo_hash::matrix[3] << std::endl;
}

Student* Corridor::exit()  {
    std::cout << students[population-1]->get_name() << " exits " << pseudo_hash::matrix[3] << " --> ";
    return students[--population]; 
}

Student* Corridor::forced_exit(short id)  {
    for (int i=0;i<population;i++)  {
        if ((students[i]->get_classroom_id()%6)==id)  {
            Student* temp=students[i];
            students[i]=students[population-1];
            students[population-1]=temp;
            
            return exit();
        }
    }
    return NULL;
}

int Corridor::get_population()  {
    return population;
}





SchoolBuilding::SchoolBuilding(int class_capacity,int yard_capacity,int stairs_capacity,int corridor_capacity) : s_count(0), t_count(0), advanced_count(0) {
    std::cout << "A school has been created" << std::endl;
    yard=new Yard(yard_capacity);
    stairs=new Stairs(stairs_capacity);
    for (int i=0;i<3;i++)  {
        floors[i]=new Floor(i,corridor_capacity,class_capacity);
    }
    students=new Student*[18*class_capacity];
}

SchoolBuilding::~SchoolBuilding()  {
    
    for (int i=0;i<t_count;i++)  {
        delete teachers[i];
    }
    for (int i=0;i<s_count;i++)  {
        delete students[i];
    }
    delete yard;
    delete stairs;
    for (int i=0;i<3;i++)  {
        delete floors[i];
    }
    delete[] students;
    std::cout << "A school has been destroyed" << std::endl;
    
}

void SchoolBuilding::register_teacher(std::string name)  {
    if (t_count>18)  { 
        std::cout << "Error: Budget for Teaching Personnel Depleted" << std::endl ; 
        return ;
    }
    teachers[t_count]=new Teacher(name,floors[t_count/6]->get_class(t_count%6));
    t_count++;
}

void SchoolBuilding::register_student(std::string name)  {
    if (s_count>18*floors[0]->get_class(0)->get_capacity())  {
        std::cout << "Building's Facilities Can Not Accomodate More Students" << std::endl;
        return ;
    }
    students[s_count]=new Student(name,floors[(s_count/6)%3]->get_class(s_count%6));
    s_count++;
}

void SchoolBuilding::print()  {
    std::cout << "School life consists of:\n";
    std::cout << "\t1)People in yard are: \n";
    yard->print();
    std::cout << "\t2)People in stairs are: \n";
    stairs->print();
    for (int i=0;i<3;i++)  {
        std::cout << "\t3)Floor " << pseudo_hash::floor[i] << " consists of :\n";
        floors[i]->print();
    }

}

void SchoolBuilding::school_begins()  {
    short kill_switch=0;
    srand(time(NULL));
    while (advanced_count<s_count && kill_switch!=3)  {
        this->place_teacher(false);
        bool flag1=true,flag2=true,flag3=true;
        bool retry1=false,retry2=false,retry3=false,retry4=false;
        int students_entering=rand()%((s_count-advanced_count)/2);
        bool final_push= ((students_entering+advanced_count)>=s_count);
        int starting_count=advanced_count;
        std::cout << students<<std::endl;
        while ((flag1+flag2)!=0)  {
            flag1=false;
            if ((advanced_count-starting_count)<students_entering)  {
                int dt_count=advanced_count-starting_count;
                for (int i=0;i<students_entering-dt_count;i++)  {
                    if (yard->space_available())  {
                        yard->enter(students[advanced_count]);
                        advanced_count++;
                        flag1=true;
                        kill_switch=0;
                    }
                }
                std::cout << std::endl;
            }
            flag2=false;
            if (!yard->space_available() ||  (flag1+flag2)==0)  {
                retry1=true;
                int stop=yard->get_population();
                for (int i=0;i<stop;i++)  {
                    if (stairs->space_available())  {
                        stairs->enter(yard->exit());
                        flag2=true;
                    }
                }
                std::cout << std::endl;
            }
            
            if ((!stairs->space_available())  ||  (flag1+flag2)==0)  {
                int stop=stairs->get_population();
                for (int i=0;i<stop;i++)  {
                    short floor_choice=stairs->floor_distribution();
                    if (floors[floor_choice]->space_available_in_corridor())  {
                        floors[floor_choice]->enter(stairs->exit());
                    }
                }
            }
        }
        kill_switch++;
    }
    for (int i=0;i<3;i++)  {
        floors[i]->flush();
    }
    this->place_teacher(true);
}

void SchoolBuilding::place_teacher(bool all)  {
    short pick=rand()%2;
    int repeat=1;
    if (pick==1 || all)  {
        int array[18];
        int number_of_candidates;
        if (all)  {
            repeat=18;
        }
        for (int j=0;j<repeat;j++)  {
            number_of_candidates=0;
            for (int i=0;i<18;i++)  {
                if (!teachers[i]->is_in_class())  {
                    array[number_of_candidates]=i;
                    number_of_candidates++;
                }
            }
            if (number_of_candidates!=0)  {
                pick=rand()%(number_of_candidates);
                teachers[array[pick]]->enter_class(); 
            }
        }
    }
}





Floor::Floor(int height,int corridor_capacity,int class_capacity) : height(height), advanced_count(0), s_count(0) {
    std::cout << "A floor has been created" << std::endl;
    corridor=new Corridor(corridor_capacity);
    for (int i=0;i<6;i++)  {
        classrooms[i]=new Classroom(class_capacity,6*height+i);
    }
    students=new Student*[6*this->get_class(0)->get_capacity()];
}

Floor::~Floor()  {
    delete corridor;
    for (int i=0;i<6;i++)  {
        delete classrooms[i];
    }
    delete[] students;
    std::cout << "A floor has been destroyed" << std::endl;
}

Classroom* Floor::get_class(short number)  {
    return this->classrooms[number];
}

void Floor::print()  {
    std::cout << "\t\t-People in corridor of " << pseudo_hash::floor[height] << "-floor are: \n";
    corridor->print();
    for (int i=0;i<6;i++)  {
        std::cout << "\t\t-People in class " << pseudo_hash::floor[height] << classrooms[i]->get_id()%6 << " are:\n";
        classrooms[i]->print();
    }
}

void Floor::enter(Student* student)  {
    std::cout << student->get_name() << " enters floor " << pseudo_hash::floor[this->height] << " --> ";
    corridor->enter(student);
    if (!corridor->space_available())  {
        std::cout << std::endl;
        int stop=corridor->get_population();
        for (int i=0;i<stop;i++)  {
            int id=corridor->get_student_class_id()%6;
            if (!classrooms[id]->teacher_inside())  {
                classrooms[id]->enter(corridor->exit());
            }
        }
        std::cout << std::endl;
        
    }
}

void Floor::flush()  {
        int stop=corridor->get_population();
        for (int i=0;i<stop;i++)  {
            for (short id=0;id<6;id++)  {
                if (!classrooms[id]->teacher_inside())  {
                    Student* temp;
                    if ((temp=corridor->forced_exit(id))!=NULL)  {
                        classrooms[id]->enter(temp);
                    }
                }
            }
        }
        std::cout << std::endl;
}

bool Floor::students_advance()  { 
    short kill_switch=1;
    while (kill_switch!=2 && advanced_count!=s_count)  {
        kill_switch=0;
        for (int i=advanced_count;i<s_count;i++)  {
            if (corridor->space_available())  {
                kill_switch=0;
                corridor->enter(students[advanced_count]);
                advanced_count++;  
            }
            else  {
                kill_switch++;
                return false;
            }
        }
        if (kill_switch!=2)  {
            int stop=corridor->get_population();
            for (int i=0;i<stop;i++)  {
                int id=corridor->get_student_class_id()%6;
                if (!classrooms[id]->teacher_inside())  {
                    classrooms[id]->enter(corridor->exit());
                }
            }
        }
    }
    return true;
}

bool Floor::space_available_in_corridor()  {
    return corridor->space_available();
}



Stairs::Stairs(int capacity) : population(0), capacity(capacity) {
    std::cout << "Stairs have been created" << std::endl;
    students=new Student*[capacity];
}

Stairs::~Stairs()  {
    std::cout << "Stairs have been destroyed" << std::endl;
    delete[] students;
}

void Stairs::print()  {
    for (int i=0;i<population;i++)  {
        std::cout << "\t->Student " << students[i]->get_name() << std::endl;
    }  
    std::cout << std::endl;
}

bool Stairs::space_available()  {
    return population<capacity? true:false;
}

short Stairs::floor_distribution()  {
    return this->students[population-1]->get_classroom_id()/6;
}

void Stairs::enter(Student* student)  {
    student->set_location_to(2);
    students[population]=student;
    population++;
    std::cout << student->get_name() << " enters " << pseudo_hash::matrix[2] << std::endl;
}

bool Stairs::is_empty()  {
    return population==0? true:false;
}

Student* Stairs::exit()  {
    std::cout << students[population-1]->get_name() << " exits " << pseudo_hash::matrix[2] << " --> ";
    return students[--population]; 
}

int Stairs::get_population()  {
    return population;
}


Yard::Yard(int capacity) : population(0), capacity(capacity)  {
    std::cout << "A yard has been created" << std::endl;
    students=new Student*[capacity];
}

Yard::~Yard()  {
    std::cout << "A yard has been destroyed" << std::endl;
    delete[] students;
}

void Yard::print()  {
    for (int i=0;i<population;i++)  {
        std::cout << "\t->Student " << students[i]->get_name() << std::endl;
    }  
    std::cout << std::endl;
}

bool Yard::space_available()  {
    return population<capacity? true:false;
}

bool Yard::is_empty()  {
    return population==0? true:false;
}

void Yard::enter(Student* student)  {
    student->set_location_to(1);
    students[population]=student;
    population++;
    std::cout <<  student->get_name() << " enters school --> ";
    std::cout << student->get_name() << " enters " << pseudo_hash::matrix[1] << std::endl;
}

Student* Yard::exit()  {
    std::cout << students[population-1]->get_name() << " exits " << pseudo_hash::matrix[1] << " --> ";
    return students[--population]; 
}

int Yard::get_population()  {
    return population;
}


Teacher::Teacher(std::string name, Classroom* classroom) : in_class(false) {
    this->name.assign(name);
    this->classroom=classroom;
    this->classroom->assign_teacher(name);
    std::cout << "A Teacher has been created: " << name << ", teacher of classroom " << pseudo_hash::floor[(classroom->get_id()/6)%3] << classroom->get_id()%6 << std::endl;
}

Teacher::~Teacher()  {
    std::cout << "A Teacher to be destroyed: " << name << ", teacher of classroom " << pseudo_hash::floor[(classroom->get_id()/6)%3] << classroom->get_id()%6 << std::endl ;
}

void Teacher::enter_class()  {
    classroom->teacher_enters();
    std::cout << "Teacher " << name << " entes classroom " << pseudo_hash::floor[(classroom->get_id()/6)%3] << classroom->get_id()%6 << std::endl; 
    in_class=true;
}

bool Teacher::is_in_class()  {
    return classroom->teacher_inside();
}

Student::Student(std::string name,Classroom* classroom) : location(0) {
    this->name.assign(name);
    this->classroom=classroom;
    //classroom->assign_student(this);
    std::cout << "A Student has been created: " << name << ", student of classroom " << pseudo_hash::floor[(classroom->get_id()/6)%3] << classroom->get_id()%6 << std::endl;
}

Student::~Student()  {
    std::cout << "A Student to be destroyed: " << name << ". He currently is ";
    switch (location)
    {
    case 0 :
        std::cout << "at the school's entrance\n";
        break;
    case 1 :
        std::cout << "in the yard\n";
        break;
    case 2 :
        std::cout << "at the stairs\n";
        break;
    case 3 :
        std::cout << "on the corridor of floor "<< pseudo_hash::floor[(this->classroom->get_id()/6)%3] << std::endl;
        break;
    case 4 :
        std::cout << "inside his classroom\n";
        break;
    default:
        break;
    }
}

void Student::set_location_to(short i)  {
    location=i;
}

short Student::get_classroom_id()  {
    return this->classroom->get_id();
}

std::string Student::get_name()  {
    return name;
}



