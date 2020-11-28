#include <string>

class Sequence;
class Student_Pair;


class School  {
    private:
        Sequence** arrangements;//the arrangement of each classroom
        Sequence* large_sequence;//the unified arrangemet, in which the lonely pairs of opposite gender have merged 
        int number_of_sequences;
        int number_of_students;
        void switch_member_of_pair(Student_Pair* pair1,Student_Pair* pair2,bool full_switch,bool gender);//replaces both members if its a full_switch, or only the member of gender indicated otherewise
        void Set_availability_to_open();//sets every sequences, open for the transfer of a consecutive naughty pair(the reason will become apparent laters when we use it)
        Student_Pair* pick_random(Student_Pair* original_pair,int sequence_id,bool same_class,bool vvip_scenario,bool full_switch,bool gender_of_pair);//Pick a random pair from the sequence which satisfies the citeria listed 
        void swap(Student_Pair* pair,bool gender);//causes a naughty pair or student to swap with another random, calling all necessary functions
    public:
        School(const std::string* boys,const std::string* girls,int size_boys,int size_girls,int number_of_classrooms,int mess_limit,int quiet_limit);
        ~School();
        void print_arrangements_per_classroom();  
        void print_unified_arrangement(); 
        void create_unified_sequence();
        void behave(int L);//the algorithm where for L times, random students cause trouble and are replaced with their peers
};

class Student  {
    private: 
        std::string name;
        Sequence* sequence;//We want to keep a pointer to the original sequence a student belonged(aka his classroom)
        bool mischievous;//if the student is mischievous or not
        bool gender;
    public:
        Student(const std::string name,bool gender,Sequence* sequence);
        ~Student() {}
        Sequence* get_sequence();
        bool is_mischievous();
        void causes_noise();//apply the "mischievous" status effect to a student
        void repent();//cure a student from the "mischievous status effect"
        bool get_gender();
        std::string get_name();
};

class Student_Pair  {
    private:
        Student* Girl;
        Student* Boy;
        Sequence* sequence;//pairs are only the storage of students, so they do not switch and keeping their sequence is useful for the puropose of trying ot pick other pairs of different sequences
        short mode_of_tranfer;//when swap is called on this pair, it will act based on the mode of transfer of the pair
        bool vvip;//whether the pair is in a series of consecutive pairs more than 2, and thus needs special treatment to be placed in a different sequence than its other peers
        bool start_of_consecutive;//whether or not the pair, is the first in a series of consecuitve pairs
        bool double_penalty;//whether when swtching this pair, we need to penaltize its classroom by a double amount
        short situation;//whether its a pair of only a girl, only a boy, or a complete pair
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
        short bad_pair();//returns how bad is the pair
        int get_sequence_id();
        short get_mode_of_transfer();
        void set_mode_of_transfer(short mode);
        void award_double_penalty_status();
        void award_vvip_status();
        void pay_and_repent(bool both_members,bool gender);
        bool cause_trouble(int& rolls,int max_rolls);
        void complete_pair(Student_Pair* other_half,bool gender);//adds a second student to a lonely pair nad completes it
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
        void copy_pair(Student_Pair* pair);//we pass the pointer from another pair to the array of this sequence(will only occur when we create the unified seqeunce)
        void print();
        int get_id();
        int count_boys();
        int count_girls();
        int count_students();
        void increase_degree_of_disorder(int n);
        bool get_availability();
        void set_availability_to(bool status);
        int get_pair_position();
        void send_to_oblivion(Student_Pair* pair);//destroys a pair without touching any of its members(will only occur on a lonely when a pair completion occurs, and thus the pair will no longer has any use)
        
        Student_Pair* get_nth_pair(int n);
};
