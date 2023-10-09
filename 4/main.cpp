#include <iostream>
#include"helper.h"

using namespace std;

int main() {
    int st=0;
    Gate *tmp = new Gate;
    string* outputvalues = new string[tmp->total_input_line_count()];
    while(st < tmp->total_input_line_count() ) {
        int i=0;
        Gate *x = new Gate;
        x->read_circuit(st);
        x->read_input();

        AND *tmp1 = new AND;
        OR *tmp2 = new OR;
        NOT *tmp3 = new NOT;
        FLIPFLOP *tmp4 = new FLIPFLOP;
        DECODER *tmp5 = new DECODER;

        int line=0;
        int line_count=0;

        while(1) {
            if( !(x->circuit_lines[line].empty()) ) {
                line++;
            } 
            else {
                break;
            }
        }

        int arr_size=0;
        while(!(x->circuit_lines[i].empty())) {
            line_count++;
            string temp_gatename, temp_outputname;
    
            int* temp_values = new int[10];
            arr_size=0;
        
            istringstream lbl(x->circuit_lines[i]);
            string lblnm;
            lbl >> lblnm;
            temp_gatename=lblnm;
            if(temp_gatename=="DECODER") {
                for(int l=0;l<4;l++) {
                    lbl >> lblnm;
                }
                string* decoder_names=new string[2];
                lbl >> lblnm;
                decoder_names[0]=lblnm;
                lbl >> lblnm;
                decoder_names[1]=lblnm;
                tmp5->output(outputvalues,decoder_names,x,st);
            }
            else{
                lbl >> lblnm;
                temp_outputname=lblnm;
                while( lbl >> lblnm ) {
                    for(int j=0 ; j< x->InputNumber ; j++ ) {
                        if( lblnm == x->Input_label_names[j] ) {
                            temp_values[arr_size]=x->Input_label_values[j];
                            arr_size++;
                        }
                    }
                }
        
                if(temp_gatename=="AND") {
                    tmp1->gate_answ(temp_values,arr_size,temp_outputname,x);
                }
                if(temp_gatename=="OR") {
                    tmp2->gate_answ(temp_values,arr_size,temp_outputname,x);
                }
                if(temp_gatename=="NOT") {
                    tmp3->gate_answ(temp_values,temp_outputname,x);
                }
                if(temp_gatename=="FLIPFLOP") {
                    tmp4->gate_answ(temp_values,temp_outputname,x,tmp4);
                }
                
                if(line_count==line) {
                    if(temp_gatename=="AND") {
                        tmp1->output(outputvalues,arr_size,x,st);
                    }
                    if(temp_gatename=="OR") {
                        tmp2->output(outputvalues,arr_size,x,st);
                    }
                    if(temp_gatename=="NOT") {
                        tmp3->output(outputvalues,arr_size,x,st);
                    }
                    if(temp_gatename=="FLIPFLOP") {
                        tmp4->output(outputvalues,arr_size,x,st);
                    }
                }
            }
            i++;
            delete temp_values;
        }
        st++;
    }

    ofstream _out("input.txt");
    for(int k=0 ; k<st ; k++) {
        for(int l=0 ; l<outputvalues[k].size() ; l++ ) {
            _out << outputvalues[k][l] << " " ;
        }
        _out << "\n";
    }
    _out.close();
    
    return 0;
}