#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


//get weighted sum
//apply weighted sum to sigmoid function
//


class log_reg{
    vector <float> x,t;
    float b,learning_rate,w;

    public:

    log_reg(){
        b=0;
        learning_rate=0.001;
        w=0;
    }

    float sigmoid(float z){
        return 1.0/(1.0+exp(-z));
    }

    void inp(vector<float>&x_inp,vector<float>&t_inp){
        x=x_inp;
        t=t_inp;
    }

    float prediction(float x,float w){
        float z = x*w + b;
        return sigmoid(z);
    }

    void gradiant_descent(){
        float dw=0,db=0;
        float n=t.size();

        for (int i =0;i<x.size();i++){
            float t_pred= prediction(x[i],w);
            float err=t_pred - t[i];
            
            dw+=err*x[i];
            db+=err;
        }

        w-=learning_rate*dw/n;
        b-=learning_rate*db/n;
    }

    void train(int epochs){
        for(int i=0;i<epochs;i++){
            gradiant_descent();
        }
    }

    float loss(){
            float loss = 0.0;
            int m = t.size();
            for (int i = 0; i < m; i++) {
                float t_pred = prediction(x[i],w);
                loss += -t[i] * log(t_pred) - (1 - t[i]) * log(1 - t_pred);
            }
            return loss / m;
    }

    void test_model(){
        for (int i = 0; i < x.size(); i++){
            float prob = prediction(x[i],w);
            int label = (prob >= 0.5) ? 1 : 0;
            cout << "Predicted: " << label << " (Probability: " << prob << ")" << endl;
        }
    }


};

log_reg L;

int main(){
    vector <float> x={45, 85, 50,  43,	89,	91,	60,	67,	30,	50};
    vector <float> t={45, 85, 50,  43,	89,	91,	60,	67,	30,	50};
    
    L.inp(x,t);
    L.train(1000);
    L.test_model();

    return 0;
}