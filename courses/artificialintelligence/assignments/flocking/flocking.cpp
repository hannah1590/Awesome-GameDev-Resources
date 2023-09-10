#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

pair<float, float> operator+(const pair<float,float> & left, const pair<float,float> & right)
{
    return make_pair(left.first + right.first, left.second + right.second);
}
pair<float, float> operator-(const pair<float,float> & left, const pair<float,float> & right)
{
    return make_pair(left.first - right.first, left.second - right.second);
}
pair<float, float> operator/(const pair<float,float> & left, const float right)
{
    return make_pair(left.first / right, left.second / right);
}
pair<float, float> operator*(const pair<float,float> & left, const float right)
{
    return make_pair(left.first * right, left.second * right);
}

class agent
{
public:
    agent() = default;
    agent(float x, float y, float vx, float vy)
    {
        pos.first = x;
        pos.second = y;

        vel.first = vx;
        vel.second = vy;
    }

    pair<float, float> getPos(){ return pos; }
    pair<float, float> getVel(){ return vel; }

    void setForceCenter(pair<float,float> fC) { forceCenter = fC; }
    void setForceSeparate(pair<float,float> fS) { forceSeparate = fS; }
    void setForceAlign(pair<float,float> fA) { forceAlign = fA; }

    pair<float,float> getForce(float kC, float kS, float kA)
    {
        return (forceCenter * kC) + (forceSeparate * kS) + (forceAlign * kA);
    }

    pair<float,float> getNewVel(float t, float kC, float kS, float kA)
    {
        vel = vel + (getForce(kC, kS, kA) * t);
        return vel;
    }

    pair<float,float> getNewPos(float t, pair<float,float> newVel)
    {
        pos = pos + (newVel * t);
        return pos;
    }
private:
    pair<float, float> pos;
    pair<float, float> vel;
    pair<float, float> forceCenter;
    pair<float, float> forceSeparate;
    pair<float, float> forceAlign;
};

int main(){

    float rC;    // cohesion radius
    float rS;    // separation radius
    float fSMax; // max separation force
    float rA;    // alignment radius
    float kC;    // cohesion constant
    float kS;    // separation constant
    float kA;    // alignment constant
    float n;     // number of agents

    float x;     // x coord
    float y;     // y coord
    float vx;    // x vel
    float vy;    // y vel
    float t;     // time

    pair<float, float> pCM;  // pos of center of mass
    pair<float, float> fC;   // force moving agent to center of mass in cohesion radius
    pair<float, float> fS;   // force moving agent from other agents in separation radius
    pair<float, float> vAvg; // avg vel of the agents
    pair<float, float> fA;   // force aligning agents with the avg vel of the group

    cin >> rC >> rS >> fSMax >> rA >> kC >> kS >> kA >> n;

    auto* agents = new agent[(int)n];

    for(int i = 0; (float)i < n; i++)
    {
        cin >> x >> y >> vx >> vy;
        agents[i] = agent(x,y,vx,vy);
    }

    while(!cin.eof()) {
        cin >> t;
        pCM = make_pair(0.0f,0.0f);
        vAvg = make_pair(0.0f,0.0f);

        for(int i = 0; (float)i < n; i++)
        {
            pCM = pCM + agents[i].getPos(); // adding agents pos to pos of center mass
            vAvg = vAvg + agents[i].getVel(); // Adding agents vel to avg vel
        }

        for (int i = 0; (float) i < n; i++) {
            pair<float, float> temp = ((pCM - agents[i].getPos()) / (n - 1)) -
                                      agents[i].getPos(); // deleting the current pos data from the combination of neighbor data
            temp.first = pow(temp.first, 2.0f);
            temp.second = pow(temp.second, 2.0f);
            float tempSqrt = sqrt(temp.first + temp.second);

            if (tempSqrt <= rC) {
                fC = (((pCM - agents[i].getPos()) / (n - 1)) - agents[i].getPos()) / rC;
                agents[i].setForceCenter(fC);
            } else {
                fC = make_pair(0.0f, 0.0f);
                agents[i].setForceCenter(fC);
            }

            fS = make_pair(0.0f, 0.0f); // resets fS
            for (int j = 0; (float) j < n; j++) {
                // getting the force of separation for each agent
                temp = agents[i].getPos() - agents[j].getPos();
                temp.first = pow(temp.first, 2.0f);
                temp.second = pow(temp.second, 2.0f);
                tempSqrt = sqrt(temp.first + temp.second);

                if (0 < tempSqrt && tempSqrt <= rS) {
                    fS = fS + ((agents[i].getPos() - agents[j].getPos()) / tempSqrt) / tempSqrt;
                }
            }

            // Checks if force separate is greater than the max value it can be
            tempSqrt = sqrt(pow(fS.first, 2.0f) + pow(fS.second, 2.0f));

            if (tempSqrt <= fSMax) {
                agents[i].setForceSeparate(fS);
            } else {
                fS = (fS / tempSqrt) * fSMax;
                agents[i].setForceSeparate(fS);
            }

            for(int j = 0; (float)j < n; j++)
            {
                temp = agents[i].getPos() - agents[j].getPos();
                temp.first = pow(temp.first, 2.0f);
                temp.second = pow(temp.second, 2.0f);
                tempSqrt = sqrt(temp.first + temp.second);

                if (tempSqrt > rA && rA != 0) {
                    vAvg = vAvg - agents[j].getVel();
                }
            }
            temp = (vAvg / n) - agents[i].getVel();
            temp.first = pow(temp.first, 2.0f);
            temp.second = pow(temp.second, 2.0f);
            tempSqrt = sqrt(temp.first + temp.second);
            if (rA != 0) {
                fA = ((vAvg / n) / tempSqrt) * tempSqrt;
                agents[i].setForceAlign(fA);
            }
            else{
                fA = make_pair(0.0f,0.0f);
                agents[i].setForceAlign(fA);
            }
        }

        for (int i = 0; (float) i < n; i++) {
            pair<float, float> newVel = agents[i].getNewVel(t, kC, kS, kA);
            pair<float, float> newPos = agents[i].getNewPos(t, newVel);

            cout << fixed << setprecision(3) << newPos.first << " " << newPos.second << " " << newVel.first << " "
                 << newVel.second << endl;
        }
        cin >> t;
    }

    delete[] agents;
}

