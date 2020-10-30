<!-- markdownlint-disable MD024 -->

# Code Structure

## Chassis

### Classes

- Virtual class and two inherited classes.
- **Virtual:** `Chassis`
  - **Inherited 1:** `SkidSteerChassis`
  - **Inherited 2:** `XDriveChassis`

### Builder

- Classes built using a builder, `ChassisBuilder`
  - Methods:
    - `.with_motors(MotorGroup l, MotorGroup r)`, `.with_motors(Motor lf, Motor lb, Motor rf, Motor rb)`  
      - Sets motor numbers to be used.  
    - `.with_gearing(pros::e_motor_gearset_e cart)`  
      - Sets gearing to be used.  
    - `.with_brake(pros::e_motor_brake_mode_e brake_mode)`  
      - Sets brake mode to be used.  
    - `.with_enc_unit(pros::e_motor_encoder_units_e enc_unit`  
      - Sets encoder units to be used.  
    - `.build()`
      - Return the object.

### Base Virtual Class Outline

```cpp
class Chassis
{
public:
    // idk how its gonna work i'll see
    Chassis();
    ~Chassis();

    // Movement
    virtual void move(int vol) = 0;
    virtual void move(int vol_l, int vol_r) = 0;
    virtual void move_vel(int vel) = 0;
    virtual void move_vel(int vel_l, int vel_r) = 0;

    // Config (for after the build)
    virtual Chassis& set_brake_mode(pros::e_motor_brake_mode_e brake_mode) = 0;
    virtual Chassis& set_enc_units(pros::e_motor_encoder_units_e enc_unit) = 0;

    // might need other functions i'll see

protected:
    // motor numbers here i guess
    pros::e_motor_gearset_e cart;
    pros::e_motor_brake_mode_e brake_mode;
    pros::e_motor_encoder_units_e enc_unit;
}
```

### Misc. Notes

- Need implementations for X-Drive.
  - This looks like a [`good resource for x-drive stuff`](https://www.vexforum.com/t/x-drive-programming-help/67262/2)
- Need to learn builder design.
  - This looks like a [`good resource for builder design`](https://gist.github.com/pazdera/1121152)

## Conveyor

- Simple class.
- Won't make it too configurable since there's not gonna be much that changes.
- 2 motors w/ same configurations as last time.
- Same methods as well.
- Only difference is invoking C functions instead of creating PROS C++ objects.

## Intake

- Same as Conveyor.

## Sensors

### Classes

- Will have one main Sensor class constructed with a builder to prevent a long ass constructor.
- Also a builder is probably nicer.
- Better for code explanation later???

### Builder

- Sensors class built with SensorsBuilder
  - Methods:
    - `.with_vision(std::uint8_t vision_port)`
      - Defines a Vision port (im only anticipating the use of one)
    - `.with_optical(std::uint8_t optical_port)`
      - Defines an Optical Sensor port (im only anticipating the use of one)
    - `.with_ultrasonic(std::uint8_t ultrasonic_port)`
      - Defines an Ultrasonic port (im only anticipating the use of one)
    - `.with_tracking(TrackingWheels wheels)`
      - Defines a structure for tracking wheels.
      - 2 - 3 tracking wheels is what I'm guessing.

### TrackingWheels Structure Outline

```cpp
struct TrackingWheels
{
    // use char instead of uint8_t b/c it correlates better w/ what's on the brain.
    TrackingWheels(char L1, char R1, char M1)
    {
        auto char_to_uint = [](char var){
            if (var == 'A')
                return 1;
            else if (var == 'C')
                return 3;
            else if (var == 'E')
                return 5;
            else if (var == 'G')
                return 7;
            else
                return 0;
        };

        pt_left_top = char_to_uint(L1)
        pt_left_bot = ++pt_left_top;
        pt_right_top = char_to_uint(R1)
        pt_right_bot = ++pt_right_top;
        pt_middle_top = char_to_uint(M1)
        pt_middle_bot = ++pt_middle_top;
    }

    std::uint8_t    pt_left_top,
                    pt_left_bot,
                    pt_right_top,
                    pt_right_bot,
                    pt_middle_top,
                    pt_middle_bot;
}
```

### Misc. Notes

- Not much except for builder design; same as Chassis essentially.

## Odometry

- Pilons doc about odom.
- Needs to run in a separate thread.
- Need a way to consistently start robot in same spot more or less.
  - Could use an absolute point on field, move to it, measure, adjust for error.
  - Could also just move around and spin around and use measurements to adjust that way.
  - Maybe bump into the walls (better with X-Drive) and measure error like that using anticipated measurements.

## PID

- Need PID loop (simple)
  - Skip out on the integral.
- Need slew this time to control acceleration.

## Main Files

- Not too different from the old code.

## Conclude

- The main thing that will be changed is the organization of the classes to allow for more versatility later (in anticipation of a rebuild).
- General improvements that are probably better.
- Learn builder design, something I can have under my tool belt.
