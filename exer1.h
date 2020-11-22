#include <string>

class Student;
class Teacher;


class Classroom  {
    private:
        std::string teacher;
        int capacity;
        //int registered_students_count;
        Student** students;
        int population;
        short id;
        bool entry_possible;
    public:
        void print();
        void enter(Student* student);
        bool teacher_inside();
        int get_capacity();
        short get_id();
        //void assign_student(Student* student);
        void assign_teacher(std::string name);
        void teacher_enters();
        //Classroom()  {}
        Classroom(int capacity,short id); 
        ~Classroom();
};

class Corridor {
    private:
        Student** students;
        int population;
        int capacity;
    public:
        Student* forced_exit(short id);
        void print();
        bool is_empty();
        int get_student_class_id();
        int get_population();
        bool space_available();
        void enter(Student* student);
        Student* exit();
        //Corridor()  {}
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
        short floor_distribution();
        int get_population();
        bool space_available();
        void enter(Student* student);
        Student* exit();
        //Stairs()  {}
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
        //Yard()  {}
        Yard(int capacity); 
        ~Yard(); 
};

class Floor  {
    private:
        int advanced_count;
        int s_count;
        Classroom* classrooms[6];
        Corridor* corridor;
        Student** students;
        short height;
    public:
        Classroom* get_class(short number);
        void print();
        bool space_available_in_corridor();
        bool students_advance();
        void enter(Student* student);
        void flush();
        //Floor()  {}
        Floor(int height,int corridor_capacity,int class_capacity);
        ~Floor();
};

class SchoolBuilding  {
    private:
        Student** students;
        Teacher* teachers[18];
        int advanced_count;
        int s_count;
        short t_count;
        Floor* floors[3];
        Yard* yard;
        Stairs* stairs;
    public:
        void school_begins();
        void stairs_exit();
        bool exit(Student* student);
        void register_student(std::string name);
        void register_teacher(std::string name);
        void print();
        void place_teacher(bool all);
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
        void set_location_to(short i);
        //Student()  {}
        Student(std::string name,Classroom* classroom); 
        ~Student();
};

class Teacher  {
    private:
        std::string name;
        bool in_class;
        Classroom* classroom;
    public:
        void enter_class();
        bool is_in_class();
        std::string get_name() const;
        Teacher()  {  }
        Teacher(std::string name,Classroom* classroom);
        ~Teacher();
};
