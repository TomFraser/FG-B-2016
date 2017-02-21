from math import cos, fabs, radians

#Running this script will provide an array which you can drop into your program where each element in the array contains a motor power value

def get_motor_values(angle, speed = 255, motors = (60, 180, 300)): #Counting up if robot spins clockwise, counting down if robot spins counter-clockwise

        angle  = radians(angle)
        values = []

        for motor_angle in motors:
                motor_angle = radians(motor_angle + 90)
                values.append(cos(motor_angle - angle))

        speed /= fabs(max(values, key = fabs))
        return [int(round(i * speed)) for i in values]

def __main__():
        """Calculate the motor values for every angle and output them.
        For Windows users, keeps the dialog open with an infinite loop

        __main__() -> void

        Prints out the results in the format of a C array
        """

        print("int motorDirValues[360][3] {")

        for i in range(0, 360, 1):
                print(str(get_motor_values(i))[1:-1])


if __name__ == "__main__":
        __main__()
