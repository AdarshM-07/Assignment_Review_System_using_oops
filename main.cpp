
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class IMG_Member
{
private:
protected:
    string name;
    string enroll_no;

public:
    string get_name()
    {
        return name;
    }
    string get_enroll_no()
    {
        return enroll_no;
    }
    IMG_Member(){};
};

class Assignment
{
protected:
    string name, content, status;
    vector<string> remark;
    bool iterationStatus;

public:
    Assignment(string n, string c, vector<string> &r, string s = "Pending", bool i = false)
    {
        name = n;
        content = c;
        status = s;
        iterationStatus = i;
        remark = r;
    }
    void get_assig_details()
    {
        cout << "Assignment Name: " << name << endl;
        cout << "Content: " << content << endl;
    }
    void assignRemark(string s)
    {
        remark.push_back(s);
    }
    vector<string> showRemark()
    {
        return remark;
    }
    string get_name()
    {
        return name;
    }
    string get_status()
    {
        return status;
    }
    string get_content()
    {
        return content;
    }

    bool get_iterationStatus()
    {
        return iterationStatus;
    }
    void update_status(string a, bool b)
    {
        status = a;
        iterationStatus = b;
    }
};

vector<Assignment> tot_assignments;

class Student : public IMG_Member
{
private:
    string password;
    vector<Assignment> assignments;

public:
    Student(){};
    Student(string n, string e, string p)
    {
        name = n;
        enroll_no = e;
        password = p;
        assignments = tot_assignments;
    }

    void displayProfile()
    {
        cout << "Name: " << name << endl;
        cout << "Enrollment No.: " << enroll_no << endl;
        cout << "Total assignments: " << assignments.size() << endl;
        cout << "Pending assignments: " << ct_pendAssign() << endl;
    }

    string get_pass()
    {
        return password;
    }
    vector<Assignment> get_assign()
    {
        return assignments;
    }
    void req_iterate(string name)
    {
        for (int i = 0; i < assignments.size(); i++)
        {
            if (assignments[i].get_name() == name)
            {
                assignments[i].update_status("Pending", true);
            }
        }
    }
    void getRemark(string name)
    {
        for (auto i : assignments)
        {
            if (i.get_name() == name)
            {
                for (auto j : i.showRemark())
                {
                    cout << "-" << j << endl;
                }
            }
        }
    }
    void showAssignments()
    {
        int k = 1;
        for (auto i : assignments)
        {
            cout << "Assignment"
                 << " " << k << endl;
            i.get_assig_details();
            k++;
        }
    }
    void getPendingAssignments() const
    {
        cout << "Pending assignments for student " << name << ":" << endl;
        for (auto assignment : assignments)
        {
            if (assignment.get_status() == "Pending")
                cout << "- " << assignment.get_name() << endl;
        }
    }

    int ct_pendAssign()
    {
        int pd = 0;
        for (auto i : assignments)
        {
            if (i.get_status() == "Pending")
            {
                pd++;
            }
        }
        return pd;
    }
    void addAssgn(string n, string c)
    {
        vector<string> v;
        Assignment a(n, c, v, "Pending", false);
        assignments.push_back(a);
    }
    void load_assignments(vector<Assignment> a)
    {
        assignments = a;
    }
};

map<string, Student> studentProfile;

class Reviewer : public IMG_Member
{
private:
    string password;

public:
    Reviewer(){};
    Reviewer(string n, string e, string p)
    {
        name = n;
        enroll_no = e;
        password = p;
    }

    void displayProfile()
    {
        cout << "Reviewer Profile:" << endl;
        cout << "Name: " << name << endl;
        cout << "Enrollment Number: " << enroll_no << endl;
    }
    void showAssignments()
    {
        int k = 1;
        for (auto i : tot_assignments)
        {
            cout << "Assignment"
                 << " " << k << endl;
            i.get_assig_details();
            k++;
        }
    }
    string get_pass()
    {
        return password;
    }

    void uploadAssignment(string name, string content, vector<string> remark)

    {
        Assignment a(name, content, remark, "Pending", false);
        tot_assignments.push_back(a);
    }

    void suggestIteration(string enroll_no, string name, string remark)
    {

        Student s1 = studentProfile[enroll_no];

        vector<Assignment> v;
        v = s1.get_assign();
        for (int i = 0; i < v.size(); i++)
        {

            if (v[i].get_name() == name)
            {
                Assignment a1 = v[i];
                a1.assignRemark(remark);
                a1.update_status("Pending", false);

                v[i] = a1;
                break;
            }
        }
        s1.load_assignments(v);

        studentProfile[enroll_no] = s1;
    }
    void markCompleted(string enroll_no, string name)
    {

        Student s2 = studentProfile[enroll_no];
        vector<Assignment> v;
        v = s2.get_assign();

        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].get_name() == name)
            {
                Assignment a1 = v[i];
                a1.update_status("Completed", false);
                v[i] = a1;
                break;
            }
        }
        s2.load_assignments(v);
        studentProfile[enroll_no] = s2;
    }
};

map<string, Reviewer> ReviewerProfile;

void loginNewStu()
{
    string name;
    string enroll_no;
    string password;

    cout << "Name: ";
    cin >> name;

    cout << "Enrollment Number: ";
    cin >> enroll_no;

    cout << "Enter Password: ";
    cin >> password;

    Student s(name, enroll_no, password);
    studentProfile[enroll_no] = s;
}
void loginNewRev()
{
    string name;
    string enroll_no;
    string password;

    cout << "Name: ";
    cin >> name;

    cout << "Enrollment Number: ";
    cin >> enroll_no;

    cout << "Enter Password: ";
    cin >> password;

    Reviewer r(name, enroll_no, password);
    ReviewerProfile[enroll_no] = r;
}
void pg1()
{
    cout << "     ******      *******      ******      " << endl;
    cout << "1. Already a member" << endl;
    cout << "2. Add new member" << endl;
    cout << "3. Go Back" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter 1/2/3/4" << endl;
    cout << "     ******      *******      ******      " << endl;
}
void pg2_1()
{
    cout << "     ******      *******      ******      " << endl;
    cout << "1. Student login" << endl;
    cout << "2. Reviewer login" << endl;
    cout << "3. Go Back" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter 1/2/3/4" << endl;
    cout << "     ******      *******      ******      " << endl;
}
void pg2_2()
{
    cout << "     ******      *******      ******      " << endl;
    cout << "1. Student registration" << endl;
    cout << "2. Reviewer registration" << endl;
    cout << "3. Go Back" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter 1/2/3/4" << endl;
    cout << "     ******      *******      ******      " << endl;
}

void review()
{
    while (true)
    {
        pg1();
        int r1;
        cin >> r1;
        if (r1 == 1)
        {
            while (true)
            {
                pg2_1();
                int r2;
                cin >> r2;
                string enroll_no;
                string password;
                string name;
                string content;
                string remark;

                if (r2 == 1)
                {
                    cout << "Enrollment Number: ";
                    cin >> enroll_no;
                    cout << "Enter Password: ";
                    cin >> password;

                    while (true)
                    {

                        if (studentProfile[enroll_no].get_pass() == password)
                        {

                            cout << "     ******      *******      ******      " << endl;
                            cout << "Welcome " << studentProfile[enroll_no].get_name() << endl;
                            cout << "Choose an option" << endl;
                            cout << "1. Get your profile" << endl;
                            cout << "2. Work on Assignments" << endl;
                            cout << "3. Go Back" << endl;
                            cout << "4. Exit" << endl;
                            cout << "Enter 1/2/3/4" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            int r3;
                            cin >> r3;
                            if (r3 == 1)
                            {
                                studentProfile[enroll_no].displayProfile();
                            }
                            else if (r3 == 2)
                            {
                                int k;
                                k = 1;
                                cout << "     ******      *******      ******      " << endl;
                                for (auto i : studentProfile[enroll_no].get_assign())
                                {
                                    cout << k << ". " << i.get_name() << "\t" << i.get_status() << endl;
                                    k++;
                                }
                                cout << "     ******      *******      ******      " << endl;

                                while (true)
                                {
                                    cout << "     ******      *******      ******      " << endl;
                                    cout << "Choose an option" << endl;
                                    cout << "1. Send assignment for iteration" << endl;
                                    cout << "2. View remark" << endl;
                                    cout << "3. View Assignments" << endl;
                                    cout << "4. Go Back" << endl;
                                    cout << "5. Exit" << endl;
                                    cout << "Enter 1/2/3/4/5" << endl;
                                    cout << "     ******      *******      ******      " << endl;
                                    int r4;
                                    cin >> r4;

                                    if (r4 == 1)
                                    {
                                        cout << "Enter Assignment name" << endl;

                                        cin >> name;

                                        Student s = studentProfile[enroll_no];

                                        s.req_iterate(name);
                                        studentProfile[enroll_no] = s;
                                    }
                                    if (r4 == 2)
                                    {

                                        cout << "Enter Assignment name: ";
                                        cin >> name;
                                        Student s_ = studentProfile[enroll_no];
                                        s_.getRemark(name);
                                    }
                                    if (r4 == 3)
                                    {
                                        studentProfile[enroll_no].showAssignments();
                                    }
                                    if (r4 == 4)

                                        break;
                                    if (r4 == 5)
                                        return;
                                }
                            }

                            else if (r3 == 3)
                                break;
                            else if (r3 == 4)
                                return;
                        }

                        else
                        {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "INVALID ENROLLNO OR PASSWORD" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            break;
                        }
                    }
                }
                else if (r2 == 2)
                {
                    string enrl, pass;
                    cout << "Enrollment Number: ";
                    cin >> enrl;
                    cout << "Enter Password: ";
                    cin >> pass;
                    while (true)
                    {

                        if (ReviewerProfile[enrl].get_pass() == pass)
                        {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "Welcome " << ReviewerProfile[enrl].get_name() << endl;
                            cout << "Choose an option" << endl;
                            cout << "1. Get your profile" << endl;
                            cout << "2. See Assignments" << endl;
                            cout << "3. Upload Assignment" << endl;
                            cout << "4. Go Back" << endl;
                            cout << "5. Exit" << endl;
                            cout << "Enter 1/2/3/4/5" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            int r3;
                            cin >> r3;
                            if (r3 == 1)
                            {
                                ReviewerProfile[enrl].displayProfile();
                            }
                            else if (r3 == 2)
                            {
                                cout << "     ******      *******      ******      " << endl;
                                ReviewerProfile[enrl].showAssignments();
                                cout << "     ******      *******      ******      " << endl;

                                while (true)
                                {
                                    cout << "     ******      *******      ******      " << endl;
                                    cout << "Choose an option" << endl;
                                    cout << "1. Review Assignment" << endl;
                                    cout << "2. Go Back" << endl;
                                    cout << "3. Exit" << endl;
                                    cout << "Enter 1/2/3" << endl;
                                    cout << "     ******      *******      ******      " << endl;
                                    int r4;
                                    cin >> r4;
                                    if (r4 == 1)
                                    {

                                        cout << "     ******      *******      ******      " << endl;
                                        string n2;
                                        cout << "Enter Assignment name" << endl;
                                        cin >> n2;
                                        cout << "     ******      *******      ******      " << endl;
                                        cout << "This is the list of students with iteration request !! " << endl;
                                        cout << "Name" << "\t" << "\t" << "EnrollmentNo" << endl;
                                        for (auto i : studentProfile)
                                        {
                                            for (auto j : i.second.get_assign())
                                            {
                                                if (j.get_name() == n2 && j.get_iterationStatus())
                                                {

                                                    cout << i.second.get_name() << "\t" << "\t" << i.second.get_enroll_no() << endl;
                                                }
                                                // cout << j.get_name()<<"\t"<< n2 << "\t" << j.get_iterationStatus() << endl;
                                            }
                                        }

                                        while (true)
                                        {
                                            cout << "     ******      *******      ******      " << endl;
                                            cout << "Enter Enrollment no. of student to iterate" << endl;
                                            string enrl1;
                                            cin >> enrl1;
                                            cout << "     ******      *******      ******      " << endl;
                                            cout << "Choose an option" << endl;
                                            cout << "1. Mark as Complete" << endl;
                                            cout << "2. Give remark" << endl;
                                            cout << "3. Go Back" << endl;
                                            cout << "4. Exit" << endl;
                                            cout << "Enter 1/2/3/4" << endl;
                                            cout << "     ******      *******      ******      " << endl;
                                            int r7;
                                            cin >> r7;

                                            if (r7 == 1)
                                            {
                                                Reviewer r = ReviewerProfile[enrl];
                                                r.markCompleted(enrl1, n2);
                                                ReviewerProfile[enrl] = r;
                                            }
                                            if (r7 == 2)
                                            {
                                                string rmk;
                                                cout << "Enter remark" << endl;
                                                cin >> rmk;

                                                Reviewer r = ReviewerProfile[enrl1];
                                                r.suggestIteration(enrl1, n2, rmk);
                                                ReviewerProfile[enrl1] = r;
                                            }
                                            if (r7 == 3)
                                                break;

                                            if (r7 == 4)
                                                return;

                                            else
                                                break;
                                        }
                                    }

                                    else if (r4 == 2)
                                        break;

                                    else if (r4 == 3)
                                        return;

                                    else
                                        break;
                                }
                            }
                            else if (r3 == 3)
                            {
                                cout << "     ******      *******      ******      " << endl;
                                string n, c;
                                cout << "Enter Assignment Name: ";
                                cin >> n;
                                cout << "Enter Assignment Content: ";
                                cin >> c;
                                vector<string> v;
                                ReviewerProfile[enroll_no].uploadAssignment(n, c, v);
                                for (auto i : studentProfile)
                                {
                                    i.second.addAssgn(n, c);
                                    studentProfile[i.first] = i.second;
                                }
                                cout << "     ******      *******      ******      " << endl;
                            }
                            else if (r3 == 4)
                            {
                                break;
                            }
                            else if (r3 == 5)
                            {
                                return;
                            }
                        }
                        else
                        {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "INVALID ENROLLNO OR PASSWORD" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            break;
                        }
                    }
                }
                else if (r2 == 3)
                {
                    break;
                }
                else if (r2 == 4)
                {
                    return;
                }
            }
        }
        else if (r1 == 2)
        {

            while (true)
            {
                pg2_2();
                int r5;
                cin >> r5;
                if (r5 == 1)
                {
                    loginNewStu();
                }
                else if (r5 == 2)
                {
                    loginNewRev();
                }
                else if (r5 == 3)
                {
                    break;
                }
                else if (r5 == 4)
                {
                    return;
                }
            }
        }
        else if (r1 == 3)
        {
            break;
        }
        else if (r1 == 4)
        {
            return;
        }
    }
}
void loadStudents()
{
    ifstream fin("/member/student_database.txt");
    string line;
    while (getline(fin, line, '@'))
    {
        stringstream sts(line);
        string name, enroll_no, password, item;
        vector<Assignment> assignments;

        getline(sts, name, ',');
        getline(sts, enroll_no, ',');
        getline(sts, password, '{');

        Student s(name, enroll_no, password);

        string assignments_str;
        getline(sts, assignments_str, '}');
        stringstream sts_assignments(assignments_str);
        while (getline(sts_assignments, item, '+'))
        {
            if (item.empty())
                continue;
            stringstream sts_assignment(item);
            string assignment_name, content, status, iterationStatus, remark;
            vector<string> remarks;

            getline(sts_assignment, assignment_name, '|');
            getline(sts_assignment, content, '|');
            getline(sts_assignment, status, '|');
            getline(sts_assignment, iterationStatus, '|');
            while (getline(sts_assignment, remark, '|'))
            {
                remarks.push_back(remark);
            }
            bool iterStat = (iterationStatus == "1");
            Assignment a(assignment_name, content, remarks, status, iterStat);
            assignments.push_back(a);
        }

        s.load_assignments(assignments);
        studentProfile.insert(make_pair(enroll_no, s));
    }
    fin.close();
}

void loadReviewers()
{
    ifstream fin2("/member/reviewer_database.txt");
    string line2;
    while (getline(fin2, line2, '~'))
    {
        stringstream sts(line2);
        string name, enroll_no, password;

        getline(sts, name, ',');
        getline(sts, enroll_no, ',');
        getline(sts, password, '!');

        Reviewer r(name, enroll_no, password);
        ReviewerProfile.insert(make_pair(enroll_no, r));
    }
    fin2.close();
}

void loadAssignments()
{
    ifstream fin3("/member/tot_assignment.txt");
    if (fin3.is_open())
    {
        string line3;
        while (getline(fin3, line3, '~'))
        {
            stringstream sts(line3);
            string item;
            vector<string> assignment_details;

            while (getline(sts, item, '|'))
            {
                assignment_details.push_back(item);
            }

            if (!assignment_details.empty())
            {
                string name = assignment_details[0];
                string content = assignment_details[1];
                vector<string> remarks;

                Assignment assignment(name, content, remarks, "Pending", false);
                tot_assignments.push_back(assignment);
            }
        }
    }
    fin3.close();
}

void loadRecord()
{
    loadStudents();
    loadReviewers();
    loadAssignments();
}

void store()
{
    ofstream fout;
    fout.open("/member/student_database.txt");
    for (auto it : studentProfile)
    {
        Student s = it.second;
        fout << s.get_name() << ',';
        fout << s.get_enroll_no() << ',';
        fout << s.get_pass() << '{';

        for (auto i : s.get_assign())
        {
            fout << i.get_name() << '|';
            fout << i.get_content() << '|';
            fout << i.get_status() << '|';
            fout << i.get_iterationStatus() << '|';
            if (i.showRemark().size())
            {
                for (auto j : i.showRemark())
                {
                    fout << j << '|';
                }
                fout << '+';
            }
        }
        fout << '}';
    }
    fout.close();

    ofstream fout2;
    fout2.open("/member/reviewer_database.txt");
    for (auto it : ReviewerProfile)
    {
        Reviewer r = it.second;
        fout2 << r.get_name() << ',';
        fout2 << r.get_enroll_no() << ',';
        fout2 << r.get_pass() << '!';
        fout2 << '~';
    }

    fout2.close();

    ofstream fout3;
    fout3.open("/member/tot_assignment.txt");
    if (tot_assignments.size())
    {
        for (auto it : tot_assignments)
        {
            Assignment assig = it;
            fout3 << it.get_name() << '|' << it.get_content() << '|';
            fout3 << '~';
        }
    }
    fout3.close();
}

int main()
{
    loadRecord();
    review();
    store();
    return 0;
}
