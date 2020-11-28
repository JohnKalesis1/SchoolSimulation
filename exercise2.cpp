#include <iostream>
#include "student_sequences.h"
#include <cmath>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

bool complex_maths(int type1,int type2,int rem1,int rem2,int limit)  {
    bool success_flag1=((type1!=type2 && (rem1+rem2)==0) || (type1==type2)); //assert if populations of each genre can create a distribution that's acceptible to the exercise 
    bool success_flag2=((rem1+rem2)<=limit);
    return success_flag1 && success_flag2;

}

void School::Set_availability_to_open()  {  // Set all sequences to accesible for entry of consecutive pair
    for (int i=0;i<number_of_sequences;i++)  {
        arrangements[i]->set_availability_to(true);
    }
}

Student_Pair* School::pick_random(Student_Pair* original_pair,int sequence_id,bool same_class,bool vvip_scenario,bool full_switch,bool gender_of_pair)  {
    int choices[arrangements[sequence_id]->get_pair_position()+1]; //Pick a random pair out of some candidates from one sequence
    int posible_choices=0;                                         //this is plausible if for each valid candidate, we store his position in an array
    Student_Pair* pair;
    if (same_class)  {   //case of pickinh a pair from the same sequence
        for (int i=0;i<arrangements[sequence_id]->get_pair_position();i++)  {
            if (arrangements[sequence_id]->get_nth_pair(i)!=original_pair)  {
                if (full_switch && arrangements[sequence_id]->get_nth_pair(i)->get_situation()==3)  { //if the change that will occur is for both members of the pair, then we need to search for a complete pair 
                    choices[posible_choices]=i;
                    posible_choices++;
                }
                else if ((gender_of_pair && arrangements[sequence_id]->get_nth_pair(i)->get_situation()!=2)||(!gender_of_pair &&arrangements[sequence_id]->get_nth_pair(i)->get_situation()!=1) )  {
                    choices[posible_choices]=i; //else, if it's a girl, we require that the pair has a girl, or if it is a boy, we require that the pair has a boy
                    posible_choices++;
                }
            }
        }
        int pick=choices[rand()%posible_choices]; //random choice from possible candidates
        pair=arrangements[sequence_id]->get_nth_pair(pick);
        return pair;
    }
    else  { //searching for a pair in a different sequence
        for (int i=0;i<number_of_sequences;i++)  {
            if ((sequence_id+i+1)%number_of_sequences!=sequence_id)  { //we will look at the next sequence, until we reach all the way to the previous
                if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_availability())  {//This condition will only matter if we are examining a consecutive pair, so that we try and place the consecutive pairs in different sequences
                    for (int j=0;j<arrangements[(sequence_id+i+1)%number_of_sequences]->get_pair_position();j++)  {
                        if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(j)->get_importance()!=1 && arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(j)->get_situation()==3)  {
                            choices[posible_choices]=j;//The pair must not be a consecutive pair(that would mix up the proccess of placing them in different classrooms) and must be a complete pair
                            posible_choices++;
                        }
                    }
                    int pick=choices[rand()%posible_choices];
                    pair=arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(pick);
                    if (vvip_scenario)  {//if we just place a consecutive pair, we make sure that any other consecutive pair of the same arrangement of consecutives, will not be placed in the same sequence
                        arrangements[(sequence_id+i+1)%number_of_sequences]->set_availability_to(false);
                    }
                    return pair;
                }
            }
        }
    } //if we reach this far, it means that from an arrangement of consecutive pairs, no other classrooms are available to follow the rule, one-per-classroom, thus we allow for placing two pairs in same sequence, and so on... 
    Set_availability_to_open();
    for (int i=0;i<number_of_sequences;i++)  {//repeat of the above
        if ((sequence_id+i+1)%number_of_sequences!=sequence_id)  {
            if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_availability())  {
                for (int j=0;j<arrangements[(sequence_id+i+1)%number_of_sequences]->get_pair_position();j++)  {
                    if (arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(j)->get_importance()!=1 && arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(j)->get_situation()==3)  {
                        choices[posible_choices]=j;
                        posible_choices++;
                    }
                }
                int pick=choices[rand()%posible_choices];
                pair=arrangements[(sequence_id+i+1)%number_of_sequences]->get_nth_pair(pick);
                if (vvip_scenario)  {
                    arrangements[(sequence_id+i+1)%number_of_sequences]->set_availability_to(false);
                }
                return pair;
            }
        }
    }
}

School::School(const std::string* boys,const std::string* girls,int size_boys,int size_girls,int number_of_sequences,int mess_limit,int quiet_limit) : number_of_sequences(number_of_sequences) {
    arrangements=new Sequence*[number_of_sequences];
    int registered_girls=0;
    int registered_boys=0;
    int remainder_boys=size_boys%number_of_sequences;
    int remainder_girls=size_girls%number_of_sequences;
    if (remainder_boys==0 && size_boys/number_of_sequences==(size_girls/number_of_sequences+1))  {//special case if the populations are consecutive multiples of the number of sequences
        remainder_boys=number_of_sequences;  //thus we consider the (number of sequences) students as those that will be placed as an extra in each class
    }//For the ration of pipulations to be complete, the smallest number, MUST be a multiple of the number of sequences(Explained the reasons in the README)
    else if (remainder_girls==0 && size_girls/number_of_sequences==(size_boys/number_of_sequences+1))  {
        remainder_girls=number_of_sequences;
    }
    int number_of_students=size_boys+size_girls;
    int boys_to_girls_difference=size_boys-size_girls;
    if (!complex_maths(size_boys/number_of_sequences,size_girls/number_of_sequences,remainder_boys,remainder_girls,number_of_sequences))  {
        std::cout<< "----Wrong ratio of boys and girls----" << std::endl;
        throw ;
    }
    if (boys_to_girls_difference>0)  {
        large_sequence=new Sequence(size_boys);//create an empty sequence, which will be the arrangement of classrooms, with its max size being the number of the highest population
    }
    else if (boys_to_girls_difference<=0)  {
        large_sequence=new Sequence(size_girls);
    }
    int min_size;
    if(size_girls>size_boys)  { //minimum nubmer of pairs for each classroom(those will be complete pairs)
        min_size=size_boys/number_of_sequences;
    }
    else  {
        min_size=size_boys/number_of_sequences;
    }
    for (int i=0;i<number_of_sequences;i++)  { 
        if (remainder_boys>0)  { //place +1 boy as the lonely pair of the sequence 
            arrangements[i]=new Sequence(boys+registered_boys,girls+registered_girls,min_size,2,mess_limit,quiet_limit,i);
            registered_girls=registered_girls+min_size;//οι αυξησεις ειναι αναλογες με τους αριθμους μαθητων που μπηκαν στην αρχικη ακολουθια
            registered_boys=registered_boys+min_size+1;
            remainder_boys--;
        }
        else if (remainder_girls>0)  {//place +1 girl as the lonely pair of the sequence
            arrangements[i]=new Sequence(boys+registered_boys,girls+registered_girls,min_size,1,mess_limit,quiet_limit,i);
            registered_girls=registered_girls+min_size+1;
            registered_boys=registered_boys+min_size;
            remainder_girls--;
        }
        else  {//even number of boys and girls
            arrangements[i]=new Sequence(boys+registered_boys,girls+registered_girls,min_size,0,mess_limit,quiet_limit,i);
            registered_girls=registered_girls+min_size;
            registered_boys=registered_boys+min_size;
        }
    }
}

School::~School()  {
    for (int i=0;i<number_of_sequences;i++)  {
        delete arrangements[i];
    }
    delete[] arrangements;
    delete large_sequence;
}

void School::switch_member_of_pair(Student_Pair* pair1,Student_Pair* pair2,bool full_switch,bool gender)  {
    if (full_switch)  {
        pair1->pay_and_repent(1,0);  //charge the class of every naughty student of the pair with a penalty and remove the <naughty> statuw effect from them
        pair2->pay_and_repent(1,0);
        Student* temp_boy=pair2->get_member(0); //swap through the use of a temporary variable
        Student* temp_girl=pair2->get_member(1);
        pair2->replace_member(pair1->get_member(1),1);
        pair2->replace_member(pair1->get_member(0),0);
        pair1->replace_member(temp_girl,1);
        pair1->replace_member(temp_boy,0);
    }
    else if (gender) {  //charge only the classes of the girls
        pair1->pay_and_repent(0,1);
        pair2->pay_and_repent(0,1);
        Student* temp_girl=pair2->get_member(1);
        pair2->replace_member(pair1->get_member(1),1);
        pair1->replace_member(temp_girl,1);
    }
    else  {//charge only rhe classes of the boys
        pair1->pay_and_repent(0,0);
        pair2->pay_and_repent(0,0);
        Student* temp_boy=pair2->get_member(0);
        pair2->replace_member(pair1->get_member(0),0);
        pair1->replace_member(temp_boy,0);
    }
}

void School::swap(Student_Pair* pair,bool gender)  {
    Student_Pair* other_pair;
    std::cout << "-->";
    if (pair->get_mode_of_transfer()==0)  {//a swap will occur with a student of the same sequence
        std::cout << "Student makes noise ("<<pair->get_member(gender)->get_name() << "). Student's classroom will receive 1 point.";
        std::cout << " He will be switched with another student of the same sequence: ";
        other_pair=pick_random(pair,pair->get_sequence_id(),true,false,false,gender);//only the "gender" and the "same sequence" are important criteria for the search
        std::cout<<other_pair->get_member(gender)->get_name()<<std::endl;
        if (other_pair->bad_pair()!=0)  {//if the other student is also naughty, punish his classroom
            std::cout << "Second student also happens to make noise, his classroom will also receive 1 point.\n";
        }
        std::cout << "Initial Status:\n";
        pair->get_sequence_belonging()->print(); //print initial sequence
        switch_member_of_pair(pair,other_pair,0,gender);//swap and punish pairs
        std::cout << "Final Status:\n";
        pair->get_sequence_belonging()->print();//print final sequence
        std::cout<<std::endl;
    }
    else if (pair->get_mode_of_transfer()==1)  {//a swap will occur with a pair of the same sequence
        other_pair=pick_random(pair,pair->get_sequence_id(),true,false,true,false);//only the "complete pair" and the "same sequence" are important criteria for the search
        std::cout << "Students couple makes noise (" << pair->get_member(0)->get_name()<< " " <<pair->get_member(1)->get_name() << "). Their repsective classrooms will receive 1 point. ";
        std::cout << "They will be switched with the couple of the same sequence: ";
        std::cout << "(" <<other_pair->get_member(0)->get_name()<< " " <<other_pair->get_member(1)->get_name() << ")\n";
        if (other_pair->bad_pair()==3)  {//Print the the other pair will also be punished
            std::cout << "Second pair also happens to make noise, their repsective classrooms will also receive 1 point";
        }
        else if (other_pair->bad_pair()!=0) {
            std::cout << "A student of second pair also happens to make noise, his classroom will also receive 1 point";
        }
        std::cout << "Initial Status:\n";
        pair->get_sequence_belonging()->print();
        switch_member_of_pair(pair,other_pair,1,0);
        std::cout << "Final Status:\n";
        pair->get_sequence_belonging()->print();
        std::cout<<std::endl;
    }
    else  {//a swao will occur with a pair of another sequence
        other_pair=pick_random(pair,pair->get_sequence_id(),false,pair->get_importance(),true,false);//only the "complete pair" and the "different sequence" are important criteria for the search, with the vvip scenario extra functions being used if its used
        std::cout << "Students couple make a lot of noise (" << pair->get_member(0)->get_name()<< " " <<pair->get_member(1)->get_name() << "). Their repsective classrooms will receive 2 points. "; 
        std::cout <<"They will be switched with a couple of a separate sequence: ";
        std::cout << "(" <<other_pair->get_member(0)->get_name()<< " " <<other_pair->get_member(1)->get_name() << ")\n";
        if (other_pair->bad_pair()==3)  { 
            int point;
            if (other_pair->get_mode_of_transfer()==2)  { //if the other pair would also need to change sequence, then we punish it now
                point=2;
            }
            else  {
                point=1;
            }
            std::cout << "Second pair also happens to make noise, their repsective classrooms will receive "<< point <<" point";
            if (point==2)  {
                std::cout << "s\n";
            }
            else  {
                std::cout << '\n';
            }
        }
        else if (other_pair->bad_pair()!=0) {
            std::cout << "A student of second pair also happens to make noise, his classroom will also receive 1 point\n";
        }
        std::cout << "Initial Status:" << std::endl;
        pair->get_sequence_belonging()->print();
        switch_member_of_pair(pair,other_pair,1,0);
        std::cout << "Final Status:\n";
        pair->get_sequence_belonging()->print();
        std::cout<<std::endl;
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
    int liability[number_of_sequences];//an array for the positions of the lonely pairs, in case we find an opportunity to place them in another lonely pair of opposite gender
    int liability_count=0;
    int last_lonely_pair;
    for (int i=0;i<number_of_sequences;i++)  {
        int j;
        for (j=0;(j<arrangements[i]->count_girls()) && (j<arrangements[i]->count_boys());j++)  {
            large_sequence->copy_pair(arrangements[i]->get_nth_pair(j)); //copy(pass the pointer) of every complete pair to the large sequence
        }
        if (arrangements[i]->count_girls()!=arrangements[i]->count_boys())  {//if this arrangement has a lonely pair
            last_lonely_pair=arrangements[i]->count_students()/2;
            if (arrangements[i]->get_nth_pair(last_lonely_pair)->get_situation()==2)  { //if its a boy
                bool success=false;
                for (int k=0;k<liability_count;k++)  {//search if we have a lonely pair with a girl
                    if (liability[k]!=-1 && large_sequence->get_nth_pair(liability[k])->get_situation()==1)  {
                        large_sequence->get_nth_pair(liability[k])->complete_pair(arrangements[i]->get_nth_pair(last_lonely_pair),false);//put the boy in the pair of the girl
                        arrangements[i]->send_to_oblivion(arrangements[i]->get_nth_pair(last_lonely_pair));//destroy the Pair object used to store the boy
                        liability[k]=-1; //if we were successful, make the girl's position infit to be used again
                        success=true;
                        break;
                    }
                }
                if (!success)  {
                    large_sequence->copy_pair(arrangements[i]->get_nth_pair(j)); //if we are not successful, copy the lonely pair, with the hope that it may get completed in the future
                    liability[liability_count]=large_sequence->get_pair_position()-1;//its position being the current last pair of the large sequence
                    liability_count++;
                }
            }
            else if (arrangements[i]->get_nth_pair(last_lonely_pair)->get_situation()==1)  {//same scenario but for a girl
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
    while (L-->0)  {//number of repetitions 
        srand(time(NULL));
        int naughty_students;
        bool double_mess=0;
        int limit=large_sequence->get_pair_position();
        for (int i=0;i<L;i++)  {
            naughty_students=rand()%(limit/2);//number of naughty students per repetition
            for (int j=0;j<naughty_students;j++)  {
                int pick=rand()%limit;//choosing a pair to become naughty
                if (large_sequence->get_nth_pair(pick)->bad_pair()!=0)  {//if the pair is already naughty, we ignore it(since rand() and rand()-1 students aren't really different in our case)
                    continue;
                }
                bool both=large_sequence->get_nth_pair(pick)->cause_trouble(j,naughty_students);//make one of the students of the pair, or both, to become mishievous
                if (rand()%3==0 && both && (pick+1)<limit && (j+1)<naughty_students && large_sequence->get_nth_pair(pick+1)->get_situation()==3)  {//if in the previous pair, we chose both students to cause noise, then we try and do it to the next
                    both=large_sequence->get_nth_pair(pick+1)->cause_trouble(j,naughty_students);//in an effort to make consecutives pais of naughty students to appear more often
                    if (rand()%3==0 && both && (pick+2)<limit && (j+1)<naughty_students && large_sequence->get_nth_pair(pick+2)->get_situation()==3)  {//likewise if we have created two consecutives, we try and create a third
                        large_sequence->get_nth_pair(pick+2)->cause_trouble(j,naughty_students);
                    }  
                }
                //keep in mind that there is nothing that states that in the next pair, there won't appear another consecutive series
                //thus there is no limit to the maximum amount of consecutives pairs one can have in a series of consecutives 
            }
            for (int i=0;i<number_of_sequences;i++)  {
                int noisy_pairs_counter=0;//counter of all non-consecutive mischievous pairs and consecutive mischievous pairs which number less than 3
                int start_of_consecutive_pair=0;//stores the position of the first consecutive in a series of consecutives
                int consecutive_counter=0;
                for (int j=0;j<arrangements[i]->get_pair_position();j++)  {
                    if (arrangements[i]->get_nth_pair(j)->bad_pair()==3)  {//if we find a naughty pair
                        if (consecutive_counter==0)  {//and there isn't one in the previous pair
                            start_of_consecutive_pair=j;//we store its position in hope that more consecutives will appear afterwards
                        }
                        consecutive_counter++;
                        noisy_pairs_counter++;
                    }
                    else  {//else, if we don't find a naughty pair
                        if (consecutive_counter>2)  {//we check to see if we had previously found a series of consecutives with length greater than two,
                            for (int k=start_of_consecutive_pair;k<start_of_consecutive_pair+consecutive_counter;k++)  {
                                if (k==start_of_consecutive_pair)  {
                                    arrangements[i]->get_nth_pair(k)->set_to_start_of_consecutive_pairs();//set the first pair of the series of consecutives as the start of them
                                }
                                arrangements[i]->get_nth_pair(k)->award_vvip_status();//trigger all the necessary flags
                                arrangements[i]->get_nth_pair(k)->award_double_penalty_status();
                                arrangements[i]->get_nth_pair(k)->set_mode_of_transfer(2);
                            }
                            noisy_pairs_counter=noisy_pairs_counter-consecutive_counter;//τmore than 2 consecutive pairs do not count towards the noisey_pairs_counter
                            consecutive_counter=0;
                        }
                        consecutive_counter=0;//else if we didn't have more than 2, we don't do anything for now
                        if (arrangements[i]->get_nth_pair(j)->bad_pair()==2 || arrangements[i]->get_nth_pair(j)->bad_pair()==1)  {
                            arrangements[i]->get_nth_pair(j)->set_mode_of_transfer(0);//if we find a mishievous student, we set his mode of transfer
                        }
                    }
                }
                for (int j=0;j<arrangements[i]->get_pair_position();j++)  {
                    if (arrangements[i]->get_nth_pair(j)->bad_pair()==3 && arrangements[i]->get_nth_pair(j)->get_importance()!=1)  {//searching the remaining naughty pairs that didn't receive any mode of transfer
                        if (noisy_pairs_counter>2)  {//if we have more than two, prepare them to be moved to another sequence
                            arrangements[i]->get_nth_pair(j)->set_mode_of_transfer(2);
                            arrangements[i]->get_nth_pair(j)->award_double_penalty_status();
                        }
                        else  {//else, prepare them to me moved in their own sequence
                            arrangements[i]->get_nth_pair(j)->set_mode_of_transfer(1);
                        }
                    }
                }
            } 
            //from now on, we will perform 3 iterations of the large sequence
            for (int i=0;i<large_sequence->get_pair_position();i++)  {
                if (large_sequence->get_nth_pair(i)->get_importance())  {//in the first, we switch all consecutive pairs(>2) with others of different seqeunces
                    if (large_sequence->get_nth_pair(i)->is_consecutive_pairs_start())  {//if  its the start of a series of consecutive pairs, make all the sequences available to place a pair
                        Set_availability_to_open();
                    }
                    swap(large_sequence->get_nth_pair(i),0); //make the switch and punish the students related to it
                }
            }  
            for (int i=0;i<large_sequence->get_pair_position();i++)  {
                if (large_sequence->get_nth_pair(i)->bad_pair()==3)  {//in the second iteration, we look at the remaining naughty pairs, and switch them
                    swap(large_sequence->get_nth_pair(i),0);    
                }
            }
            for (int i=0;i<large_sequence->get_pair_position();i++)  {
                if (large_sequence->get_nth_pair(i)->bad_pair()==1)  {//lastly we look for mischievous students and make switch them
                    swap(large_sequence->get_nth_pair(i),1);
                }
                else if (large_sequence->get_nth_pair(i)->bad_pair()==2)  {
                    swap(large_sequence->get_nth_pair(i),0);  
                }
            }
        }
    }

}











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

bool Student::is_mischievous()  {
    return mischievous;
}

void Student::causes_noise()  {
    mischievous=true;
}






Sequence* Student_Pair::get_sequence_belonging()  {
    return sequence;
}

short Student_Pair::get_mode_of_transfer()  {
    return mode_of_tranfer;
}

void Student_Pair::set_mode_of_transfer(short mode)  {
    mode_of_tranfer=mode;
}

void Student_Pair::award_double_penalty_status()  {
    double_penalty=1;
}

void Student_Pair::award_vvip_status()  {
    vvip=1;
}

int Student_Pair::get_sequence_id()  {
    return sequence->get_id();
}

Student_Pair::Student_Pair(Student* Girl,Student* Boy,Sequence* sequence) : start_of_consecutive(0), sequence(sequence), situation(0), vvip(0), double_penalty(0) {
    if (Girl!=NULL)  {
        situation++;
    }
    if (Boy!=NULL)  {
        situation=situation+2;
    }
    this->Girl=Girl;
    this->Boy=Boy;
}

Student_Pair::~Student_Pair()  {
    if (Boy!=NULL)  { //this is mainly for the case where we may want to destroy a Student_Pair, but have removed all students from it(due to a completion of a lonely pair) 
        delete Boy;
        Boy=NULL;
    }
    if (Girl!=NULL)  {
        delete Girl;
        Girl=NULL;
    }
}

void Student_Pair::pay_and_repent(bool both_members,bool gender)  {
    if (both_members)  { //increase the "classroom's" degree of disorder for the naughty kids that are swapped
        Boy->get_sequence()->increase_degree_of_disorder(Boy->is_mischievous()*(double_penalty+1)); 
        Girl->get_sequence()->increase_degree_of_disorder(Girl->is_mischievous()*(double_penalty+1));
        Boy->repent();
        Girl->repent();
    }
    else  {
        if (gender)  {
            Girl->get_sequence()->increase_degree_of_disorder(Girl->is_mischievous());
            Girl->repent();
        }
        else  {
            Boy->get_sequence()->increase_degree_of_disorder(Boy->is_mischievous());
            Boy->repent();
        }
    }
    double_penalty=0; //remove all naughty status for the pair
    vvip=0;
}

short Student_Pair::bad_pair()  {//a representation which tranlastes to: 3->Bad_Pair, 2->Bad_Boy, 1->Bad_Girl
    if (Boy==NULL) return Girl->is_mischievous(); 
    if (Girl==NULL) return 2*Boy->is_mischievous();
    return 2*Boy->is_mischievous()+Girl->is_mischievous();

}

std::string Student_Pair::get_name_of_boy()  {
    return Boy->get_name();
}

std::string Student_Pair::get_name_of_girl()  {
    return Girl->get_name();
}

short Student_Pair::get_situation()  {//a represenation similar to the bad_pair(), 3->Pair_of_Boy_and_Girl, 2->Pair_of_Boy, 1->Pair_of_Girl
    return situation;
}

void Student_Pair::complete_pair(Student_Pair* other_half,bool gender)  {//make a lonely pair into a complete pair
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

void Student_Pair::set_to_start_of_consecutive_pairs()  {
    start_of_consecutive=true;
}


bool Student_Pair::is_consecutive_pairs_start()  {
    return start_of_consecutive;
}

Student* Student_Pair::get_member(bool gender)  {
    if (gender)  {
        return Girl;
    }
    else  {
        return Boy;
    }
}

bool Student_Pair::cause_trouble(int &rolls,int max_rolls)  {
    if (situation==3)  { //if not a lonely pair
        if (rand()%2==0 && rolls+1<max_rolls)  {//and there are enought rolls for two choices, try and create a bad_pair
            rolls=rolls+2;
            get_member(0)->causes_noise();
            get_member(1)->causes_noise();
            return true;
        }
        else  {//else go for either of its two members
            get_member(rand()%2)->causes_noise();
            rolls++;
        }  
    }
    else if (situation==2)  {//unless of course there is only one member, in which case, choose it
        get_member(0)->causes_noise();
        rolls++;
    } 
    else  {
        get_member(1)->causes_noise();
        rolls++;
    }
    return false;
}

bool Student_Pair::get_importance()  {
    return vvip;
}


/*
Student_Pair::Student_Pair(const Student_Pair& pair)  {
    this->Boy=pair.Boy;
    this->Girl=pair.Girl;
    this->situation=pair.situation;
}*/










int Sequence::count_boys()  {
    if (get_nth_pair(get_pair_position()-1)->get_situation()==2)  {
        return get_pair_position();
    }
    else  {
        return get_pair_position()-1;
    }
}

int Sequence::count_girls()  {
    if (get_nth_pair(get_pair_position()-1)->get_situation()==1)  {
        return get_pair_position();
    }
    else  {
        return get_pair_position()-1;
    }
}

int Sequence::count_students()  {
    return count_boys()+count_girls();
}

int Sequence::get_id()  {
    return id;
}

int Sequence::get_pair_position()  {
    return pairs_count;
}

void Sequence::send_to_oblivion(Student_Pair* pair)  {
    pairs_count--; 
    pair->replace_member(NULL,0);//make both members NULL so that the destructor of Student_Pair does not try and destroy the pointers to object Student
    pair->replace_member(NULL,1);//since all we do is pass around the pointers of objects, deleting one would affect others pairs that hold the same pointer 
    delete pair;//This will only occur on the last pair of a classroom, therefore there will be no fear of messing up the array
}

bool Sequence::get_availability()  {
    return available;
}

void Sequence::set_availability_to(bool status)  {
    available=status;
}

Sequence::Sequence(int max_size) : pairs_count(0), id(-1) {
    pairs=new Student_Pair*[max_size]; //create an empty sequence with an id of -1, signifying that it is the large sequence(important for the destructor)
}

Sequence::Sequence(const std::string* boys,const std::string* girls,int min_size,int mode,int mess_limit,int quiet_limit,short id) : pairs_count(0), available(true), degree_of_disorder(0), quiet_limit(quiet_limit), mess_limit(mess_limit), id(id) {
    pairs=new Student_Pair*[min_size+(mode!=0)];//if mode!=0 then an extra student will be placed as the lonely pair, thus requiring min_size+1 pairs
    int i;
    for (i=0;i<min_size;i++)  {
        Student* Boy=new Student(boys[i],0,this);
        Student* Girl=new Student(girls[i],1,this);
        pairs[i]=new Student_Pair(Girl,Boy,this);//create pairs and insert them on the array
        pairs_count++;
    }
    if (mode==1)  {
        
        Student* Girl=new Student(girls[i],1,this); 
        pairs[i]=new Student_Pair(Girl,NULL,this);//make a pair of only a girl
        pairs_count++;
    }
    else if (mode==2)  {
        Student* Boy=new Student(boys[i],0,this);
        pairs[i]=new Student_Pair(NULL,Boy,this);//make a pair of only a boy
        pairs_count++;
    }
}

Sequence::~Sequence()  {
    if (id!=-1)  {//since large sequence and the small sequences share the same pairs, we must be carefull not to delete them twice
        for (int i=0;i<pairs_count;i++)  {//thus, we delete every pair of the small seqeunces
            delete pairs[i];
        }
    }
    delete[] pairs;//and for the large sequence we delete only its array which holds those pairs
}

/*
void Sequence::add_to_arrangement(Student* Girl,Student* Boy)  {
    pairs[pairs_count]=new Student_Pair(Girl,Boy);
    pairs_count++;
}
*/



void Sequence::print()  {
    bool flip=true;
    int size=5;
    for (int i=0;i<pairs_count;i++)  { //first iteration prints the upper row of student pairs
        if (flip)  {
            if (pairs[i]->get_situation()!=1)  {//if there is a boy in the upper part of the pair we are trying to print, we print it
                printf("%*s",size,pairs[i]->get_name_of_boy().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); //else we print nothing, as the pair only has a girl which will be printed in the lower row at the second iteration 
            }
            flip=false;
        }
        else  {
            if (pairs[i]->get_situation()!=2)  {//same for girl
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
    for (int i=0;i<pairs_count;i++)  {
        if (flip)  {
            if (pairs[i]->get_situation()!=2)  {//if there is a girl in the lower part of the pair we are trying to print, we print it
                printf("%*s",size,pairs[i]->get_name_of_girl().c_str()); 
            }
            else  {
                printf("%*s",size,"-"); //else we print nothing, as the pair only has a boy which has already been printed in the upper row at the first iteration
            }
            flip=false;
        }
        else  {
            if (pairs[i]->get_situation()!=1)  {//same for boy
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


void Sequence::copy_pair(Student_Pair* pair)  {//store the pointer to the pair in the array of the large sequence(so that changes in the small sequences affect the large sequence and vice versa)
    pairs[pairs_count]=pair;
    pairs_count++;
} 


void Sequence::increase_degree_of_disorder(int n)  {
    degree_of_disorder=degree_of_disorder+n;
}

Student_Pair* Sequence::get_nth_pair(int n)  {
    return pairs[n];
}
