#include "CommandGroup.h"

void CommandGroup::InitAutoCommands(){

    RobotDrive.DriveInit();
    RobotArm.ArmInit();
    RobotClaw.ClawInit();

    safeLock = 1;
    estadoCompressor = 1;

}

void CommandGroup::InitCommands(){

    RobotDrive.DriveInit();
    RobotArm.ArmInit();
    RobotClaw.ClawInit();

    safeLock = 1;
    estadoCompressor = 1;

}

void CommandGroup::PeriodicCommands(){                                   

    RobotDrive.Drive(pilotStick.GetY(), pilotStick.GetZ(), safeLock);
    RobotArm.ArmFeed(safeLock, operatorStick.GetY());
    
} 

void CommandGroup::PilotCommands(){

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonBACK)){
        
        safeLock = !safeLock;

        if(safeLock == 1){

            RobotClaw.EnableCompressor();

        }
        
    }

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonRB)){

        RobotDrive.DriveSpeedChange(1, 0.1);
    }

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonLB)){

        RobotDrive.DriveSpeedChange(-1, 0.1);

    }

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonRT)){

        RobotDrive.DriveSpeedMax();
    }

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonLT)){

        RobotDrive.DriveSpeedStandard();

    }

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonY)){

        RobotDrive.DriveDirection();

    }

    if(pilotStick.GetRawButtonPressed(JoystickConstants::buttonB)){

        RobotDrive.DriveSlowTurn();

    }

}

void CommandGroup::OperatorCommands(){
    
    if(operatorStick.GetRawButtonPressed(JoystickConstants::buttonBACK)){
        
        safeLock = !safeLock;

        if(safeLock == 1){

            RobotClaw.EnableCompressor();

        }
        
    }

    if(operatorStick.GetRawButtonPressed(JoystickConstants::buttonB) && safeLock == 1){

        if(estadoCompressor == 0){

            RobotClaw.EnableCompressor();
            estadoCompressor = 1;

       } else {

            RobotClaw.DisableCompressor();
            estadoCompressor = 0;

       }

    }else if(safeLock == 0 && estadoCompressor == 1){

        RobotClaw.DisableCompressor();
        estadoCompressor = 0;

    }

    if(operatorStick.GetRawButtonPressed(JoystickConstants::buttonX) && safeLock == 1){

        RobotClaw.AtivarSolenoide();

    }

    if(operatorStick.GetRawButton(JoystickConstants::buttonRT)){

        RobotClaw.ClawSlideForward(safeLock, ClawConstants::forwardSlidePercent);

    }else if(operatorStick.GetRawButton(JoystickConstants::buttonLT)){

        RobotClaw.ClawSlideReturn(safeLock, ClawConstants::returnSlidePercent);

    }else {

        RobotClaw.ClawStop();

    }

    if(operatorStick.GetRawButtonPressed(JoystickConstants::buttonY) && safeLock == 1){

        RobotArm.ArmMaxSpeed();

    }

    if(operatorStick.GetRawButtonPressed(JoystickConstants::buttonA) && safeLock == 1){

        RobotArm.ArmStandardSpeed();

    }

}

void CommandGroup::Log(){

    RobotDrive.DriveLog();
    RobotArm.ArmLog();
    RobotClaw.ClawLog();

    frc::SmartDashboard::PutNumber("Piloto JoyY", pilotStick.GetY());
    frc::SmartDashboard::PutNumber("Piloto JoyZ", pilotStick.GetZ());
    frc::SmartDashboard::PutNumber("Operador JoyY", operatorStick.GetY());

    frc::SmartDashboard::PutBoolean("SafeLock", safeLock);

}

void CommandGroup::Teste(){

    PeriodicCommands();

}