#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CAD {
protected:
    static int nextId;
    int id;

public:
    CAD() {
        id = nextId++;
    }

    virtual ~CAD() {}

    int getId() const {
        return id;
    }

    virtual void display() = 0;
    virtual CAD* clone() = 0;
};

int CAD::nextId = 1;

class Line: public CAD {
    double x1, y1, x2, y2;

public:
    Line(double a, double b, double c, double d) {
        x1 = a; y1 = b; x2 = c; y2 = d;
    }

    void display() override {
        cout << "LINE ID: " << id << " "
             << x1 << " " << y1 << " "
             << x2 << " " << y2 << endl;
    }

    CAD* clone() override {
        return new Line(x1, y1, x2, y2);
    }
};

class Circle : public CAD {
    double x, y, r;

public:
    Circle(double a, double b, double c) {
        x = a; y = b; r = c;
    }

    void display() override {
        cout << "CIRCLE ID: " << id << " "
             << x << " " << y
             << " Radius: " << r << endl;
    }

    CAD* clone() override {
        return new Circle(x, y, r);
    }
};

class Text : public CAD {
    double x, y;
    string content;

public:
    Text(double a, double b, string t) {
        x = a; y = b; content = t;
    }

    void display() override {
        cout << "TEXT ID: " << id << " "
             << x << " " << y
             << " \"" << content << "\"" << endl;
    }

    CAD* clone() override {
        return new Text(x, y, content);
    }
};

class Document {
    vector<CAD*> objects;

public:
    void addObject(CAD* obj) {
        objects.push_back(obj);
    }

    void listObjects() {
        if (objects.empty()) {
            cout << "No objects found.\n";
            return;
        }

        for (auto obj : objects) {
            obj->display();
        }
    }

    void deleteObject(int id) {
        for (int i = 0; i < objects.size(); i++) {
            if (objects[i]->getId() == id) {
                delete objects[i];
                objects.erase(objects.begin() + i);
                cout << "Deleted successfully.\n";
                return;
            }
        }
        cout << "Object not found.\n";
    }

    void cloneObject(int id) {
        for (auto obj : objects) {
            if (obj->getId() == id) {
                objects.push_back(obj->clone());
                cout << "Cloned successfully.\n";
                return;
            }
        }
        cout << "Object not found.\n";
    }

    ~Document() {
        for (auto obj : objects)
            delete obj;
    }
};


int main() {
    Document doc;
    int choice;

    while (true) {
        cout << "\nDetails\n";
        cout << "1. Add Line\n";
        cout << "2. Add Circle\n";
        cout << "3. Add Text\n";

        cout << "4. Clone Object\n";
        cout << "5. Delete Object\n";
        cout << "6. List Objects\n";

        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            double x1, y1, x2, y2;
            cout << "Enter x1 y1 x2 y2: ";
            cin >> x1 >> y1 >> x2 >> y2;
            doc.addObject(new Line(x1, y1, x2, y2));
        }
        else if (choice == 2) {
            double x, y, r;
            cout << "Enter center x y radius: ";
            cin >> x >> y >> r;
            doc.addObject(new Circle(x, y, r));
        }
        else if (choice == 3) {
            double x, y;
            string text;
            cout << "Enter x y: ";
            cin >> x >> y;
            cin.ignore();
            cout << "Enter text: ";
            getline(cin, text);
            doc.addObject(new Text(x, y, text));
        }
        else if (choice == 4) {
            int id;
            cout << "Enter ID to clone: ";
            cin >> id;
            doc.cloneObject(id);
        }
        else if (choice == 5) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            doc.deleteObject(id);
        }
        else if (choice == 6) {
            doc.listObjects();
        }
        else if (choice == 7) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}