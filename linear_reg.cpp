#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class reg{
    vector <float> x,y;
    float coeff,const_term,sum_xy,sum_x,sum_y,sum_x_sq,sum_y_sq;

public:

    reg() : coeff(0), const_term(0), sum_xy(0), sum_x(0), sum_y(0), sum_x_sq(0) {}

    void calculate_coeff(){
        float N = x.size();
        float num = ((N * sum_xy)-sum_x * sum_y);
        float den = ((N * sum_x_sq) - sum_x * sum_x);
        if (den==0){
            return;
        }
        coeff = num / den;
    }

    void calculate_const(){
           float N = x.size();
        float num = (sum_y * sum_x_sq - sum_x * sum_xy);
        float den = (N * sum_x_sq - sum_x * sum_x);
        if(den==0){
            return;
        }
        const_term = num / den;
    }

    void PrintBestFittingLine(){
        if (coeff == 0 && const_term == 0) {
            calculate_coeff();
            calculate_const();
        }
        cout << coeff << "x + " << const_term << endl;
    }

      float predict(float x){
        cout<<(coeff*x+const_term);
        return coeff * x + const_term;
    }

    float errorIn(float num){
        float closest_val=x[0];
        float min_dif=num-x[0];
        for (float val :x) {
            if((num-val) < min_dif){
                closest_val=val;
                min_dif=num-val;
            }
        }
        return predict(closest_val) - y[&closest_val - &x[0]];
    }

    void inp(vector<float>&x_inp,vector<float>&y_inp){
            x=x_inp;
            y=y_inp;

           for (int i = 0; i < x.size(); i++) {
            sum_xy += x[i] * y[i];
            sum_x += x[i];
            sum_y += y[i];
            sum_x_sq += x[i] * x[i];
            sum_y_sq += y[i] * y[i];
        }
    }
};


int main(){

    reg r;

    vector<float>x;
    vector<float>y;

    std::ifstream file("array.bin", std::ios::binary);
    std::vector<float> data((std::istreambuf_iterator<char>(file)), {});

   
    r.inp(y,x);
    r.PrintBestFittingLine();
    r.predict(10);
    return 0;
}