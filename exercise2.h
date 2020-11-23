#include <string>

class Sequence;
class Student_Pair;


class School  {
    private:
        Sequence** arrangements;
        Sequence* large_sequence;
        int number_of_sequences;
        void switch_member_of_pair(Student_Pair* pair1,Student_Pair* pair2,bool full_switch,bool gender);
        void Set_availability_to_open();
        Student_Pair* pick_random(Student_Pair* original_pair,int sequence_id,bool same_class,bool vvip_scenario,bool full_switch,bool gender_of_pair);
        void swap(Student_Pair* pair,bool gender);
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
        bool is_mischievous();
        void causes_noise();
        void repent();
        bool get_gender();
        std::string get_name();
};

class Student_Pair  {
    private:
        Student* Girl;
        Student* Boy;
        Sequence* sequence;
        short mode_of_tranfer;
        bool vvip;
        bool start_of_consecutive;
        bool double_penalty;
        short situation;
    public:
        Student_Pair() {}
        Student_Pair(const Student_Pair& pair);
        Student_Pair(Student* Girl,Student* Boy,Sequence* sequence);
        ~Student_Pair();
        bool is_consecutive_pairs_start();
        void set_to_start_of_consecutive_pairs();
        std::string get_name_of_girl();
        std::string get_name_of_boy();
        Student* get_member(bool gender);
        Sequence* get_sequence_belonging();
        bool get_importance();
        void replace_member(Student* student,bool gender);
        short get_situation();
        short bad_pair();
        int get_sequence_id();
        short get_mode_of_transfer();
        void set_mode_of_transfer(short mode);
        void award_double_penalty_status();
        void award_vvip_status();
        void pay_and_repent(bool both_members,bool gender);
        bool cause_trouble(int& rolls,int max_rolls);
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
        int get_id();
        int count_boys();
        int count_girls();
        int count_students();
        void increase_degree_of_disorder(int n);
        bool get_availability();
        void set_availability_to(bool status);
        int get_pair_position();
        void send_to_oblivion(Student_Pair* pair);
        
        Student_Pair* get_nth_pair(int n);
};
