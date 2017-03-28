//
// Created by Chris Jerrett on 3/24/17.
//

#ifndef SLAM_STEPPERMOTOR_H
#define SLAM_STEPPERMOTOR_H

class StepperMotor {

    private:
        int steps;

        const int getStep();

    public:
        const int getAngle();
        const void stepp();

};


#endif //SLAM_STEPPERMOTOR_H
