#include <iostream>
#include "student_sequences.h"
#include <cmath>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

bool complex_maths(int type1,int type2,int rem1,int rem2,int limit)  {
    bool success_flag1=((type1!=type2 && (rem1+rem2)==0) || (type1==type2));
    bool success_flag2=((rem1+rem2)<=limit);
    return success_flag1 && success_flag2;

}

void School::Set_availability_to_open()  {
    for (int i=0;i<number_of_sequences;i++)  {
        arrangements[i]->set_availability_to(true);
    }
}

Student_Pair* School::pick_random(Student_Pair* original_pair,int sequence_id,bool same_class,bool vvip_scenario,bool gender_of_pair)  {
    int choices[arrangements[sequence_id]->get_pair_position()];
    int posible_choices=0;
    Student_Pair* pair;
    if (same_class)  {
        for (int i=0;i<arrangements[sequence_id]->get_pair_position();i++)  {
            if (arrangements[sequence_id]->get_nth_pair(i)!=original_pair)  {
                if ((gender_of_pair && arrangements[sequence_id]->get_nth_pair(i)->get_situation()!=1)||(!gender_of_pair &&arrangements[sequence_id]->get_nth_pair(i)->get_situation()!=2))  {
                    choices[posible_choices]=i;
                    posible_choices++;
                }
            }
        }
        int pick=choices[rand()%posible_choices];
        pair=arrangements[sequence_id]->get_nth_pair(pick);
    }
    else  {
        for (int i=0;i<number_of_sequences;i++)  {
            if ((sequence_id+i+1)%number_of_sequences!=sequence_id)  {
                if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_availbility())  {
                    for (int j=0;j<arrangements[(sequence_id+i+1)%number_of_sequences]->get_pair_position();j++)  {
                        if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(j)->get_importance()!=1)  {
                            choices[posible_choices]=i;
                            posible_choices++;
                        }#include <iostream>
#include "student_sequences.h"
#include <cmath>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

bool complex_maths(int type1,int type2,int rem1,int rem2,int limit)  {
    bool success_flag1=((type1!=type2 && (rem1+rem2)==0) || (type1==type2));
    bool success_flag2=((rem1+rem2)<=limit);
    return success_flag1 && success_flag2;

}

void School::Set_availability_to_open()  {
    for (int i=0;i<number_of_sequences;i++)  {
        arrangements[i]->set_availability_to(true);
    }
}

Student_Pair* School::pick_random(Student_Pair* original_pair,int sequence_id,bool same_class,bool vvip_scenario,bool gender_of_pair)  {
    int choices[arrangements[sequence_id]->get_pair_position()];
    int posible_choices=0;
    Student_Pair* pair;
    if (same_class)  {
        for (int i=0;i<arrangements[sequence_id]->get_pair_position();i++)  {
            if (arrangements[sequence_id]->get_nth_pair(i)!=original_pair)  {
                if ((gender_of_pair && arrangements[sequence_id]->get_nth_pair(i)->get_situation()!=1)||(!gender_of_pair &&arrangements[sequence_id]->get_nth_pair(i)->get_situation()!=2))  {
                    choices[posible_choices]=i;
                    posible_choices++;
                }
            }
        }
        int pick=choices[rand()%posible_choices];
        pair=arrangements[sequence_id]->get_nth_pair(pick);
    }
    else  {
        for (int i=0;i<number_of_sequences;i++)  {
            if ((sequence_id+i+1)%number_of_sequences!=sequence_id)  {
                if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_availbility())  {
                    for (int j=0;j<arrangements[(sequence_id+i+1)%number_of_sequences]->get_pair_position();j++)  {
                        if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(j)->get_importance()!=1)  {
                            choices[posible_choices]=i;
                            posible_choices++;
                        }
                    int pick=choices[rand()%posible_choices];
                    pair=arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(pick);
                    }
                    if (vvip_scenario)  {
                        arrangements[(sequence_id+i+1)%number_of_sequences]->set_availability_to(false);
                    }
                    break;
                }
            }
        }
    }
    return pair;
}

School::School(const std::string* boys,const std::string* girls,int size_boys,int size_girls,int number_of_sequences,int mess_limit,int quiet_limit) : number_of_sequences(number_of_sequences) {
    arrangements=new Sequence*[number_of_sequences];
    class_sequence_begin=new int[number_of_sequences];
    int registered_girls=0;
    int registered_boys=0;
    int remainder_boys=size_boys%number_of_sequences;
    int remainder_girls=size_girls%number_of_sequences;
    int number_of_students=size_boys+size_girls;
    int boys_to_girls_difference=size_boys-size_girls;
    if (!complex_maths(size_boys/number_of_sequences,size_girls/number_of_sequences,remainder_boys,remainder_girls,number_of_sequences))  {
        std::cout<< "----Wrong ratio of boys and girls----" << std::endl;
        throw ;
    }
    if (boys_to_girls_difference>0)  {
        large_sequence=new Sequence(size_girls+boys_to_girls_difference);
    }
    else if (boys_to_girls_difference<=0)  {
        large_sequence=new Sequence(size_boys-boys_to_girls_difference);
    }
    int min_size;
    if(size_girls>size_boys)  {
        min_size=size_boys;
    }
    else  {
        min_size=size_boys;
    }
    for (int i=0;i<number_of_sequences;i++)  { 
        if (remainder_boys>0)  {
            arrangements[i]=new Sequence(boys+registered_boys,girls+registered_girls,min_size,2,mess_limit,quiet_limit,i);
            registered_girls=registered_girls+min_size;
            registered_boys=registered_boys+min_size+1;
            remainder_boys--;
        }
        else if (remainder_girls>0)  {
            arrangements[i]=new Sequence(boys+registered_boys,girls+registered_girls,min_size,1,mess_limit,quiet_limit,i);
            registered_girls=registered_girls+min_size+1;
            registered_boys=registered_boys+min_size;
            remainder_girls--;
        }
        else  {
            arrangements[i]=new Sequence(boys+registered_boys,girls+registered_girls,(size_boys+size_girls)/number_of_sequences,0,mess_limit,quiet_limit,i);
            registered_girls=registered_girls+(size_boys+size_girls)/number_of_sequences;
            registered_boys=registered_boys+(size_boys+size_girls)/number_of_sequences;
        }
    }
}

School::~School()  {
    for (int i=0;i<number_of_sequences;i++)  {
        delete arrangements[i];
    }
    delete[] arrangements;
    delete[] large_sequence;
}

void School::swap(int id,Student_Pair* pair,short mode,bool gender,bool vvip_scenario)  {
    Student_Pair* other_pair;
    if (mode==0)  {
        other_pair=pick_random(pair,id,true,false,gender);
        arrangements[id]->switch_member_of_pair(pair,other_pair,0,gender);  
    }
    else if (mode==1)  {
        other_pair=pick_random(pair,id,true,false,false);
        arrangements[id]->switch_member_of_pair(pair,other_pair,1,0);
    }
    else  {
        other_pair=pick_random(pair,id,false,true,false);
        arrangements[id]->switch_member_of_pair(pair,other_pair,1,0);
    }
}

void School::print_arrangements_per_classroom()  {
    for (int i=0;i<number_of_sequences;i++)  {
        std::cout << "Classroom " << i+1 << " arrangement:\n";
        arrangements[i]->print();
    }
    std::cout << std::endl;
}

void School::print_unified_arrangement()  {
    std::cout << "Arrangement of all arrangements is: \n";
    large_sequence->print();
    std::cout << std::endl;
}

void School::create_unified_sequence()  {
    int liability[number_of_sequences];
    int liability_count=0;
    int last_lonely_pair;
    for (int i=0;i<number_of_sequences;i++)  {
        int j;
        class_sequence_begin[i]=large_sequence->get_pair_position();
        for (j=0;(j<arrangements[i]->count_girls()) && (j<arrangements[i]->count_boys());j++)  {
            large_sequence->copy_pair(arrangements[i]->get_nth_pair(j));
        }
        if (arrangements[i]->count_girls()!=arrangements[i]->count_boys())  {
            last_lonely_pair=arrangements[i]->count_students()/2;
            if (arrangements[i]->get_nth_pair(last_lonely_pair)->get_situation()==2)  {
                bool success=false;
                for (int k=0;k<liability_count;k++)  {
                    if (liability[k]!=-1 && large_sequence->get_nth_pair(liability[k])->get_situation()==1)  {
                        large_sequence->get_nth_pair(liability[k])->complete_pair(arrangements[i]->get_nth_pair(last_lonely_pair),false);
                        arrangements[i]->send_to_oblivion(arrangements[i]->get_nth_pair(last_lonely_pair));
                        liability[k]=-1;
                        success=true;
                        break;
                    }
                }
                if (!success)  {
                    large_sequence->copy_pair(arrangements[i]->get_nth_pair(j));
                    liability[liability_count]=large_sequence->get_pair_position()-1;
                    liability_count++;
                }
            }
            else if (arrangements[i]->get_nth_pair(last_lonely_pair)->get_situation()==1)  {
                bool success=false;
                for (int k=0;k<liability_count;k++)  {
                    if (liability[k]!=-1 && large_sequence->get_nth_pair(liability[k])->get_situation()==2)  {
                        large_sequence->get_nth_pair(liability[k])->complete_pair(arrangements[i]->get_nth_pair(last_lonely_pair),true);
                        arrangements[i]->send_to_oblivion(arrangements[i]->get_nth_pair(last_lonely_pair));
                        liability[k]=-1;
                        success=true;
                        break;
                    }
                }
                if (!success)  {
                    large_sequence->copy_pair(arrangements[i]->get_nth_pair(j));
                    liability[liability_count]=large_sequence->get_pair_position()-1;
                    liability_count++;
                }
            }
            else  {
                std::cout << "Error" << std::endl;
                throw ;
            }
            
        
        }
    }
}

void School::behave(int L)  {
    srand(time(NULL));
    int naughty_students;
    bool double_mess=0;
    int limit=large_sequence->get_pair_position();
    for (int i=0;i<L;i++)  {
        naughty_students=rand()%(limit);
        int baddest[naughty_students];
        int bad_pairs=0;
        for (int j=0;j<naughty_students;j++)  {
            int pick=rand()%limit;
            while (true)  {
                if (large_sequence->get_nth_pair(pick%limit)->bad_pair()!=0)  {
                    pick++;
                }
                else  {
                    double_mess=large_sequence->get_nth_pair(pick%limit)->cause_trouble();
                    baddest[bad_pairs]=pick%limit;
                    bad_pairs++;
                    if (double_mess)  {
                        naughty_students--;
                    }
                }
            }
            
        }
        for (int j=0;j<number_of_sequences;j++)  {

        } 
        
    }

}

int Sequence::get_pair_position()  {
    return pairs_count;
}




/*

Classroom::Classroom(int id,int min_size,int mess_limit,int quiet_limit) : number_of_boys(0), number_of_girls(0), id(id)  {
    boys=new Student*[min_size/2+1];
    girls=new Student*[min_size/2+1];
    sequence=new Sequence(min_size+1,mess_limit,quiet_limit,this);
}

Classroom::~Classroom()  {
    for (int i=0;i<number_of_boys;i++)  {
        delete boys[i];
    }
    delete[] boys;
    for (int i=0;i<number_of_girls;i++)  {
        delete girls[i];
    }
    delete[] girls;
    delete sequence;
}

void Classroom::register_student(std::string name,bool gender,int class_id)  {
    if (gender)  {
        girls[number_of_girls]=new Student(name,gender,class_id);
        number_of_girls++;
    }
    else  {
        boys[number_of_boys]=new Student(name,gender,class_id);
        number_of_boys++;
    }
}

int Classroom::count_boys()  {
    return number_of_boys;
}

int Classroom::count_girls()  {
    return number_of_girls;
}

int Classroom::count_students()  {
    return number_of_boys+number_of_girls;
}

void Classroom::create_arrangement()  {
    for (int i=0;i<number_of_girls && i<number_of_boys;i++)  {
        sequence->add_to_arrangement(girls[i],boys[i]);
    }
    if (number_of_girls>number_of_boys)  {
        sequence->add_to_arrangement(girls[number_of_girls-1],NULL);
    }
    else if (number_of_girls<number_of_boys)  {
        sequence->add_to_arrangement(NULL,boys[number_of_boys-1]);
    }
}

Sequence* Classroom::get_arrangement()  {
    return sequence;
}
*/

Student::Student(std::string name,bool gender,Sequence* sequence) : gender(gender), sequence(sequence), mischievous(false)  {
    this->name.assign(name);
}

Sequence* Student::get_sequence()  {
    return sequence;
}

void Student::repent()  {
    mischievous=false;
}

bool Student::get_gender()  {
    return gender;
}

std::string Student::get_name()  {
    return name;
}


Student_Pair::Student_Pair(Student* Girl,Student* Boy) : situation(0), vvip(0), double_penalty(0) {
    if (Girl!=NULL)  {
        situation++;
    }
    if (Boy!=NULL)  {
        situation=situation+2;
    }
    this->Girl=Girl;
    this->Boy=Boy;
}

void Student_Pair::pay_and_repent(bool both_members,bool gender)  {
    if (both_members)  {
        Boy->get_sequence()->increase_degree_of_disorder(Boy->is_michievous()*(double_penalty+1));
        Girl->get_sequence()->increase_degree_of_disorder(Girl->is_michievous()*(double_penalty+1));
        Boy->repent();
        Girl->repent();
    }
    else  {
        if (gender)  {
            Girl->get_sequence()->increase_degree_of_disorder(Girl->is_michievous());
            Girl->repent();
        }
        else  {
            Boy->get_sequence()->increase_degree_of_disorder(Boy->is_michievous());
            Boy->repent();
        }
        double_penalty=0;
        vvip=0;
    }
}

short Student_Pair::bad_pair()  {
    return 2*Boy->is_michievous()+Girl->is_michievous();
}

std::string Student_Pair::get_name_of_boy()  {
    return Boy->get_name();
}

std::string Student_Pair::get_name_of_girl()  {
    return Girl->get_name();
}

short Student_Pair::get_situation()  {
    return situation;
}

void Student_Pair::complete_pair(Student_Pair* other_half,bool gender)  {
    if (gender)  {
        this->Girl=other_half->Girl;
    }
    else  {
        this->Boy=other_half->Boy;
    }
    situation=3;  
}

void Student_Pair::replace_member(Student* student,bool gender)  {
    if (gender)  {
        this->Girl=student;
    }
    else  {
        this->Boy=student;
    }
}

Student* Student_Pair::get_member(bool gender)  {
    if (gender)  {
        return Girl;
    }
    else  {
        return Boy;
    }
}

bool Student_Pair::cause_trouble()  {
    short pick=rand()%3;
    if (pick==0)  {
        Girl->causes_noise();
        return false;
    }
    else if (pick==1)  {
        Boy->causes_noise();
        return false;
    }
    else  {
        Boy->causes_noise();
        Girl->causes_noise();
        return true;
    }
}


/*Student_Pair::Student_Pair(const Student_Pair& pair)  {
    this->Boy=pair.Boy;
    this->Girl=pair.Girl;
    this->situation=pair.situation;
}*/

void Sequence::send_to_oblivion(Student_Pair* pair)  {
    pairs_count--; // will only occur on the last pair of a classroom
    delete pair;
}

bool Sequence::get_availability()  {
    return available;
}

void Sequence::set_availability_to(bool status)  {
    available=status;
}

Sequence::Sequence(const std::string* boys,const std::string* girls,int min_size,int mode,int mess_limit,int quiet_limit,short id) : pairs_count(0), available(true), degree_of_disorder(0), quiet_limit(quiet_limit), mess_limit(mess_limit) {
    pairs=new Student_Pair*[min_size+(mode!=0)];
    int i;
    for (i=0;i<min_size;i++)  {
        Student* Boy=new Student(boys[i],0,this);
        Student* Girl=new Student(girls[i],1,this);
        pairs[i]=new Student_Pair(Girl,Boy);
        pairs_count++;
    }
    if (mode==1)  {
        Student* Girl=new Student(girls[i],1,this);
        pairs[i]=new Student_Pair(Girl,NULL);
        pairs_count++;
    }
    else if (mode==2)  {
        Student* Boy=new Student(boys[i],0,this);
        pairs[i]=new Student_Pair(Boy,NULL);
        pairs_count++;
    }
}

Sequence::~Sequence()  {
    for (int i=0;i<pairs_count;i++)  {
        delete pairs[i];
    }
    delete[] pairs;
}
/*
void Sequence::add_to_arrangement(Student* Girl,Student* Boy)  {
    pairs[pairs_count]=new Student_Pair(Girl,Boy);
    pairs_count++;
}
*/

void Sequence::switch_member_of_pair(Student_Pair* pair1,Student_Pair* pair2,bool full_switch,bool gender)  {
    if (full_switch)  {
        pair1->pay_and_repent(1,0);
        pair2->pay_and_repent(1,0);
        Student* temp_boy=pair2->get_member(0);
        Student* temp_girl=pair2->get_member(1);
        pair2->replace_member(pair1->get_member(1),1);
        pair2->replace_member(pair1->get_member(0),0);
        pair1->replace_member(temp_girl,1);
        pair1->replace_member(temp_boy,0);
    }
    else if (gender) {
        pair1->pay_and_repent(0,1);
        pair2->pay_and_repent(0,1);
        Student* temp_girl=pair2->get_member(1);
        pair2->replace_member(pair1->get_member(1),1);
        pair1->replace_member(temp_girl,1);
    }
    else  {
        pair1->pay_and_repent(0,0);
        pair2->pay_and_repent(0,0);
        Student* temp_boy=pair2->get_member(0);
        pair2->replace_member(pair1->get_member(0),0);
        pair1->replace_member(temp_boy,0);
    }
}

void Sequence::print()  {
    bool flip=true;
    int size=7;
    for (int i=0;i<pairs_count;i++)  {
        if (flip)  {
            if (pairs[i]->get_situation()!=1)  {
                printf("%*s",size,pairs[i]->get_name_of_boy().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=false;
        }
        else  {
            if (pairs[i]->get_situation()!=2)  {
                printf("%*s",size,pairs[i]->get_name_of_girl().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=true;
        }
    }
    std::cout << std::endl;
    flip=true;
    size=7;
    for (int i=0;i<pairs_count;i++)  {
        if (flip)  {
            if (pairs[i]->get_situation()!=2)  {
                printf("%*s",size,pairs[i]->get_name_of_girl().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=false;
        }
        else  {
            if (pairs[i]->get_situation()!=1)  {
                printf("%*s",size,pairs[i]->get_name_of_boy().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=true;
        }
    }
    std::cout << std::endl;

}

void Sequence::copy_pair(Student_Pair* pair)  {
    pairs[pairs_count]=pair;
    pairs_count++;
} 

void Sequence::increase_degree_of_disorder(int n)  {
    degree_of_disorder=degree_of_disorder+n;
}

Student_Pair* Sequence::get_nth_pair(int n)  {
    return pairs[n];
}

                    int pick=choices[rand()%posible_choices];
                    pair=arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(pick);
                    }
                    if (vvip_scenario)  {
                        arrangements[(sequence_id+i+1)%number_of_sequences]->set_availability_to(false);
                    }
                    break;
                }
            }
        }
    }
    return pair;
}

/*School::School(const std::string* boys,const std::string* girls,int size_boys,int size_girls,int number_of_sequences,int mess_limit,int quiet_limit) : number_of_sequences(number_of_sequences) {
    arrangements=new Sequence*[number_of_sequences];
    class_sequence_begin=new int[number_of_sequences];
    int registered_girls=0;
    int registered_boys=0;
    int remainder_boys=size_boys%number_of_sequences;
    int remainder_girls=size_girls%number_of_sequences;
    int number_of_students=size_boys+size_girls;
    int boys_to_girls_difference=size_boys-size_girls;
    if (!complex_maths(size_boys/number_of_sequences,size_girls/number_of_sequences,remainder_boys,remainder_girls,number_of_sequences))  {
        std::cout<< "----Wrong ratio of boys and girls----" << std::endl;
        throw ;
    }
    if (boys_to_girls_difference>0)  {
        large_sequence=new Sequence(size_girls+boys_to_girls_difference);
    }
    else if (boys_to_girls_difference<=0)  {
        large_sequence=new Sequence(size_boys-boys_to_girls_difference);
    }
    for (int i=0;i<number_of_sequences;i++)  { 
        arrangements[i]=new Sequence(boys,girls,registered_boys,registered_girls,size_boys,number_of_sequences,mess_limit,quiet_limit,i);
    }
}*/

School::~School()  {
    for (int i=0;i<number_of_sequences;i++)  {
        delete arrangements[i];
    }
    delete[] arrangements;
    delete[] large_sequence;
}

void School::swap(int id,Student_Pair* pair,short mode,bool gender)  {
    if (mode==0)  {
        arrangements[id]->switch_member_of_pair(pair,pick_random(pair,id,true,false,gender),0,gender);  
    }
    else if (mode==1)  {
        arrangements[id]->switch_member_of_pair(pair,pick_random(pair,id,true,ue,false,gender),1,gender);
    }
    else  {

    }
}

void School::print_arrangements_per_classroom()  {
    for (int i=0;i<number_of_sequences;i++)  {
        std::cout << "Classroom " << i+1 << " arrangement:\n";
        arrangements[i]->print();
    }
    std::cout << std::endl;
}

void School::print_unified_arrangement()  {
    std::cout << "Arrangement of all arrangements is: \n";
    large_sequence->print();
    std::cout << std::endl;
}

void School::create_unified_sequence()  {
    int liability[number_of_sequences];
    int liability_count=0;
    int last_lonely_pair;
    for (int i=0;i<number_of_sequences;i++)  {
        int j;
        class_sequence_begin[i]=large_sequence->get_pair_position();
        for (j=0;(j<arrangements[i]->count_girls()) && (j<arrangements[i]->count_boys());j++)  {
            large_sequence->copy_pair(arrangements[i]->get_nth_pair(j));
        }
        if (arrangements[i]->count_girls()!=arrangements[i]->count_boys())  {
            last_lonely_pair=arrangements[i]->count_students()/2;
            if (arrangements[i]->get_nth_pair(last_lonely_pair)->get_situation()==2)  {
                bool success=false;
                for (int k=0;k<liability_count;k++)  {
                    if (liability[k]!=-1 && large_sequence->get_nth_pair(liability[k])->get_situation()==1)  {
                        large_sequence->get_nth_pair(liability[k])->complete_pair(arrangements[i]->get_nth_pair(last_lonely_pair),false);
                        arrangements[i]->send_to_oblivion(arrangements[i]->get_nth_pair(last_lonely_pair));
                        liability[k]=-1;
                        success=true;
                        break;
                    }
                }
                if (!success)  {
                    large_sequence->copy_pair(arrangements[i]->get_nth_pair(j));
                    liability[liability_count]=large_sequence->get_pair_position()-1;
                    liability_count++;
                }
            }
            else if (arrangements[i]->get_nth_pair(last_lonely_pair)->get_situation()==1)  {
                bool success=false;
                for (int k=0;k<liability_count;k++)  {
                    if (liability[k]!=-1 && large_sequence->get_nth_pair(liability[k])->get_situation()==2)  {
                        large_sequence->get_nth_pair(liability[k])->complete_pair(arrangements[i]->get_nth_pair(last_lonely_pair),true);
                        arrangements[i]->send_to_oblivion(arrangements[i]->get_nth_pair(last_lonely_pair));
                        liability[k]=-1;
                        success=true;
                        break;
                    }
                }
                if (!success)  {
                    large_sequence->copy_pair(arrangements[i]->get_nth_pair(j));
                    liability[liability_count]=large_sequence->get_pair_position()-1;
                    liability_count++;
                }
            }
            else  {
                std::cout << "Error" << std::endl;
                throw ;
            }
            
        
        }
    }
}

void School::behave(int L)  {
    srand(time(NULL));
    int naughty_students;
    bool double_mess=0;
    int limit=large_sequence->get_pair_position();
    for (int i=0;i<L;i++)  {
        naughty_students=rand()%(limit);
        int baddest[naughty_students];
        int bad_pairs=0;
        for (int j=0;j<naughty_students;j++)  {
            int pick=rand()%limit;
            while (true)  {
                if (large_sequence->get_nth_pair(pick%limit)->bad_pair()!=0)  {
                    pick++;
                }
                else  {
                    double_mess=large_sequence->get_nth_pair(pick%limit)->cause_trouble();
                    baddest[bad_pairs]=pick%limit;
                    bad_pairs++;
                    if (double_mess)  {
                        naughty_students--;
                    }
                }
            }
            
        }
        for (int j=0;j<number_of_sequences;j++)  {

        } 
        
    }

}

int Sequence::get_pair_position()  {
    return pairs_count;
}





Classroom::Classroom(int id,int min_size,int mess_limit,int quiet_limit) : number_of_boys(0), number_of_girls(0), id(id)  {
    boys=new Student*[min_size/2+1];
    girls=new Student*[min_size/2+1];
    sequence=new Sequence(min_size+1,mess_limit,quiet_limit,this);
}

Classroom::~Classroom()  {
    for (int i=0;i<number_of_boys;i++)  {
        delete boys[i];
    }
    delete[] boys;
    for (int i=0;i<number_of_girls;i++)  {
        delete girls[i];
    }
    delete[] girls;
    delete sequence;
}

void Classroom::register_student(std::string name,bool gender,int class_id)  {
    if (gender)  {
        girls[number_of_girls]=new Student(name,gender,class_id);
        number_of_girls++;
    }
    else  {
        boys[number_of_boys]=new Student(name,gender,class_id);
        number_of_boys++;
    }
}

int Classroom::count_boys()  {
    return number_of_boys;
}

int Classroom::count_girls()  {
    return number_of_girls;
}

int Classroom::count_students()  {
    return number_of_boys+number_of_girls;
}

void Classroom::create_arrangement()  {
    for (int i=0;i<number_of_girls && i<number_of_boys;i++)  {
        sequence->add_to_arrangement(girls[i],boys[i]);
    }
    if (number_of_girls>number_of_boys)  {
        sequence->add_to_arrangement(girls[number_of_girls-1],NULL);
    }
    else if (number_of_girls<number_of_boys)  {
        sequence->add_to_arrangement(NULL,boys[number_of_boys-1]);
    }
}

Sequence* Classroom::get_arrangement()  {
    return sequence;
}

Student::Student(std::string name,bool gender,int class_id) : gender(gender), class_id(class_id), mischievous(false)  {
    this->name.assign(name);
}

void Student::repent()  {
    mischievous=false;
}

bool Student::get_gender()  {
    return gender;
}

std::string Student::get_name()  {
    return name;
}


Student_Pair::Student_Pair(Student* Girl,Student* Boy) : situation(0) {
    if (Girl!=NULL)  {
        situation++;
    }
    if (Boy!=NULL)  {
        situation=situation+2;
    }
    this->Girl=Girl;
    this->Boy=Boy;
}

short Student_Pair::bad_pair()  {
    return 2*Boy->is_michievous()+Girl->is_michievous();
}

std::string Student_Pair::get_name_of_boy()  {
    return Boy->get_name();
}

std::string Student_Pair::get_name_of_girl()  {
    return Girl->get_name();
}

short Student_Pair::get_situation()  {
    return situation;
}

void Student_Pair::complete_pair(Student_Pair* other_half,bool gender)  {
    if (gender)  {
        this->Girl=other_half->Girl;
    }
    else  {
        this->Boy=other_half->Boy;
    }
    situation=3;  
}

void Student_Pair::replace_member(Student* student,bool gender)  {
    if (gender)  {
        this->Girl=student;
    }
    else  {
        this->Boy=student;
    }
}

Student* Student_Pair::get_member(bool gender)  {
    if (gender)  {
        return Girl;
    }
    else  {
        return Boy;
    }
}

bool Student_Pair::cause_trouble()  {
    short pick=rand()%3;
    if (pick==0)  {
        Girl->causes_noise();
        return false;
    }
    else if (pick==1)  {
        Boy->causes_noise();
        return false;
    }
    else  {
        Boy->causes_noise();
        Girl->causes_noise();
        return true;
    }
}


/*Student_Pair::Student_Pair(const Student_Pair& pair)  {
    this->Boy=pair.Boy;
    this->Girl=pair.Girl;
    this->situation=pair.situation;
}*/

void Sequence::send_to_oblivion(Student_Pair* pair)  {
    pairs_count--; // will only occur on the last pair of a classroom
    delete pair;
}

bool Sequence::get_availability()  {
    return available;
}

void Sequence::set_availability_to(bool status)  {
    available=status;
}

/*Sequence::Sequence(const std::string* boys,const std::string* girls,int &registered_boys,int &registered_girls,int number_of_sequences,int mess_limit,int quiet_limit,short id) : pairs_count(0), degree_of_disorder(0), quiet_limit(quiet_limit), mess_limit(mess_limit) {
    for (int j=0;j<size_girls/number_of_sequences;j++)  {
        arrangements[i]->register_student(boys[registered_boys]l,false,i);
        arrangements[i]->register_student(girls[registered_girls],true,i);
        registered_girls++;
        registered_boys++;
    }
    if (remainder_girls>0)  {
        arrangements[i]->register_student(girls[registered_girls],true,i);
        registered_girls++;
        remainder_girls--;
    }
    else if (remainder_boys>0)  {
        arrangements[i]->register_student(boys[registered_boys],false,i);
        registered_boys++;
        remainder_boys--;
    }
}

Sequence::~Sequence()  {
    for (int i=0;i<pairs_count;i++)  {
        delete pairs[i];
    }
    delete[] pairs;
}

void Sequence::add_to_arrangement(Student* Girl,Student* Boy)  {
    pairs[pairs_count]=new Student_Pair(Girl,Boy);
    pairs_count++;
}*/


void Sequence::switch_member_of_pair(Student_Pair* pair1,Student_Pair* pair2,bool full_switch,bool gender)  {
    if (full_switch)  {
        pair1->pay_and_repent(1,0);
        pair2->pay_and_repent(pair2,1,0);
        Student* temp_boy=pair2->get_member(0);
        Student* temp_girl=pair2->get_member(1);
        pair2->replace_member(pair1->get_member(1),1);
        pair2->replace_member(pair1->get_member(0),0);
        pair1->replace_member(temp_girl,1);
        pair1->replace_member(temp_boy,0);
    }
    else if (gender) {
        pair1->pay_and_repent(0,1);
        pair2->pay_and_repent(0,1);
        Student* temp_girl=pair2->get_member(1);
        pair2->replace_member(pair1->get_member(1),1);
        pair1->replace_member(temp_girl,1);
    }
    else  {
        pair1->pay_and_repent(0,0);
        pair2->pay_and_repent(0,0);
        Student* temp_boy=pair2->get_member(0);
        pair2->replace_member(pair1->get_member(0),0);
        pair1->replace_member(temp_boy,0);
    }
}

void Sequence::print()  {
    bool flip=true;
    int size=7;
    for (int i=0;i<pairs_count;i++)  {
        if (flip)  {
            if (pairs[i]->get_situation()!=1)  {
                printf("%*s",size,pairs[i]->get_name_of_boy().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=false;
        }
        else  {
            if (pairs[i]->get_situation()!=2)  {
                printf("%*s",size,pairs[i]->get_name_of_girl().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=true;
        }
    }
    std::cout << std::endl;
    flip=true;
    size=7;
    for (int i=0;i<pairs_count;i++)  {
        if (flip)  {
            if (pairs[i]->get_situation()!=2)  {
                printf("%*s",size,pairs[i]->get_name_of_girl().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=false;
        }
        else  {
            if (pairs[i]->get_situation()!=1)  {
                printf("%*s",size,pairs[i]->get_name_of_boy().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); 
            }
            flip=true;
        }
    }
    std::cout << std::endl;

}

void Sequence::copy_pair(Student_Pair* pair)  {
    pairs[pairs_count]=pair;//new Student_Pair(*pair);
    pairs_count++;
} 

Student_Pair* Sequence::get_nth_pair(int n)  {
    return pairs[n];
}
