#ifndef HELPER_H_
#define HELPER_H_
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

class Gate {
    protected:
        int OutputNumber;
        int stateCount=0;
        string Output_label_names[20];
        string gate_outputnames[100];
        int gate_outputvalues[100];
    public:
        string Input_label_names[20];
        int Input_label_values[20];
        string circuit_lines[20];
        int InputNumber;
        Gate();
        void read_circuit(int val); //Reads circuit.txt
        void read_input();          //Reads input.txt
        int total_input_line_count();   //Returns total state count
        virtual void gate_answ();       //Returns gate outputs
        virtual void output();          //Saves outputs to input.txt
};

class AND : public Gate {
    public:
        void gate_answ(int* values,int arr_size,string on,Gate* adr);
        void output(string* otp,int arr_size, Gate* x,int st);
};

class OR : public Gate {
    public:
        void gate_answ(int* values,int arr_size,string on,Gate* adr);
        void output(string* otp,int arr_size, Gate* x,int st);
};

class NOT : public Gate {
    public:
        void gate_answ(int* values,string on,Gate *adr);
        void output(string* otp,int arr_size, Gate* x,int st);
};

class FLIPFLOP : public Gate{
    public:
        int former_out=0;
        void gate_answ(int* values,string on,Gate *adr,FLIPFLOP *adr2);
        void output(string* otp,int arr_size, Gate* x,int st);
};

class DECODER : public Gate {
    public:
        void output(string* otp,string* decname, Gate* x, int st);
};

#endif
