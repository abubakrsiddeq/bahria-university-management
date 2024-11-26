#include <iostream>
#include <string>
#include <iomanip>

// Using standard namespace
using namespace std;

// Engine class
class Engine {
private:
    int PowerInCC;
    string fuel_type;
    float torque;

public:
    Engine(int InCC, string f_tp, float t) : PowerInCC(InCC), fuel_type(f_tp), torque(t) {}

    void start() {
        cout << "Engine Started." << endl;
    }

    void stop() {
        cout << "Engine Stopped." << endl;
    }

    void fuelInjection() {
        cout << "Fuel is being injected in the Engine." << endl;
    }
};

// GearBox class
class GearBox {
private:
    int Gear_count;
    string type;

public:
    GearBox(int count, string t) : Gear_count(count), type(t) {}

    void Shift_gear(int gear) {
        cout << "Gear shifted to " << gear << endl;
    }

    void Engage_clutch() {
        cout << "Clutch engaged." << endl;
    }
};

// SteeringBox class
class steering_box {
private:
    string sensitivity_level;
    string steering_type;

public:
    steering_box(string s_lvl, string s_tp) : sensitivity_level(s_lvl), steering_type(s_tp) {}

    void turn_left() {
        cout << "Turning to left." << endl;
    }

    void turn_right() {
        cout << "Turning to right." << endl;
    }

    void adjust_sensitivitylvl() {
        cout << "Sensitivity level adjusted to " << sensitivity_level << endl;
    }
};

// Body class
class Body {
private:
    string color;
    string material;
    string dimension;

public:
    Body(string c, string m, string d) : color(c), material(m), dimension(d) {}

    void paint(string new_color) {
        color = new_color;
        cout << "Car is painted to " << color << "." << endl;
    }

    void repair() {
        cout << "Car body is repaired." << endl;
    }
};

// Wheel class
class Wheel {
private:
    int size;
    string type;
    int pressure_lvl;

public:
    Wheel(int s, string t, int p_level) : size(s), type(t), pressure_lvl(p_level) {}

    void rotate() {
        cout << "Wheel is rotating." << endl;
    }

    void inflate(int pressure) {
        pressure_lvl = pressure;
        cout << "Pressure level inflated to " << pressure_lvl << " PSI." << endl;
    }

    void replace() {
        cout << "Wheel replaced." << endl;
    }
};

// Car class
class Car {
private:
    Engine hybrd_engine;
    GearBox gearbox;
    steering_box s_box;
    Body body;
    Wheel wheel;

public:
    Car(Engine eng, GearBox gb, steering_box sb, Body b, Wheel w)
        : hybrd_engine(eng), gearbox(gb), s_box(sb), body(b), wheel(w) {}

    void drive() {
        cout << "\n======== Driving the Car ========" << endl;
        hybrd_engine.start();
        gearbox.Shift_gear(1);
        s_box.turn_left();
        wheel.rotate();
        gearbox.Shift_gear(2);
        s_box.turn_right();
        cout << "=================================" << endl;
    }

    void stop() {
        cout << "\n======== Stopping the Car ========" << endl;
        wheel.replace();
        hybrd_engine.stop();
        cout << "==================================" << endl;
    }

    Body& getBody() { return body; } // Provide access to Body
    Wheel& getWheel() { return wheel; } // Provide access to Wheel
};

// Main function
int main() {
    Engine hybrd_engine(2000, "Petrol", 300.0);
    GearBox gearbox(6, "Manual");
    steering_box s_box("High", "Power Steering");
    Body body("Red", "Steel", "4m x 1.8m x 1.4m");
    Wheel wheel(18, "Alloy", 32);

    Car myCar(hybrd_engine, gearbox, s_box, body, wheel);

    // Demonstrate Car functionalities
    myCar.drive();
    myCar.stop();
    myCar.getBody().paint("Blue");
    myCar.getWheel().inflate(34);

    return 0;
}
