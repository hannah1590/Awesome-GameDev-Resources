#include <iostream>
#include <cmath>

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
        return forceCenter * kC + forceSeparate * kS + forceAlign * kA;
    }

    pair<float,float> getNewVel(float t, float kC, float kS, float kA)
    {
        return vel + getForce(kC, kS, kA) * t;
    }

    pair<float,float> getNewPos(float t, pair<float,float> newVel)
    {
        return pos + newVel * t;
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

    pair<float, float> pCM(0.0f,0.0f); // pos of center of mass
    pair<float, float> fC;                       // force moving agent to center of mass in cohesion radius
    pair<float, float> fS(0.0f,0.0f);  // force moving agent from other agents in separation radius
    pair<float, float> vAvg(0.0f,0.0f);// avg vel of the agents
    pair<float, float> fA(0.0f,0.0f);  // force aligning agents with the avg vel of the group

    cin >> rC >> rS >> fSMax >> rA >> kC >> kS >> kA >> n;

    auto* agents = new agent[n];

    for(int i = 0; i < n; i++)
    {
        cin >> x >> y >> vx >> vy;
        agents[i] = agent(x,y,vx,vy);

        // adding agents pos to pos of center mass
        pCM = pCM + agents[i].getPos();

        // Adding agents vel to avg vel
        vAvg = vAvg + agents[i].getVel();
    }



    // dividing pos of center mass by num of agents to get final value
    pCM = pCM / n;

    // dividing sum of velocities by num of agents to get avg
    vAvg = vAvg / n;

    for(int i = 0; i < n; i++)
    {
        // getting the force moving the agent to center of mass
        pair<float,float> temp = pCM - agents[i].getPos();
        temp.first = pow(temp.first,2);
        temp.second = pow(temp.second,2);
        float tempSqrt = sqrt(temp.first + temp.second);

        if(tempSqrt <= rC)
        {
            fC = pCM - agents[i].getPos() / rC;
            agents[i].setForceCenter(fC);


        }
        else
        {
            fC = make_pair(0.0f,0.0f);
            agents[i].setForceCenter(fC);
        }

        for(int j = 0; j < n; j++)
        {
            // getting the force of separation for each agent
            temp = agents[i].getPos() - agents[j].getPos();
            temp.first = pow(temp.first,2);
            temp.second = pow(temp.second,2);
            tempSqrt = sqrt(temp.first + temp.second);



            if(j == i){ break; }
            else if(0 < tempSqrt && tempSqrt <= rS)
            {
                fS = fS + (agents[i].getPos() - agents[j].getPos()) / tempSqrt;
            }
        }

        // Checks if force separate is greater than the max value it can be
        tempSqrt = sqrt(pow(fS.first,2) + pow(fS.second,2));

        if(tempSqrt <= fSMax)
        {
            agents[i].setForceSeparate(fS);
        }
        else
        {
            fS = (fS/tempSqrt) * fSMax;
            agents[i].setForceSeparate(fS);
        }

        // getting the force aligning the agents together
        temp = vAvg - agents[i].getVel();
        temp.first = pow(temp.first,2);
        temp.second = pow(temp.second,2);
        tempSqrt = sqrt(temp.first + temp.second);

        if(tempSqrt <= rA && tempSqrt > 0.0f)
        {
            fA = vAvg - agents[i].getVel() / rA;
            agents[i].setForceAlign(fA);
        }
        else
        {
            fA = make_pair(0.0f,0.0f);
            agents[i].setForceAlign(fA);
        }
    }

    cin >> t;

    for(int i = 0; i < n; i++)
    {
        pair<float,float> newVel = agents[i].getNewVel(t, kC, kS, kA);
        pair<float,float> newPos = agents[i].getNewPos(t, newVel);

        cout << newVel.first << " " << newVel.second << " " << newPos.first << " " << newPos.second << endl;
    }

    delete[] agents;
}

