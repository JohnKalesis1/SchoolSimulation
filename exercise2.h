#include <string>

class Sequence;
class Student_Pair;


class School  {
    private:
        Sequence** arrangements;
        int* classrooms_bad_points;
        Sequence* large_sequence;
        int number_of_sequences;
        int *class_sequence_begin;
        void Set_availability_to_open();
        Student_Pair* pick_random(Student_Pair* original_pair,int sequence_id,bool same_class,bool vvip_scenario,bool gender_of_pair);
        void swap(int id,Student_Pair* pair,short mode,bool gender,bool vvip_scenario);
    public:
        School(const std::string* boys,const std::string* girls,int size_boys,int size_girls,int number_of_classrooms,int mess_limit,int quiet_limit);
        ~School();
        void print_arrangements_per_classroom();  
        void print_unified_arrangement(); 
        void create_unified_sequence();
        void behave(int L);
};

class Student  {
    private: 
        std::string name;
        Sequence* sequence;
        bool mischievous;
        bool gender;
    public:
        Student(const std::string name,bool gender,Sequence* sequence);
        ~Student() {}
        Sequence* get_sequence();
        short is_michievous();
        short causes_noise();
        void repent();
        bool get_gender();
        std::string get_name();
};

class Student_Pair  {
    private:
        Student* Girl;
        Student* Boy;
        bool vvip;
        bool double_penalty;
        short situation;
    public:
        short consists_of();
        Student_Pair() {}
        Student_Pair(const Student_Pair& pair);
        Student_Pair(Student* Girl,Student* Boy);
        ~Student_Pair()  {}
        std::string get_name_of_girl();
        std::string get_name_of_boy();
        Student* get_member(bool gender);
        Sequence* get_sequence_belonging();
        bool get_importance();
        void replace_member(Student* student,bool gender);
        short get_situation();
        short bad_pair();
        void pay_and_repent(bool both_members,bool gender);
        bool cause_trouble();
        void complete_pair(Student_Pair* other_half,bool gender);
};

class Sequence  {
    private:
        int mess_limit;
        int degree_of_disorder;
        int quiet_limit;
        int pairs_count;
        int id;
        bool available;
        Student_Pair** pairs;
    public:
        Sequence(int max_size);
        Sequence(const std::string* boys,const std::string* girls,int min_size,int mode,int mess_limit,int quiet_limit,short id);
        ~Sequence();
        void add_to_arrangement(Student* Girl,Student* Boy);
        void copy_pair(Student_Pair* pair);
        void print();
        int count_boys();
        int count_girls();
        int count_students();
        void increase_degree_of_disorder(int n);
        bool get_availability();
        void set_availability_to(bool status);
        int get_pair_position();
        void send_to_oblivion(Student_Pair* pair);
        void switch_member_of_pair(Student_Pair* pair1,Student_Pair* pair2,bool full_switch,bool gender);
        Student_Pair* get_nth_pair(int n);
};