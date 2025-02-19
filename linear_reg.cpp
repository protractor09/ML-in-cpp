#include <iostream>
#include <vector>
#include <fstream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
using namespace std;
using namespace py = pybind11;
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

reg r;

// Function to take input in two float vectors and pass it to the inp method 
py::array_t<float> take_inp(py::array_t<float> arr1, py::array_t<float> arr2) {
    auto buf1 = arr1.request(), buf2 = arr2.request();

    vector<float>x;
    vector<float>y;

    if (buf1.size != buf2.size) {
        throw std::runtime_error("Arrays must be the same size!");
    }

    float* ptr1 = (float*)buf1.ptr;
    float* ptr2 = (float*)buf2.ptr;
    
    // Create an output array of the same size
    py::array_t<float> result(buf1.size);
    float* ptr_res = (float*)result.request().ptr;

    for (ssize_t i = 0; i < buf1.size; i++) {
        x.push_back(ptr1[i]);  
        y.push_back(ptr2[i]);
    }

    r.inp(x,y);
    return;
}

// Expose the function to Python
PYBIND11_MODULE(my_module, m) {
    m.def(&take_inp);
}


int main(){
    r.PrintBestFittingLine();
    return 0;
}