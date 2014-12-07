/*
* Copyright (C) 2014 iCub Facility - Istituto Italiano di Tecnologia
* Author: Ugo Pattacini
* email:  ugo.pattacini@iit.it
* Permission is granted to copy, distribute, and/or modify this program
* under the terms of the GNU General Public License, version 2 or any
* later version published by the Free Software Foundation.
*
* A copy of the license can be found at
* http://www.robotcub.org/icub/license/gpl.txt
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details
*/

#include <string>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>

#include "Controller.h"                   // Model's header file
#include "rtwtypes.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;

static RT_MODEL_Controller_T Controller_M_;
static RT_MODEL_Controller_T *const Controller_M = &Controller_M_;// Real-time model 
static P_Controller_T Controller_P = {
  0.0,                                 // Variable: Plant_IC
                                       //  Referenced by:
                                       //    '<S1>/Unit Delay'
                                       //    '<S1>/Unit Delay2'
                                       //    '<S6>/Discrete Integrator'

  100.0,                               // Variable: Plant_Max
                                       //  Referenced by: '<S6>/Discrete Integrator'

  -100.0,                              // Variable: Plant_Min
                                       //  Referenced by: '<S6>/Discrete Integrator'

  1.0,                                 // Mask Parameter: EdgeDetector_model
                                       //  Referenced by: '<S8>/Constant1'

  0,                                   // Mask Parameter: EdgeDetector_ic
                                       //  Referenced by: '<S8>/Unit Delay'

  0.0,                                 // Expression: 0
                                       //  Referenced by: '<S1>/Constant'


  //  Expression: [1 1]
  //  Referenced by: '<S8>/either edge'

  { 1.0, 1.0 },

  //  Expression: [0 1]
  //  Referenced by: '<S8>/neg. edge'

  { 0.0, 1.0 },

  //  Expression: [1 0]
  //  Referenced by: '<S8>/pos. edge'

  { 1.0, 0.0 },
  0,                                   // Computed Parameter: OUT_Y0
                                       //  Referenced by: '<S9>/OUT'

  0,                                   // Computed Parameter: OUT_Y0_d
                                       //  Referenced by: '<S10>/OUT'


  // Start of '<S1>/Reference Plant'
  {
    0.005                              // Computed Parameter: DiscreteIntegrator_gainval
                                       //  Referenced by: '<S6>/Discrete Integrator'

  }
  // End of '<S1>/Reference Plant'
  ,

  // Start of '<S1>/Filter1'
  {
    //  Expression: [4.5e-4 9e-4 4.5e-4]
    //  Referenced by: '<S5>/Discrete Filter'

    { 0.00045, 0.0009, 0.00045 },

    //  Expression: [1 -1.921 0.9231]
    //  Referenced by: '<S5>/Discrete Filter'

    { 1.0, -1.921, 0.9231 },
    0.0                                // Expression: 0
                                       //  Referenced by: '<S5>/Discrete Filter'

  }
  // End of '<S1>/Filter1'
  ,

  // Start of '<S1>/Filter'
  {
    //  Expression: [4.5e-4 9e-4 4.5e-4]
    //  Referenced by: '<S4>/Discrete Filter'

    { 0.00045, 0.0009, 0.00045 },

    //  Expression: [1 -1.921 0.9231]
    //  Referenced by: '<S4>/Discrete Filter'

    { 1.0, -1.921, 0.9231 },
    0.0                                // Expression: 0
                                       //  Referenced by: '<S4>/Discrete Filter'

  }
  // End of '<S1>/Filter'
  ,

  // Start of '<S1>/Compensator'
  {
    1.0,                               // Mask Parameter: DiscretePIDController_I
                                       //  Referenced by: '<S7>/Integral Gain'

    10.0,                              // Mask Parameter: DiscretePIDController_P
                                       //  Referenced by: '<S7>/Proportional Gain'

    0.005,                             // Computed Parameter: Integrator_gainval
                                       //  Referenced by: '<S7>/Integrator'

    0.0                                // Expression: InitialConditionForIntegrator
                                       //  Referenced by: '<S7>/Integrator'

  }
  // End of '<S1>/Compensator'
};                                     // Modifiable parameters

static B_Controller_T Controller_B;    // Observable signals
static DW_Controller_T Controller_DW;  // Observable states

// '<Root>/reference'
static real_T Controller_U_reference;

// '<Root>/enable_compensation'
static boolean_T Controller_U_enable_compensation;

// '<Root>/plant_output'
static real_T Controller_U_plant_output;

// '<Root>/controller_output'
static real_T Controller_Y_controller_output;

// '<Root>/controller_reference'
static real_T Controller_Y_controller_reference;

// '<Root>/plant_reference'
static real_T Controller_Y_plant_reference;


/******************************************************/
class CtrlModule: public RFModule
{
    PolyDriver drv;
    IControlMode2 *imod;
    IInteractionMode *iint;
    IEncoders *ienc;    
    IVelocityControl *ivel;
    int joint;
    bool compliant;
    
    BufferedPort<Vector> dataIn;
    BufferedPort<Vector> dataOut;
    RpcServer            rpc;

public:
    /******************************************************/
    bool configure(ResourceFinder &rf)
    {
        Time::turboBoost();
        string name=rf.check("name",Value("yarpMinJerk")).asString().c_str();
        string robot=rf.check("robot",Value("icubSim")).asString().c_str();
        string part=rf.check("part",Value("left_arm")).asString().c_str();
        joint=rf.check("joint",Value(3)).asInt();
        compliant=rf.check("compliant");

        Property option;
        option.put("device","remote_controlboard");
        option.put("remote",("/"+robot+"/"+part).c_str());
        option.put("local",("/"+name+"/"+part).c_str());
        if (!drv.open(option))
            return false;

        drv.view(imod);
        drv.view(iint);
        drv.view(ienc);
        drv.view(ivel);

        imod->setControlMode(joint,VOCAB_CM_VELOCITY);
        if (compliant)
            iint->setInteractionMode(joint,VOCAB_IM_COMPLIANT);

        IControlLimits *ilim; drv.view(ilim);
        double min_joint,max_joint;
        ilim->getLimits(joint,&min_joint,&max_joint);

        double enc;
        while (!ienc->getEncoder(joint,&enc))
            Time::delay(0.1);
        
        Controller_P.Plant_IC=enc;
        Controller_P.Plant_Max=max_joint;
        Controller_P.Plant_Min=min_joint;

        yInfo("enc=%g in [%g, %g] deg",enc,min_joint,max_joint);

        // Pack model data into RTM
        Controller_M->ModelData.defaultParam = &Controller_P;
        Controller_M->ModelData.blockIO = &Controller_B;
        Controller_M->ModelData.dwork = &Controller_DW;

        // Initialize model
        Controller_initialize(Controller_M, &Controller_U_reference,
                              &Controller_U_enable_compensation,
                              &Controller_U_plant_output,
                              &Controller_Y_controller_output,
                              &Controller_Y_controller_reference,
                              &Controller_Y_plant_reference);

        Controller_U_reference=enc;
        Controller_U_plant_output=enc;
        Controller_U_enable_compensation=false;
        
        dataIn.open(("/"+name+"/data:i").c_str());
        dataOut.open(("/"+name+"/data:o").c_str());
        rpc.open(("/"+name+"/rpc").c_str());
        attach(rpc);
        
        return true;
    }

    /******************************************************/
    bool respond(const Bottle &cmd, Bottle &reply)
    {
        int ack=Vocab::encode("ack");
        int on=Vocab::encode("on");
        int off=Vocab::encode("off");
        int get=Vocab::encode("get");

        int sw=cmd.get(0).asVocab();
        if ((sw==on) || (sw==off))
        {
            Controller_U_enable_compensation=(sw==on);
            reply.addVocab(ack);
            return true;
        }
        else if (sw==get)
        {
            reply.addVocab(ack);
            reply.addVocab(Controller_U_enable_compensation?on:off);
            return true;
        }
        else
            return RFModule::respond(cmd,reply);
    }

    /******************************************************/
    double getPeriod()
    {
        return 0.01;
    }
    
    /******************************************************/
    bool updateModule()
    {
        if (Vector *in=dataIn.read(false))
            Controller_U_reference=(*in)[0];
        ienc->getEncoder(joint,&Controller_U_plant_output);

        // Step the model
        Controller_step(Controller_M, Controller_U_reference,
                        Controller_U_enable_compensation, Controller_U_plant_output,
                        &Controller_Y_controller_output,
                        &Controller_Y_controller_reference,
                        &Controller_Y_plant_reference);
        
        ivel->velocityMove(joint,Controller_Y_controller_output);

        Vector &out=dataOut.prepare();
        out.resize(5);
        out[0]=Controller_U_reference;
        out[1]=Controller_Y_plant_reference;
        out[2]=Controller_U_plant_output;
        out[3]=Controller_Y_controller_reference;
        out[4]=Controller_Y_controller_output;
        dataOut.write();

        return true;
    }

    /******************************************************/
    bool close()
    {
        // Terminate model
        Controller_terminate(Controller_M);

        imod->setControlMode(joint,VOCAB_CM_POSITION);
        if (compliant)
            iint->setInteractionMode(joint,VOCAB_IM_STIFF);
        
        rpc.close();
        dataOut.close();
        dataIn.close();        
        drv.close();

        return true;
    }
};


/******************************************************/
int main(int argc, char *argv[])
{   
    Network yarp;
    if (!yarp.checkNetwork())
    {
        yError("Yarp network seems unavailable!");
        return -1;
    }
    
    CtrlModule mod;
    ResourceFinder rf;
    return mod.runModule(rf);
}

