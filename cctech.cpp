#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Shape {
protected:
    static int count;
    int id;

public:
    Shape() {
        id = count;
        count++;
    }

    virtual void show() = 0;
    virtual Shape* copy() = 0;

    int getId() {
        return id;
    }

    virtual ~Shape() {}
};

int Shape::count = 1;


class Line : public Shape {
    double x1,y1,x2,y2;

public:
    Line(double a,double b,double c,double d) {
        x1=a; y1=b; x2=c; y2=d;
    }

    void show() {
        cout<<"Line ID "<<id<<" : ";
        cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    }

    Shape* copy() {
        return new Line(x1,y1,x2,y2);
    }
};


class Circle : public Shape {
    double x,y,r;

public:
    Circle(double a,double b,double c) {
        x=a; y=b; r=c;
    }

    void show() {
        cout<<"Circle ID "<<id<<" : ";
        cout<<"Center "<<x<<" "<<y<<" Radius "<<r<<endl;
    }

    Shape* copy() {
        return new Circle(x,y,r);
    }
};


class Text : public Shape {
    double x,y;
    string msg;

public:
    Text(double a,double b,string t) {
        x=a; y=b; msg=t;
    }

    void show() {
        cout<<"Text ID "<<id<<" : ";
        cout<<x<<" "<<y<<" -> "<<msg<<endl;
    }

    Shape* copy() {
        return new Text(x,y,msg);
    }
};


class Manager {
    vector<Shape*> arr;

public:
    void add(Shape* s) {
        arr.push_back(s);
    }

    void displayAll() {
        if(arr.size()==0) {
            cout<<"Nothing to display\n";
            return;
        }

        for(int i=0;i<arr.size();i++) {
            arr[i]->show();
        }
    }

    void remove(int id) {
        for(int i=0;i<arr.size();i++) {
            if(arr[i]->getId()==id) {
                delete arr[i];
                arr.erase(arr.begin()+i);
                cout<<"Removed\n";
                return;
            }
        }
        cout<<"ID not found\n";
    }

    void cloneObj(int id) {
        for(int i=0;i<arr.size();i++) {
            if(arr[i]->getId()==id) {
                arr.push_back(arr[i]->copy());
                cout<<"Cloned\n";
                return;
            }
        }
        cout<<"ID not found\n";
    }

    ~Manager() {
        for(int i=0;i<arr.size();i++) {
            delete arr[i];
        }
    }
};


int main() {

    Manager m;
    int ch;

    while(1) {

        cout<<"\n1 Line\n2 Circle\n3 Text\n4 Clone\n5 Delete\n6 List\n7 Exit\n";
        cout<<"Choice: ";
        cin>>ch;

        if(ch==1) {
            double a,b,c,d;
            cin>>a>>b>>c>>d;
            m.add(new Line(a,b,c,d));
        }
        else if(ch==2) {
            double a,b,c;
            cin>>a>>b>>c;
            m.add(new Circle(a,b,c));
        }
        else if(ch==3) {
            double a,b;
            string t;
            cin>>a>>b;
            cin.ignore();
            getline(cin,t);
            m.add(new Text(a,b,t));
        }
        else if(ch==4) {
            int id;
            cin>>id;
            m.cloneObj(id);
        }
        else if(ch==5) {
            int id;
            cin>>id;
            m.remove(id);
        }
        else if(ch==6) {
            m.displayAll();
        }
        else if(ch==7) {
            break;
        }
    }

    return 0;
}