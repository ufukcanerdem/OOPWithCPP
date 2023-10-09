#include<iostream>
#include<string>
#include"helper.h"

using namespace std;

Gate::Gate() {}

void Gate::read_circuit(int val) {
    stateCount=val;
    ifstream _cir;
    _cir.open("circuit.txt");
    string inp;
    int count=0;
    int input_count=0;
    int output_count=0;

    while( count == 0 && !(_cir.eof()) ) {
        getline(_cir, inp);
        count++;
        if( count == 1 ) {
            istringstream lbl(inp);
            string lblnm;
            
            while(lbl >> lblnm) {
                if( lblnm != "INPUT" ) {
                    Input_label_names[input_count]=lblnm;
                    input_count++;
                }
            }
        }
    }

    while( count == 1 && !(_cir.eof()) ) {
        getline(_cir, inp);
        count++;
        if( count == 2 ) {
            istringstream lbl(inp);
            string lblnm;
            
            while(lbl >> lblnm) {
                if( lblnm != "OUTPUT" ) {
                    Output_label_names[output_count]=lblnm;
                    output_count++;
                }
            }
        }
    }

    InputNumber=input_count;
    OutputNumber=output_count;

    int temp_count=0;

    while( !(_cir.eof()) ) {
        getline(_cir, inp);
        circuit_lines[temp_count]=inp;
        temp_count++;
    }
    _cir.close();
}

void Gate::read_input() {
    int count=0;
    int input_count=0;
    ifstream _inpt;
    _inpt.open("input.txt");

    string inp;
    for(int i=0 ; i < stateCount ; i++ ) {
        getline(_inpt, inp);
    }
    while( count < 1) {
        count++;    
        getline(_inpt, inp);
        istringstream lbl(inp);
        string lblnm;    
            while(lbl >> lblnm) {
                    Input_label_values[input_count]=stoi(lblnm);
                    input_count++;
            }
    }
    _inpt.close();
}

void Gate::output(){}
void Gate::gate_answ(){
}

int Gate::total_input_line_count() {
    ifstream _inpt;
    string inp;
    _inpt.open("input.txt");
    int count=0;
    while(getline(_inpt,inp)) {
        count++;
    }
    _inpt.close();
    return count;
}


void AND::gate_answ(int* values, int arr_size,string on,Gate *adr){
    int temp_answ=1;
    for(int i=0 ; i<arr_size ; i++) {
        temp_answ*=values[i];
    }
    int k=0;
    while(1) {
        if(adr->Input_label_names[k].empty() ) {
            adr->Input_label_values[k]=temp_answ;
            adr->Input_label_names[k]=on;
            break;
        }
        k++;
    }
    adr->InputNumber++;
}

void AND::output(string* otp,int arr_size, Gate* x,int st) {
    int k=0;
    while(1) {
        if(x->Input_label_names[k].empty() ) {
            break;
        }
        k++;
    }
    otp[st]=to_string(x->Input_label_values[k-1]);
}

void OR::gate_answ(int* values, int arr_size,string on,Gate *adr){
    int temp_answ=0;
    for(int i=0 ; i<arr_size ; i++) {
        if(values[i] == 1) {
            temp_answ=1;
            break;
        }
    }
    int k=0;
    while(1) {
        if(adr->Input_label_names[k].empty() ) {
            adr->Input_label_values[k]=temp_answ;
            adr->Input_label_names[k]=on;
            break;
        }
        k++;
    }
    adr->InputNumber++;
}

void OR::output(string* otp,int arr_size, Gate* x,int st) {
    int k=0;
    while(1) {
        if(x->Input_label_names[k].empty() ) {
            break;
        }
        k++;
    }
    otp[st]=to_string(x->Input_label_values[k-1]);
}

void NOT::gate_answ(int* values,string on,Gate *adr) {
    int temp_answ=0;
    if(values[0] == 1) {
        temp_answ=0;
    }
    else if(values[0] == 0) {
        temp_answ=1;
    }
    int k=0;
    while(1) {
        if(adr->Input_label_names[k].empty() ) {
            adr->Input_label_values[k]=temp_answ;
            adr->Input_label_names[k]=on;
            break;
        }
        k++;
    }
    adr->InputNumber++;
}

void NOT::output(string* otp,int arr_size, Gate* x,int st) {
    int k=0;
    while(1) {
        if(x->Input_label_names[k].empty() ) {
            break;
        }
        k++;
    }
    otp[st]=to_string(x->Input_label_values[k-1]);
}

void FLIPFLOP::gate_answ(int* values,string on,Gate *adr, FLIPFLOP *adr2) {
    int temp_answ=0;
    
    if(former_out == 0) {
        if(values[0] == 0 ){
            temp_answ=0;
        }
        else if(values[0] == 1) {
            temp_answ=1;
        }
    }

    else if(former_out == 1) {
        if(values[0] == 0 ){
            temp_answ=1;
        }
        else if(values[0] == 1) {
            temp_answ=0;
        }
    }

    int k=0;
    while(1) {
        if(adr->Input_label_names[k].empty() ) {
            adr->Input_label_values[k]=temp_answ;
            adr->Input_label_names[k]=on;
            break;
        }
        k++;
    }
    adr->InputNumber++;
    adr2->former_out=temp_answ;
}

void FLIPFLOP::output(string* otp,int arr_size, Gate* x,int st) {
    int k=0;
    while(1) {
        if(x->Input_label_names[k].empty() ) {
            break;
        }
        k++;
    }
    otp[st]=to_string(x->Input_label_values[k-1]);
}



void DECODER::output(string* otp,string* decname, Gate* x, int st) {
    int k=0;
    int xvals[2];
    while(!(x->Input_label_names[k].empty()) ) {
        if(x->Input_label_names[k] == decname[0]) {
            xvals[0] = x->Input_label_values[k];
        }
        if(x->Input_label_names[k] == decname[1]) {
            xvals[1] = x->Input_label_values[k];
        }
        k++;
    }
    
    if( xvals[0] == 0 && xvals[1] == 0 ) {
        otp[st] = "1000";
    }

    else if( xvals[0] == 0 && xvals[1] == 1 ) {
        otp[st] = "0100";
    }

    else if( xvals[0] == 1 && xvals[1] == 0 ) {
        otp[st] = "0010";
    }

    else if( xvals[0] == 1 && xvals[1] == 1 ) {
        otp[st] = "0001";
    }
}