#include <vector>
#include <string>



class Classroom;

class Person  {
    protected:
        std::string name;
        int exhaustion;
    public:
        Person(std::string name);
        ~Person() {}
        std::string& get_name();
        int get_exhaustion();
        void increase_exhaustion(int n);
};

class Teacher: public Person {
    private:
        Classroom* classroom;
        bool inside_classroom;
    public: 
        Teacher(Classroom* classroom,std::string name);
        ~Teacher() {}
        bool is_in_classroom();
        void teach(int hours);
        void place();


};

class Student: public Person {
    protected:
        Classroom* classroom;
        bool inside_classroom;
    public:
        Student(Classroom* classroom,std::string name) : Person(name), inside_classroom(false), classroom(classroom) {}      
        virtual ~Student() {}
        virtual void attend(int hours)=0;
        virtual void print()=0;
        void enters_classroom();
        int get_classroom_id();
};

class Junior : public Student {
    public:
        Junior(Classroom* classroom,std::string name);
        ~Junior() {}
        void print();
        void attend(int hours);
};

class Senior : public Student {
    public:
        Senior(Classroom* classroom,std::string name);
        ~Senior() {}
        void print();
        void attend(int hours);
};


class Space {
    protected:
        std::vector<Student*> students;
    public:
        Space() {}
        ~Space() {}
        void enter(Student* student);
};

class Yard: public Space  {
    public:
        Yard();
        ~Yard() {}
        void enter(Student* student);
        Student* exit();
};

class Stairs: public Space  {
    public:
        Stairs();
        ~Stairs() {}
        void enter(Student* student);
        Student* exit();
        int floor_distribution();
};

class Corridor: public Space  {
    public:
        Corridor();
        ~Corridor() {}
        void enter(Student* student);
        Student* exit();
};

class Classroom : public Space {
    private:
        int id;
        Teacher* teacher;
    public:
        Classroom(int id);
        ~Classroom() {}
        void register_teacher(Teacher* teacher);
        int get_id();
        void print();
        void enter(Student* student);
        void operate(int hours);
};

class Floor  {
    private:
        Corridor corridor;
        std::vector<Classroom> classrooms;
        int floor_number;
    public:
        Floor(int floor_number);
        ~Floor() {}
        Classroom* get_classroom(int index);
        void enter(Student* student);
        void operate(int hours);
        void print();
};

class School {
    private:
        std::vector<Student*> students;
        std::vector<Teacher*> teachers;
        std::vector<Floor> floors;
        Yard yard;
        Stairs stairs;
        int juniors_iterator;
        int seniors_iterator;
        static inline int Junior_exhaustion_rate=0;
        static inline int Senior_exhaustion_rate=0;
        static inline int Teacher_exhaustion_rate=0;
    public:
        School(int Lj,int Ls,int Lt); 
        ~School();
        void register_senior(std::string name);
        void register_junior(std::string name);
        void register_teacher(std::string name);
        static int get_junior_exhaustion_rate();
        static int get_senior_exhaustion_rate();
        static int get_teacher_exhaustion_rate();
        void begins();
        void print();
        void operate(int hours);
};
