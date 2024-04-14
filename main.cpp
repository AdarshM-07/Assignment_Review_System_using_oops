
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
    // virtual void add_data() = 0;
    // virtual void get_data() = 0;
    
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
    bool iterationStatus ;

public:
    
    Assignment(){};
    Assignment(string name, string content ,vector<string>&remark, string status = "Pending", bool iterationStatus = false)
    {
        this->name = name;
        this->content = content;
        this->status = status;
        this->iterationStatus = iterationStatus;
    }
    void get_assig_details()
    {
        cout << "Assignment Name: " << name << endl;
        cout << "Content: " << content << endl;
        // cout << "Assignment Status: " << status << endl;
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
    Student(string name, string enroll_no, string password)
    {
        this->name = name;
        this->enroll_no = enroll_no;
        this->password = password;
    }
    void addProfile()
    {
        string name;
        string enroll_no;
        string password;

        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        cin >> name;
        this->name = name;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enrollment Number: ";
        cin >> enroll_no;
        this->enroll_no = enroll_no;

        cout << "Enter Password: ";
        cin >> password;
        this->password = password;

        assignments = tot_assignments;
    }
    void displayProfile()
    {
        cout << "Name: " << name << endl;
        cout << "Enrollment No.: " << enroll_no << endl;
        cout << "Total assignments: " << assignments.size() << endl;
        int ctr = 0;
        for (auto it : assignments)
        {
            if (it.get_status() == "Pending")
            {
                ctr++;
            }
        }
        cout << "Pending assignments: " << ctr << endl;
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
        for (auto i : assignments)
        {
            if (i.get_name() == name)
            {
                i.update_status("Pending", true);
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
    // Method to get pending assignments
    void getPendingAssignments() const
    {
        cout << "Pending assignments for student " << name << ":" << endl;
        for (auto assignment : assignments)
        {
            if (assignment.get_status() == "Pending")
                cout << "- " << assignment.get_name() << endl;
        }
    }
    void load_assignments(vector<Assignment> assignments)
    {
        this->assignments = assignments;
    }
};
map<string, Student> studentProfile;
// Class representing a Reviewer, inheriting from IMG_Member
class Reviewer : public IMG_Member
{
private:
    string password;

public:
    Reviewer(){};
    Reviewer(string name, string enroll_no, string password)
    {
        this->name = name;
        this->enroll_no = enroll_no;
        this->password = password;
    }
    void addProfile()
    {
        string name;
        string enroll_no;
        string password;

        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Name: ";
        cin >> name;
        this->name = name;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');


        cout << "Enrollment Number: ";
        cin >> enroll_no;
        this->enroll_no = enroll_no;

        cout << "Enter Password: ";
        cin >> password;
        this->password = password;
    }
    void displayProfile()
    {
        cout << "Reviewer Profile:" << endl;
        cout << "Name: " << name << endl;
        cout << "Enrollment Number:: " << enroll_no << endl;
    }
    void showAssignments()
    {
        int k = 1;
        for (auto i : tot_assignments)
        {
            cout << "Assignment"
                 << " " << k << endl;
            i.get_assig_details();
        }
    }
    string get_pass()
    {
        return password;
    }

    void uploadAssignment(string name, string content,vector<string>&remark)
    {
        tot_assignments.push_back(Assignment(name, content ,remark,"Pending",false));
    }

    // Method to suggest iteration
    void suggestIteration(string enroll_no, string name, string remark)
    {
        for (auto i : studentProfile)
        {
            if (i.first == enroll_no)
            {
                for (auto j : i.second.get_assign())
                {
                    if (j.get_name() == name)
                    {
                        j.assignRemark(remark);
                        j.update_status("Pending", false);
                    }
                }
            }
        }
    }
    void markCompleted(string enroll_no, string name)
    {
        for (auto i : studentProfile)
        {
            if (i.first == enroll_no)
            {
                for (auto j : i.second.get_assign())
                {
                    if (j.get_name() == name)
                    {
                        j.update_status("Completed", false);
                    }
                }
            }
        }
    }
};


map<string, Reviewer> ReviewerProfile;

void loginNewStu()
{
    string name;
    string enroll_no;
    string password;

    cout << "Name: "<<endl;
    cin >> name;

    cout << "Enrollment Number: "<<endl;
    cin >> enroll_no;

    cout << "Enter Password: "<<endl;
    cin >> password;
    Student s(name, enroll_no, password);
    studentProfile[enroll_no] = s;
}
void loginNewRev()
{
    string name;
    string enroll_no;
    string password;

    cout << "Name: "<<endl;
    cin >> name;

    cout << "Enrollment Number: "<<endl;
    cin >> enroll_no;

    cout << "Enter Password: "<<endl;
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

void review() {
    while (true) {
        pg1();
        int r1;
        cin >> r1;
        if (r1 == 1) {
            while (true) {
                pg2_1();
                int r2;
                cin >> r2;
                string enroll_no;
                string password;
                string name;
                string content;
                string remark;
                vector<string>v;
                
                if (r2 == 1) {

                    while (true) {
                        cout << "Enrollment Number: "<<endl;
                        cin >> enroll_no;
                        cout << "Enter Password: "<<endl;
                        cin >> password;
                        if (password == studentProfile[enroll_no].get_pass()) {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "Welcome " << studentProfile[enroll_no].get_name() << endl;
                            cout << "What do you want to do ?" << endl;
                            cout << "1. Get your profile" << endl;
                            cout << "2. Work on Assignments" << endl;
                            cout << "3. Go Back" << endl;
                            cout << "4. Exit" << endl;
                            cout << "Enter 1/2/3/4" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            int r3;
                            cin >> r3;
                            if (r3 == 1) {
                                studentProfile[enroll_no].displayProfile();
                            } 
                            else if (r3 == 2) {
                                int k;
                                k = 1;
                                cout << "     ******      *******      ******      " << endl;
                                for (auto i : studentProfile[enroll_no].get_assign()) {
                                    cout << k << ". " << i.get_name() << "\t" << i.get_status() << endl;
                                }
                                cout << "     ******      *******      ******      " << endl;
                                
                                while (true) {
                                    cout << "     ******      *******      ******      " << endl;
                                    cout << "What do you want to do ?" << endl;
                                    cout << "1. Send assignment for iteration" << endl;
                                    cout << "2. View remark" << endl;
                                    cout << "3. Go Back" << endl;
                                    cout << "4. Exit" << endl;
                                    cout << "Enter 1/2/3/4" << endl;
                                    cout << "     ******      *******      ******      " << endl;
                                    int r4;
                                    cin >> r4;
                                  
                                    if(r4==1){
                                        cout << "Enter Assignment name" << endl;
                                        cin >> name;
                                        studentProfile[enroll_no].req_iterate(name);
                                       }
                                    if(r4==2){
                                        cout << "Enter Assignment name" << endl;
                                        cin >> name;
                                        studentProfile[enroll_no].getRemark(name);
                                       }
                                    if(r4==3)
                                       
                                        break;
                                    if(r4==4)
                                        return;
                                        
                                   
                                    }
                                }
                            
                             else if (r3 == 3) 
                                break;
                             else if (r3 == 4) 
                                return;
                            }

                         else {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "INVALID ENROLLNO OR PASSWORD" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            return;
                        }
                    }
                }
                else if (r2 == 2) {
                    while (true) {
                        cout << "Enrollment Number: "<<endl;;
                        cin >> enroll_no;
                        cout << "Enter Password: "<<endl;
                        cin >> password;
                        if (password == ReviewerProfile[enroll_no].get_pass()) {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "Welcome " << ReviewerProfile[enroll_no].get_name() << endl;
                            cout << "What do you want to do ?" << endl;
                            cout << "1. Get your profile" << endl;
                            cout << "2. See Assignments" << endl;
                            cout << "3. Upload Assignment" << endl;
                            cout << "4. Go Back" << endl;
                            cout << "5. Exit" << endl;
                            cout << "Enter 1/2/3/4/5" << endl;
                            cout << "     ******      *******      ******      " << endl;
                            int r3;
                            cin >> r3;
                            if (r3 == 1) {
                                ReviewerProfile[enroll_no].displayProfile();
                            } 
                            else if (r3 == 2) {
                                cout << "     ******      *******      ******      " << endl;
                                ReviewerProfile[enroll_no].showAssignments();
                                cout << "     ******      *******      ******      " << endl;
                                
                                while (true) {
                                    cout << "     ******      *******      ******      " << endl;
                                    cout << "What do you want to do ?" << endl;
                                    cout << "1. Review Assignment" << endl;
                                    cout << "2. Go Back" << endl;
                                    cout << "3. Exit" << endl;
                                    cout << "Enter 1/2/3" << endl;
                                    cout << "     ******      *******      ******      " << endl;
                                    int r4;
                                    cin >> r4;
                                    if(r4==1) {
                                    
                                        cout << "     ******      *******      ******      " << endl;
                                        cout << "Enter Assignment name" << endl;
                                        cin >> name;
                                        cout << "     ******      *******      ******      " << endl;
                                        cout << "This is the list of students with iteration request" << endl;
                                        for (auto i : studentProfile) {
                                            for (auto j : i.second.get_assign()) {
                                                if (j.get_name() == name && j.get_iterationStatus()) {
                                                    cout << i.second.get_name() << "\t" << i.second.get_enroll_no() << endl;
                                                }
                                            }
                                        }
                                        
                                        while (true) {
                                            cout << "     ******      *******      ******      " << endl;
                                            break;
                                            cout << "Enter Enrollment no. of student to iterate" << endl;
                                            cin >> enroll_no;
                                            cout << "     ******      *******      ******      " << endl;
                                            cout << "1. Mark as Complete" << endl;
                                            cout << "2. Give remark" << endl;
                                            cout << "3. Go Back" << endl;
                                            cout << "4. Exit" << endl;
                                            cout << "Enter 1/2/3/4" << endl;
                                            int r7;
                                            cin >> r7;
                                            
                                            if(r7==1) 
                                                ReviewerProfile[enroll_no].markCompleted(enroll_no, name);
                                                
                                            if(r7==2) {
                                                cout << "Enter remark" << endl;
                                                cin >> remark;
                                                ReviewerProfile[enroll_no].suggestIteration(enroll_no, name, remark);
                                                }
                                            if(r7==3) 
                                                break;
                                                
                                            if(r7==4) 
                                                return;
                                               
                                            else
                                                break;
                                            }
                                        }
                                    
                                        
                                    else if(r4==2)
                                        break;
                                        
                                    else if(r4==3)
                                        return;
                                       
                                    else 
                                        break;
                                    
                                }

                            }
                             else if (r3 == 3) {
                                cout << "     ******      *******      ******      " << endl;
                                cout << "Enter Assignment Name" << endl;
                                cin >> name;
                                cout << "Enter Assignment Content" << endl;
                                cin >> content;
                                ReviewerProfile[enroll_no].uploadAssignment(name, content,v);
                                cout << "     ******      *******      ******      " << endl;
                            } else if (r3 == 4) {
                               break;
                            } else if (r3 == 5) {
                                return;
                            }
                        }
                         else {
                            cout << "     ******      *******      ******      " << endl;
                            cout << "INVALID ENROLLNO OR PASSWORD" << endl;
                            cout << "     ******      *******      ******      " << endl;
                        }
                    }
                } else if (r2 == 3) {
                    break;
                } else if (r2 == 4) {
                    return;
                }
            }
        } else if (r1 == 2) {
            
            while (true) {
                pg2_2();
                int r5;
                cin >> r5;
                if (r5 == 1) {
                    loginNewStu();
                } else if (r5 == 2) {
                    loginNewRev();
                } else if (r5 == 3) {
                    break;
                } else if (r5 == 4) {
                    return;
                }
            }
        } else if (r1 == 3) {
            break;
        } else if (r1 == 4) {
            return;
        }
    }
}


void store()
{
    ofstream fout;
    fout.open("student_database.txt");
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
            for(auto j : i.showRemark()){
                fout << j << '|';
            }
            fout << "-~";
        }
        fout << '}';
    }
    fout.close();

    ofstream fout2;
    fout2.open("reviewer_database.txt");
    for (auto it : ReviewerProfile)
    {
        Reviewer r = it.second;
        fout2 << r.get_name() << ',';
        fout2 << r.get_enroll_no() << ',';
        fout2 << r.get_pass() << '{';
        fout2 << '}';
    }
    fout2.close();

    ofstream fout3;
    fout3.open("tot_assignment.txt");
    for (auto it : tot_assignments)
    {
        Assignment assig = it;
        fout3 << it.get_name() << '|' << it.get_content() << '|';
        fout3 << '~';
    }
    fout3.close();
}


void loadStudents() {
    ifstream fin("Student_database.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string name, enroll_no, password, item;
        vector<Assignment> assignments;

        getline(ss, name, ',');
        getline(ss, enroll_no, ',');
        getline(ss, password, '{');

        Student s(name, enroll_no, password);

        string assignments_str;
        getline(ss, assignments_str, '}');
        stringstream ss_assignments(assignments_str);
        while (getline(ss_assignments, item, '~')) {
            if (item.empty())
                continue;
            stringstream ss_assignment(item);
            string assignment_name, content, status, iterationStatus, remark;
            vector<string> remarks;

            getline(ss_assignment, assignment_name, '|');
            getline(ss_assignment, content, '|');
            getline(ss_assignment, status, '|');
            getline(ss_assignment, iterationStatus, '|');
            while (getline(ss_assignment, remark, '-')) {
                remarks.push_back(remark);
            }
            bool iterStat = (iterationStatus == "true");
            Assignment a(assignment_name, content,remarks, status,  iterStat);
            assignments.push_back(a);
        }

        s.load_assignments(assignments);
        studentProfile.insert(make_pair(enroll_no, s));
    }
    fin.close();
}

void loadReviewers() {
    ifstream fin2("Reviewer_database.txt");
    string line2;
    while (getline(fin2, line2)) {
        stringstream ss(line2);
        string name, enroll_no, password, item;

        getline(ss, name, ',');
        getline(ss, enroll_no, ',');
        getline(ss, password, '{');

        Reviewer r(name, enroll_no, password);
        ReviewerProfile.insert(make_pair(enroll_no, r));
    }
    fin2.close();
}

void loadAssignments() {
    ifstream fin3("tot_assignment.txt");
    if (fin3.is_open()) {
        string line3;
        while (getline(fin3, line3)) {
            stringstream ss(line3);
            string item;
            vector<string> assignment_details;

            while (getline(ss, item, '|')) {
                assignment_details.push_back(item);
            }

            if (!assignment_details.empty()) {
                string name = assignment_details[0];
                string content = assignment_details[1];
                vector<string> remarks;

                Assignment assignment(name, content,remarks, "Pending",  false);
                tot_assignments.push_back(assignment);
            }
        }
    }
    fin3.close();
}

void load() {
    loadStudents();
    loadReviewers();
    loadAssignments();
}

int main()
{
    #ifndef ONLINE_JUDGE
    clock_t T = clock();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false), cout.tie(NULL), cin.tie(NULL);
load();
review();
store();
    return 0;
}

