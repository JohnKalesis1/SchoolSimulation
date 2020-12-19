import java.util.Vector;

interface StringConstants {   
    static char[] floor={'A','B','C'};
}
abstract class Person  {
    protected String name;
    protected int exhaustion;

    Person(String name) {
        this.name=new String(name);
        exhaustion=0;
    }
    String get_name()  {
        return name;
    }

    int get_exhaustion()  {
        return exhaustion;
    }

    void increase_exhaustion(int n)  {
        exhaustion=exhaustion+n;
    }
}

class Teacher extends Person  {
    private Classroom classroom;
    private boolean inside_classroom;
    Teacher(Classroom classroom,String name) {
        super(name);
        this.classroom=classroom;
        inside_classroom=false;
        System.out.print("A Teacher has been created, " + this.name +" of classroom "+ StringConstants.floor[classroom.get_id()/6] + classroom.get_id()%6+ '\n');
        classroom.register_teacher(this);
    }

    boolean is_in_classroom() {
        return inside_classroom;
    }

    void teach(int hours)  {
        int exhaustion_rate=School.get_teacher_exhaustion_rate();
        increase_exhaustion(hours*exhaustion_rate);
    }
    void place()  {
        inside_classroom=true;
    }

}

abstract class Student extends Person {
    protected Classroom classroom;
    protected boolean inside_classroom;
    Student(Classroom classroom,String name) {
        super(name); 
        inside_classroom=false; 
        this.classroom=classroom;
    }
    void enters_classroom()  {
        inside_classroom=true;
    }
    int get_classroom_id()  {
        return classroom.get_id();
    }
    abstract void attend(int hours);
    abstract void print();
}


class Junior extends Student  {
    Junior(Classroom classroom,String name) {
        super(classroom,name);
        System.out.print("A Junior student has been created, "+ this.name +" of classroom "+ StringConstants.floor[classroom.get_id()/6] + classroom.get_id()%6+ '\n');
    }
    void attend(int hours)  {
        int exhaustion_rate=School.get_junior_exhaustion_rate();
        increase_exhaustion(hours*exhaustion_rate);
    }

    void print()  {
        System.out.print("Junior "+ name + "("+ exhaustion +")");
    }
}

class Senior extends Student  {
    Senior(Classroom classroom,String name)  {
        super(classroom,name);
        System.out.print("A Senior student has been created, "+ this.name +" of classroom "+ StringConstants.floor[classroom.get_id()/6] + classroom.get_id()%6+ '\n');
    }

    void attend(int hours)  {
        int exhaustion_rate=School.get_senior_exhaustion_rate();
        increase_exhaustion(hours*exhaustion_rate); 
    }

    void print()  {
        System.out.print("Senior "+ name + "("+ exhaustion +")");
    }
}


abstract class Space  {
    protected Vector<Student> students;
    Space()  {
        students=new Vector<Student>(1);
    }
    void enter(Student student)  {
        students.set(0,student);
    }
}

class Yard extends Space  {
    Yard()  {
        super();
        System.out.print("The yard has been created \n");
        students.add(null);
    }

    void enter(Student student)  {
        student.print();
        System.out.print(" enters yard\n");
        super.enter(student);
    }

    Student exit()  {
        students.get(0).print();
        System.out.print(" exits yard.");
        return students.get(0);
    }
}

class Stairs extends Space  {
    Stairs()  {
        super();
        System.out.print("The stairs has been created \n");
        students.add(null);
    }
    void enter(Student student)  {
        student.print();
        System.out.print(" enters stairs\n");
        super.enter(student);
    }
    Student exit()  {
        students.get(0).print();
        System.out.print(" exits stairs.");
        return students.get(0);
    }
    int floor_distribution()  {
        return students.get(0).get_classroom_id()/6;
    }
}

class Corridor extends Space  {
    Corridor()  {
        super();
        System.out.print("A corridor has beem created \n");
        students.add(null);
    }

    void enter(Student student)  {
        student.print();
        System.out.print(" enters corridor\n");
        super.enter(student);
    }

    Student exit()  {
        students.get(0).print();
        System.out.print(" exits corridor.");
        return students.get(0);
    }
}
class Classroom extends Space { 
    private int id;
    private Teacher teacher;
    Classroom(int id)  {
        super();
        System.out.print("A classroom has beem created "+ id+ '\n');
        this.id=id;
    }

    void register_teacher(Teacher teacher)  {
        this.teacher=teacher;
    }

    int get_id()  {
        return id;
    }

    void enter(Student student)  {
        System.out.print(student.get_name() + " enters classroom\n");
        students.add(student);
    }

    void print()  {
        System.out.print("\tClassroom " + id%6 + ":\n");
        for (int i=0;i<students.size();i++)  {
            System.out.print("\t->");
            students.get(i).print();
            System.out.print('\n');
        }
        if (teacher.is_in_classroom())  { 
            System.out.print("\t->Teacher " + teacher.get_name() +"(" +teacher.get_exhaustion()+ ")"+ '\n');
        }
        System.out.print('\n');
    }

    void operate(int hours)  {
        for (int i=0;i<students.size();i++)  {
            students.get(i).attend(hours);
        }
        teacher.teach(hours);
    }
}


class Floor  {
    private Corridor corridor;
    private Vector<Classroom> classrooms;
    private int floor_number;
    Floor(int floor_number)  {
        classrooms=new Vector<Classroom>(6);
        corridor=new Corridor();
        this.floor_number=floor_number;
        for (int i=0;i<6;i++)  {
            classrooms.add(new Classroom(6*floor_number+i));
        }
    }

    Classroom get_classroom(int index)  {
        return classrooms.get(index);
    }

    void operate(int hours)  {
        for (int i=0;i<6;i++)  {
            classrooms.get(i).operate(hours);
        }
    }
    void enter(Student student)  {
        student.print();
        System.out.print(" enters floor "+ StringConstants.floor[floor_number] + ".");
        corridor.enter(student);
        classrooms.get(student.get_classroom_id()%6).enter(corridor.exit());
    }

    void print()  {
        System.out.print(" Floor " + StringConstants.floor[floor_number] + " consists of:\n");
        for (int i=0;i<6;i++)  {
            classrooms.get(i).print();
        }
        System.out.print('\n');
    }
}

class School  {
    private Vector<Student> students;
    private Vector<Teacher> teachers;
    private Vector<Floor> floors;
    private Yard yard;
    private Stairs stairs;
    private int juniors_iterator;
    private int seniors_iterator;
    private static int Junior_exhaustion_rate;
    private static int Senior_exhaustion_rate;
    private static int Teacher_exhaustion_rate;
    static {
        Junior_exhaustion_rate=0;
        Senior_exhaustion_rate=0;
        Teacher_exhaustion_rate=0;
    }
    public School(int Lj,int Ls,int Lt)  {
        students=new Vector<Student>();
        teachers=new Vector<Teacher>(18);
        floors=new Vector<Floor>(3);
        juniors_iterator=0; 
        seniors_iterator=0; 
        Junior_exhaustion_rate=Lj;
        Senior_exhaustion_rate=Ls;
        Teacher_exhaustion_rate=Lt;
        yard=new Yard();
        stairs=new Stairs();
        for (int i=0;i<3;i++)  {
            floors.add(new Floor(i));
        }
        
    }

    public void print()  {
        System.out.print("School building consists of: \n");
        for (int i=0;i<3;i++)  {
            floors.get(i).print();
        }
    }

    public void begins()  {
        for (int i=0;i<students.size();i++)  {
            students.get(i).print();
            System.out.print(" enters school building.");
            yard.enter(students.get(i));
            stairs.enter(yard.exit());
            floors.get(stairs.floor_distribution()).enter(stairs.exit());
            System.out.print("\n");
        }
        for (int i=0;i<teachers.size();i++)  {
            teachers.get(i).place();
        }
    }

    public void operate(int hours)  {
        for (int i=0;i<3;i++)  {
            floors.get(i).operate(hours);
        }
    }

    public void register_junior(String name)  {
        students.add(new Junior(floors.get((juniors_iterator%9)/3).get_classroom(juniors_iterator%3),name));
        juniors_iterator++;
    }

    public void register_senior(String name)  {
        students.add(new Senior(floors.get((seniors_iterator%9)/3).get_classroom(seniors_iterator%3+3),name));
        seniors_iterator++;
    }

    public void register_teacher(String name)  {
        teachers.add(new Teacher(floors.get(teachers.size()/6).get_classroom(teachers.size()%6),name));
    }

    static int get_junior_exhaustion_rate()  {
        return Junior_exhaustion_rate;
    }

    static int get_teacher_exhaustion_rate()  {
        return Teacher_exhaustion_rate;
    }

    static int get_senior_exhaustion_rate()  {
        return Senior_exhaustion_rate;
    }
}
