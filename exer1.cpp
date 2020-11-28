#include "school_facilities.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace pseudo_hash  {
    std::string matrix[]={"school entrance","yard","stairs","corridor"}; //a way to minimize space used by each Student object 
    char floor[]={'A','B','C'};//a one on one representation for floors using the alphabet
};


void Classroom::assign_teacher(std::string name)  {
    this->teacher.assign(name);
}

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

Classroom::Classroom(int capacity,short id)  : entry_possible(true), population(0), capacity(capacity), id(id) {
    std::cout << "A classroom has been created" << std::endl;
    students=new Student*[capacity]; //space to store students that enter the classroom
}

Classroom::~Classroom()  {
    std::cout << "A classroom has been destroyed" << std::endl;
    delete[] students;//delete only the array where the pointers are stored, not the pointes themselves
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
    students[population]=student;//store the pointer of the student that entered
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
    return students[population-1]->get_classroom_id();//we only care for the last student of the classroom, as we are stimualting a priority queue structure of storing data
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
    return students[--population];//we return the last student and reduce the counter for the population
}

Student* Corridor::forced_exit(short id)  {
    for (int i=0;i<population;i++)  {//since we are usign a priotirty queue, if the last student can't exit, then neither can the rest
        if ((students[i]->get_classroom_id()%6)==id)  {//but in the case of the last wave of students, we want those that are in the cor
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
        delete students[i]; //given that we keep all the pointers in the School class, it is easier to delete all the student objects through the array and not in the destructor of each space
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
    teachers[t_count]=new Teacher(name,floors[t_count/6]->get_class(t_count%6));//since teaching personel will only go up to 18, using division by 6 allows us to separate them into 3 floors,
    t_count++; //while which each modulus by 6, we can split those that entered the floor into 6 classrooms 
    //this way we assign all the teachers to one floor and then move onto the next floor to assign the rest
}

void SchoolBuilding::register_student(std::string name)  {
    if (s_count>18*floors[0]->get_class(0)->get_capacity())  {
        std::cout << "Building's Facilities Can Not Accomodate More Students" << std::endl;
        return ;
    }//in this case, students don't have a limit, and therefore we need to also make sure that the floor numbers don't exceed 3.
    students[s_count]=new Student(name,floors[(s_count/6)%3]->get_class(s_count%6));//like the teachers, we assign (number_of_classrooms) students to each floor and then move onto the next
    s_count++;//with the difference that we will repeat this over and over again
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
    short kill_switch=0;//given that we repeat this process until all students have entered, there is a chance an obstacle appears and no student can advance  into the school
    int number_of_wave=0;
    srand(time(NULL));
    while (advanced_count<s_count && kill_switch!=3)  {//therefore we have placed a killswitch which will trigger when no one moves in three consecutive turns
        this->place_teacher(false);
        bool flag1=true,flag2=true,flag3=false;//flags that show if there was movement between each space
        int students_entering=rand()%((s_count-advanced_count)/4+1)+1;
        bool final_push= ((students_entering+advanced_count)>=s_count);//a flag that signifies that the last batch of students will enter, therefore they should ignore all restrictions about whether the space they are in is full or not
        int starting_count=advanced_count;//how many students are inside the school at each advancement
        number_of_wave++;
        std::cout <<"\n-> Wave "<< number_of_wave << ":\n"<<std::endl;
        while ((flag1+flag2+flag3)!=0)  {
            flag1=false;
            if ((advanced_count-starting_count)<students_entering)  {//if some of the students of the current wave have not entered the school
                int dt_count=advanced_count-starting_count;
                for (int i=0;i<students_entering-dt_count;i++)  {
                    if (yard->space_available())  {//see if there is space on the yard
                        yard->enter(students[advanced_count]);//and make them enter it
                        advanced_count++;
                        flag1=true;//signifies that there was movement between the school's entrance and the yard
                        kill_switch=0;//since an advancement was made, reset the kill switch
                    }
                }
                std::cout << std::endl;
            }
            flag2=false;
            if (!yard->space_available() ||  flag1==0)  {//try to advance if the current space is full or if there will be no more students coming from the yard(in this wave)
                int stop=yard->get_population();
                for (int i=0;i<stop;i++)  {
                    if (stairs->space_available())  {
                        stairs->enter(yard->exit());
                        flag2=true;//signifies that there was movement between the yard and the stairs
                        kill_switch=0;
                    }
                }
                std::cout << std::endl;
            }
            flag3=false;
            if ((!stairs->space_available())  ||  (flag1+flag2)==0)  {//try to advance if the current space is full or if there will be no more students coming from the yard and stairs
                int stop=stairs->get_population();
                for (int i=0;i<stop;i++)  {
                    short floor_choice=stairs->floor_distribution();//get the floor number of the student's classroom
                    if (floors[floor_choice]->space_available_in_corridor())  {
                        floors[floor_choice]->enter(stairs->exit());
                        flag3=true;//signifies that there was movement between the stairs and the corridor
                        kill_switch=0;
                    }
                }
            }
            if ((flag1+flag2+flag3)==0)  {
                for (int i=0;i<3;i++)  {
                    flag3=floors[i]->flush();//signals whether someone managed to move from a corridor to a classroom(same variable as movement from stairs ot floor, but it doesn't matter)
                }
            }
        }
        kill_switch++;
    }
    this->place_teacher(true);//if there are remaining teachers who have not entered, place them inside their classrooms
}

void SchoolBuilding::place_teacher(bool all)  {
    short pick=rand()%4;
    int repeat=1;
    if (pick!=1 || all)  {
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
        classrooms[i]=new Classroom(class_capacity,6*height+i);//id of each classroom needs to be able to show which floor the classroom belongs to, which now will be visible my dividing by 6
    }
}

Floor::~Floor()  {
    delete corridor;
    for (int i=0;i<6;i++)  {
        delete classrooms[i];
    }
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
    corridor->enter(student);//Enter the student inside the corridor
    if (!corridor->space_available())  {//and if the corridor has reached max capacity then try and enter the students inside their respective classrooms
        std::cout << std::endl;
        int stop=corridor->get_population();
        for (int i=0;i<stop;i++)  {
            int id=corridor->get_student_class_id()%6;//get the classroom id of each student that tries to enter 
            if (!classrooms[id]->teacher_inside())  {//and if there is no teacher inside the classroom
                classrooms[id]->enter(corridor->exit());//enter the student in the classroom
            }
        }
        std::cout << std::endl;
        
    }
}

bool Floor::flush()  {
        int stop=corridor->get_population();
        bool return_value=false;
        for (int i=0;i<stop;i++)  {
            for (short id=0;id<6;id++)  {
                if (!classrooms[id]->teacher_inside())  {
                    Student* temp;
                    if ((temp=corridor->forced_exit(id))!=NULL)  {//if we find that there is a student who can enter his classroom
                        classrooms[id]->enter(temp);//we enter him
                        return_value=true;//and return that there was movement between corridor and classroom
                    }
                }
            }
        }
        std::cout << std::endl;
        return return_value;
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
    return this->students[population-1]->get_classroom_id()/6;//we always "play" with the last student of a space
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



