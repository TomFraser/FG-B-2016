//NOTE ---------------------> For a easier time I would recomend using the python script to generate an array of motor values.


//This is FG&Bs motor array. Its a 2D array where each vertical element is a different direction and each horizontal element is a PWM value (We have 4 motors)
//Yours should look similar but with less only 3 in each horizontal element if you are using 3 motors, we also add a {0,0,0,0} for when we dont see the ball so we stay still

/*int moveArray[21][4] = {
    {0,0,0,0},
    {-255, -208, 208, 255},
    {-174, -232, 118, 255},
    {-104, -253, 40, 255},
    {-27, -255, -40, 236},
    {60, -255, -130, 213},
    {180, -255, -255, 180},
    {213, -130, -255, 60},
    {236, -40, -255, -27},
    {255, 40, -253, -104},
    {255, 118, -232, -174},
    {255, 208, -208, -255},
    {174, 232, -118, -255},
    {104, 253, -40, -255},
    {27, 255, 40, -236},
    {-60, 255, 130, -213},
    {-180, 255, 255, -180},
    {-213, 130, 255, -60},
    {-236, 40, 255, 27},
    {-255, -40, 253, 104},
    {-255, -118, 232, 174}
};
*/


//This is a bit of sample code on how to calculate motor values on the fly.
//This code wont compile, it should be taken as an example and not used.

//It should be noted that most programming languages, arduino and C++ included use radians instead of degrees when using sine, cos and tan functions.
//Incase you havent learnt radians in maths yet, I have provided some example fucntions on how to convert between them.

int motorArray[3] = {}; //This is the array we will put our completed values in. each element in the array is the PWM or power for a certain motor.
int angleArray[3] = {60, 180, 300}; //This is the angles of the motors.

int angle = 0; //The angle is the direction you want to move, the easiest way to do this is to multply your tsop number by the degrees between the tsops

void setup(){
    //Who needs a setup anyway?
}

void loop(){
    motorArray[0] = cos(((degToRad(angleArray[0] + 90))) - (degToRad(angle))); //Here we are using our degToRad function to convert our motor angles to radians that we can use to calculate the PWM power of the motor
    motorArray[1] = cos(((degToRad(angleArray[1] + 90))) - (degToRad(angle)));
    motorArray[2] = cos(((degToRad(angleArray[2] + 90))) - (degToRad(angle)));
    //Each of the elements in motorArray is the values for our PWM motorArray

    //The following is an example and wont work
    MotorA.set(motorArray[0]); //This would write the PWM in the element to the motor allowing it to move in a direction
    MotorB.set(motorArray[1]);
    MotorC.set(motorArray[2]);
}

float radToDeg(int radian){
    return radian*(180/PI); //Note that PI should be a pre determined value for arduino, if not put this at the top of your program: #define PI 3.141592653589793
}

float degToRad(int degree){
    return degree*(PI/180);
}
