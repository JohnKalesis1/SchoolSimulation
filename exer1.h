#include <string>

class Student;
class Teacher;


class Classroom  {
    private:
        std::string teacher;//since we only need the teacher's name, there is no need to have the entire object(only the Teacher stores the pointer to his clasroom)
        int capacity;
        Student** students;//an array of pointers to Student objects
        int population;
        short id;
        bool entry_possible;
    public:
        void print();
        void enter(Student* student);//stores the pointer of the student to the last position of the classrooms array
        bool teacher_inside();
        int get_capacity();
        short get_id();
        void assign_teacher(std::string name);
        void teacher_enters();
        Classroom(int capacity,short id); 
        ~Classroom();
};

class Corridor {
    private:
        Student** students;
        int population;
        int capacity;
    public:
        Student* forced_exit(short id);//if a student of with the classroom id is waiting in the corridor, re-arrange his position  with the last of the array and call the exit function
        void print();
        bool is_empty();
        int get_student_class_id();
        int get_population();
        bool space_available();
        void enter(Student* student);//stores the pointer of the student to the last position of the array
        Student* exit();//returns the pointer to the last student of the array and reduces the count of students
        Corridor(int capacity);
        ~Corridor();  
};

class Stairs  {
    private:
        Student** students;
        int population;
        int capacity;
        int advanced_count;
    public:
        void print();
        bool is_empty();
        short floor_distribution();//returns the floor that the last student of the array must enter in order to reach his calssroom
        int get_population();
        bool space_available();
        void enter(Student* student);//same as previous 
        Student* exit();//same as previous 
        Stairs(int capacity);
        ~Stairs(); 
};

class Yard  {
    private:
        Student** students;
        int population;
        int advanced_count;
        int capacity;
    public:
        void print();
        bool is_empty();
        int get_population();
        bool space_available();
        void enter(Student* student);
        Student* exit();
        Yard(int capacity); 
        ~Yard(); 
};

class Floor  {
    private:
        int advanced_count;
        int s_count;
        Classroom* classrooms[6];
        Corridor* corridor;
        short height;
    public:
        Classroom* get_class(short number);
        void print();
        bool space_available_in_corridor();//returns true if there is space available in thefloor's corridor
        void enter(Student* student);//enters the student into the corridor by calling the corridor's enter() function
        bool flush();//force all the students in the corridor to try and enter their classrooms(explaining its significance in the function's body)
        Floor(int height,int corridor_capacity,int class_capacity);
        ~Floor();
};

class SchoolBuilding  {
    private:
        Student** students;
        Teacher* teachers[18];
        int advanced_count;//how many students have entered the school 
        int s_count;//how many students are registered in the school
        short t_count;//how many teachers are registered in the school
        Floor* floors[3];
        Yard* yard;
        Stairs* stairs;
        void place_teacher(bool all);//a function that randomly picks a teacher and places him in his classroom(has a second mode where it places all the teachers when called)
    public:
        void school_begins();//initiate the advancement of students to reach their classrooms
        void register_student(std::string name);
        void register_teacher(std::string name);
        void print();
        SchoolBuilding(int class_capacity,int yard_capacity,int stairs_capacity,int corridor_capacity);
        ~SchoolBuilding();
};

class Student  {
    private:
        std::string name;
        short location;
        Classroom* classroom;
    public:
        short get_classroom_id();
        std::string get_name();
        void set_location_to(short i);//when a student advances to a new location, this will indicate where he is
        Student(std::string name,Classroom* classroom); 
        ~Student();
};

class Teacher  {
    private:
        std::string name;
        bool in_class;
        Classroom* classroom;
    public:
        void enter_class();//place the teacher in his classroom and prohibit all entry to it 
        bool is_in_class();
        std::string get_name() const;
        Teacher()  {  }
        Teacher(std::string name,Classroom* classroom);
        ~Teacher();
};
